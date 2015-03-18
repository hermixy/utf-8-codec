/*
 *    This file is part of Utf8String.
 *
 *    Utf8String is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utf8String is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utf8String.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utf8-string.h"

#include <stdio.h>
#include <stdlib.h>

int utf8_string__Test_Init(void);

int utf8_string__Test_Done(void);

int utf8_string__Test_Get_Byte(void);

int utf8_string__Test_Get_Byte_Span(void);

int utf8_string__Test_Get_Sequence(void);

int utf8_string__Test_Get_Point(void);

int main(void){

	fprintf(stdout, "Running Init test... ");
	if (utf8_string__Test_Init() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running Done test... ");
	if (utf8_string__Test_Done() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running Get_Byte test... ");
	if (utf8_string__Test_Get_Byte() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running Get_Byte_Span test... ");
	if (utf8_string__Test_Get_Byte_Span() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running Get_Sequence test... ");
	if (utf8_string__Test_Get_Sequence() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running Get_Point test... ");
	if (utf8_string__Test_Get_Point() != 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	return EXIT_SUCCESS;
}

int utf8_string__Test_Init(void){

	utf8_string string;

	if (utf8_string_Init(&string) < 0){
		fprintf(stderr, "string initialization failed\n");
		return -1;
	}

	if (string.byte_array != NULL){
		fprintf(stderr, "string.byte_array should be NULL after initialization\n");
		return -2;
	}

	if (string.byte_count != 0){
		fprintf(stderr, "string.byte_count should be 0 after initialization\n");
		return -3;
	}

	return 0;
}

int utf8_string__Test_Done(void){

	utf8_string string;

	if (utf8_string_Init(&string) < 0){
		fprintf(stderr, "string initialization failed\n");
		return -1;
	}

	string.byte_array = malloc(sizeof(utf8_byte));
	if (!string.byte_array){
		fprintf(stderr, "failed to malloc byte for test\n");
		return -2;
	}
	string.byte_count = 1;

	utf8_string_Done(&string);

	if (string.byte_array != NULL){
		fprintf(stderr, "byte_array is not NULL after utf8_string_Done\n");
		return -3;
	}

	if (string.byte_count != 0){
		fprintf(stderr, "byte_count is not 0 after utf8_string_Done\n");
		return -4;
	}

	return 0;
}

int utf8_string__Test_Get_Byte(void){

	utf8_byte byte_array[3];

	utf8_byte test_byte = 0;

	utf8_string string;

	int i = 0;

	byte_array[0] = 0x01;
	byte_array[1] = 0x03;
	byte_array[2] = 0x05;

	string.byte_array = byte_array;
	string.byte_count = 3;

	for (i = 0; i < 3; i++){

		if (utf8_string_Get_Byte(&string, i, &test_byte) < 0){
			fprintf(stderr, "failed to get byte %d\n", i);
			return -1;
		}

		if (test_byte != byte_array[i]){
			fprintf(stderr, "byte[%d] value is different\n", i);
			return -1;
		}
	}

	return 0;
}

int utf8_string__Test_Get_Byte_Span(void){

	utf8_byte byte_array[3];

	utf8_string string;

	int i = 0;

	byte_array[0] = 0x01;
	byte_array[1] = 0xC0;
	byte_array[2] = 0xFE;

	string.byte_array = byte_array;
	string.byte_count = 3;

	for (i = 0; i < 3; i++){
		if (utf8_string_Get_Byte_Span(&string, i) != utf8_byte_Get_Span(byte_array[i])){
			fprintf(stderr, "byte[%d] span is different\n", i);
			return -1;
		}
	}

	return 0;
}

int utf8_string__Test_Get_Sequence(void){

	utf8_sequence sequence;

	/* used for creating artificial utf8 strings. */
	utf8_byte byte_array[256];

	/* used for creating artificial utf8 strings. */
	utf8_string string;

	byte_array[0] = 0xC0;
	byte_array[1] = 0x81;

	string.byte_array = byte_array;
	string.byte_count = 2;

	if (utf8_string_Get_Sequence(&string, 0, &sequence) < 0){
		fprintf(stderr, "failed to get sequence at index 0\n");
		return -1;
	}

	if ((sequence.byte_array[0] != 0xC0) || (sequence.byte_array[1] != 0x81)){
		fprintf(stderr, "sequence test at index 0 contains incorrect data\n");
		return -2;
	}

	byte_array[2] = 0xE0;
	byte_array[3] = 0x80;
	byte_array[4] = 0x80;

	string.byte_count += 3;

	if (utf8_string_Get_Sequence(&string, 1, &sequence) < 0){
		fprintf(stderr, "failed to get sequence at index 1\n");
		return -3;
	}

	if ((sequence.byte_array[0] != 0xE0)
	 || (sequence.byte_array[1] != 0x80)
	 || (sequence.byte_array[2] != 0x80)){
		fprintf(stderr, "sequence test at index 1 contains incorrect data\n");
		return -4;
	}

	return 0;
}

