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

/**@file xst_instruction_traits.h
 * @brief Definition of constants and trait classes for instruction-based deposits.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_instruction_traits.h

#ifndef _XST_INSTRUCTION_TRAITS_H_INCLUDED_
#define _XST_INSTRUCTION_TRAITS_H_INCLUDED_

namespace cttl_impl {

/**Identifies @c CTTL_POP_DATA instruction to pop data from location specified by the operand.*/
static const int pop_data_   = 1;


/**Identifies @c CTTL_PUSH_DATA instruction to translate data at location specified by the operand.*/
static const int push_data_  = 2;

/**Identifies @c CTTL_PUSH_VALUE instruction to push constant integer value specified by 2nd operand at location specified by 1st operand.*/
static const int push_value_ = 3;

/**Identifies @c CTTL_PUSH_TOP instruction to push data from location specified by 2nd operand at location specified by 1st operand.*/
static const int push_top_   = 4;

/**Identifies @c CTTL_PUSH_SIZE instruction to push size of location specified by 2nd operand at location specified by 1st operand.*/
static const int push_size_  = 5;


/**Identifies @c CTTL_MOVE_VALUE instruction to assign constant integer value specified by 2nd operand at location specified by 1st operand.*/
static const int move_value_ = 6;

/**Identifies @c CTTL_MOVE_TOP instruction to assign data from location specified by 2nd operand at location specified by 1st operand.*/
static const int move_top_   = 7;

/**Identifies @c CTTL_MOVE_SIZE instruction to assign size of location specified by 2nd operand at location specified by 1st operand.*/
static const int move_size_  = 8;


/**Identifies @c CTTL_ADD_VALUE instruction to add constant integer value specified by 2nd operand at location specified by 1st operand.*/
static const int add_value_  = 9;

/**Identifies @c CTTL_ADD_TOP instruction to add data from location specified by 2nd operand at location specified by 1st operand.*/
static const int add_top_    = 10;

/**Identifies @c CTTL_ADD_SIZE instruction to add size of location specified by 2nd operand at location specified by 1st operand.*/
static const int add_size_   = 11;


/**Identifies @c CTTL_SUB_VALUE instruction to subtract constant integer value specified by 2nd operand from location specified by 1st operand.*/
static const int sub_value_  = 12;

/**Identifies @c CTTL_SUB_TOP instruction to subtract data from location specified by 2nd operand from location specified by 1st operand.*/
static const int sub_top_    = 13;

/**Identifies @c CTTL_SUB_SIZE instruction to subtract size of location specified by 2nd operand from location specified by 1st operand.*/
static const int sub_size_   = 14;


/**Identifies @c CTTL_NEG_TOP instruction to negate data at location specified by the operand.*/
static const int neg_top_    = 15;


/**Identifies @c CTTL_MUL_VALUE instruction to multiply constant integer value specified by 2nd operand at location specified by 1st operand.*/
static const int mul_value_  = 16;

/**Identifies @c CTTL_MUL_TOP instruction to multiply data from location specified by 2nd operand at location specified by 1st operand.*/
static const int mul_top_    = 17;

/**Identifies @c CTTL_MUL_SIZE instruction to multiply size of location specified by 2nd operand at location specified by 1st operand.*/
static const int mul_size_   = 18;


/**Identifies @c CTTL_DIV_VALUE instruction to divide constant integer value specified by 2nd operand at location specified by 1st operand.*/
static const int div_value_  = 19;

/**Identifies @c CTTL_DIV_TOP instruction to divide data from location specified by 2nd operand at location specified by 1st operand.*/
static const int div_top_    = 20;

/**Identifies @c CTTL_DIV_SIZE instruction to divide size of location specified by 2nd operand at location specified by 1st operand.*/
static const int div_size_   = 21;



/**@struct xst_instruction_traits
 * @brief Implements primary template describing deposit instruction traits.
 *
 * @tparam OpcodeT
 *        specifies instruction code.
 *
 */
template< int OpcodeT >
struct xst_instruction_traits {

    enum { length_ = 2 };

};  // struct xst_instruction_traits

/**@struct xst_instruction_traits< pop_data_ >
 * @brief Implements template specialization for @c CTTL_POP_DATA instruction traits.
 *
 */
template<>
struct xst_instruction_traits< pop_data_ > {

    enum { length_ = 1 };

};  // struct xst_instruction_traits

/**@struct xst_instruction_traits< push_data_ >
 * @brief Implements template specialization for @c CTTL_PUSH_DATA instruction traits.
 *
 */
template<>
struct xst_instruction_traits< push_data_ > {

    enum { length_ = 1 };

};  // struct xst_instruction_traits

/**@struct xst_instruction_traits< neg_top_ >
 * @brief Implements template specialization for @c CTTL_NEG_TOP instruction traits.
 *
 */
template<>
struct xst_instruction_traits< neg_top_ > {

    enum { length_ = 1 };

};  // struct xst_instruction_traits

}   // namespace cttl_impl


#endif //_XST_INSTRUCTION_TRAITS_H_INCLUDED_
