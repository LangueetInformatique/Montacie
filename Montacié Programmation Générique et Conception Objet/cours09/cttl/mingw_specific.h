////////////////////////////////////////////////////////////////////////
//
// This file is part of Common Text Transformation Library.
// Copyright (C) 1997-2009 by Igor Kholodov. 
//
// Common Text Transformation Library is free software: you can
// redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Common Text Transformation Library is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Common Text Transformation Library.
// If not, see <http://www.gnu.org/licenses/>.
//
// mailto:cttl@users.sourceforge.net
// http://cttl.sourceforge.net/
// http://sourceforge.net/projects/cttl/
//
////////////////////////////////////////////////////////////////////////

/**@file mingw_specific.h
 * @brief MinGW 3.2 missing wide character support workaround.
 *
 * Include this file in cttl.h header to avoid errors related to
 * bug [ 664369 ] Missing wide character support in MinGW 3.2.
 * 
 * A very simple example yeilds the following error:
 * 
 * @code
#include <string>

int main()
{
    std::wstring TestString;
    return 0;
}

main.cpp: undefined reference to
`std::basic_string<wchar_t, std::char_traits<wchar_t>,
...
@endcode
*
*/


#ifndef _CTTL_MINGW_SPECIFIC_H_INCLUDED_
#define _CTTL_MINGW_SPECIFIC_H_INCLUDED_

#ifdef __MINGW32__
#   if ( __MINGW32_MAJOR_VERSION > 2 && __MINGW32_MINOR_VERSION < 3 && __GNUC__ == 3 && __GNUC_MINOR__ == 2 )

        namespace std {

            struct wstring {
                typedef wchar_t value_type;

                wstring( const wchar_t* )
                {
                }

            }; // struct wstring

        } // namespace std

#   endif // __MINGW32_MAJOR_VERSION > 2 && __MINGW32_MINOR_VERSION < 3
#endif // __MINGW32__

#endif // _CTTL_MINGW_SPECIFIC_H_INCLUDED_
