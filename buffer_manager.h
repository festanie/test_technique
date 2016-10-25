#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef   	BUFFER_H
#define   	BUFFER_H

typedef struct {
	uint8_t * buffer;
	int head;
	int tail;
	int maxlen;
} buffer_t;

buffer_t * buffer_init(size_t buffer_size);

int buffer_write(buffer_t * buf,size_t data_len, uint8_t* data);

int buffer_is_empty(buffer_t * buf);

size_t buffer_size(buffer_t * buf);

uint8_t buffer_read_byte(buffer_t * buf);

int find_marker(uint16_t marker, buffer_t * buffer);

#endif
