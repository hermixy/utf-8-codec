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

#include "utf-8-closed-intervals.h"

const int utf8_closed_intervals[7][2] = {
	{ 0x00, 0x7F },
	{ 0x80, 0xBF }, /* note, this does not occur in the first byte of a sequence. */
	{ 0xC0, 0xDF },
	{ 0xE0, 0xEF },
	{ 0xF0, 0xF7 },
	{ 0xF8, 0xFB },
	{ 0xFC, 0xFD }
};
