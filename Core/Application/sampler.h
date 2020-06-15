/*
 * sampler.h
 *
 *  Created on: Jun 12, 2020
 *      Author: andriitkach
 */

#ifndef _APPLICATION_SAMPLER_H_
#define _APPLICATION_SAMPLER_H_

#include "sampler_HAL.h"

void sampler_init_ring_buf(void);
void sampler_push_byte(uint8_t);
void sampler_create_packet(void);
void sampler_precalc_crc16_lut(void);
uint16_t sampler_calc_crc16(uint8_t *, uint16_t);

#endif /* _APPLICATION_SAMPLER_H_ */
