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

/**@file xst_literal_translator.h
 * @brief Defines function object for translations of
 *        character literals to various data types inside lambda expressions.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_literal_translator.h

#ifndef _XST_LITERAL_TRANSLATOR_H_INCLUDED_
#define _XST_LITERAL_TRANSLATOR_H_INCLUDED_

#ifdef NDEBUG

#define CTTL_LAMBDA_ASSERT( xexpr ) operator+( const_scalar( 1 ) )
#define CTTL_LAMBDA_TRACE( xexpr ) operator+( const_scalar( 1 ) )
#else
/**Macro for run-time assertions inside lambda expressions.*/
#define CTTL_LAMBDA_ASSERT( xexpr )                 \
    (                                                   \
        ( xexpr )                                       \
        ||                                              \
        --(                                             \
            scalar( 0 )                                 \
            ^                                           \
            atoi                                        \
            ^                                           \
            "Assertion failed: " #xexpr                 \
            " in "                                      \
            __FILE__                                    \
            ":"                                         \
            CTTL_QUOTED_EXPRESSION( __LINE__ )          \
        )                                               \
    )

/**Macro for simple message tracing inside lambda expressions.*/
#define CTTL_LAMBDA_TRACE( xmessage ) ( ++( scalar( 0 )^atoi^( xmessage ) ) )

#endif // NDEBUG

namespace cttl_impl {

/**@class xst_literal_translator
* @brief Function object to enclose character literal into lambda expression
*        with potential of conversion to various data types.
*
* @tparam CharT
*        specifies type of characters.
*
* The function call operator asserts that its argument is not false.
* Macro @c CTTL_LAMBDA_ASSERT uses @c xst_literal_translator for run-time
* assertions inside lambda expressions.
*
*/
template< typename CharT >
class xst_literal_translator
{
private:
    /**Stores string literal.*/
    CharT const* m_pchar;

public:
    /**Constructs and initializes the object from an edge object.*/
    xst_literal_translator( CharT const* pchar_ )
        :
    m_pchar( pchar_ )
    {
    }

    /**Copy constructor.*/
    xst_literal_translator( xst_literal_translator< CharT > const& other_ )
        :
    m_pchar( other_.m_pchar )
    {
    }

    /**Translates boolean value to character literal.
    *
    * Asserts that the specified argument is @c true.
    */
    CharT const* operator() ( bool CTTL_LAMBDA_ASSERT_ )
    {
        trace_deposit();
        assert( CTTL_LAMBDA_ASSERT_ );
        return m_pchar;
    }

private:
    /**Auxiliary function to keep trace of character literal translations at run time.*/
    void trace_deposit()
    {
        CTTL_TRACE_DEPOSIT_TEXT( '\"' );
        CTTL_TRACE_DEPOSIT_MONOSPACE_TEXT( m_pchar );
        CTTL_TRACE_DEPOSIT_TEXT( "\" " );
    }

}; // class xst_literal_translator

}   // namespace cttl_impl


#endif //_XST_LITERAL_TRANSLATOR_H_INCLUDED_
