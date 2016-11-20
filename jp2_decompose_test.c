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

#define N_IMAGE 25;
#define HEAD_LEN 4;
#define BLOCK_LEN 200;



int main(int argc, char *argv[])
{
	if (argc<3) {
		fprintf(stderr,"Too few arguments");
		return -1;
	}

	//Write jp2 file in buffer
	FILE * fp;

	fp=fopen(argv[1],"rb");
	if (fp==NULL){
		fprintf(stderr,"Error while opening file %s: %s.", argv[1],strerror(errno));
		return -1;
	}

	size_t f_size = get_file_size(fp);
	uint8_t * j2k_buf = malloc(f_size*sizeof(j2k_buf));
	fread(j2k_buf,1,f_size,fp);

	fclose(fp);



	//Decompose buffer in packets

	uint8_t head_len=HEAD_LEN;
	uint8_t block_len=BLOCK_LEN;
	uint8_t n_img = N_IMAGE;
	transmit_object_t * tr_object = transmit_init(j2k_buf, head_len, block_len);
	uint8_t * packet;

	fp=fopen(argv[2],"wb");

	for(int img=0;img<n_img; img++){
		
		while (!end_of_image(tr_object)){

			packet = form_packet(tr_object);

			// Print output packets in file
			fprintf(fp, "Packet %i : \n",get_packet_number(tr_object));
			for(int i=0;i<head_len+block_len; i++){
				fprintf(fp,"%02X ", packet[i] );
				if (i%16==15) {fprintf(fp,"\n");}
			}
			fprintf(fp,"\n\n");
		}
	}

	fclose(fp);
	
	//End Transmission
	transmit_end(tr_object);
	free(j2k_buf);

	return 0;

}
