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

/**@file coreutils.h
* @brief Defines core string utility functions for CTTL library.
*
*  @see
*  - cttl::string_toupper()
*  - cttl::string_tolower()
*  - cttl::string_array2string()
*/

// coreutils.h: string utility functions

#ifndef _CTTL_COREUTILS_H_INCLUDED_
#define _CTTL_COREUTILS_H_INCLUDED_

#include <cassert>
#include <algorithm>
#include <ctype.h>

namespace cttl {

    /**Converts string to UPPERCASE. */
    template< typename StringT >
    inline void
        string_toupper( StringT& str_ )
    {
        std::transform( str_.begin(), str_.end(), str_.begin(), toupper );
    }

    /**Converts string to lowercase.*/
    template< typename StringT >
    inline void
        string_tolower( StringT& str_ )
    {
        std::transform( str_.begin(), str_.end(), str_.begin(), tolower );

    }

    /**Loads text from array of string literals into a string provided by the user.
    *
    * @tparam StringT
    *        specifies type of the string.
    *
    * @tparam CharT
    *        specifies character type.
    *
    * @param str_
    *        reference to the target string.
    *
    * @param array_
    *        source array of string literals.
    *
    * @param delimiter_
    *        a multi-character delimiter to be inserted between source text fragments.
    *
    * @pre
    *        Array should have trailing @c NULL string, for example,
    *        @n <tt>char const* arr[] = { "abc", "def", NULL };</tt>
    *
    */
    template< typename StringT, typename CharT >
    inline void
        string_array2string( StringT& str_, CharT const* const* array_, CharT const* delimiter_ )
    {
        assert( array_ );
        if ( !*array_ ) {
            str_.clear();
            return;
        }
        str_ = *array_++;

        while ( *array_ ) {
            if ( delimiter_ )
                str_ += delimiter_;
            str_ += *array_++;
        }
    }

    /**Loads text from array of string literals into a string provided by the user.
    *
    * @tparam StringT
    *        specifies type of the string.
    *
    * @tparam CharT
    *        specifies character type.
    *
    * @param str_
    *        reference to the target string.
    *
    * @param array_
    *        source array of string literals.
    *
    * @pre
    *        Array should have trailing @c NULL string, for example,
    *        @n <tt>char const* arr[] = { "abc", "def", NULL };</tt>
    *
    */
    template< typename StringT, typename CharT >
    inline void
        string_array2string( StringT& str_, CharT const* const* array_ )
    {
        static const CharT delimiter[] = { CharT( '\t' ), 0x00 };
        string_array2string( str_, array_, delimiter );
    }

    /**Loads text from array of string literals into a string provided by the user.
    *
    * @tparam StringT
    *        specifies type of the string.
    *
    * @tparam CharT
    *        specifies character type.
    *
    * @param str_
    *        reference to the target string.
    *
    * @param array_
    *        source array of string literals.
    *
    * @param delimiter_
    *        a single-character delimiter to be inserted between source text fragments.
    *
    * @pre
    *        Array should have trailing @c NULL string, for example,
    *        @n <tt>char const* arr[] = { "abc", "def", NULL };</tt>
    *
    */
    template< typename StringT, typename CharT >
    inline void
        string_array2string( StringT& str_, CharT const* const* array_, CharT delimiter_ )
    {
        const CharT delimiter[] = { delimiter_, 0x00 };
        string_array2string( str_, array_, delimiter );
    }

}   // namespace cttl


#endif //_CTTL_COREUTILS_H_INCLUDED_
