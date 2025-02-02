#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define BUTTON              GPIO_Pin_0
#define PORT_BUTTON         GPIOB
#define PORT_BUTTON_CLOCK   RCC_APB2Periph_GPIOB

#define LED              GPIO_Pin_13
#define PORT_LED         GPIOC
#define PORT_LED_CLOCK   RCC_APB2Periph_GPIOC

#define LED_ON           GPIO_ResetBits(PORT_LED, LED);
#define LED_OFF          GPIO_SetBits(PORT_LED, LED);

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
    Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
	GPIO_Config();
    
    GPIO_SetBits(PORT_LED, LED);
    while(1){
        
        if(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON) == 0)
        {
            while(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON) == 0);
            GPIO_WriteBit(PORT_LED, LED, (BitAction)(1^GPIO_ReadOutputDataBit(PORT_LED, LED)));
        }
        
    }
}
/*Delay tuong doi*/
void Delay(uint32_t t)
{
    unsigned int i,j;
    
    for(i=0;i<t;i++){
        for(j=0;j< 0x2AFF; j++);
    }

}

void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*enble clock for GPIOC*/
	RCC_APB2PeriphClockCmd(PORT_BUTTON_CLOCK|PORT_LED_CLOCK, ENABLE);
    
	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin  = BUTTON;
	GPIO_Init(PORT_BUTTON,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = LED;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(PORT_LED, &GPIO_InitStructure);
}

void Clock_Config(void)
{
    /* RCC system reset */
    RCC_DeInit();
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div2);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    /*enable HSI source clock*/
    RCC_HSICmd(ENABLE);	
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x00) {}    
}



