/*
 * Copyright (c) 2016 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arm_hal_interrupt.h"
#include "arm_hal_interrupt_private.h"
#include "cmsis_os.h"


static uint8_t sys_irq_disable_counter;

static osMutexDef(critical);
static osMutexId critical_mutex_id;

void platform_critical_init(void)
{
    critical_mutex_id = osMutexCreate(osMutex(critical));
}

void platform_enter_critical(void)
{
    osMutexWait(critical_mutex_id, osWaitForever);
    sys_irq_disable_counter++;
}

void platform_exit_critical(void)
{
    --sys_irq_disable_counter;
    osMutexRelease(critical_mutex_id);
}
