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

/**@file xst_iterator_writer.h
 * @brief Helper function object to
 *        write data from lambda compound to STL output iterator.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_iterator_writer.h

#ifndef _XST_ITERATOR_WRITER_H_INCLUDED_
#define _XST_ITERATOR_WRITER_H_INCLUDED_

namespace cttl_impl {

/**@class xst_iterator_writer
 * @brief Helper function object to write lambda compound to output iterator.
 *
 * @tparam OutputIteratorT
 *        specifies type of STL
 *        <a href="http://www.sgi.com/tech/stl/OutputIterator.html">output iterator</a>.
 *
 */
template< typename OutputIteratorT >
class xst_iterator_writer
{
private:
    /**Reference to output iterator.*/
    OutputIteratorT& m_iterator;

public:
    /**Constructs and initializes the object.*/
    xst_iterator_writer( OutputIteratorT& iterator_ )
        :
    m_iterator( iterator_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_iterator_writer< OutputIteratorT >& operator=( xst_iterator_writer< OutputIteratorT > const& );

public:
    /**Overloaded function call operator implements iterator output.
    *
    * @tparam TerminalT
    *        specifies type of terminal node of lambda compound.
    *
    */
    template< typename TerminalT >
    void operator() ( TerminalT const& terminal_ )
    {
        *m_iterator = terminal_.top( const_scalar( 0 ) );
        ++m_iterator;
    }

}; // struct xst_iterator_writer

}   // namespace cttl_impl

#endif // _XST_ITERATOR_WRITER_H_INCLUDED_
