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

int utf8_point_Get_Span(utf8_point point){

	if (point <= 0x7F){
		return 1;
	}

	if ((point >= 0xC0) && (point <= 0xDF)){
		return 2;
	}

	if ((point >= 0xE0) && (point <= 0xEF)){
		return 3;
	}

	if ((point >= 0xF0) && (point <= 0xF7)){
		return 4;
	}

	if ((point >= 0xF8) && (point <= 0xFB)){
		return 5;
	}

	if ((point >= 0xFC) && (point <= 0xFD)){
		return 6;
	}

	return -1;
}

