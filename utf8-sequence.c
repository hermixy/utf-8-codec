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

#include <string.h>

int utf8_sequence_Init(utf8_sequence * sequence){
	memset(sequence, 0, sizeof(*sequence));
	return 0;
}

void utf8_sequence_Done(utf8_sequence * sequence){
	memset(sequence, 0, sizeof(*sequence));
}

utf8_char utf8_sequence_Decode(utf8_sequence * sequence){

	int point_index = 0;

	utf8_char c = 0;

	int point_count = utf8_point_Get_Span(sequence->point_array[0]);
	if (point_count < 0){
		return -1;
	}

	for (point_index = 0; point_index < point_count; point_index++){

		int point_bit_count = 0;

		int point_data = utf8_point_Get_Data(sequence->point_array[point_index]);
		if (point_data < 0){
			return -1;
		}

		point_bit_count = utf8_point_Get_Data_Bit_Count(sequence->point_array[point_index]);
		if (point_bit_count < 0){
			return -1;
		}

		c <<= point_bit_count;
		c += point_data;
	}

	return c;
}

int utf8_sequence_Encode(utf8_sequence * sequence, utf8_char c){

	memset(sequence, 0, sizeof(*sequence));

	if (c <= 0x7F){

		sequence->point_array[0] = (utf8_point) (c & 0x7F);
		return 1;

	} else if (c <= 0x07FF){

		sequence->point_array[0] = (utf8_point) (((c >> 0x06) & 0x1F) | 0xC0);
		sequence->point_array[1] = (utf8_point) (((c >> 0x00) & 0x3F) | 0x80);
		return 2;

	} else if (c <= 0xFFFF){

		sequence->point_array[0] = (utf8_point) (((c >> 0x0C) & 0x0F) | 0xE0);
		sequence->point_array[1] = (utf8_point) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->point_array[2] = (utf8_point) (((c >> 0x00) & 0x3F) | 0x80);
		return 3;

	} else if (c <= 0x1FFFFF){

		sequence->point_array[0] = (utf8_point) (((c >> 0x12) & 0x07) | 0xF0);
		sequence->point_array[1] = (utf8_point) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->point_array[2] = (utf8_point) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->point_array[3] = (utf8_point) (((c >> 0x00) & 0x3F) | 0x80);
		return 4;

	} else if (c <= 0x3FFFFFF){

		sequence->point_array[0] = (utf8_point) (((c >> 0x18) & 0x03) | 0xF8);
		sequence->point_array[1] = (utf8_point) (((c >> 0x12) & 0x3F) | 0x80);
		sequence->point_array[2] = (utf8_point) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->point_array[3] = (utf8_point) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->point_array[4] = (utf8_point) (((c >> 0x00) & 0x3F) | 0x80);
		return 5;

	} else if (c <= 0x7FFFFFFF){

		sequence->point_array[0] = (utf8_point) (((c >> 0x1E) & 0x01) | 0xFC);
		sequence->point_array[1] = (utf8_point) (((c >> 0x18) & 0x3F) | 0x80);
		sequence->point_array[2] = (utf8_point) (((c >> 0x12) & 0x3F) | 0x80);
		sequence->point_array[3] = (utf8_point) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->point_array[4] = (utf8_point) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->point_array[5] = (utf8_point) (((c >> 0x00) & 0x3F) | 0x80);
		return 6;
	}

	/* should be unreachable, but would
	 * otherwise indicate an invalid range */
	return -1;
}

