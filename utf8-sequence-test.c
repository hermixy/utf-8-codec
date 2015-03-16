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

int utf8_sequence__Test_Decode(void);

int utf8_sequence__Test_Encode(void);

int main(void){

	if (utf8_sequence__Test_Init() < 0){
		fprintf(stderr, "Init test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Done() < 0){
		fprintf(stderr, "Done test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Decode() < 0){
		fprintf(stderr, "Decode test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_sequence__Test_Encode() < 0){
		fprintf(stderr, "Encode test failed\n");
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

int utf8_sequence__Test_Decode__Fail(utf8_sequence * sequence, utf8_char expected_char);

int utf8_sequence__Test_Decode(void){

	utf8_sequence sequence;
	utf8_sequence_Init(&sequence);

	sequence.point_array[0] = 0x00;
	if (utf8_sequence_Decode(&sequence) != 0x00){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x00);
	}

	sequence.point_array[0] = 0x7F;
	if (utf8_sequence_Decode(&sequence) != 0x7F){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x7F);
	}

	sequence.point_array[0] = 0xC2;
	sequence.point_array[1] = 0x80;
	if (utf8_sequence_Decode(&sequence) != 0x80){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x80);
	}

	sequence.point_array[0] = 0xCF;
	sequence.point_array[1] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0x03FF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x03FF);
	}

	sequence.point_array[0] = 0xDF;
	sequence.point_array[1] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0x07FF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x07FF);
	}

	sequence.point_array[0] = 0xE8;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	if (utf8_sequence_Decode(&sequence) != 0x8000){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x8000);
	}

	sequence.point_array[0] = 0xEF;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0xFFFF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0xFFFF);
	}

	sequence.point_array[0] = 0xF4;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	if (utf8_sequence_Decode(&sequence) != 0x100000){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x100000);
	}

	sequence.point_array[0] = 0xF7;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0x1FFFFF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x1FFFFF);
	}

	sequence.point_array[0] = 0xF9;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	sequence.point_array[4] = 0x80;
	if (utf8_sequence_Decode(&sequence) != 0x01000000){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x01000000);
	}

	sequence.point_array[0] = 0xFB;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	sequence.point_array[4] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0x03FFFFFF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x03FFFFFF);
	}

	sequence.point_array[0] = 0xFD;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	sequence.point_array[4] = 0x80;
	sequence.point_array[5] = 0x80;
	if (utf8_sequence_Decode(&sequence) != 0x40000000){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x40000000);
	}

	sequence.point_array[0] = 0xFD;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	sequence.point_array[4] = 0xBF;
	sequence.point_array[5] = 0xBF;
	if (utf8_sequence_Decode(&sequence) != 0x7FFFFFFF){
		return utf8_sequence__Test_Decode__Fail(&sequence, 0x7FFFFFFF);
	}

	return 0;
}

int utf8_sequence__Test_Decode__Fail(utf8_sequence * sequence, utf8_char expected_char){

	utf8_char actual_char = utf8_sequence_Decode(sequence);

	fprintf(stderr, "utf8_sequence__Test_Decode failed:\n");
	fprintf(stderr, "\texpected:   %ld\n", expected_char);
	fprintf(stderr, "\tdecoded to: %ld\n", actual_char);
	fprintf(stderr, "\tsequence.point_array[0]: %X\n", sequence->point_array[0]);
	fprintf(stderr, "\tsequence.point_array[1]: %X\n", sequence->point_array[1]);
	fprintf(stderr, "\tsequence.point_array[2]: %X\n", sequence->point_array[2]);
	fprintf(stderr, "\tsequence.point_array[3]: %X\n", sequence->point_array[3]);
	fprintf(stderr, "\tsequence.point_array[4]: %X\n", sequence->point_array[4]);
	return -1;
}

int utf8_sequence__Unit_Test_Encode(utf8_sequence * expected_sequence, utf8_char c);

int utf8_sequence__Test_Encode(void){

	utf8_sequence sequence;
	utf8_sequence_Init(&sequence);

	sequence.point_array[0] = 0x00;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -1;
	}

	sequence.point_array[0] = 0x7F;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -2;
	}

	sequence.point_array[0] = 0xC2;
	sequence.point_array[1] = 0x80;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -3;
	}

	sequence.point_array[0] = 0xCF;
	sequence.point_array[1] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -4;
	}

	sequence.point_array[0] = 0xDF;
	sequence.point_array[1] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -5;
	}

	sequence.point_array[0] = 0xE8;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -6;
	}

	sequence.point_array[0] = 0xEF;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -7;
	}

	sequence.point_array[0] = 0xF4;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -8;
	}

	sequence.point_array[0] = 0xF7;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -9;
	}

	sequence.point_array[0] = 0xF9;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	sequence.point_array[4] = 0x80;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -10;
	}

	sequence.point_array[0] = 0xFB;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	sequence.point_array[4] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -11;
	}

	sequence.point_array[0] = 0xFD;
	sequence.point_array[1] = 0x80;
	sequence.point_array[2] = 0x80;
	sequence.point_array[3] = 0x80;
	sequence.point_array[4] = 0x80;
	sequence.point_array[5] = 0x80;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -12;
	}

	sequence.point_array[0] = 0xFD;
	sequence.point_array[1] = 0xBF;
	sequence.point_array[2] = 0xBF;
	sequence.point_array[3] = 0xBF;
	sequence.point_array[4] = 0xBF;
	sequence.point_array[5] = 0xBF;
	if (utf8_sequence__Unit_Test_Encode(&sequence, 0x00000000) < 0){
		return -13;
	}

	return 0;
}

int utf8_sequence__Unit_Test_Encode(utf8_sequence * expected_sequence, utf8_char c){

	int i = 0;

	utf8_sequence actual_sequence;
	utf8_sequence_Init(&actual_sequence);

	if (utf8_sequence_Encode(&actual_sequence, c) < 0){
		fprintf(stderr, "utf8_sequence_Encode failed\n");
		return -1;
	}

	for (i = 0; i < 6; i++){
		if (actual_sequence.point_array[i] != expected_sequence->point_array[i]){
			fprintf(stderr, "sequence mismatch at [%d]:\n", i);
			fprintf(stderr, "expected: %X\n", expected_sequence->point_array[i]);
			fprintf(stderr, "actual:   %X\n", actual_sequence.point_array[i]);
			return -2;
		}
	}

	return 0;
}

