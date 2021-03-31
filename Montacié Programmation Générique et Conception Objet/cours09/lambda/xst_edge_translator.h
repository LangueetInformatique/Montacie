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

/**@file xst_edge_translator.h
 * @brief Defines function object for translations of
 *        <tt>cttl::edge</tt> to C-style string.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_edge_translator.h

#ifndef _XST_EDGE_TRANSLATOR_H_INCLUDED_
#define _XST_EDGE_TRANSLATOR_H_INCLUDED_

namespace cttl_impl {

/**@class xst_edge_translator
* @brief Function object to translate
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>
*        to a null-terminated array of characters.
*
* @tparam PolicyT
*        specifies
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>
*        of the edge.
*
* @tparam StringT
*        specifies type of input string.
*
*/
template< typename PolicyT, typename StringT >
class xst_edge_translator
{
public:
    /**Defines type of input characters.*/
    typedef typename StringT::value_type char_T;

private:
    /**Reference to encapsulated substring object.*/
    cttl::const_edge< PolicyT, StringT > const& m_edge;

    /**Stores copy of substring value.*/
    StringT m_value;

public:
    /**Constructs and initializes the object from an edge.*/
    xst_edge_translator( cttl::const_edge< PolicyT, StringT > const& edge_ )
        :
    m_edge( edge_ )
    {
    }

    /**Copy constructor.*/
    xst_edge_translator( xst_edge_translator< PolicyT, StringT > const& other_ )
        :
    m_edge( other_.m_edge )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_edge_translator< PolicyT, StringT >& operator=( xst_edge_translator< PolicyT, StringT > const& );

public:
    /**Translate CTTL substring to null-terminated array of characters.
    *
    * @tparam InputValueT
    *         specifies source type to translate from.
    *
    */
    template< typename InputValueT >
    char_T const* operator() ( InputValueT const& )
    {
        trace_deposit();
        m_value = m_edge.text();
        return m_value.c_str();
    }

private:
    /**Auxiliary function to keep trace of substring translations at run time.*/
    void trace_deposit()
    {
#if ( CTTL_VERSION >= 300 )
        CTTL_TRACE_DEPOSIT_TEXT( "edge@" );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.first.offset() );
        CTTL_TRACE_DEPOSIT_TEXT( '-' );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.second.offset() );
        CTTL_TRACE_DEPOSIT_TEXT( " \"" );
        CTTL_TRACE_DEPOSIT_MONOSPACE_TEXT( m_edge.text().c_str() );
        CTTL_TRACE_DEPOSIT_TEXT( "\" " );
#else
        CTTL_TRACE_DEPOSIT_TEXT( "edge(" );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.first.identity() );
        CTTL_TRACE_DEPOSIT_TEXT( ',' );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.second.identity() );
        CTTL_TRACE_DEPOSIT_TEXT( ")@" );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.first.offset() );
        CTTL_TRACE_DEPOSIT_TEXT( '-' );
        CTTL_TRACE_DEPOSIT_TEXT( m_edge.second.offset() );
        CTTL_TRACE_DEPOSIT_TEXT( " \"" );
        CTTL_TRACE_DEPOSIT_MONOSPACE_TEXT( m_edge.text().c_str() );
        CTTL_TRACE_DEPOSIT_TEXT( "\" " );
#endif //( CTTL_VERSION == 300 )
    }

}; // class xst_edge_translator

}   // namespace cttl_impl


#endif //_XST_EDGE_TRANSLATOR_H_INCLUDED_
