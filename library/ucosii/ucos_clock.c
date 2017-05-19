
#include "ucos_ii.h"
#include "stm32f10x.h"



/* ¶¨Òå10MS*/
void SysTick_Congfiguration(void)
{
	if(SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC))/*SystemCoreClock/1000000 = 1us*/
    {
		while(1);
    }
}


void SysTick_Enable(FunctionalState NewState)
{
	if(ENABLE == NewState)
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	else
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

