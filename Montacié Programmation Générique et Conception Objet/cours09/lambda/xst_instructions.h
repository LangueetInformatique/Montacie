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

/**@file xst_instructions.h
 * @brief Definition of macros and implementation classes for instruction-based deposits.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_instructions.h

#ifndef _XST_INSTRUCTIONS_H_INCLUDED_
#define _XST_INSTRUCTIONS_H_INCLUDED_

/**Macro for instruction to pop data from location specified by @c XLOCATION operand.*/
#define CTTL_POP_DATA( XLOCATION )              const_scalar( pop_data_ )   ^const_scalar( XLOCATION )

/**Macro for instruction to negate data at location specified by @c XLOCATION operand.*/
#define CTTL_NEG_TOP( XLOCATION )               const_scalar( neg_top_ )    ^const_scalar( XLOCATION )


/**Macro for instruction to translate data at location specified by @c XLOCATION operand.*/
#define CTTL_PUSH_DATA( XLOCATION )             const_scalar( push_data_ )  ^const_scalar( XLOCATION )

/**Macro for instruction to push constant integer value specified by @c XVALUE operand at location specified by @c XLOCATION operand.*/
#define CTTL_PUSH_VALUE( XLOCATION, XVALUE )    const_scalar( push_value_ ) ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to push data from location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_PUSH_TOP( XLOCATION, XLOCATION2 )  const_scalar( push_top_ )   ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to push size of location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_PUSH_SIZE( XLOCATION, XLOCATION2 ) const_scalar( push_size_ )  ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


/**Macro for instruction to assign constant integer value specified by @c XVALUE operand at location specified by @c XLOCATION operand.*/
#define CTTL_MOVE_VALUE( XLOCATION, XVALUE )    const_scalar( move_value_ ) ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to assign data from location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_MOVE_TOP( XLOCATION, XLOCATION2 )  const_scalar( move_top_ )   ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to assign size of location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_MOVE_SIZE( XLOCATION, XLOCATION2 ) const_scalar( move_size_ )  ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


/**Macro for instruction to add constant integer value specified by @c XVALUE operand at location specified by @c XLOCATION operand.*/
#define CTTL_ADD_VALUE( XLOCATION, XVALUE )    const_scalar( add_value_ )   ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to add data from location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_ADD_TOP( XLOCATION, XLOCATION2 )  const_scalar( add_top_ )     ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to add size of location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_ADD_SIZE( XLOCATION, XLOCATION2 ) const_scalar( add_size_ )    ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


/**Macro for instruction to subtract constant integer value specified by @c XVALUE operand from location specified by @c XLOCATION operand.*/
#define CTTL_SUB_VALUE( XLOCATION, XVALUE )    const_scalar( sub_value_ )   ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to subtract data from location specified by @c XLOCATION2 operand from location specified by @c XLOCATION operand.*/
#define CTTL_SUB_TOP( XLOCATION, XLOCATION2 )  const_scalar( sub_top_ )     ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to subtract size of location specified by @c XLOCATION2 operand from location specified by @c XLOCATION operand.*/
#define CTTL_SUB_SIZE( XLOCATION, XLOCATION2 ) const_scalar( sub_size_ )    ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


/**Macro for instruction to multiply constant integer value specified by @c XVALUE operand at location specified by @c XLOCATION operand.*/
#define CTTL_MUL_VALUE( XLOCATION, XVALUE )    const_scalar( mul_value_ )   ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to multiply data from location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_MUL_TOP( XLOCATION, XLOCATION2 )  const_scalar( mul_top_ )     ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to multiply size of location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_MUL_SIZE( XLOCATION, XLOCATION2 ) const_scalar( mul_size_ )    ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


/**Macro for instruction to divide constant integer value specified by @c XVALUE operand at location specified by @c XLOCATION operand.*/
#define CTTL_DIV_VALUE( XLOCATION, XVALUE )    const_scalar( div_value_ )   ^const_scalar( XLOCATION )  ^const_scalar( XVALUE )

/**Macro for instruction to divide data from location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_DIV_TOP( XLOCATION, XLOCATION2 )  const_scalar( div_top_ )     ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )

/**Macro for instruction to divide size of location specified by @c XLOCATION2 operand at location specified by @c XLOCATION operand.*/
#define CTTL_DIV_SIZE( XLOCATION, XLOCATION2 ) const_scalar( div_size_ )    ^const_scalar( XLOCATION )  ^const_scalar( XLOCATION2 )


namespace cttl_impl {

////////////////////////////////////////////////////////////////////////
// lambda instructions
////////////////////////////////////////////////////////////////////////

// one-operand instructions

/**Primary template for cttt_impl::xst_instruction_1_operand is not used.*/
template< int FirstOperandT, int OpcodeT >
struct xst_instruction_1_operand {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& )
    {
        assert( false );
    }

};  // struct xst_instruction_1_operand

// two-operand instructions

/**Primary template for cttt_impl::xst_instruction_2_operand is not used.*/
template< int FirstOperandT, int SecondOperandT, int OpcodeT >
struct xst_instruction_2_operand {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& )
    {
        assert( false );
    }

};  // struct xst_instruction_2_operand

