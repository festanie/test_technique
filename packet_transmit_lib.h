/*
 * Author: 	St�phanie Kerckhof
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
typedef struct transmit_object_t transmit_object_t;

/********************************************************************
* DESCRIPTION :	Creates a new transmit_object_t	
*
* INPUTS : 
*			buf 		pointer to the buffer from which the 
*						data to be transmitted will be read.
*			head_len	header size
*			block_len	data part size 
*       
* OUTPUTS :
*       pointer to an initialised transmit_object_t. counter=0.
*		soi=1. eoi=0
*
*********************************************************************/
transmit_object_t * transmit_init(uint8_t * buf, uint8_t head_len, uint8_t block_len);

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
* DESCRIPTION :     Returns a transmission packet from a jpeg2000 
*					file.
*
* INPUTS : 
*		transmit 	Packet transmission object
*       
* OUTPUTS :
*       pointer to the packet of data
*
*********************************************************************/
uint8_t * form_packet(transmit_object_t * transmit);

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
