#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef   	BUFFER_H
#define   	BUFFER_H


/********************************************************************
 * Buffer
 *
 * buf : 		pointer to the buffer containing the data 
 * head : 		position of the first valid data in the buffer
 * tail : 		position of the last valid data in the buffer
 * maxlen:		length of the buffer
 *
 ********************************************************************/
typedef struct {
	uint8_t * buffer;
	int head;
	int tail;
	int maxlen;
} buffer_t;

/********************************************************************
* DESCRIPTION :	Creates a new buffer	
*
* INPUTS : 
*			buf 		pointer to the buffer from which the 
*						data to be transmitted will be read.
*			head_len	header size
*			block_len	data part size 
*       
* OUTPUTS :
*       	pointer to a initialized buffer
*
*********************************************************************/
buffer_t * buffer_init(size_t buffer_size);

/********************************************************************
* DESCRIPTION :	Checks if buffer is almost full	
*
* INPUTS : 
*			buf 		pointer to the buffer
*			size 		minimum number of bytes needed in buffer
*       
* OUTPUTS :
*      		0 if buffer is empty, else 1
*
*********************************************************************/
int buffer_is_afull(buffer_t * buf, size_t size);

/********************************************************************
* DESCRIPTION :	Checks if buffer is empty	
*
* INPUTS : 
*			buf 		pointer to the buffer
*       
* OUTPUTS :
*      		0 if buffer is empty, else 1
*
*********************************************************************/
int buffer_is_empty(buffer_t * buf);


/********************************************************************
* DESCRIPTION :	Computes buffer remaining size	
*
* INPUTS : 
*			buf 		pointer to the buffer
*       
* OUTPUTS :
*      		number of remaining free bytes in buffer
*
*********************************************************************/
size_t buffer_size(buffer_t * buf);


/********************************************************************
* DESCRIPTION :	Writes in buffer	
*
* INPUTS : 
*			buf 		pointer to the buffer
*			data_len	number of bytes written in the buffer
*			data 		data to write
*       
* OUTPUTS :
*      		0 if success, -1 if error
*
*********************************************************************/
int buffer_write(buffer_t * buf,size_t data_len, uint8_t* data);


/********************************************************************
* DESCRIPTION :	Reads byte from buffer	
*
* INPUTS : 
*			buf 		pointer to the buffer
*       
* OUTPUTS :
*      		byte read from buffer
*
*********************************************************************/
uint8_t buffer_read_byte(buffer_t * buf);



//int find_marker(uint16_t marker, buffer_t * buffer);

#endif