int utf8_string__Test_Get_Point(void){

	utf8_point point;

	utf8_byte byte_array[256];

	utf8_string string;

	string.byte_array = byte_array;

	string.byte_array[0] = 0;
	string.byte_count = 1;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0){
		fprintf(stderr, "failed to get point 0\n");
		return -1;
	}

	string.byte_array[0] = 0x7F;
	string.byte_count = 1;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F\n");
		return -2;
	}

	string.byte_array[0] = 0xC2;
	string.byte_array[1] = 0x80;
	string.byte_count = 2;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x80){
		fprintf(stderr, "failed to get point 0x80\n");
		return -3;
	}

	string.byte_array[0] = 0xDF;
	string.byte_array[1] = 0xBF;
	string.byte_count = 2;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x7FF){
		fprintf(stderr, "failed to get point 0x7FF\n");
		return -4;
	}

	string.byte_array[0] = 0xE0;
	string.byte_array[1] = 0xA0;
	string.byte_array[2] = 0x80;
	string.byte_count = 3;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x800){
		fprintf(stderr, "failed to get point 0x800\n");
		return -5;
	}

	string.byte_array[0] = 0xEF;
	string.byte_array[1] = 0xBF;
	string.byte_array[2] = 0xBF;
	string.byte_count = 3;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0xFFFF){
		fprintf(stderr, "failed to get point 0x7FFF\n");
		return -6;
	}

	string.byte_array[0] = 0xF0;
	string.byte_array[1] = 0x90;
	string.byte_array[2] = 0x80;
	string.byte_array[3] = 0x80;
	string.byte_count = 4;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x010000){
		fprintf(stderr, "failed to get point 0x010000\n");
		return -7;
	}

	string.byte_array[0] = 0x00;
	string.byte_array[1] = 0x7F;
	string.byte_count = 2;
	if (utf8_string_Get_Point(&string, 1, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0x00\n");
		return -8;
	}

	string.byte_array[0] = 0xC2;
	string.byte_array[1] = 0x80;
	string.byte_array[2] = 0x7F;
	string.byte_count = 3;
	if (utf8_string_Get_Point(&string, 1, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0xC2 0x80\n");
		return -9;
	}

	string.byte_array[0] = 0xE8;
	string.byte_array[1] = 0x80;
	string.byte_array[2] = 0x80;
	string.byte_array[3] = 0x7F;
	string.byte_count = 4;
	if (utf8_string_Get_Point(&string, 1, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0xE8 0x80 0x80\n");
		return -10;
	}

	string.byte_array[0] = 0x00;
	string.byte_array[1] = 0x00;
	string.byte_array[2] = 0x7F;
	string.byte_count = 3;
	if (utf8_string_Get_Point(&string, 2, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0x00 0x00\n");
		return -11;
	}

	string.byte_array[0] = 0xC2;
	string.byte_array[1] = 0x80;
	string.byte_array[2] = 0x00;
	string.byte_array[3] = 0x7F;
	string.byte_count = 4;
	if (utf8_string_Get_Point(&string, 2, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0xC2 0x80 0x00\n");
		return -12;
	}

	string.byte_array[0] = 0x00;
	string.byte_array[1] = 0xC2;
	string.byte_array[2] = 0x80;
	string.byte_array[3] = 0x7F;
	string.byte_count = 4;
	if (utf8_string_Get_Point(&string, 0, &point) < 0 || point != 0x00){
		fprintf(stderr, "failed to get point 0x00 before 0xC2 0x80 0x7F\n");
		return -13;
	}

	if (utf8_string_Get_Point(&string, 1, &point) < 0 || point != 0x80){
		fprintf(stderr, "failed to get point 0x80 before 0x7F and after 0x00\n");
		return -14;
	}

	if (utf8_string_Get_Point(&string, 2, &point) < 0 || point != 0x7F){
		fprintf(stderr, "failed to get point 0x7F after 0x00 0xC2 0x80\n");
		return -15;
	}

	return 0;
}

