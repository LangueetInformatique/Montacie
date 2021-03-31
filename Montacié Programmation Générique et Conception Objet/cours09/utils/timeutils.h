////////////////////////////////////////////////////////////////////////
// Common Text Transformation Library
// Copyright (C) 1997-2006 by Igor Kholodov. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// mailto:cttl@users.sourceforge.net
// http://sourceforge.net/projects/cttl/
////////////////////////////////////////////////////////////////////////

/**@file timeutils.h
 * @brief Rudimentary functions to handle time.
 *
 */

// timeutils.h

#ifndef _CTTL_TIMEUTILS_H_INCLUDED_
#define _CTTL_TIMEUTILS_H_INCLUDED_

#include <string.h>

/* Use the following defines to suppress microsoft deprecation warnings:
#ifdef _WIN32
    // suppress windows platform deprecation warnings:
#   ifndef _CRT_SECURE_NO_DEPRECATE
#   define _CRT_SECURE_NO_DEPRECATE
#   endif // _CRT_SECURE_NO_DEPRECATE
#endif // _WIN32
*/

#include <ctime>
#include <string>

namespace cttl {

/**Returns current time.*/
inline
time_t current_time()
{
    return time( NULL );
}

/**Converts time_t to string.*/
inline
CTTL_STD_STRING time2string( time_t time_ )
{
    CTTL_STD_CHAR* ptime = reinterpret_cast< CTTL_STD_CHAR* >( ctime( &time_ ) );  // get rid of the trailing \n
    return CTTL_STD_STRING( ptime, strlen( reinterpret_cast< char const* >( ptime ) ) - 1 );
}

}//namespace cttl


#endif // _CTTL_TIMEUTILS_H_INCLUDED_
