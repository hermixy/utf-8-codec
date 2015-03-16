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
#include "utf8-closed-intervals.h"

int utf8_point_Get_Span(utf8_point point){

	if ((point >= utf8_closed_intervals[0][0]) && (point <= utf8_closed_intervals[0][1])){
		return 1;
	}

	/* skip interval[1], which does not indicate a span */

	if ((point >= utf8_closed_intervals[2][0]) && (point <= utf8_closed_intervals[2][1])){
		return 2;
	}

	if ((point >= utf8_closed_intervals[3][0]) && (point <= utf8_closed_intervals[3][1])){
		return 3;
	}

	if ((point >= utf8_closed_intervals[4][0]) && (point <= utf8_closed_intervals[4][1])){
		return 4;
	}

	if ((point >= utf8_closed_intervals[5][0]) && (point <= utf8_closed_intervals[5][1])){
		return 5;
	}

	if ((point >= utf8_closed_intervals[6][0]) && (point <= utf8_closed_intervals[6][1])){
		return 6;
	}

	return -1;
}

int utf8_point_Get_Data(utf8_point point){

	int data_mask = 0;

	int data_bit_count = utf8_point_Get_Data_Bit_Count(point);
	if (data_bit_count < 0){
		return -1;
	}

	data_mask = (1 << (data_bit_count + 1)) - 1;

	return point & data_mask;
}

int utf8_point_Get_Data_Bit_Count(utf8_point point){

	if ((point >= utf8_closed_intervals[0][0]) && (point <= utf8_closed_intervals[0][1])){
		return 7;
	}

	if ((point >= utf8_closed_intervals[1][0]) && (point <= utf8_closed_intervals[1][1])){
		return 6;
	}

	if ((point >= utf8_closed_intervals[2][0]) && (point <= utf8_closed_intervals[2][1])){
		return 5;
	}

	if ((point >= utf8_closed_intervals[3][0]) && (point <= utf8_closed_intervals[3][1])){
		return 4;
	}

	if ((point >= utf8_closed_intervals[4][0]) && (point <= utf8_closed_intervals[4][1])){
		return 3;
	}

	if ((point >= utf8_closed_intervals[5][0]) && (point <= utf8_closed_intervals[5][1])){
		return 2;
	}

	if ((point >= utf8_closed_intervals[6][0]) && (point <= utf8_closed_intervals[6][1])){
		return 1;
	}

	return -1;
}


