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

utf8_byte utf8_string_Get_Point(utf8_string * str, int i){
	return str->byte_array[i];
}

int utf8_string_Get_Point_Span(utf8_string * str, int i){

	int byte_span = utf8_byte_Get_Span(str->byte_array[i]);
	if (byte_span < 0){
		return -1;
	}

	return byte_span;
}

