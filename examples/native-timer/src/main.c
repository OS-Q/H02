/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
// #include <stdint.h>
#include "main.h"

volatile uint32_t time_ms_cnt=0;

void led_init(void)
{
    GPIOB->DDR|=0x20;
    GPIOB->CR1|=0x20;
    GPIOB->CR2|=0x00;
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main()
{
    // pin_init();
    led_init();
    clk_init();
    tim4_init(125);
    // tim1_init(16,1000);
    while (1)
    {
        if(time_ms_cnt%1000==0)
        {
            GPIOB->ODR ^= 0x20;
            delay_ms(10);
        }
    }
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
#ifdef __TIMER1_H
void tim1_isr(void) __interrupt(11)
{
    time_ms_cnt++;
    TIM1->SR1=0x00;
}
#endif /*__TIMER1_H*/
#ifdef __TIMER4_H
void tim4_isr(void) __interrupt(23)
{
    time_ms_cnt++;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    // TIM4->SR1=0x00;
}
#endif /*__TIMER4_H*/

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
