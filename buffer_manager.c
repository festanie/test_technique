#include "buffer_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


buffer_t* buffer_init(size_t buffer_size){
	buffer_t* buf = malloc(sizeof(buffer_t));
	uint8_t* buffer = malloc(buffer_size);
	buf->buffer = buffer;
	buf->head=0;
	buf->tail=0;
	buf->maxlen=buffer_size;
	return  buf;
};


int buffer_is_empty(buffer_t * buf){
	return (buf->head==buf->tail);
}

size_t buffer_size(buffer_t * buf){
	return (buf->tail-buf->head);
}

int buffer_is_afull(buffer_t * buf, size_t size){
	return ((buf->maxlen-buf->tail)<size);
}

int buffer_write(buffer_t * buf,size_t data_len, uint8_t* data){
	if(buf->maxlen-buf->tail<data_len){
		fprintf(stderr,"No sufficient space in buffer to write data");
		return -1;
	}
	for(int i=0; i<data_len; i++){
		buf->buffer[i+buf->tail]=data[i];
	}
	buf->tail=buf->tail+data_len;
	return 0;
};

uint8_t buffer_read_byte(buffer_t * buf){
	if (buffer_is_empty(buf)){
		fprintf(stderr,"Can't read byte, buffer is empty");
		return -1;
	}
	uint8_t byte = buf->buffer[buf->head];
	buf->head++;
	return byte;
}

/*int find_marker(uint16_t marker, buffer_t * buf){
	for(int i=buf->head; i<buf->tail-1; i++){
		if (buf->buffer[i]==(uint8_t)marker>>8 && buf->buffer[i+1]==(uint8_t)marker) {
			return i;
		};
	};

	fprintf(stderr,"Marker %02X not found in buffer",marker);
	return NULL;
};
*/

