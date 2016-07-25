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

#include <stdio.h>
#include "contiki.h"
#include "dev/i2c.h"
#include "adc128d818.h"

/*---------------------------------------------------------------------------*/
#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
/*---------------------------------------------------------------------------*/
/*
   uint16_t
   adc128_read_reg(uint8_t reg, uint8_t *buf, uint8_t num)
   {

   //if((buf == NULL) || (num < 0)) {
   //  return ADC128_ERROR;
   //}
   uint8_t buf1[2];
   uint16_t value;

   //i2c_master_enable();
   if(i2c_single_send(ADC128_ADDR, reg) == I2C_MASTER_ERR_NONE) {
     printf("ADC128_READ_REG: ADDR: %x, REG: %x\n", ADC128_ADDR, reg);

    if(i2c_burst_receive(ADC128_ADDR, buf1, num) == I2C_MASTER_ERR_NONE) {
      value = ((256 * buf1[0]) + buf1[1]) >> 4;
      return value;
        //printf("ADC value:%d\n",value);
    }
      return ADC128_SUCCESS;
   }
   return ADC128_ERROR;
   }
 */
/*---------------------------------------------------------------------------*/
uint16_t
adc128_read_channel(uint8_t reg)
{

  uint8_t buf[2];
  uint16_t value;

  if(i2c_single_send(ADC128_ADDR, reg) == I2C_MASTER_ERR_NONE) {
    if(i2c_burst_receive(0x37, buf, 2) == I2C_MASTER_ERR_NONE) {
      value = ((256 * buf[0]) + buf[1]) >> 4;
      return value;
    }
  }
}
/*---------------------------------------------------------------------------*/
int
adc128_write_reg(uint8_t reg, uint8_t value)
{
  uint8_t buf[2];

  buf[0] = reg;
  buf[1] = value;

  PRINTF("REG: %x, Value: %x\n", reg, value);

  i2c_master_enable();
  if(i2c_burst_send(ADC128_ADDR, buf, 2) == I2C_MASTER_ERR_NONE) {
    return ADC128_SUCCESS;
  }
  return ADC128_ERROR;
}
/*---------------------------------------------------------------------------*/
int
adc128_init()
{

  i2c_init(I2C_SDA_PORT, I2C_SDA_PIN, I2C_SCL_PORT, I2C_SCL_PIN,
           I2C_SCL_NORMAL_BUS_SPEED);

  if(adc128_write_reg(ADC128_CONV_RATE_REG, CONTINUOUS_MODE) == ADC128_ERROR) {
    PRINTF("ADC128: failed to write register\n");
    return ADC128_ERROR;
  }

  if(adc128_write_reg(ADC128_ADV_CONFIG_REG, EXT_REF | MODE_1) == ADC128_ERROR) {
    PRINTF("ADC128: failed to write register\n");
    return ADC128_ERROR;
  }

  if(adc128_write_reg(ADC128_CHANNEL_DISABLE_REG, CHANNEL_DISABLE_MASK) == ADC128_ERROR) {
    PRINTF("ADC128: failed to write register\n");
    return ADC128_ERROR;
  }

  if(adc128_write_reg(ADC128_CONFIG_REG, ADC128_START) == ADC128_ERROR) {
    PRINTF("ADC128: failed to write register\n");
    return ADC128_ERROR;
  }
}
/**
 * @}
 * @}
 * @}
 */
