/*
 * Author: 	St�phanie Kerckhof
 * Purpose: Test packet_transmit_lib functions.
 *
 * 			The code decomposes the file given in argument in packets.
 * 			The packets are output on the console.
 *
 * Usage:	jp2_decompose_text.exe "filename.jp2"
 */

/*
 ============================================================================
 Name        : intopix.c
 Author      : Stéphanie Kerckhof
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "packet_transmit_lib.h"
#include "buffer_manager.h"

int main(int argc, char *argv[])
{
	if (argc<2) {
		fprintf(stderr,"Too few arguments");
		return -1;
	}

	FILE * fp;

	fp=fopen(argv[1],"rb");
	if (fp==NULL){
		fprintf(stderr,"Error while opening file %s: %s.", argv[1],strerror(errno));
		return -1;
	}

	size_t buffer_size = 1024*200;
	buffer_t * j2k_buf = buffer_init(buffer_size);
	size_t f_size = get_file_size(fp);
	uint8_t * data = malloc(f_size);
	fread(data,1,f_size,fp);

	int error = 0;


	while (error==0){
		error = buffer_write(j2k_buf, f_size, data);
	}


	uint8_t head_len=4;
	uint8_t block_len=200;


	transmit_param_t * param = transmit_init(j2k_buf, head_len, block_len);
	uint8_t * packet;

	while (!buffer_is_empty(j2k_buf)){

		packet = form_packet(param);

		// Print output packet on console
		fprintf(stdout, "Packet %i : \n",param->counter);
		for(int i=0;i<head_len+block_len; i++){
			fprintf(stdout,"%02X ", packet[i] );
			if (i%16==15) {printf("\n");}
		}
		fprintf(stdout,"\n\n");
	}




/*	transmit_param_t transmit_file;
	transmit_file.fp = fp;
	transmit_file.counter = 0;
	transmit_file.headlen = 4;
	transmit_file.blocklen = 200;

	uint8_t last_packet=0;
	uint8_t *packet;
	uint8_t packet_len = transmit_file.headlen+transmit_file.blocklen;

	while(last_packet==0){
		packet = form_packet(transmit_file);
		transmit_file.counter++;
		last_packet = (packet[0]&0x40)>>6;
		printf("Packet %i : \n",transmit_file.counter);
		for(int i=0;i<packet_len; i++){
			printf("%02X ", packet[i] );
			if (i%16==15) {printf("\n");}
		}
		printf("\n\n");
	}

	
*/
	fclose(fp);
	return 0;

}
