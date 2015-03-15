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

int utf8_string__Test_Get_Point(void);

int utf8_string__Test_Get_Point_Span(void);

int main(void){

	if (utf8_string__Test_Init() != 0){
		fprintf(stderr, "Init test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_string__Test_Done() != 0){
		fprintf(stderr, "Done test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_string__Test_Get_Point() != 0){
		fprintf(stderr, "Get_Point test failed\n");
		return EXIT_FAILURE;
	}

	if (utf8_string__Test_Get_Point_Span() != 0){
		fprintf(stderr, "Get_Point_Span test failed\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int utf8_string__Test_Init(void){

	utf8_string string;

	if (utf8_string_Init(&string) < 0){
		fprintf(stderr, "string initialization failed\n");
		return -1;
	}

	if (string.point_array != NULL){
		fprintf(stderr, "string.point_array should be NULL after initialization\n");
		return -2;
	}

	if (string.point_count != 0){
		fprintf(stderr, "string.point_count should be 0 after initialization\n");
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

	string.point_array = malloc(sizeof(utf8_point));
	if (!string.point_array){
		fprintf(stderr, "failed to malloc point for test\n");
		return -2;
	}
	string.point_count = 1;

	utf8_string_Done(&string);

	if (string.point_array != NULL){
		fprintf(stderr, "point_array is not NULL after utf8_string_Done\n");
		return -3;
	}

	if (string.point_count != 0){
		fprintf(stderr, "point_count is not 0 after utf8_string_Done\n");
		return -4;
	}

	return 0;
}

int utf8_string__Test_Get_Point(void){

	utf8_point point_array[3];

	utf8_string string;

	int i = 0;

	point_array[0] = 0x01;
	point_array[1] = 0x03;
	point_array[2] = 0x05;

	string.point_array = point_array;
	string.point_count = 3;

	for (i = 0; i < 3; i++){
		if (utf8_string_Get_Point(&string, i) != point_array[i]){
			fprintf(stderr, "point[%d] value is different\n", i);
			return -1;
		}
	}

	return 0;
}

int utf8_string__Test_Get_Point_Span(void){

	utf8_point point_array[3];

	utf8_string string;

	int i = 0;

	point_array[0] = 0x01;
	point_array[1] = 0xC0;
	point_array[2] = 0xFE;

	string.point_array = point_array;
	string.point_count = 3;

	for (i = 0; i < 3; i++){
		if (utf8_string_Get_Point_Span(&string, i) != utf8_point_Get_Span(point_array[i])){
			fprintf(stderr, "point[%d] span is different\n", i);
			return -1;
		}
	}

	return 0;
}

