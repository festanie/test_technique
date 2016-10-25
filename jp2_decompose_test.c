/*
 * Name:	jp2_decompose_test.c
 * Author: 	Stephanie Kerckhof
 * Purpose: Test packet_transmit_lib functions.
 *
 * 			The code create a stream in a buffer from a
 *			jp2 file and decomposes it in an output file.
 *
 * Usage:	jp2_decompose_text.exe filename.jp2 output.txt
 *
 *			filename.jp2 = 	jpeg2000 file
 *			output.txt = 	file in which the packets will
 *							be printed
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "packet_transmit_lib.h"
#include "buffer_manager.h"

int main(int argc, char *argv[])
{
	if (argc<3) {
		fprintf(stderr,"Too few arguments");
		return -1;
	}

	FILE * fp;

	fp=fopen(argv[1],"rb");
	if (fp==NULL){
		fprintf(stderr,"Error while opening file %s: %s.", argv[1],strerror(errno));
		return -1;
	}

	//Write jp2 files in buffer

	size_t buffer_size = 1024*200;
	buffer_t * j2k_buf = buffer_init(buffer_size);
	size_t f_size = get_file_size(fp);
	uint8_t * data = malloc(f_size);
	fread(data,1,f_size,fp);

	fclose(fp);

	while (!(buffer_is_afull(j2k_buf,f_size))){
		buffer_write(j2k_buf, f_size, data);
	}

	free(data);

	//Decompose buffer in packets

	uint8_t head_len=4;
	uint8_t block_len=200;


	transmit_param_t * param = transmit_init(j2k_buf, head_len, block_len);
	uint8_t * packet;

	fp=fopen(argv[2],"wb");

	while (!buffer_is_empty(j2k_buf)){

		packet = form_packet(param);

		// Print output packets in file
		fprintf(fp, "Packet %i : \n",param->counter);
		for(int i=0;i<head_len+block_len; i++){
			fprintf(fp,"%02X ", packet[i] );
			if (i%16==15) {fprintf(fp,"\n");}
		}
		fprintf(fp,"\n\n");
	}

	fclose(fp);


	return 0;

}
