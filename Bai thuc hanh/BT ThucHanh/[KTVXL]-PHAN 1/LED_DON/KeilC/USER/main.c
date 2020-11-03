//dieu khien 8 led
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
  Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
	GPIO_Config();
	while(1)
	{
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            Delay(1000);   
						GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            Delay(1000);			
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
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

