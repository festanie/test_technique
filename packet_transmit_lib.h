/*
 * Author: 	Stephanie Kerckhof
 * Purpose: Functions helping to the transmission of files in
 * 			smaller packets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#ifndef   	PACKET_TRANSMIT_H
#define   	PACKET_TRANSMIT_H


/********************************************************************
 * Packet Transmision Object
 *
 * Structure containing information on the packet transmission.
 *
 ********************************************************************/
typedef struct transmit_object_t
{	uint8_t * buf;
	uint64_t buf_pos;
	uint64_t buf_size;
	uint8_t * packet;
	uint32_t counter;
	uint8_t headlen;
	uint8_t blocklen;
	uint8_t soi;
	uint8_t eoi;
} transmit_object_t;

/********************************************************************
* DESCRIPTION :	Creates a new transmit_object_t	
*
* INPUTS : 
*			buf 		pointer to the image buffer from which the
*						data to be transmitted will be read.
*			head_len	header size
*			block_len	data part size 
*       
* OUTPUTS :
*       pointer to an initialised transmit_object_t. counter=0.
*		soi=1. eoi=0
*
*********************************************************************/
transmit_object_t * transmit_init(uint8_t head_len, uint8_t block_len);

/********************************************************************
* DESCRIPTION :	Ends the existing transmission. Free used memory.	
*
* INPUTS : 
*			transmit 		Packet transmission object
*       
*
*********************************************************************/
void transmit_end(transmit_object_t * transmit);


/********************************************************************
* DESCRIPTION :	Set buffer properties in transmit object.
*
* INPUTS :
*			transmit 		Packet transmission object
*			buf				pointer to image buffer
*			buf_size		size of image buffer
*
*
*********************************************************************/
void transmit_set_buf(transmit_object_t * transmit, uint8_t * buf, uint64_t buf_size);

/********************************************************************
* DESCRIPTION :     Update information contained in transmission
* 					object relatively to actual packet.
*
* INPUTS : 
*		transmit 	Packet transmission object
*       
*
*********************************************************************/
void * form_packet(transmit_object_t * transmit);

/********************************************************************
* DESCRIPTION :     Returns the actual packet number
*
* INPUTS : 
*		transmit 	Packet transmission object
*       
* OUTPUTS :
*       packet number
*
*********************************************************************/
uint64_t get_packet_number(transmit_object_t * transmit);

/********************************************************************
* DESCRIPTION :     Returns if this is the last packet of image
*
* INPUTS : 
*		transmit 	Packet transmission object
*       
* OUTPUTS :
*       1 if end of image
*
*********************************************************************/
uint8_t end_of_image(transmit_object_t * transmit);


/********************************************************************
* DESCRIPTION :     Print packet to file
*
* INPUTS :
*		transmit 	Packet transmission object
*		fp			Pointer to the file in which the packet will be
*					printed
*
*
*********************************************************************/
void print_packet(transmit_object_t * transmit, FILE * fp);

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

