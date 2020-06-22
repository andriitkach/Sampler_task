/*
 * sampler_HAL.c
 *
 *  Created on: Jun 12, 2020
 *      Author: andriitkach
 */

#include "sampler_HAL.h"

#ifdef USE_CUBE_IDE_HAL

extern UART_HandleTypeDef huart2;
//extern volatile uint8_t buf_ready;

Pin_t pin0;
Pin_t pin1;
Pin_t pin2;
Pin_t pin3;
Pin_t pin4;
Pin_t pin5;
Pin_t pin6;
Pin_t pin7;


void sampler_init_pinout(void) {

	pin0.GPIO_perif = SAMPLER_PIN0_PORT;
	pin1.GPIO_perif = SAMPLER_PIN1_PORT;
	pin2.GPIO_perif = SAMPLER_PIN2_PORT;
	pin3.GPIO_perif = SAMPLER_PIN3_PORT;
	pin4.GPIO_perif = SAMPLER_PIN4_PORT;
	pin5.GPIO_perif = SAMPLER_PIN5_PORT;
	pin6.GPIO_perif = SAMPLER_PIN6_PORT;
	pin7.GPIO_perif = SAMPLER_PIN7_PORT;

	pin0.GPIO_pin_num = SAMPLER_PIN0_NUM;
	pin1.GPIO_pin_num = SAMPLER_PIN1_NUM;
	pin2.GPIO_pin_num = SAMPLER_PIN2_NUM;
	pin3.GPIO_pin_num = SAMPLER_PIN3_NUM;
	pin4.GPIO_pin_num = SAMPLER_PIN4_NUM;
	pin5.GPIO_pin_num = SAMPLER_PIN5_NUM;
	pin6.GPIO_pin_num = SAMPLER_PIN6_NUM;
	pin7.GPIO_pin_num = SAMPLER_PIN7_NUM;
}

uint8_t sampler_get_pin_val(void) {

	uint8_t pin0_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin0.GPIO_perif, pin0.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin1_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin1.GPIO_perif, pin1.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin2_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin2.GPIO_perif, pin2.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin3_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin3.GPIO_perif, pin3.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin4_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin4.GPIO_perif, pin4.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin5_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin5.GPIO_perif, pin5.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin6_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin6.GPIO_perif, pin6.GPIO_pin_num)) ? 0 : 1;
	uint8_t pin7_val = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(pin7.GPIO_perif, pin7.GPIO_pin_num)) ? 0 : 1;


	return (pin7_val << 7) + (pin6_val << 6) + (pin5_val << 5) + (pin4_val << 4) +
			(pin3_val << 3)  + (pin2_val << 2) + (pin1_val << 1) + pin0_val;
}

void sampler_wait_trans_cplt(void) {
	while(HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY) {}
}

void sampler_send_packet(uint8_t * packet_start, uint16_t packet_size) {
	HAL_UART_Transmit_DMA(&huart2, packet_start, packet_size);
}

#endif /* USE_CUBE_IDE_HAL */
