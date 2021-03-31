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

/**@file xst_deposit_adaptor.h
 * @brief Defines lambda expression trace macros and
 *        adaptor class for lambda instructions.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_deposit_adaptor.h

#ifndef _XST_DEPOSIT_ADAPTOR_H_INCLUDED_
#define _XST_DEPOSIT_ADAPTOR_H_INCLUDED_

#if ( !defined( CTTL_TRACE_DEPOSITS ) )
#   if ( !defined( CTTL_TRACE_DEPOSITS_OFF ) )
#       if ( defined( CTTL_TRACE_RULES ) || defined( CTTL_TRACE_EVERYTHING ) )
#           define CTTL_TRACE_DEPOSITS
#       endif
#   endif
#endif

#if ( defined( CTTL_TRACE_DEPOSITS ) )

#   if ( defined( CTTL_TRACE_DEPOSIT_LINE_ON ) )
#       define CTTL_TRACE_DEPOSIT_LINE( xtext ) CTTL_TRACE_DEPOSIT_TEXT( xtext CTTL_QUOTED_EXPRESSION( __LINE__ ) " " )
#   else
#       define CTTL_TRACE_DEPOSIT_LINE( xtext )
#   endif // CTTL_TRACE_DEPOSIT_LINE_ON

#       define CTTL_TRACE_DEPOSIT_TEXT( xtext )             CTTL_UNILOG_STREAM << ( xtext )
#       define CTTL_TRACE_DEPOSIT_JUSTIFY()                 xtl_trace_grammar::trace_justify()
#       define CTTL_TRACE_DEPOSIT_MONOSPACE_TEXT( xtext )   xtl_trace_grammar::output_monospace_text( xtext )
#       define CTTL_TRACE_DEPOSIT_DELAYED_CHAR( xchar )     xst_trace_delayed_char< xchar > CTTL_TRACE_VARIABLE( xst_delayed_char_ ); if ( sizeof( CTTL_TRACE_VARIABLE( xst_delayed_char_ ) ) ){}

#   else
/**Macro sends argument to CTTL_UNILOG_STREAM.*/
#       define CTTL_TRACE_DEPOSIT_TEXT( xtext )
/**Macro justifies output with current trace output spacing level.*/
#       define CTTL_TRACE_DEPOSIT_JUSTIFY()
/**Macro removes output control characters and sends argument to CTTL_UNILOG_STREAM.*/
#       define CTTL_TRACE_DEPOSIT_MONOSPACE_TEXT( xtext )
/**Macro delayed character trace. @see cttl_impl::xst_trace_delayed_char documentation.*/
#       define CTTL_TRACE_DEPOSIT_DELAYED_CHAR( xchar )
/**Macro sends argument to CTTL_UNILOG_STREAM along with current line.*/
#       define CTTL_TRACE_DEPOSIT_LINE( xtext )

#endif // CTTL_TRACE_DEPOSITS

/**@namespace cttl_impl
 * @brief Namespace @c cttl_impl contains implementation classes and
 * functions of CTTL library.
 *
 */
namespace cttl_impl {

/**@class xst_trace_delayed_char
 * @brief Helper object to display single character upon
 *        return from a function call or exit from a local scope.
 *
 * @tparam CharT
 *        specifies type of character to display.
 *
 */
template< char CharT >
struct xst_trace_delayed_char {
    ~xst_trace_delayed_char()
    {
        CTTL_TRACE_DEPOSIT_TEXT( CharT );
    }
}; // struct xst_trace_delayed_char

/**@class xst_deposit_adaptor
 * @brief Expression adaptor for lambda instructions.
 *
 * @tparam ProgramLambdaT
 *        specifies type of program,
 *        a lambda compound consisting opcodes
 *        and rudimentary references to operands within lambda.
 *
 * @tparam TargetLambdaT
 *        specifies type of
 *        target lambda compound against which the @c ProgramLambdaT
 *        will be executed..
 *
 */
template< typename TargetLambdaT, typename ProgramLambdaT >
class xst_deposit_adaptor {

private:
    /**Deposit program.*/
    ProgramLambdaT m_program;

    /**Reference to the target lambda compound.*/
    TargetLambdaT& m_lambda;

public:

    /**Constructs and initializes the object.*/
    xst_deposit_adaptor( TargetLambdaT& lambda_, ProgramLambdaT program_ )
    :
    m_program( program_ ),
    m_lambda( lambda_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_deposit_adaptor< TargetLambdaT, ProgramLambdaT >& operator=( xst_deposit_adaptor< TargetLambdaT, ProgramLambdaT > const& );

public:
    /**Implements <a href="http://cttl.sourceforge.net/">CTTL</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of
    *        parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @param edge_
    *        reference to the
    *        parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *    Grammar expression represented by @c xst_deposit_adaptor always succeeds.
    *
    * @return
    *    Grammar
    *    <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
    *    Runs the program against target lambda compound.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'd' );
        m_lambda.update( m_program );
        return edge_.first.offset();
    }
        
};  // xst_deposit_adaptor


}   // namespace cttl_impl


#endif //_XST_DEPOSIT_ADAPTOR_H_INCLUDED_
