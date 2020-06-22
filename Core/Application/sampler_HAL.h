/*
 * sample_HAL.h
 *
 *  Created on: Jun 12, 2020
 *      Author: andriitkach
 */

#ifndef _APPLICATION_SAMPLE_HAL_H_
#define _APPLICATION_SAMPLE_HAL_H_

#include "sampler_config.h"

#ifdef USE_CUBE_IDE_HAL

#include "stm32f4xx_hal.h"

#define SAMPLER_PIN0_PORT 	GPIOB
#define SAMPLER_PIN1_PORT 	GPIOB
#define SAMPLER_PIN2_PORT 	GPIOB
#define SAMPLER_PIN3_PORT 	GPIOB
#define SAMPLER_PIN4_PORT 	GPIOB
#define SAMPLER_PIN5_PORT 	GPIOB
#define SAMPLER_PIN6_PORT 	GPIOB
#define SAMPLER_PIN7_PORT 	GPIOB

#define SAMPLER_PIN0_NUM 	GPIO_PIN_0
#define SAMPLER_PIN1_NUM 	GPIO_PIN_1
#define SAMPLER_PIN2_NUM 	GPIO_PIN_2
#define SAMPLER_PIN3_NUM 	GPIO_PIN_3
#define SAMPLER_PIN4_NUM 	GPIO_PIN_4
#define SAMPLER_PIN5_NUM 	GPIO_PIN_5
#define SAMPLER_PIN6_NUM 	GPIO_PIN_7
#define SAMPLER_PIN7_NUM 	GPIO_PIN_8

#define PAYLOAD_LENGTH  	128

typedef struct {
	GPIO_TypeDef *  GPIO_perif;
	uint16_t 		GPIO_pin_num;
} Pin_t;

uint8_t sampler_get_pin_val(void);
void 	sampler_init_pinout(void);
void 	sampler_send_packet(uint8_t *, uint16_t);
void 	sampler_wait_trans_cplt(void);

#endif /* USE_CUBE_IDE_HAL */


#endif /* _APPLICATION_SAMPLE_HAL_H_ */
