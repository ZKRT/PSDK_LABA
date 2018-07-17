#include "sys.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

static void Wrap_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
  uint32_t prioritygroup = 0x00U;
  
  prioritygroup = NVIC_GetPriorityGrouping();
  
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

static void NVIC_Configuration(void)
{
//    /* Set the Vector Table base location at 0x08000000 */
//    /* 0x8000000 - 0x08004000 is bootloader */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    Wrap_NVIC_SetPriority(SVCall_IRQn, 0, 0);
    Wrap_NVIC_SetPriority(PendSV_IRQn, 15, 0);
    Wrap_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

static void SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    uint32_t         cnts;

    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (uint32_t)rcc_clocks.HCLK_Frequency / 1000;

    SysTick_Config(cnts);
}

void Sys_Init(void)
{
    NVIC_Configuration();
    SysTick_Configuration();
}
