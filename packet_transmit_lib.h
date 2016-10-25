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
 * buf : 		pointer to the buffer containing the data 
 * counter : 	number of the actual packet
 * headlen : 	size of the header
 * blocklen : 	size of the data part
 * soi : 		start of image
 * eoi : 		end of image
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

/********************************************************************
* DESCRIPTION :	Creates a new transmit_param_t	
*
* INPUTS : 
*			buf 		pointer to the buffer from which the 
*						data to be transmitted will be read.
*			head_len	header size
*			block_len	data part size 
*       
* OUTPUTS :
*       pointer to an initialised transmit_param_t. counter=0.
*		soi=1. eoi=0
*
*********************************************************************/
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
* DESCRIPTION :     Computes file size. 
*
* INPUTS : 
*		fp 		 	File pointer
*       
* OUTPUTS :
*       size of the file.
*********************************************************************/
uint64_t get_file_size(FILE * fp);



#endif
