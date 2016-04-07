/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
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
#include "ns_types.h"
#include "arm_hal_random.h"

#include "driverRFPhy.h"
#include "mbedtls/entropy_poll.h"

void arm_random_module_init(void)
{
}

uint32_t arm_random_seed_get(void)
{
    uint32_t result = 0;
    uint8_t mac[8];
#ifdef MBEDTLS_ENTROPY_HARDWARE_ALT
    /* Grab a seed from a function we provide for mbedtls */
    size_t len;
    mbedtls_hardware_poll(NULL, (uint8_t *) &result, sizeof result, &len);
#endif
    rf_read_mac_address(mac);
    for (int i = 0; i <= 7; i++) {
        result ^= (uint32_t) mac[i] << ((i % 4) * 8);
    }
    result ^= rf_read_random();
    return result;
}
