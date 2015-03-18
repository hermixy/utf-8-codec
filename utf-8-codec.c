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

int utf_8_codec_Calculate_Length_Decoded(unsigned char in){

	if (in < 0x80){
		return 1;
	} else if (in < 0xC0){
		return 2;
	} else if (in < 0xE0){
		return 3;
	} else if (in < 0xF0){
		return 4;
	}

	/* out of range */
	return -1;
}

int utf_8_codec_Calculate_Length_Encoded(signed long int in){
	(void) in;
	return 0;
}

int utf_8_codec_Decode(unsigned char * in, long int * out){

	if (in[0] < 0x80){

		*out = 0x7F & in[0];

	} else if (in[0] < 0xC0){

		*out = (0x1F & in[0]) << 0x06;
		*out += 0x3F & in[1];

	} else if (in[0] < 0xE0){

		*out = (0x0F & in[0]) << 0x0C;
		*out += (0x3F & in[1]) << 0x06;
		*out += 0x3F & in[2];

	} else if (in[0] < 0xF0){

		*out = (0x07 & in[0]) << 0x13;
		*out += (0x3F & in[1]) << 0x0C;
		*out += (0x3F & in[2]) << 0x06;
		*out += 0x3F & in[3];

	} else {
		/* out of range */
		return -1;
	}

	return 0;
}

int utf_8_codec_Encode(unsigned char * out, long int in){
	(void) out;
	(void) in;
	return 0;
}

