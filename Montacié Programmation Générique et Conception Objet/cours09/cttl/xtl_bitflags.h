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

/**@file xtl_bitflags.h
* @brief Defines cttl_impl::xtl_bitflags class.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*/

#ifndef _CTTL_XTL_BITFLAGS_H_INCLUDED_
#define _CTTL_XTL_BITFLAGS_H_INCLUDED_

/**@namespace cttl_impl
*@brief Namespace @c cttl_impl contains implementation classes of CTTL library.
*/
namespace cttl_impl {

    /**@struct xtl_bitflags
    * @brief Encapsulates bit operations on an integer type.
    *
    * The following code demonstrates use of @c xtl_bitflags struct:
    * @include xtl_bitflags.cpp
    * This sample program prints:
    * @include xtl_bitflags.txt
    *
    */
    struct xtl_bitflags
    {
        /**Defines type that represents bits of an integer.*/
        typedef unsigned int value_type;

        /**Constructs new object and sets flags provided by the user.
        *
        * @param flags_
        *        Bit values to initialize the new object.
        *
        */
        xtl_bitflags( value_type flags_ = 0 ) 
            : bits( flags_ )
        {
        }

        /**Clears (sets to zero) bits specified by the caller.
        *
        * @param flags_
        *        Specifies bits to be cleared.
        *
        * @return
        *        Old bit values.
        *
        */
        value_type clear( value_type flags_ )
        {
            value_type old_value = bits;
            bits &= ~flags_;
            return old_value;
        }

        /**Sets bits provided by the user.
        *
        * @param flags_
        *        Specifies bits to be set.
        *
        * @return
        *        Old bit values.
        *
        */
        value_type set( value_type flags_ )
        {
            value_type old_value = bits;
            bits |= flags_;
            return old_value;
        }

        /**Tests if bits are set.
        *
        * @param flags_
        *        Specifies bits to be tested.
        *
        * @return
        *        Non-zero result if at least one of the @c flags_ is set.
        *
        */
        value_type test( value_type flags_ ) const
        {
            return bits & flags_;
        }

        /**Tests flags.
        *
        * @param flags_
        *        Specifies bits to be tested.
        *
        * @return
        *        Non-zero result only if <i>all</i> @c flags_ are set.
        *
        */
        bool exact_test( value_type flags_ ) const
        {
            return ( bits & flags_ ) == flags_;
        }

        /**Converts encapsulated bits to the @c xtl_bitflags::value_type */
        operator value_type() const
        {
            return bits;
        }

        /**Stores encapsulated bits. */
        value_type bits;

    };  // struct xtl_bitflags

}   // namespace cttl_impl

#endif //_CTTL_XTL_BITFLAGS_H_INCLUDED_
