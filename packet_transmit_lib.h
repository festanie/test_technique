/*
 * Author: 	St�phanie Kerckhof
 * Purpose: Functions helping to the transmission of files in
 * 			smaller packets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "buffer_manager.h"

#ifndef   	PACKET_TRANSMIT_H
#define   	PACKET_TRANSMIT_H


/********************************************************************
 * Packet Transmission Parameters
 *
 * fp : File from which the packet will be fetched
 * counter : number of the actual packet
 * headlen : size of the header
 * blocklen : size of the data part
 *
 ********************************************************************/
typedef struct
{
	buffer_t * buf;
	uint32_t counter;
	uint8_t headlen;
	uint8_t blocklen;
	uint8_t soi;
	uint8_t eoi;
}transmit_param_t;

transmit_param_t * transmit_init(buffer_t * buf, uint8_t head_len, uint8_t block_len);

/********************************************************************
* DESCRIPTION :     Returns a transmission packet from a jpeg2000 
*					file.
*
* INPUTS : 
*		transmit 	Parameters of the packet transmission
*       
* OUTPUTS :
*       pointer to the packet of data
*
*********************************************************************/
uint8_t * form_packet(transmit_param_t * transmit);


/********************************************************************
* DESCRIPTION :     Computes the number of bytes in the file
*					from the given offset to the end. 
*
* INPUTS : 
*		fp 		 	File pointer
*		f_offset	number of offset bytes
*       
* OUTPUTS :
*       size of the file from the given offset.
*********************************************************************/
uint64_t get_remaining_size(FILE * fp, uint64_t f_offset);

uint64_t get_file_size(FILE * fp);



#endif
