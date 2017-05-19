#include "stm32f10x.h"
#include "ucos_ii.h"
#include "ucos_clock.h"

static void RCC_Configuration(void);
static void Initial_Configuration(void);
static void GPIO_Configuration(void);
static void Led_Blink_Task(void *p_arg);


/*任务优先级*/
#define LED_TASK_PRIO  4

/*任务堆栈大小*/
#define LED_TASK_STK_SIZE  80


static OS_STK Led_task_stk[LED_TASK_STK_SIZE];



int main(void)
{
    Initial_Configuration();
    OSInit();//os初始化
    
    /*建立任务*/
    OSTaskCreate(Led_Blink_Task,(void *)0,&Led_task_stk[LED_TASK_STK_SIZE-1],LED_TASK_PRIO);

    /*启动OS*/
    OSStart();
    
    return 0;
}

static void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOA的外设时钟
}


static void Initial_Configuration(void)
{
       RCC_Configuration();
       SysTick_Congfiguration();
       GPIO_Configuration();       
}



void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}



void Led_Blink_Task(void *p_arg)
{
    (void)p_arg;
    while(1)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
        OSTimeDlyHMSM(0,0,0,500);
        GPIO_SetBits(GPIOB,GPIO_Pin_8);
        OSTimeDlyHMSM(0,0,0,500);
    }
}

