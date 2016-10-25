/*
 * Author: 	Stephanie Kerckhof
 * Purpose: Functions helping to the transmission of files in
 * 			smaller packets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "packet_transmit_lib.h"

transmit_param_t * transmit_init(buffer_t * buf, uint8_t head_len, uint8_t block_len){
	transmit_param_t * transmit = malloc(sizeof(transmit_param_t));
	transmit->buf=buf;
	transmit->blocklen=block_len;
	transmit->counter=0;
	transmit->eoi=0;
	transmit->headlen=head_len;
	transmit->soi=1;
	return  transmit;
};

uint8_t * form_packet(transmit_param_t * transmit)
{

	uint64_t count = transmit->counter;
	uint8_t block_len = transmit->blocklen;
	uint8_t head_len = transmit->headlen;
	uint8_t soi = transmit->soi;
	uint8_t eoi = transmit->eoi;
		
	uint8_t * packet;
	packet = (uint8_t *) malloc(head_len+block_len);

	// Change start of image flag if last packet was the first
	// or the last one;
	if (eoi||(soi&&count!=0)){
		soi = 0;
	}

	/****************************************************************
	* 	Extraction of block of data from buffer
	*****************************************************************/
	uint8_t *block;
	block = packet+head_len;

	uint8_t eop = 0;
	uint8_t byte_cnt = 0;
	block[byte_cnt]=buffer_read_byte(transmit->buf);

	// Read buffer and check for end of file marker
	while(!eop){
		byte_cnt++;
		block[byte_cnt]=buffer_read_byte(transmit->buf);
		eoi = (block[byte_cnt-1]==0xFF&&block[byte_cnt]==0xD9);
		eop=(eoi||byte_cnt==block_len-1);
	}

	//If image not a multiple of block_len, last byte is 0x00
	if (eoi){
		block[byte_cnt+1]=0x00;
	}


	/****************************************************************
	*	Constitution of header
	*	---------------------------------------------------
	*	Byte 0 of header composed of
	*		0 (msb)	- first packet flag
	*		1 		- last packet flag
	*		2 to 7 	- reserved
	*	Byte 1-3 of header composed of 3 bytes of counter,
	*	byte1 contains counter msb.
	*****************************************************************/

	uint8_t *head;
	head = packet;
	
	uint8_t first = soi;
	uint8_t last = eoi;

	head[0]=first<<7|last<<6;
	head[1]=(uint8_t)(count>>16);
	head[2]=(uint8_t)(count>>8);
	head[3]=(uint8_t)count;

	/****************************************************************
	* 	Transmission parameters update
	****************************************************************/
	transmit->counter++;
	transmit->soi=soi;
	transmit->eoi=eoi;

	return packet;

}


uint64_t get_file_size(FILE * fp)
{
	uint64_t size;

	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0, SEEK_SET);

	return size;
}
