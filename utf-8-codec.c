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

/** @file */

#include "utf-8-codec.h"

/** Calculate the expected length of a utf-8 sequence
 * based on the first byte in the sequence.
 * @param in The first byte in the utf-8 sequence.
 * @return The length of the utf-8 sequence, including the first byte.
 * If an error occurs, -1 is returned.
 * */

int utf_8_codec_Calculate_Length_Decoded(unsigned char in){

	if (in < 0x80){
		return 1;
	} else if (in < 0xE0){
		return 2;
	} else if (in < 0xF0){
		return 3;
	} else if (in < 0xF8){
		return 4;
	}

	/* out of range */
	return -1;
}

/** Calculate what the sequence length would be of a 32 bit character.
 * @param in A 32 bit character.
 * @return The length of what the encoded sequence would be.
 * If an error occurs, -1 is returned.
 * */

int utf_8_codec_Calculate_Length_Encoded(signed long int in){

	if (in < 0x80){
		return 1;
	} else if (in < 0x800){
		return 2;
	} else if (in < 0x010000){
		return 3;
	} else if (in < 0x110000){
		return 4;
	}

	/* out of range */
	return -1;
}

/** Decode a utf-8 sequence.
 * 
 * @param in A buffer containing a utf-8 sequence.
 * The size of the buffer is calculated by the first byte in the sequence.
 *
 * @param out A pointer to at least a 32 bit data type to store the result.
 *
 * @return The amount of bytes in the sequence that were decoded.
 * If an error occurs, -1 is returned.
 * */

int utf_8_codec_Decode(const unsigned char * in, long int * out){

	if (in[0] <= 0x7F){
		*out = 0x7F & in[0];
		return 1;
	} else if (in[0] <= 0xDF){
		*out = (0x1F & in[0]) << 0x06;
		*out += 0x3F & in[1];
		return 2;
	} else if (in[0] <= 0xEF){
		*out = (0x0F & in[0]) << 0x0C;
		*out += (0x3F & in[1]) << 0x06;
		*out += 0x3F & in[2];
		return 3;
	} else if (in[0] <= 0xF7){
		*out = (0x07 & in[0]) << 0x12;
		*out += (0x3F & in[1]) << 0x0C;
		*out += (0x3F & in[2]) << 0x06;
		*out += 0x3F & in[3];
		return 4;
	}

	/* out of range */
	return -1;
}

/** Encode a utf-8 sequence.
 *
 * @param out A buffer where the result will be stored.
 * This buffer must be large enough to store the sequence.
 * The size may be calculated with utf_8_codec_Calculate_Length_Encoded().
 *
 * @param in The character to encode. Must be > 0 and < 0x110000.
 *
 * @return The amount of bytes written to the buffer. If an error occurs,
 * -1 is returned.
 * */

int utf_8_codec_Encode(unsigned char * out, long int in){

	if (in < 0x80){
		out[0] = (unsigned char) in;
		return 1;
	} else if (in < 0x0800){
		out[0] = (unsigned char) (((in >> 0x06) & 0x1F)) | 0xC0;
		out[1] = (unsigned char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 2;
	} else if (in < 0x010000){
		out[0] = (unsigned char) (((in >> 0x0C) & 0x0F)) | 0xE0;
		out[1] = (unsigned char) (((in >> 0x06) & 0x3F)) | 0x80;
		out[2] = (unsigned char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 3;
	} else if (in < 0x110000){
		out[0] = (unsigned char) (((in >> 0x12) & 0x07)) | 0xF0;
		out[1] = (unsigned char) (((in >> 0x0C) & 0x3F)) | 0x80;
		out[2] = (unsigned char) (((in >> 0x06) & 0x3F)) | 0x80;
		out[3] = (unsigned char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 4;
	}

	/* out of range */
	return -1;
}

