/*
 * Copyright (c) 2016 ARM Limited, All Rights Reserved
 */

#include "cmsis.h"

#include "arm_hal_interrupt.h"

static uint8_t sys_irq_disable_counter;

void platform_enter_critical(void)
{
    __disable_irq();
    sys_irq_disable_counter++;
}

void platform_exit_critical(void)
{
    if(--sys_irq_disable_counter == 0) {
        __enable_irq();
    }
}

void platform_interrupts_disabled(void)
{
    sys_irq_disable_counter++;
}

void platform_interrupts_enabling(void)
{
    --sys_irq_disable_counter;
}

