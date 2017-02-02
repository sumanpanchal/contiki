/*
 * Copyright (c) 2017, Indian Institute of Science
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
/*---------------------------------------------------------------------------*/
/*
 * \addtogroup zoul-examples
 * @{
 * \defgroup zoul-ad5242-test Test AD5242
 *
 * The example application shows how to use AD5242 Digital Potentiometer using
 * using Remote I2C interface.
 * Datasheet:
 * http://www.analog.com/media/en/technical-documentation/data-sheets/AD5241_5242.pdf
 *
 * @{
 *
 *
 * \file
 *  Example demonstrating AD5242 I2C Compatible, 256-Position Digital Potentiometers
 *  using Remote i2c interface.
 *
 * \author
 *         Sumankumar Panchal <suman@ece.iisc.ernet.in>
 */
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "cpu.h"
#include "sys/etimer.h"
#include "sys/rtimer.h"
#include "dev/uart.h"
#include "dev/button-sensor.h"
#include "dev/adc-zoul.h"
#include "dev/serial-line.h"
#include "dev/sys-ctrl.h"
#include "dev/i2c.h"

#include <stdio.h>
#include <stdint.h>
/*---------------------------------------------------------------------------*/
#define LOOP_PERIOD        5
#define LOOP_INTERVAL       (CLOCK_SECOND * LOOP_PERIOD)
/* #define LEDS_OFF_HYSTERISIS ((RTIMER_SECOND * LOOP_PERIOD) >> 1) */
/*---------------------------------------------------------------------------*/
#define AD5242_ADDR 0x2C

/*---------------------------------------------------------------------------*/
static struct etimer et;
static int counter1, counter2;
/*---------------------------------------------------------------------------*/
PROCESS(zoul_ad5242_demo_process, "Zoul AD5242 Digipot");
AUTOSTART_PROCESSES(&zoul_ad5242_demo_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(zoul_ad5242_demo_process, ev, data)
{

  PROCESS_BEGIN();

  i2c_init(I2C_SDA_PORT, I2C_SDA_PIN, I2C_SCL_PORT, I2C_SCL_PIN, I2C_SCL_FAST_BUS_SPEED);

  counter1 = 100;
  counter2 = 100;

  printf("AD5242 Digipot test application\n");

  etimer_set(&et, LOOP_INTERVAL);

  uint8_t buf1[2], buf[2];

  while(1) {

    PROCESS_YIELD();

    if(ev == PROCESS_EVENT_TIMER) {

      printf("Set RDAC-1: %d, Set RDAC-2: %d\t", counter1, counter2);

      buf1[0] = 0x00;
      buf1[1] = counter1;

      if(i2c_burst_send(AD5242_ADDR, buf1, 2) == I2C_MASTER_ERR_NONE) {
        if(i2c_burst_receive(AD5242_ADDR, buf, 1) == I2C_MASTER_ERR_NONE) {
          printf("RDAC-1: buf[0]=%d\n", buf[0]);
        }
      } else {
        printf("Error\n");
      }

      buf1[0] = 0x80;
      buf1[1] = counter2;

      if(i2c_burst_send(AD5242_ADDR, buf1, 2) == I2C_MASTER_ERR_NONE) {
        if(i2c_burst_receive(AD5242_ADDR, buf, 1) == I2C_MASTER_ERR_NONE) {
          printf("RDAC-2: buf[0]=%d\n", buf[0]);
        }
      } else {
        printf("Error\n");
      }

      etimer_set(&et, LOOP_INTERVAL);
      if(counter1 < 200 || counter2 < 200) {
        counter1 += 150;
        counter2 += 150;
      } else {
        counter1 = 50;
        counter2 = 50;
      }
    }
  } /* while end */

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */
