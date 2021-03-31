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

/**@file itos.h
 * @brief Defines helper function to convert
 *        C++ built-in data types to std::string.
 *
 */

// itos.h

#ifndef _CTTL_ITOS_H_INCLUDED_
#define _CTTL_ITOS_H_INCLUDED_

#include "string_format.h"

namespace cttl {

    /**Converts C++ built-in data types to std::string.
    *
    * For example,
    @code
    int i = 127;
    std::string ss = itos( i );
    @endcode
    *
    */
    template< typename SourceT >
    CTTL_STD_STRING itos( SourceT source_ )
    {
        return type2string( source_ );
    }

}   // namespace cttl

#endif // _CTTL_ITOS_H_INCLUDED_
