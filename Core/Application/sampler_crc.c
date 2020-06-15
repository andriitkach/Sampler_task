/*
 * smpler_crc.c
 *
 *  Created on: Jun 14, 2020
 *      Author: andriitkach
 */

#include "main.h"

static uint16_t crc16_lut[256];
static const uint16_t poly = 0xA001;
static const uint16_t init_crc = 0xffff;

void sampler_precalc_crc16_lut(void) {
	for(uint8_t data = 0; data < 256; data++) {
		uint16_t xor_res = ((uint16_t)data << 8);
		for(uint8_t bit = 0; bit < 8; bit++) {
			if(xor_res & 0x8000) {
				xor_res <<= 1;
				xor_res ^= poly;
			}
			else {
				xor_res <<= 1;
			}
		}
		crc16_lut[data] = xor_res;
		if(data == 255)
			break;
	}
}
uint16_t sampler_calc_crc16(uint8_t * data, uint16_t size) {
	uint16_t crc = init_crc;
	uint16_t cnt = 0;
	for(cnt = 0; cnt < size; cnt++) {
		uint8_t pos = (uint8_t)((crc >> 8) ^ data[cnt]);
		crc = (crc << 8) ^ (uint16_t)crc16_lut[pos];
	}
	return crc;
}
