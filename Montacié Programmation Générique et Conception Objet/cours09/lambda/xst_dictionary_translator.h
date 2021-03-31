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

/**@file xst_dictionary_translator.h
 * @brief Defines function object for dictionary-style translations.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_translator.h

#ifndef _XST_DICTIONARY_TRANSLATOR_H_INCLUDED_
#define _XST_DICTIONARY_TRANSLATOR_H_INCLUDED_

namespace cttl_impl {

/**@class xst_dictionary_translator
* @brief Function object to translate value of source type to integral
*        type by storing it inside a dictionary represented by
*        sequence and associative container.
*
* @tparam SequenceT
*        specifies
*        <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a>
*        type.
*
* @tparam MapT
*        specifies
*        <a href="http://www.sgi.com/tech/stl/UniqueAssociativeContainer.html">unique associative container</a>
*        type.
*
* @remarks
*        Value of type <tt>MapT::key_type</tt> is translated to <tt>MapT::data_type</tt> by
*        checking unique key value and inserting it into container if key
*        is not present. The @c data_type is generated automatically as next
*        available sequential number.
*
*/
template< typename SequenceT, typename MapT >
class xst_dictionary_translator
{
public:
    /**Defines type of value to translate from.*/
    typedef typename SequenceT::value_type value_T;
    typedef typename SequenceT::size_type size_T;

private:
    /**Reference to sequence object.*/
    SequenceT& m_sequence;

    /**Reference to associative container.*/
    MapT& m_map;

public:
    /**Constructs and initializes the object.*/
    xst_dictionary_translator( SequenceT& vector_, MapT& map_ )
        :
    m_sequence( vector_ ),
    m_map( map_ )
    {
    }

    /**Copy constructor.*/
    xst_dictionary_translator( xst_dictionary_translator< SequenceT, MapT > const& other_ )
        :
    m_sequence( other_.m_sequence ),
    m_map( other_.m_map )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_dictionary_translator< SequenceT, MapT >& operator=( xst_dictionary_translator< SequenceT, MapT > const& );

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
        // is this value already in the dictionary ?
        typename MapT::const_iterator it = m_map.find( value_T( value_ ) );
        if ( it == m_map.end() ) {
            // no, this value is new,
            // generate new identity
            m_map.insert(
                std::make_pair( value_, id )
                );
            m_sequence.push_back( value_T( value_ ) );
            //assert( m_sequence.size() == m_map.size() );

        } else
            // yes, value already exists, return its identity:
            id = it->second;

        trace_deposit( id, value_ );
        return id;
    }

private:
    /**Auxiliary function to keep trace of dictionary values.*/
    template< typename InputValueT >
    void trace_deposit(
        size_T
#if ( defined( CTTL_TRACE_DEPOSITS ) )
        id_
#endif
        , InputValueT const&
#if ( defined( CTTL_TRACE_DEPOSITS ) )
        value_
#endif
        )
    {
        CTTL_TRACE_DEPOSIT_TEXT( "dictionary[" );
        CTTL_TRACE_DEPOSIT_TEXT( id_ );
        CTTL_TRACE_DEPOSIT_TEXT( "]=\"" );
        CTTL_TRACE_DEPOSIT_TEXT( value_ );
        CTTL_TRACE_DEPOSIT_TEXT( "\" " );
    }

}; // class xst_dictionary_translator


}   // namespace cttl_impl


#endif //_XST_DICTIONARY_TRANSLATOR_H_INCLUDED_
