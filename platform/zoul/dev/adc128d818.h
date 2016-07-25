/*
 * Copyright (c) 2016, Indian Institute of Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *    TI ADC128D818 driver.
 * \author
 *    Sumankumar Panchal <suman@ece.iisc.ernet.in>
 *    Akshay P M <akshaypm@ece.iisc.ernet.in>
 *
 */

/* #ifndef ADC128D818_H_ */
/* #define ADC128D818_H_ */
#include <stdio.h>
#include "i2c.h"

#define ADC128_ADDR 0x37

#define ADC128_ERROR             (-1)
#define ADC128_SUCCESS           0x00

#define ADC128_IN0  0x20
#define ADC128_IN1  0x21
#define ADC128_IN2  0x22
#define ADC128_IN3  0x23
#define ADC128_IN4  0x24
#define ADC128_IN5  0x25
#define ADC128_IN6  0x26
#define ADC128_IN7  0x27

#define ADC128_CONFIG_REG 0x00
#define ADC128_CONV_RATE_REG  0x07
#define ADC128_ADV_CONFIG_REG   0x0B
#define ADC128_BUSY_STATUS_REG  0x0C
#define ADC128_CHANNEL_DISABLE_REG  0x08
#define ADC128_TEMP_REG 0x27

#define CHANNEL_DISABLE_MASK 0x00

#define EXT_REF 0x00
#define MODE_0  0x00
#define MODE_1  0x02
#define MODE_2  0x04
#define MODE_3  0x06

#define LOW_POWER_MODE 0x00
#define CONTINUOUS_MODE 0x01

#define ADC128_START 0x01

#define ADC128_CHANNEL_BASE_REG 0x20
#define ADC128_LIMIT_REG_BASE 0x2A
/* -------------------------------------------------------------------------- */
/* #endif / * ifndef ADC128D818_H_ * / */
/*---------------------------------------------------------------------------*/

uint16_t adc128_read_channel(uint8_t reg);

uint16_t adc128_read_reg(uint8_t reg, uint8_t *buf, uint8_t num);

int adc128_write_reg(uint8_t reg, uint8_t value);

int adc128_init();