/**@struct xst_instruction_1_operand< FirstOperandT, pop_data_ >
 * @brief Implements template specialization for @c CTTL_POP_DATA instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * Implements @c CTTL_POP_DATA instruction to pop data from location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT >
struct xst_instruction_1_operand< FirstOperandT, pop_data_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "pop_data\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        static const int first_operand = FirstOperandT;
        lambda_.pop( const_scalar( first_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_1_operand


/**@struct xst_instruction_1_operand< FirstOperandT, push_data_ >
 * @brief Implements template specialization for @c CTTL_PUSH_DATA instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * Implements @c CTTL_PUSH_DATA instruction to translate data at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT >
struct xst_instruction_1_operand< FirstOperandT, push_data_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "push_data\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        CTTL_UNILOG_FLUSH;
        static const int first_operand = FirstOperandT;
        lambda_.push( const_scalar( first_operand ), true );
    }

};  // struct xst_instruction_1_operand


/**@struct xst_instruction_1_operand< FirstOperandT, neg_top_ >
 * @brief Implements template specialization for @c CTTL_NEG_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * Implements @c CTTL_NEG_TOP instruction to negate data at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT >
struct xst_instruction_1_operand< FirstOperandT, neg_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "neg_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        static const int first_operand = FirstOperandT;
        lambda_.top( const_scalar( first_operand ) ) = -lambda_.top( const_scalar( first_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_1_operand



// binary operator instructions

/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_value_ >
 * @brief Implements template specialization for @c CTTL_PUSH_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_PUSH_VALUE instruction to push constant integer value specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "push_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        static const int first_operand = FirstOperandT;
        lambda_.push( const_scalar( first_operand ), SecondOperandT ); // 
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand

/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_top_ >
 * @brief Implements template specialization for @c CTTL_PUSH_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_PUSH_TOP instruction to push data from location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "push_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.push( const_scalar( first_operand ), lambda_.top( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand

/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_size_ >
 * @brief Implements template specialization for @c CTTL_PUSH_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_PUSH_SIZE instruction to push size of location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, push_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "push_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.push( const_scalar( first_operand ), value_T( lambda_.size( const_scalar( second_operand ) ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_value_ >
 * @brief Implements template specialization for @c CTTL_MOVE_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MOVE_VALUE instruction to assign constant integer value specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "move_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        lambda_.top( const_scalar( first_operand ) ) = SecondOperandT;
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_top_ >
 * @brief Implements template specialization for @c CTTL_MOVE_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MOVE_TOP instruction to assign data from location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "move_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) = lambda_.top( const_scalar( second_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand

/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_size_ >
 * @brief Implements template specialization for @c CTTL_MOVE_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MOVE_SIZE instruction to assign size of location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, move_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "move_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) = value_T( lambda_.size( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_value_ >
 * @brief Implements template specialization for @c CTTL_ADD_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_ADD_VALUE instruction to add constant integer value specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "add_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) += SecondOperandT;
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_top_ >
 * @brief Implements template specialization for @c CTTL_ADD_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_ADD_TOP instruction to add data from location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "add_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) += lambda_.top( const_scalar( second_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_size_ >
 * @brief Implements template specialization for @c CTTL_ADD_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_ADD_SIZE instruction to add size of location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, add_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "add_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) += value_T( lambda_.size( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_value_ >
 * @brief Implements template specialization for @c CTTL_SUB_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_SUB_VALUE instruction to subtract constant integer value specified by 2nd operand from location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "sub_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) -= SecondOperandT;
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_top_ >
 * @brief Implements template specialization for @c CTTL_SUB_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_SUB_TOP instruction to subtract data from location specified by 2nd operand from location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "sub_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) -= lambda_.top( const_scalar( second_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand



/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_size_ >
 * @brief Implements template specialization for @c CTTL_SUB_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_SUB_SIZE instruction to subtract size of location specified by 2nd operand from location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, sub_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "sub_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) -= value_T( lambda_.size( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_value_ >
 * @brief Implements template specialization for @c CTTL_MUL_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MUL_VALUE instruction to multiply constant integer value specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "mul_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) *= SecondOperandT;
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_top_ >
 * @brief Implements template specialization for @c CTTL_MUL_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MUL_TOP instruction to multiply data from location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "mul_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) *= lambda_.top( const_scalar( second_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_size_ >
 * @brief Implements template specialization for @c CTTL_MUL_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_MUL_SIZE instruction to multiply size of location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, mul_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "mul_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) *= value_T( lambda_.size( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand
 * @brief Implements template specialization for @c CTTL_DIV_VALUE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_DIV_VALUE instruction to divide constant integer value specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, div_value_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "div_value\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) /= SecondOperandT;
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand
 * @brief Implements template specialization for @c CTTL_DIV_TOP instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_DIV_TOP instruction to divide data from location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, div_top_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "div_top\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) /= lambda_.top( const_scalar( second_operand ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


/**@struct xst_instruction_2_operand
 * @brief Implements template specialization for @c CTTL_DIV_SIZE instruction.
 *
 * @tparam FirstOperandT
 *        specifies 1st operand of the instruction.
 *
 * @tparam SecondOperandT
 *        specifies 2nd operand of the instruction.
 *
 * Implements @c CTTL_DIV_SIZE instruction to divide size of location specified by 2nd operand at location specified by @c FirstOperandT operand.
 *
 */
template< int FirstOperandT, int SecondOperandT >
struct xst_instruction_2_operand< FirstOperandT, SecondOperandT, div_size_ > {

    template< typename TargetLambdaT >
    static void instruction( TargetLambdaT& lambda_ )
    {
        typedef typename TargetLambdaT::value_T value_T;
        static const int first_operand = FirstOperandT;
        static const int second_operand = SecondOperandT;

        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( "div_size\t" );
        CTTL_TRACE_DEPOSIT_TEXT( FirstOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( '\t' );
        CTTL_TRACE_DEPOSIT_TEXT( SecondOperandT );
        CTTL_TRACE_DEPOSIT_TEXT( "; " );
        lambda_.top( const_scalar( first_operand ) ) /= value_T( lambda_.size( const_scalar( second_operand ) ) );
        CTTL_UNILOG_FLUSH;
    }

};  // struct xst_instruction_2_operand


}   // namespace cttl_impl

#endif //_XST_INSTRUCTIONS_H_INCLUDED_
