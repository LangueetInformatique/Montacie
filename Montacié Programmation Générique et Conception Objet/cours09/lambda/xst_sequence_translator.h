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

/**@file xst_sequence_translator.h
 * @brief Defines function object for sequential translations.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_sequence_translator.h

#ifndef _XST_SEQUENCE_TRANSLATOR_H_INCLUDED_
#define _XST_SEQUENCE_TRANSLATOR_H_INCLUDED_

namespace cttl_impl {

/**@class xst_sequence_translator
* @brief Function object to translate value by using array index
*        of value stored in STL sequence container.
*
* @tparam SequenceT
*        specifies
*        <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a>
*        type.
*
*/
template< typename SequenceT >
class xst_sequence_translator
{
public:
    /**Defines type of value to translate from.*/
    typedef typename SequenceT::value_type value_T;
    typedef typename SequenceT::size_type size_T;

private:
    /**Reference to sequence object.*/
    SequenceT& m_sequence;

public:
    /**Constructs and initializes the object.*/
    xst_sequence_translator( SequenceT& vector_ )
        :
    m_sequence( vector_ )
    {
    }

    /**Copy constructor.*/
    xst_sequence_translator( xst_sequence_translator< SequenceT > const& other_ )
        :
    m_sequence( other_.m_sequence )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_sequence_translator< SequenceT >& operator=( xst_sequence_translator< SequenceT > const& );

public:
    /**Function call operator to translate the value.
    *
    * @tparam InputValueT
    *         specifies source type to translate from.
    *
    * @param value_
    *         Reference to source value.
    *
    */
    template< typename InputValueT >
    size_T operator() ( InputValueT const& value_ )
    {
        size_T id = m_sequence.size();
        m_sequence.push_back( value_T( value_ ) );
        trace_deposit();
        return id;
    }

private:
    /**Auxiliary function to keep trace of dictionary values.*/
    void trace_deposit()
    {
        CTTL_TRACE_DEPOSIT_TEXT( "-> seq[" );
        CTTL_TRACE_DEPOSIT_TEXT( m_sequence.size() - 1 );
        CTTL_TRACE_DEPOSIT_TEXT( "]=\"" );
        CTTL_TRACE_DEPOSIT_TEXT( m_sequence.back() );
        CTTL_TRACE_DEPOSIT_TEXT( "\" " );
    }

}; // class xst_sequence_translator


}   // namespace cttl_impl


#endif //_XST_SEQUENCE_TRANSLATOR_H_INCLUDED_
