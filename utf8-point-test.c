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

#include "utf8-point.h"

#include <stdio.h>
#include <stdlib.h>

int utf8_point__Test_Get_Span(void);

int main(void){

	if (utf8_point__Test_Get_Span() < 0){
		fprintf(stderr, "Get_Span test failed\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int utf8_point__Test_Get_Span(void){

	/* range 0xxx xxxx */
	/* min   0000 0000 */
	/* mid   0011 1111 */
	/* max   0111 1111 */

	if (utf8_point_Get_Span(0x00) != 1){
		fprintf(stderr, "point span of 0x00 should be 1\n");
		return -1;
	}

	if (utf8_point_Get_Span(0x0F) != 1){
		fprintf(stderr, "point span of 0x0F should be 1\n");
		return -2;
	}

	if (utf8_point_Get_Span(0x7F) != 1){
		fprintf(stderr, "point span of 0x7F should be 1\n");
		return -3;
	}

	/* range 110x xxxx */
	/* min   1100 0000 */
	/* mid   1100 1111 */
	/* max   1101 1111 */

	if (utf8_point_Get_Span(0xC0) != 2){
		fprintf(stderr, "point span of 0xC0 should be 2\n");
		return -4;
	}

	if (utf8_point_Get_Span(0xCF) != 2){
		fprintf(stderr, "point span of 0xCF should be 2\n");
		return -5;
	}

	if (utf8_point_Get_Span(0xDF) != 2){
		fprintf(stderr, "point span of 0xDF should be 2\n");
		return -6;
	}

	/* range 1110 xxxx */
	/* min   1110 0000 */
	/* mid   1110 0111 */
	/* max   1110 1111 */

	if (utf8_point_Get_Span(0xE0) != 3){
		fprintf(stderr, "point span of 0xE0 should be 3\n");
		return -7;
	}

	if (utf8_point_Get_Span(0xE7) != 3){
		fprintf(stderr, "point span of 0xE7 should be 3\n");
		return -8;
	}

	if (utf8_point_Get_Span(0xEF) != 3){
		fprintf(stderr, "point span of 0xEF should be 3\n");
		return -9;
	}

	/* range 1111 0xxx */
	/* min   1111 0000 */
	/* mid   1111 0011 */
	/* max   1111 0111 */

	if (utf8_point_Get_Span(0xF0) != 4){
		fprintf(stderr, "point span of 0xF0 should be 4\n");
		return -7;
	}

	if (utf8_point_Get_Span(0xF3) != 4){
		fprintf(stderr, "point span of 0xF3 should be 4\n");
		return -8;
	}

	if (utf8_point_Get_Span(0xF7) != 4){
		fprintf(stderr, "point span of 0xF7 should be 4\n");
		return -9;
	}

	/* range 1111 10xx */
	/* min   1111 1000 */
	/* mid   1111 1001 */
	/* max   1111 1011 */

	if (utf8_point_Get_Span(0xF8) != 5){
		fprintf(stderr, "point span of 0xF8 should be 5\n");
		return -7;
	}

	if (utf8_point_Get_Span(0xF9) != 5){
		fprintf(stderr, "point span of 0xF9 should be 5\n");
		return -8;
	}

	if (utf8_point_Get_Span(0xFB) != 5){
		fprintf(stderr, "point span of 0xFB should be 5\n");
		return -9;
	}

	/* range 1111 110x */
	/* min   1111 1100 */
	/* mid   n/a       */
	/* max   1111 1101 */

	if (utf8_point_Get_Span(0xFC) != 6){
		fprintf(stderr, "point span of 0xFC should be 6\n");
		return -7;
	}

	if (utf8_point_Get_Span(0xFD) != 6){
		fprintf(stderr, "point span of 0xFD should be 6\n");
		return -8;
	}

	return 0;
}

