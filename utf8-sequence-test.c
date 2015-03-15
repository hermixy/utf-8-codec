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

#include "utf8-sequence.h"

#include <stdio.h>
#include <stdlib.h>

int utf8_sequence__Test_Init(void);

int utf8_sequence__Test_Done(void);

int utf8_sequence__Test_Encode(void);

int utf8_sequence__Test_Decode(void);

int main(void){

	if (utf8_sequence__Test_Init() < 0){
		fprintf(stderr, "Init test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Done() < 0){
		fprintf(stderr, "Done test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Encode() < 0){
		fprintf(stderr, "Encode test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Decode() < 0){
		fprintf(stderr, "Decode test failed\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int utf8_sequence__Test_Init(void){

	int i = 0;

	utf8_sequence sequence;

	if (utf8_sequence_Init(&sequence) < 0){
		fprintf(stderr, "failed to initialize sequence\n");
		return -1;
	}

	if (sequence.point_count != 0){
		fprintf(stderr, "point count != 0 after initialization\n");
		return -2;
	}

	for (i = 0; i < UTF8_SEQUENCE_POINT_MAX; i++){
		if (sequence.point_array[i] != 0){
			fprintf(stderr, "point[%d] != 0\n", i);
			return -3;
		}
	}

	return 0;
}

int utf8_sequence__Test_Done(void){

	int i = 0;

	utf8_sequence sequence;

	if (utf8_sequence_Init(&sequence) < 0){
		fprintf(stderr, "failed to initialize sequence\n");
		return -1;
	}

	for (i = 0; i < UTF8_SEQUENCE_POINT_MAX; i++){
		sequence.point_array[i] = 0xF0;
	}

	utf8_sequence_Done(&sequence);

	if (sequence.point_count != 0){
		fprintf(stderr, "point count != 0 after utf8_sequence_Done\n");
		return -2;
	}

	for (i = 0; i < UTF8_SEQUENCE_POINT_MAX; i++){
		if (sequence.point_array[i] != 0){
			fprintf(stderr, "point[%d] != 0\n", i);
			return -3;
		}
	}

	return 0;
}

int utf8_sequence__Test_Encode(void){
	return 0;
}

int utf8_sequence__Test_Decode(void){
	return 0;
}

