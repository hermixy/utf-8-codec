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

#include "utf-8-byte.h"

#include <stdio.h>
#include <stdlib.h>

int utf8_byte__Test_Get_Span(void);

int utf8_byte__Test_Get_Data_Bit_Count(void);

int utf8_byte__Test_Get_Data(void);

int main(void){

	if (utf8_byte__Test_Get_Span() < 0){
		fprintf(stderr, "Get_Span test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_byte__Test_Get_Data_Bit_Count() < 0){
		fprintf(stderr, "Get_Data_Bit_Count test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_byte__Test_Get_Data() < 0){
		fprintf(stderr, "Get_Data test failed\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int utf8_byte__Test_Get_Span(void){

	/* range 0xxx xxxx */
	/* min   0000 0000 */
	/* mid   0011 1111 */
	/* max   0111 1111 */

	if (utf8_byte_Get_Span(0x00) != 1){
		fprintf(stderr, "byte span of 0x00 should be 1\n");
		return -1;
	}

	if (utf8_byte_Get_Span(0x0F) != 1){
		fprintf(stderr, "byte span of 0x0F should be 1\n");
		return -2;
	}

	if (utf8_byte_Get_Span(0x7F) != 1){
		fprintf(stderr, "byte span of 0x7F should be 1\n");
		return -3;
	}

	/* range 110x xxxx */
	/* min   1100 0000 */
	/* mid   1100 1111 */
	/* max   1101 1111 */

	if (utf8_byte_Get_Span(0xC0) != 2){
		fprintf(stderr, "byte span of 0xC0 should be 2\n");
		return -4;
	}

	if (utf8_byte_Get_Span(0xCF) != 2){
		fprintf(stderr, "byte span of 0xCF should be 2\n");
		return -5;
	}

	if (utf8_byte_Get_Span(0xDF) != 2){
		fprintf(stderr, "byte span of 0xDF should be 2\n");
		return -6;
	}

	/* range 1110 xxxx */
	/* min   1110 0000 */
	/* mid   1110 0111 */
	/* max   1110 1111 */

	if (utf8_byte_Get_Span(0xE0) != 3){
		fprintf(stderr, "byte span of 0xE0 should be 3\n");
		return -7;
	}

	if (utf8_byte_Get_Span(0xE7) != 3){
		fprintf(stderr, "byte span of 0xE7 should be 3\n");
		return -8;
	}

	if (utf8_byte_Get_Span(0xEF) != 3){
		fprintf(stderr, "byte span of 0xEF should be 3\n");
		return -9;
	}

	/* range 1111 0xxx */
	/* min   1111 0000 */
	/* mid   1111 0011 */
	/* max   1111 0111 */

	if (utf8_byte_Get_Span(0xF0) != 4){
		fprintf(stderr, "byte span of 0xF0 should be 4\n");
		return -7;
	}

	if (utf8_byte_Get_Span(0xF3) != 4){
		fprintf(stderr, "byte span of 0xF3 should be 4\n");
		return -8;
	}

	if (utf8_byte_Get_Span(0xF7) != 4){
		fprintf(stderr, "byte span of 0xF7 should be 4\n");
		return -9;
	}

	/* range 1111 10xx */
	/* min   1111 1000 */
	/* mid   1111 1001 */
	/* max   1111 1011 */

	if (utf8_byte_Get_Span(0xF8) != 5){
		fprintf(stderr, "byte span of 0xF8 should be 5\n");
		return -7;
	}

	if (utf8_byte_Get_Span(0xF9) != 5){
		fprintf(stderr, "byte span of 0xF9 should be 5\n");
		return -8;
	}

	if (utf8_byte_Get_Span(0xFB) != 5){
		fprintf(stderr, "byte span of 0xFB should be 5\n");
		return -9;
	}

	/* range 1111 110x */
	/* min   1111 1100 */
	/* mid   n/a       */
	/* max   1111 1101 */

	if (utf8_byte_Get_Span(0xFC) != 6){
		fprintf(stderr, "byte span of 0xFC should be 6\n");
		return -7;
	}

	if (utf8_byte_Get_Span(0xFD) != 6){
		fprintf(stderr, "byte span of 0xFD should be 6\n");
		return -8;
	}

	return 0;
}

int utf8_byte__Test_Get_Data_Bit_Count(void){

	utf8_byte bytes[14];

	int expected_counts[14];

	int test_count = 14;

	int i = 0;

	bytes[0] = 0x00;
	expected_counts[0] = 7;

	bytes[1] = 0x7F;
	expected_counts[1] = 7;

	bytes[2] = 0x80;
	expected_counts[2] = 6;

	bytes[3] = 0xBF;
	expected_counts[3] = 6;

	bytes[4] = 0xC0;
	expected_counts[4] = 5;

	bytes[5] = 0xDF;
	expected_counts[5] = 5;

	bytes[6] = 0xE0;
	expected_counts[6] = 4;

	bytes[7] = 0xEF;
	expected_counts[7] = 4;

	bytes[8] = 0xF0;
	expected_counts[8] = 3;

	bytes[9] = 0xF7;
	expected_counts[9] = 3;

	bytes[10] = 0xF8;
	expected_counts[10] = 2;

	bytes[11] = 0xFB;
	expected_counts[11] = 2;

	bytes[12] = 0xFC;
	expected_counts[12] = 1;

	bytes[13] = 0xFD;
	expected_counts[13] = 1;

	for (i = 0; i < test_count; i++){

		int actual_count = utf8_byte_Get_Data_Bit_Count(bytes[i]);
		if (actual_count < 0){
			fprintf(stderr, "on byte[%d]:\n", i);
			fprintf(stderr, "\tutf8_byte_Get_Data_Bit_Count failed\n");
			return -1;
		}

		if (actual_count != expected_counts[i]){
			fprintf(stderr, "on byte[%d]:\n", i);
			fprintf(stderr, "\texpected count: %d\n", expected_counts[i]);
			fprintf(stderr, "\tactual count:   %d\n", actual_count);
			return -2;
		}
	}

	return 0;
}

int utf8_byte__Test_Get_Data__Fail(utf8_byte test_byte, int data_expected);

int utf8_byte__Test_Get_Data(void){

	if (utf8_byte_Get_Data(0x00) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0x00, 0x00);
	}

	if (utf8_byte_Get_Data(0x7F) != 0x7F){
		return utf8_byte__Test_Get_Data__Fail(0x7F, 0x7F);
	}

	if (utf8_byte_Get_Data(0x80) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0x80, 0x00);
	}

	if (utf8_byte_Get_Data(0xBF) != 0x3F){
		return utf8_byte__Test_Get_Data__Fail(0xBF, 0x3F);
	}

	if (utf8_byte_Get_Data(0xC0) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0xC0, 0x00);
	}

	if (utf8_byte_Get_Data(0xDF) != 0x1F){
		return utf8_byte__Test_Get_Data__Fail(0xDF, 0x1F);
	}

	if (utf8_byte_Get_Data(0xE0) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0xE0, 0x00);
	}

	if (utf8_byte_Get_Data(0xEF) != 0x0F){
		return utf8_byte__Test_Get_Data__Fail(0xEF, 0x0F);
	}

	if (utf8_byte_Get_Data(0xF0) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0xF0, 0x00);
	}

	if (utf8_byte_Get_Data(0xF7) != 0x07){
		return utf8_byte__Test_Get_Data__Fail(0xF7, 0x07);
	}

	if (utf8_byte_Get_Data(0xF8) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0xF8, 0x00);
	}

	if (utf8_byte_Get_Data(0xFB) != 0x03){
		return utf8_byte__Test_Get_Data__Fail(0xFB, 0x03);
	}

	if (utf8_byte_Get_Data(0xFC) != 0x00){
		return utf8_byte__Test_Get_Data__Fail(0xFC, 0x00);
	}

	if (utf8_byte_Get_Data(0xFD) != 0x01){
		return utf8_byte__Test_Get_Data__Fail(0xFD, 0x01);
	}

	return 0;
}

int utf8_byte__Test_Get_Data__Fail(utf8_byte test_byte, int data_expected){
	fprintf(stderr, "utf8_byte__Test_Get_Data failed on byte '%X':\n", test_byte);
	fprintf(stderr, "expected data: %X\n", data_expected);
	fprintf(stderr, "actual data:   %X\n", utf8_byte_Get_Data(test_byte));
	return -1;
}

