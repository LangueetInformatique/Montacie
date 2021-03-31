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

/**@file string_format.h
* @brief To and from std::string conversions for C++ built-in data types.
*
*/

// string_format.h

#ifndef _STRING_FORMAT_H_INCLUDED_
#define _STRING_FORMAT_H_INCLUDED_

#include <sstream>
#include <string>

#ifndef CTTL_STD_STRING
#   define CTTL_STD_STRING std::string
#endif // CTTL_STD_STRING

#ifndef CTTL_STD_CHAR
#   define CTTL_STD_CHAR   CTTL_STD_STRING::value_type
#endif // CTTL_STD_CHAR

namespace cttl {

    /**Converts C++ floating-point type to string.
    *
    * @tparam SourceT
    *        specifies floating-point type.
    *
    * @tparam FormatT
    *        specifies STL stream manipulator, usually
    *        a function pointer:
    @code
    std::ios_base& ( *ios_base_ ) ( std::ios_base& ).
    @endcode
    *
    * @param source_
    *        constant reference to C++ object representing
    *        floating-point input variable to convert to STL string.
    *
    * @param precision_
    *        an integer specifying desired precision.
    *
    * @param ios_base_
    *        STL stream manipulator, such as 
    @code
    std::showpoint  (always show floating point)
    std::scientific (e.g. 1.234568e+003)
    std::fixed      (no exponent field)
    etc.
    @endcode
    *
    * @return
    *        std::string that contains result of the conversion.
    *
    */
    template< typename SourceT, typename FormatT >
    CTTL_STD_STRING type2string( SourceT const& source_, FormatT* ios_base_, int precision_ )
    {
        std::basic_stringstream< CTTL_STD_CHAR > stream_;
        stream_.precision( precision_ );
        stream_ << ios_base_ << source_;
        return stream_.str();
    }

    /**Converts C++ type to string.
    *
    * @tparam SourceT
    *        specifies input variable type.
    *
    * @tparam FormatT
    *        specifies STL stream manipulator, usually
    *        a function pointer:
    @code
    std::ios_base& ( *ios_base_ ) ( std::ios_base& ).
    @endcode
    *
    * @param source_
    *        constant reference to C++ object representing
    *        input variable to convert to STL string.
    *
    * @param ios_base_
    *        STL stream manipulator, such as 
    @code
    std::dec (base ten)
    std::hex (hexidecimal, base 16)
    std::oct (octal, base 8)
    etc.
    @endcode
    *
    * @return
    *        std::string that contains result od the conversion.
    *
    */
    template< typename SourceT, typename FormatT >
    CTTL_STD_STRING type2string( SourceT const& source_, FormatT* ios_base_ )
    {
        std::basic_stringstream< CTTL_STD_CHAR > stream_;
        stream_ << ios_base_ << source_;
        return stream_.str();
    }

    /**Converts C++ type to string.
    *
    * @tparam SourceT
    *        specifies input variable type.
    *
    * @param source_
    *        constant reference to C++ object representing
    *        input variable to convert to STL string.
    *
    * @return
    *        std::string that contains result od the conversion.
    *
    */
    template< typename SourceT >
    CTTL_STD_STRING type2string( SourceT const& source_ )
    {
        std::basic_stringstream< CTTL_STD_CHAR > stream_;
        stream_ << source_;
        return stream_.str();
    }

    /**Converts STL string to C++ type.
    *
    * @tparam TargetT
    *        specifies output variable type.
    *
    * @tparam FormatT
    *        specifies STL stream manipulator, usually
    *        a function pointer:
    @code
    std::ios_base& ( *ios_base_ ) ( std::ios_base& ).
    @endcode
    *
    * @param source_
    *        Input string with textual representation of the
    *        source value, such as 1234.56789, true, 0xFF, etc.
    *
    * @param target_
    *        reference to C++ object representing
    *        output variable to receive the result of conversion.
    *
    * @param ios_base_
    *        STL stream manipulator, such as 
    @code
    std::dec (base ten)
    std::hex (hexidecimal, base 16)
    std::oct (octal, base 8)
    etc.
    @endcode
    *
    * @remarks
    *        If conversion fails, target_ may receive a garbage value,
    *        which should be discarded.
    *
    * @return
    *        Boolean result of the conversion, true if successful,
    *        false otherwise.
    *
    */
    template< typename TargetT, typename FormatT >
    bool string2type(
        CTTL_STD_STRING const& source_, 
        TargetT& target_, 
        FormatT* ios_base_
        )
    {
        std::istringstream iss( source_ );
        return !( iss >> ios_base_ >> target_ ).fail();
    }

    /**Converts STL string to C++ type.
    *
    * @tparam TargetT
    *        specifies output variable type.
    *
    * @param source_
    *        Input string with textual representation of the
    *        input value, such as 12345.
    *
    * @param target_
    *        reference to C++ object representing
    *        output variable to receive the result of conversion.
    *
    * @remarks
    *        If conversion fails, target_ may receive a garbage value,
    *        which should be discarded.
    *
    * @return
    *        Boolean result of the conversion, true if successful,
    *        false otherwise.
    *
    */
    template< typename TargetT >
    bool string2type(
        CTTL_STD_STRING const& source_, 
        TargetT& target_
        )
    {
        std::istringstream iss( source_ );
        return !( iss >> target_ ).fail();
    }

} //namespace cttl

#endif // _STRING_FORMAT_H_INCLUDED_
