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

/**@file xst_traced_action_base.h
 * @brief Defines base classes for CTTL traceable closure objects.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_traced_action_base.h

#ifndef _XST_TRACED_ACTION_BASE_H_INCLUDED_
#define _XST_TRACED_ACTION_BASE_H_INCLUDED_

namespace cttl_impl {

/**@class xst_traced_action_base
 * @brief Base class for CTTL traceable closure objects.
 *
 */
class xst_traced_action_base {

private:
    /**Stores source line number of the source file where action call occurs.*/
    int m_line;

    /**Stores action name.*/
    char const* m_action_name;

protected:
    /**Constructs and initializes the object.*/
    xst_traced_action_base( int line_, char const* action_name_ )
        :
        m_line( line_ ),
        m_action_name( action_name_ )
    {
    }

    /**Displays prolog section of trace for action with no arguments.*/
    void trace_prolog() const
    {
        CTTL_UNILOG_FLUSH;
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( m_line );
        CTTL_TRACE_DEPOSIT_TEXT( "=>" );
        CTTL_TRACE_DEPOSIT_TEXT( m_action_name );
        CTTL_UNILOG_FLUSH;
        xtl_trace_grammar::depth( +1 );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
    }

    /**Displays prolog section of trace for action with one argument.*/
    template< typename ArgumentT >
    void trace_prolog( ArgumentT const& arg_ ) const
    {
        CTTL_UNILOG_FLUSH;
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( m_line );
        CTTL_TRACE_DEPOSIT_TEXT( "=>" );
        CTTL_TRACE_DEPOSIT_TEXT( m_action_name );
        CTTL_TRACE_DEPOSIT_TEXT( '\'' );
        CTTL_TRACE_DEPOSIT_TEXT( xst_scalar_traits< ArgumentT >::identity( arg_ ) );
        CTTL_TRACE_DEPOSIT_TEXT( '\'' );
        CTTL_UNILOG_FLUSH;
        xtl_trace_grammar::depth( +1 );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
    }

    /**Displays epilog section of the trace.*/
    template< typename ResultT >
    void trace_epilog( ResultT const& result_ ) const
    {
        xtl_trace_grammar::depth( -1 );
        CTTL_UNILOG_FLUSH;
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( m_line );
        CTTL_TRACE_DEPOSIT_TEXT( "<=" );
        CTTL_TRACE_DEPOSIT_TEXT( m_action_name );
        CTTL_TRACE_DEPOSIT_TEXT( ':' );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< ResultT >::identity( result_ ) );
        CTTL_UNILOG_FLUSH;
        CTTL_TRACE_DEPOSIT_JUSTIFY();
    }

};  // class xst_traced_action_base


}   // namespace cttl_impl


#endif //_XST_TRACED_ACTION_BASE_H_INCLUDED_
