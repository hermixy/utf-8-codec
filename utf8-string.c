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

#include <stdlib.h>

int utf8_string_Init(utf8_string * str){
	str->byte_array = NULL;
	str->byte_count = 0;
	return 0;
}

void utf8_string_Done(utf8_string * str){
	if (str){
		free(str->byte_array);
		str->byte_array = NULL;
		str->byte_count = 0;
	}
}

int utf8_string_Get_Byte(utf8_string * str, int i, utf8_byte * byte){
	if (i >= str->byte_count){
		return -1;
	}

	*byte = str->byte_array[i];

	return i;
}

int utf8_string_Get_Byte_Span(utf8_string * str, int i){

	int byte_span = utf8_byte_Get_Span(str->byte_array[i]);
	if (byte_span < 0){
		return -1;
	}

	return byte_span;
}

int utf8_string_Get_Sequence(utf8_string * str, int i_point_req, utf8_sequence * sequence){

	int i_byte = 0;
	int i_point = 0;

	int byte_span = 0;

	for (;;){

		if (i_point == i_point_req){
			break;
		}

		byte_span = utf8_byte_Get_Span(str->byte_array[i_byte]);
		if (byte_span < 0){
			return -1;
		}

		i_byte += byte_span;

		if (i_byte >= str->byte_count){
			break;
		}

		i_point++;
	}

	if (i_byte >= str->byte_count){
		return -1;
	}

	byte_span = utf8_byte_Get_Span(str->byte_array[i_byte]);
	if (byte_span < 0){
		return -3;
	}

	for (;;){

		sequence->byte_array[byte_span - 1] = str->byte_array[i_byte + (byte_span - 1)];

		if (--byte_span <= 0){
			break;
		}
	}

	return 0;
}

int utf8_string_Get_Point(utf8_string * str, int i, utf8_point * point){

	utf8_sequence point_sequence;

	if (utf8_sequence_Init(&point_sequence) < 0){
		return -1;
	}

	if (utf8_string_Get_Sequence(str, i, &point_sequence) < 0){
		return -2;
	}

	if (utf8_sequence_Decode(&point_sequence, point) < 0){
		return -3;
	}

	return 0;
}

