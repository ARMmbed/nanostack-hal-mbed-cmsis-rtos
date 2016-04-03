/*
 * Copyright (c) 2016 ARM Limited, All Rights Reserved
 */

#include "mbed.h"

#include "platform/arm_hal_timer.h"
#include "platform/arm_hal_interrupt.h"

static Timer timer;
static Timeout timeout;
static uint32_t due;
static void (*callback)(void);

// Called once at boot
void platform_timer_enable(void)
{
    timer.start();
}

// Actually cancels a timer, not the opposite of enable
void platform_timer_disable(void)
{
    timeout.detach();
}

// Not called while running, fortunately
void platform_timer_set_cb(void (*new_fp)(void))
{
    callback = new_fp;
}

static void timer_callback(void)
{
    due = 0;
    callback();
}

// This is called from inside platform_enter_critical - IRQs can't happen
void platform_timer_start(uint16_t slots)
{
    timer.reset();
    due = slots * UINT32_C(50);
    timeout.attach_us(timer_callback, due);
}

// This is called from inside platform_enter_critical - IRQs can't happen
uint16_t platform_timer_get_remaining_slots(void)
{
    uint32_t elapsed = timer.read_us();
    if (elapsed < due) {
        return (uint16_t) ((due - elapsed) / 50);
    } else {
        return 0;
    }
}

