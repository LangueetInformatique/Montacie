////////////////////////////////////////////////////////////////////////
// Common Text Transformation Library
// Copyright (C) 1997-2006 by Igor Kholodov. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// mailto:cttl@users.sourceforge.net
// http://sourceforge.net/projects/cttl/
////////////////////////////////////////////////////////////////////////

/**@file inode_reader.h
 * @brief Definition of cttl::inode_reader struct template.
 *
 */

// inode_reader.h

#ifndef _CTTL_INODE_READER_H_INCLUDED_
#define _CTTL_INODE_READER_H_INCLUDED_

#include <cassert>
#include <vector>
#include <iterator>
#include <functional>
#include <cstddef>

namespace cttl {

/**@struct inode_reader
 * @brief Represents readable node of a
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1000_syntax_tree.html">syntax tree</a>,
 * modeled on top of STL
 * <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a> container.
 *
 * While representing tree node, <tt>cttl::inode_reader</tt>
 * behaves as <a href="http://www.sgi.com/tech/stl/BidirectionalIterator.html">bidirectional iterator</a>.
 *
 * @tparam previous_link
 *        specifies field pointing to the previous node.
 *        As bidirectional iterator, node can be moved to the previous node
 *        by prefix and postfix decrement operators. Syntax node stores offset of the
 *        previous node in the field described by @c previous_link.
 *
 * @tparam next_link
 *        specifies field pointing to the next node.
 *        As bidirectional iterator, node can be moved to the next node
 *        by prefix and postfix increment operators. Syntax node stores offset of the
 *        next node in the field described by @c next_link.
 *
 * @tparam ContainerT
 *        specifies underlying
 *        <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a>
 *        container type.
 *
 * @see
 * - <tt>cttl::inode_writer</tt>
 *
 */
template< typename NodeDescriptorT = inode_default_descriptor, typename ContainerT = std::vector< size_t > >
#ifdef __SGI_STL_PORT
struct inode_reader : public stlport::bidirectional_iterator< inode_reader< NodeDescriptorT, ContainerT > > 
#else
struct inode_reader
#endif
{
    /**Position of the field that points to the next node.*/
    static const int next_link = NodeDescriptorT::NEXT_LINK;

    /**Position of the field that points to the previous node.*/
    static const int previous_link = NodeDescriptorT::PREVIOUS_LINK;

    /**Describes logical field positions of the node.*/
    typedef NodeDescriptorT inode_descriptor_T;

    /**Defines type container.*/
    typedef ContainerT container_T;

    /**Defines reference type of the container.*/
    typedef typename ContainerT::reference container_reference_T;

    /**Defines constant reference type of the container.*/
    typedef typename ContainerT::const_reference container_const_reference_T;

    /**Defines iterator type.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >       iterator;

    /**Defines const_iterator type.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >       const_iterator;

    /**Bidirectional iterator: value type of the node.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >        value_type;

    /**Bidirectional iterator: pointer type of the node.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >*       pointer;

    /**Bidirectional iterator: reference type of the node.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >        reference;

    /**Bidirectional iterator: const reference type of the node.*/
    typedef inode_reader< NodeDescriptorT, ContainerT >        const_reference;

    /**Bidirectional iterator: size type of the node.*/
    typedef typename ContainerT::size_type size_type;

    /**Bidirectional iterator: difference type of the node.*/
    typedef ptrdiff_t    difference_type;

    /**Bidirectional iterator: iterator category of the node.*/
    typedef std::bidirectional_iterator_tag iterator_category;

    // constructors

    /**Bidirectional iterator: default constructor.*/
    inode_reader()
        :
        m_offset( 0 ),
        m_ptr_container( NULL )
    {
    }

    /**Bidirectional iterator: copy constructor.*/
    inode_reader( inode_reader< NodeDescriptorT, ContainerT > const& other_ )
        :
        m_offset( other_.m_offset ),
        m_ptr_container( other_.m_ptr_container )
    {
    }

    /**Constructs new cttl::inode_reader and positions itself at the end.*/
    inode_reader( ContainerT& container_ )
        :
        m_offset( container_.size() ),
        m_ptr_container( &container_ )
    {
    }

    /**Constructs new cttl::inode_reader at specified position.*/
    inode_reader( ContainerT& container_, size_type offset_ )
        :
        m_offset( offset_ ),
        m_ptr_container( &container_ )
    {
    }

    /**Bidirectional iterator: assignment operator.*/
    inode_reader< NodeDescriptorT, ContainerT >& operator=( inode_reader< NodeDescriptorT, ContainerT > const& other_ )
    {
        if ( this != &other_ ) {
            m_offset = other_.m_offset;
            m_ptr_container = other_.m_ptr_container;
        }

        return *this;
    }

    /**Bidirectional iterator: dereference operator of the integer node iterator.*/
    const_reference operator*() const
    {
        return *this;
    }

    /**Bidirectional iterator: dereference operator of the integer node iterator.*/
    reference operator*()
    {
        return *this;
    }

    /**Bidirectional iterator: pointer operator of the integer node iterator.*/
    value_type const* operator->() const
    {
        return this;
    }

    /**Bidirectional iterator: pointer operator of the integer node iterator.*/
    value_type* operator->()
    {
        return this;
    }

    /**Bidirectional iterator: prefix increment operator of the integer node iterator.*/
    inode_reader< NodeDescriptorT, ContainerT >& operator++()
    {
        offset( value( next_link ) );
        return *this;
    }

    /**Bidirectional iterator: postfix increment operator of the integer node iterator.*/
    inode_reader< NodeDescriptorT, ContainerT > operator++( int )
    {
        inode_reader< NodeDescriptorT, ContainerT > sibling( *this );
        offset( value( next_link ) );
        return sibling;
    }

    /**Bidirectional iterator: prefix decrement operator of the integer node iterator.*/
    inode_reader< NodeDescriptorT, ContainerT >& operator--()
    {
        offset( value( previous_link ) );
        return *this;
    }

    /**Bidirectional iterator: postfix decrement operator of the integer node iterator.*/
    inode_reader< NodeDescriptorT, ContainerT > operator--( int )
    {
        inode_reader< NodeDescriptorT, ContainerT > sibling( *this );
        offset( value( previous_link ) );
        return sibling;
    }

    /**Bidirectional iterator: inode_reader comparison returns true if positions of two nodes are equal, false otherwise.*/
    bool operator== ( inode_reader< NodeDescriptorT, ContainerT > const& other_ ) const
    {
        return ( offset() == other_.offset() );
    }

    /**Bidirectional iterator: true if node positions are different nodes.*/
    bool operator!= ( inode_reader< NodeDescriptorT, ContainerT > const& other_ ) const
    {
        return ( offset() != other_.offset() );
    }

    /**Bidirectional iterator: returns first node of the container.*/
    inode_reader< NodeDescriptorT, ContainerT > begin() const
    {
        return inode_reader< NodeDescriptorT, ContainerT >( *m_ptr_container, 0 );
    }

    /**Returns arbitrary node of the container.*/
    inode_reader< NodeDescriptorT, ContainerT > begin( int offset_ ) const
    {
        return inode_reader< NodeDescriptorT, ContainerT >( *m_ptr_container, offset_ );
    }

    /**Bidirectional iterator: returns zero node of the container.*/
    inode_reader< NodeDescriptorT, ContainerT > end() const
    {
        return begin();
    }

    /////////////////////////////////////////////////////
    // Position and data access functions
    /////////////////////////////////////////////////////

    /**Returns mutable value stored at specific field of syntax tree node.*/
    container_reference_T value( int field_ )
    {
        return (*m_ptr_container)[ m_offset + field_ ];
    }

    /**Returns constant value at specific field of syntax tree node.*/
    container_const_reference_T value( int field_ ) const
    {
        return (*m_ptr_container)[ m_offset + field_ ];
    }

    /**Returns mutable value stored at specific field of syntax tree node.*/
    container_reference_T operator[] ( int field_ )
    {
        return value( field_ );
    }

    /**Returns constant value at specific field of syntax tree node.*/
    container_const_reference_T operator[] ( int field_ ) const
    {
        return value( field_ );
    }

    /**Sets offset of syntax tree node.*/
    void offset( size_type offset_ )
    {
        m_offset = offset_;
    }

    /**Returns current offset of the syntax tree node.*/
    size_type offset() const
    {
        return m_offset;
    }

    /////////////////////////////////////////////////////
    // Tree linkage helper functions
    /////////////////////////////////////////////////////

    /**Returns instance of cttl::inode_reader pointing to a specific relative node.*/
    inode_reader< NodeDescriptorT, ContainerT > operator() ( int field_ ) const
    {
        return inode_reader< NodeDescriptorT, ContainerT >( *m_ptr_container, value( field_ ) );
    }

protected:
    /////////////////////////////////////////////////////////////
    // inode_reader state variables
    /////////////////////////////////////////////////////////////

    /**Offset of the node.*/
    size_type m_offset;

    /**Pointer to STL sequence container providing physical storage of the syntax tree.*/
    ContainerT* m_ptr_container;

}; // inode_reader


}   // namespace cttl

#endif // _CTTL_INODE_READER_H_INCLUDED_
