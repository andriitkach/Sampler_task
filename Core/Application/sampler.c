/*
 * sampler.c
 *
 *  Created on: Jun 12, 2020
 *      Author: andriitkach
 */
#include "sampler.h"

#define PAYLOAD_SIZE 128

static uint8_t ring_buf[256];
static uint8_t packet_buf_0[PAYLOAD_SIZE*2]; //lower level protocol packet buffer
static uint8_t packet_buf_1[PAYLOAD_SIZE*4]; //upper level protocol packet buffer
static volatile uint8_t buf_start;
static volatile uint8_t buf_end;
static uint8_t sample_cnt;

void sampler_init_ring_buf(void) {
	buf_start = 0;
	buf_end = 0;
	sample_cnt = 0;
}

void sampler_push_byte(uint8_t new_byte) {
	/* This code executes in interrupt context */
	if(buf_end != buf_start-1) {
		ring_buf[buf_end++] = new_byte;
	}
	else {
		/* Error: ring buffer overflow
		 * Drop the sample */
	}
}

uint16_t sampler_wrap_packet(uint16_t size) {
	uint16_t result_cnt = 0;
	uint16_t pkt_cnt = 0;
	/* Wait if the previous packet is still being transmitted */
	sampler_wait_trans_cplt();
	packet_buf_1[result_cnt++] = 0x55;
	while(pkt_cnt < size) {
		if(packet_buf_0[pkt_cnt] == 0x55) {
			packet_buf_1[result_cnt++] = 0xAA;
			packet_buf_1[result_cnt++] = 0x00;
			pkt_cnt++;
		}
		else if(packet_buf_0[pkt_cnt] == 0xAA) {
			packet_buf_1[result_cnt++] = 0xAA;
			packet_buf_1[result_cnt++] = 0x01;
			pkt_cnt++;
		}
		else {
			packet_buf_1[result_cnt++] = packet_buf_0[pkt_cnt];
			pkt_cnt++;
		}
	}
	return result_cnt;
}

void sampler_create_packet() {
	uint8_t end = buf_end;
	uint8_t sample_cnt = end - buf_start;
	if(sample_cnt >= PAYLOAD_SIZE) {
		sampler_wait_trans_cplt();
		uint16_t pkt_cnt = 0;
		packet_buf_0[pkt_cnt] = sample_cnt;
		pkt_cnt++;
		while(buf_start != end) {
			packet_buf_0[pkt_cnt++] = ring_buf[buf_start++];
			//pkt_cnt++;
		}
		uint16_t crc16 = sampler_calc_crc16(packet_buf_0, pkt_cnt);
		/* Write crc16 into pkt_buf with little endian order */
		packet_buf_0[pkt_cnt++] = (uint8_t)crc16;
		packet_buf_0[pkt_cnt++] = (uint8_t)(crc16 >> 8);

		uint16_t res_size = sampler_wrap_packet(pkt_cnt);

		/* Send via UART */
		sampler_send_packet(packet_buf_1, res_size);

	}
}


