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

#ifndef UTF8_STRING_UTF8_STRING_H
#define UTF8_STRING_UTF8_STRING_H

#include "utf8-byte.h"

typedef struct utf8_string {
	utf8_byte * byte_array;
	int byte_count;
} utf8_string;

int utf8_string_Init(utf8_string * str);

void utf8_string_Done(utf8_string * str);

utf8_byte utf8_string_Get_Point(utf8_string * str, int i);

int utf8_string_Get_Point_Span(utf8_string * str, int i);

#endif /* UTF8_STRING_UTF8_POINT_H */

