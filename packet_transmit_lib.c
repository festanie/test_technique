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
#include <inttypes.h>

#include "packet_transmit_lib.h"

/********************************************************************
 * Packet Transmission Object
 *
 * buf : 		pointer to the buffer containing the data
 * buf_pos : 	actual position in buffer
 * buf_size :	size of buffer
 * packet:		pointer to the actual packet 
 * counter : 	number of the actual packet
 * headlen : 	size of the header
 * blocklen : 	size of the data part
 * soi : 		start of image
 * eoi : 		end of image
 *
 ********************************************************************/

/*struct transmit_object_t{
	uint8_t * buf;
	uint64_t buf_pos;
	uint64_t buf_size;
	uint8_t * packet; 
	uint32_t counter;
	uint8_t headlen;
	uint8_t blocklen;
	uint8_t soi;
	uint8_t eoi;
};*/

/********************************************************************
 * transmit_init
 ********************************************************************/
transmit_object_t * transmit_init(uint8_t head_len, uint8_t block_len){
	transmit_object_t * transmit = malloc(sizeof(transmit_object_t));
	
	transmit->packet = malloc((head_len+block_len)*sizeof(transmit->packet));
	transmit->counter=0;

	transmit->headlen=head_len;
	transmit->blocklen=block_len;

	transmit->eoi=0;
	transmit->soi=1;
	return  transmit;
};

/********************************************************************
 * transmit_set_buf
 ********************************************************************/
void transmit_set_buf(transmit_object_t * transmit, uint8_t * buf, uint64_t buf_size){
	transmit->buf=buf;
	transmit->buf_pos = 0;
	transmit->buf_size=buf_size;
}
/********************************************************************
 * transmit_end
 ********************************************************************/
void transmit_end(transmit_object_t * transmit){
	free(transmit->packet);
	free(transmit);
};

/********************************************************************
 * form_packet
 ********************************************************************/
void * form_packet(transmit_object_t * transmit)
{

	uint64_t count = transmit->counter;
	uint8_t block_len = transmit->blocklen;
	uint8_t head_len = transmit->headlen;
	uint8_t soi = transmit->soi;
	uint8_t eoi = transmit->eoi;
	uint8_t *packet = transmit->packet;


	// Change start of image flag if previous packet was the first
	// or the last one;
	if (soi&&count!=0){
		soi = 0;
	}
	if (eoi){
		soi = 1;
	}
	/****************************************************************
	* 	Extraction of block of data from buffer
	*****************************************************************/
	uint8_t *block = packet+head_len;
	
	uint8_t *buf_head = transmit->buf+transmit->buf_pos;
	uint8_t eop = 0;
	uint8_t byte_cnt = 0;
	block[0]=buf_head[0];

	// Read buffer and check for end of file marker
	while(!eop){
		byte_cnt++;
		block[byte_cnt]=buf_head[byte_cnt];
		eoi = (block[byte_cnt-1]==0xFF&&block[byte_cnt]==0xD9);
		eop=(eoi||byte_cnt==block_len-1);
	}

	transmit->buf_pos = transmit->buf_pos+byte_cnt+1;
	
	//If image not a multiple of block_len, last bytes are 0x00
	if (eoi){
		for (int i=byte_cnt+1; i<block_len; i++){
			block[i]=0x00;
		}
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

/********************************************************************
 * get_packet_number
 ********************************************************************/
uint64_t get_packet_number(transmit_object_t * transmit)
{
	return transmit->counter;
}

/********************************************************************
 * end_of_image
 ********************************************************************/
uint8_t end_of_buffer(transmit_object_t * transmit)
{
	uint8_t eob = (transmit->buf_pos==transmit->buf_size);
	return  eob;
}


/********************************************************************
 * print_packet
 ********************************************************************/
void print_packet(transmit_object_t * transmit, FILE * fp)
{

	fprintf(fp, "Packet %"PRIu64 ": \n",get_packet_number(transmit));
		for(int i=0;i<transmit->headlen+transmit->blocklen; i++){
			fprintf(fp,"%02X ", transmit->packet[i] );
			if (i%16==15) {fprintf(fp,"\n");}
		}
		fprintf(fp,"\n\n");
}




/********************************************************************
 * get_file_size
 ********************************************************************/
uint64_t get_file_size(FILE * fp)
{
	uint64_t size;

	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0, SEEK_SET);

	return size;
}

