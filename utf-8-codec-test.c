/*
 *    This file is part of Utf8Codec.
 *
 *    Utf8Codec is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utf8Codec is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utf8Codec.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utf-8-codec.h"

#include <stdio.h>
#include <stdlib.h>

int utf_8_codec_Test_Decode(void);

int main(void){

	fprintf(stdout, "Running decode test...");
	if (utf_8_codec_Test_Decode() < 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	return 0;
}

int utf_8_codec_Test_Decode(void){

	unsigned char test_buffer[4];

	long int test_c = 0;

	test_buffer[0] = 0x00;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x00){
		fprintf(stderr, "failed to decode 0x00\n");
		return -1;
	}

	test_buffer[0] = 0x7F;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x7F){
		fprintf(stderr, "failed to decode 0x7F\n");
		return -1;
	}

	test_buffer[0] = 0xC2;
	test_buffer[1] = 0x80;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x80){
		fprintf(stderr, "failed to decode 0x80\n");
		return -1;
	}

	test_buffer[0] = 0xDF;
	test_buffer[1] = 0xBF;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x07FF){
		fprintf(stderr, "failed to decode 0x07FF\n");
		return -1;
	}

	test_buffer[0] = 0xE0;
	test_buffer[1] = 0xA0;
	test_buffer[2] = 0x80;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x0800){
		fprintf(stderr, "failed to decode 0x0800\n");
		return -1;
	}

	test_buffer[0] = 0xEF;
	test_buffer[1] = 0xBF;
	test_buffer[2] = 0xBF;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0xFFFF){
		fprintf(stderr, "failed to decode 0xFFFF\n");
		return -1;
	}

	test_buffer[0] = 0xF0;
	test_buffer[1] = 0x90;
	test_buffer[2] = 0x80;
	test_buffer[3] = 0x80;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x010000){
		fprintf(stderr, "failed to decode 0x010000\n");
		return -1;
	}

	test_buffer[0] = 0xF7;
	test_buffer[1] = 0xBF;
	test_buffer[2] = 0xBF;
	test_buffer[3] = 0xBF;
	if (utf_8_codec_Decode(test_buffer, &test_c) < 0 || test_c != 0x1FFFFF){
		fprintf(stderr, "failed to decode 0x1FFFFF\n");
		return -1;
	}

	/* check to make sure that this fails */
	test_buffer[0] = 0xF8;
	if (utf_8_codec_Decode(test_buffer, &test_c) >= 0){
		fprintf(stderr, "decode did not fail in an out of bounds encoding\n");
		return -1;
	}

	return 0;
}

