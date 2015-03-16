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

utf8_point utf8_sequence_Decode(utf8_sequence * sequence){

	int byte_index = 0;

	utf8_point c = 0;

	int byte_count = utf8_byte_Get_Span(sequence->byte_array[0]);
	if (byte_count < 0){
		return -1;
	}

	for (byte_index = 0; byte_index < byte_count; byte_index++){

		int byte_bit_count = 0;

		int byte_data = utf8_byte_Get_Data(sequence->byte_array[byte_index]);
		if (byte_data < 0){
			return -1;
		}

		byte_bit_count = utf8_byte_Get_Data_Bit_Count(sequence->byte_array[byte_index]);
		if (byte_bit_count < 0){
			return -1;
		}

		c <<= byte_bit_count;
		c += byte_data;
	}

	return c;
}

int utf8_sequence_Encode(utf8_sequence * sequence, utf8_point c){

	memset(sequence, 0, sizeof(*sequence));

	if (c <= 0x7F){

		sequence->byte_array[0] = (utf8_byte) (c & 0x7F);
		return 1;

	} else if (c <= 0x07FF){

		sequence->byte_array[0] = (utf8_byte) (((c >> 0x06) & 0x1F) | 0xC0);
		sequence->byte_array[1] = (utf8_byte) (((c >> 0x00) & 0x3F) | 0x80);
		return 2;

	} else if (c <= 0xFFFF){

		sequence->byte_array[0] = (utf8_byte) (((c >> 0x0C) & 0x0F) | 0xE0);
		sequence->byte_array[1] = (utf8_byte) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->byte_array[2] = (utf8_byte) (((c >> 0x00) & 0x3F) | 0x80);
		return 3;

	} else if (c <= 0x1FFFFF){

		sequence->byte_array[0] = (utf8_byte) (((c >> 0x12) & 0x07) | 0xF0);
		sequence->byte_array[1] = (utf8_byte) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->byte_array[2] = (utf8_byte) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->byte_array[3] = (utf8_byte) (((c >> 0x00) & 0x3F) | 0x80);
		return 4;

	} else if (c <= 0x3FFFFFF){

		sequence->byte_array[0] = (utf8_byte) (((c >> 0x18) & 0x03) | 0xF8);
		sequence->byte_array[1] = (utf8_byte) (((c >> 0x12) & 0x3F) | 0x80);
		sequence->byte_array[2] = (utf8_byte) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->byte_array[3] = (utf8_byte) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->byte_array[4] = (utf8_byte) (((c >> 0x00) & 0x3F) | 0x80);
		return 5;

	} else if (c <= 0x7FFFFFFF){

		sequence->byte_array[0] = (utf8_byte) (((c >> 0x1E) & 0x01) | 0xFC);
		sequence->byte_array[1] = (utf8_byte) (((c >> 0x18) & 0x3F) | 0x80);
		sequence->byte_array[2] = (utf8_byte) (((c >> 0x12) & 0x3F) | 0x80);
		sequence->byte_array[3] = (utf8_byte) (((c >> 0x0C) & 0x3F) | 0x80);
		sequence->byte_array[4] = (utf8_byte) (((c >> 0x06) & 0x3F) | 0x80);
		sequence->byte_array[5] = (utf8_byte) (((c >> 0x00) & 0x3F) | 0x80);
		return 6;
	}

	/* should be unreachable, but would
	 * otherwise indicate an invalid range */
	return -1;
}

