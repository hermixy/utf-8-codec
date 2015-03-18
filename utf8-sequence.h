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

#ifndef UTF8_SEQUENCE_H
#define UTF8_SEQUENCE_H

#include "utf8-point.h"
#include "utf8-byte.h"

#define UTF8_SEQUENCE_POINT_MAX 6

typedef struct utf8_sequence {
	utf8_byte byte_array[UTF8_SEQUENCE_POINT_MAX];
} utf8_sequence;

int utf8_sequence_Init(utf8_sequence * sequence);

void utf8_sequence_Done(utf8_sequence * sequence);

int utf8_sequence_Decode(const utf8_sequence * sequence, utf8_point * c);

int utf8_sequence_Encode(utf8_sequence * sequence, utf8_point c);

#endif /* UTF8_SEQUENCE_H */

