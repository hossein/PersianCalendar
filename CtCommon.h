/******************************************************************************

Persian Calendar, simple Persian calendar
Copyright (C) 2014 GitHub user "Hossein"

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#pragma once
#include <QString>

//Avoid to...Double function being searched as to...do by me!
//#define Ct_To_Double(ARG) to##Double(ARG)
//Helper Defines
//USE THIS FOR EVERY PIECE OF UNICODE STRING YOU WRITE IN SOURCE CODE!
#define u(constchararray) QString::fromUtf8(constchararray)
