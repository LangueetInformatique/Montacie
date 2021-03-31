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

/**@file inode_writer.h
 * @brief Inode implementation file.
 *
 */

// inode_writer.h

#ifndef _CTTL_INODE_WRITER_H_INCLUDED_
#define _CTTL_INODE_WRITER_H_INCLUDED_

#include <cassert>
#include <vector>
#include <iterator>
#include <functional>

namespace cttl {

/**@struct inode_writer
 * @brief Represents writable node of a
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1000_syntax_tree.html">syntax tree</a>,
 * modeled on top of STL
 * <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a> container.
 *
 * In addition to tree node representation, <tt>cttl::inode_writer</tt> class
 * also behaves as STL <a href="http://www.sgi.com/tech/stl/BidirectionalIterator.html">bidirectional iterator</a>.
 *
 * @tparam previous_link
 *        specifies field for linkage with previous node.
 *        cttl::inode_reader can be moved to the previous node
 *        by prefix and postfix decrement operators.
 *
 * @tparam next_link
 *        specifies field for linkage with next node.
 *        cttl::inode_reader can be moved to the next node
 *        by prefix and postfix increment operators.
 *
 * @tparam ContainerT
 *        specifies underlying
 *        <a href="http://www.sgi.com/tech/stl/Sequence.html">sequence</a>
 *        container type.
 *
 * @see
 * - <tt>cttl::inode_reader</tt>
 *
 */
template< typename NodeDescriptorT = inode_default_descriptor, typename ContainerT = std::vector< size_t > >
#ifdef __SGI_STL_PORT
struct inode_writer : public stlport::bidirectional_iterator< inode_writer< NodeDescriptorT, ContainerT > > 
#else
struct inode_writer
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

    /**Bidirectional iterator: value type of the node.*/
    typedef typename ContainerT::value_type value_type;

    /**Defines node type.*/
    typedef inode_writer< NodeDescriptorT, ContainerT > inode_T;

    /**Defines iterator type.*/
    typedef inode_writer< NodeDescriptorT, ContainerT > iterator;

    /**Defines const_iterator type.*/
    typedef inode_writer< NodeDescriptorT, ContainerT > const_iterator;

    /**Bidirectional iterator: pointer type of the node.*/
    typedef typename ContainerT::pointer pointer;

    /**Bidirectional iterator: reference type of the node.*/
    typedef typename ContainerT::reference reference;

    /**Bidirectional iterator: const reference type of the node.*/
    typedef typename ContainerT::const_reference const_reference;

    /**Bidirectional iterator: size type of the node.*/
    typedef typename ContainerT::size_type size_type;

    /**Bidirectional iterator: difference type of the node.*/
    typedef typename ContainerT::difference_type difference_type;

    /**Bidirectional iterator: iterator category of the node.*/
    typedef std::bidirectional_iterator_tag iterator_category;

    // constructors

    /**Bidirectional iterator: default constructor.*/
    inode_writer()
        :
        m_offset( 0 ),
        m_ptr_container( NULL )
    {
    }

    /**Bidirectional iterator: copy constructor.*/
    inode_writer( inode_writer< NodeDescriptorT, ContainerT > const& other_ )
        :
        m_offset( other_.m_offset ),
        m_ptr_container( other_.m_ptr_container )
    {
    }

    /**Constructs new cttl::inode_writer and positions itself at the end.*/
    inode_writer( ContainerT& container_ )
        :
        m_offset( container_.size() ),
        m_ptr_container( &container_ )
    {
    }

    /**Constructs new cttl::inode_writer at specified position.*/
    inode_writer( ContainerT& container_, size_type offset_ )
        :
        m_offset( offset_ ),
        m_ptr_container( &container_ )
    {
    }

    /**Bidirectional iterator: assignment operator.*/
    inode_writer< NodeDescriptorT, ContainerT >& operator=( inode_writer< NodeDescriptorT, ContainerT > const& other_ )
    {
        if ( this != &other_ ) {
            m_offset = other_.m_offset;
            m_ptr_container = other_.m_ptr_container;
        }

        return *this;
    }

    /**Bidirectional iterator: dereference operator returns value at the current position.*/
    const_reference operator*() const
    {
        return value( 0 );
    }

    /**Bidirectional iterator: dereference operator returns value at the current position.*/
    reference operator*()
    {
        return value( 0 );
    }

    /**Bidirectional iterator: pointer operator returns pointer to value at the
    * current position of the syntax tree node.
    */
    value_type const* operator->() const
    {
        return &value( 0 );
    }

    /**Bidirectional iterator: pointer operator returns pointer to value at the
    * current position of the syntax tree node.
    */
    value_type* operator->()
    {
        return &value( 0 );
    }

    /**Bidirectional iterator: prefix increment operator of cttl::inode_writer
    * increments current offset.
    */
    inode_writer< NodeDescriptorT, ContainerT >& operator++()
    {
        ++m_offset;
        return *this;
    }

    /**Bidirectional iterator: postfix increment operator of cttl::inode_writer
    * increments current offset.
    */
    inode_writer< NodeDescriptorT, ContainerT > operator++( int )
    {
        inode_writer< NodeDescriptorT, ContainerT > sibling( *this );
        ++m_offset;
        return sibling;
    }

    /**Bidirectional iterator: prefix decrement operator of cttl::inode_writer
    * decrements current offset.
    */
    inode_writer< NodeDescriptorT, ContainerT >& operator--()
    {
        --m_offset;
        return *this;
    }

    /**Bidirectional iterator: postfix decrement operator of cttl::inode_writer
    * decrements current offset.
    */
    inode_writer< NodeDescriptorT, ContainerT > operator--( int )
    {
        inode_writer< NodeDescriptorT, ContainerT > sibling( *this );
        --m_offset;
        return sibling;
    }

    /**Bidirectional iterator: returns copy of cttl::inode_writer with zero offset.*/
    inode_writer< NodeDescriptorT, ContainerT > begin() const
    {
        return inode_writer< NodeDescriptorT, ContainerT >( *m_ptr_container, 0 );
    }

    /**Returns copy of cttl::inode_writer at arbitrary position.*/
    inode_writer< NodeDescriptorT, ContainerT > begin( int offset_ ) const
    {
        return inode_writer< NodeDescriptorT, ContainerT >( *m_ptr_container, offset_ );
    }

    /**Bidirectional iterator: returns copy of cttl::inode_writer with offset at
    * the end of the underlying container.
    */
    inode_writer< NodeDescriptorT, ContainerT > end() const
    {
        return begin( int( m_ptr_container->size() ) );
    }

    /////////////////////////////////////////////////////
    // Position and data access functions
    /////////////////////////////////////////////////////

    /**Assign new offset.*/
    inode_writer< NodeDescriptorT, ContainerT >& operator=( size_type size_ )
    {
        m_offset = size_;
        return *this;
    }
    /**Assign new offset.*/
    inode_writer< NodeDescriptorT, ContainerT >& operator+=( size_type size_ )
    {
        m_offset += size_;
        return *this;
    }
    /**Assign new offset.*/
    inode_writer< NodeDescriptorT, ContainerT >& operator-=( size_type size_ )
    {
        m_offset -= size_;
        return *this;
    }

    /**Returns mutable value stored at specific field of this node.*/
    reference value( int field_ )
    {
        return (*m_ptr_container)[ m_offset + field_ ];
    }

    /**Returns constant value at specific field of this node.*/
    const_reference value( int field_ ) const
    {
        return (*m_ptr_container)[ m_offset + field_ ];
    }

    /**Returns mutable value stored at specific field of this node.*/
    reference operator[] ( int field_ )
    {
        return value( field_ );
    }

    /**Returns constant value at specific field of this node.*/
    const_reference operator[] ( int field_ ) const
    {
        return value( field_ );
    }

    /**Sets offset of the node.*/
    void offset( size_type offset_ )
    {
        m_offset = offset_;
    }

    /**Returns node offset.*/
    size_type offset() const
    {
        return m_offset;
    }

    /**Returns reference to node offset.*/
    size_type& offset_reference()
    {
        return m_offset;
    }

    /////////////////////////////////////////////////////
    // Link helper functions
    /////////////////////////////////////////////////////

    /**Returns instance of inode_writer pointing to a specific relative node.*/
    inode_writer< NodeDescriptorT, ContainerT > operator() ( int field_ ) const
    {
        return inode_writer< NodeDescriptorT, ContainerT >( *m_ptr_container, value( field_ ) );
    }

    /////////////////////////////////////////////////////
    // Graph modeling functions
    /////////////////////////////////////////////////////

    /**Inserts N copies of value_type() at the end of container, and establishes new node position.*/
    inode_writer< NodeDescriptorT, ContainerT >& operator<<=( int size_ )
    {
        // 0................m_ptr_container->size()
        // |                |
        // v                v
        // |--------|-fill->|<-resize->|
        //          ^                  ^
        //          |                  |
        //          m_offset...........size_

        assert( size_ ); // node size (number of elements to insert) should not be zero

        if ( m_offset == m_ptr_container->size() ) {
            m_ptr_container->insert(
                m_ptr_container->end(), 
                size_,          // number of elements to insert
                value_type()    // value to insert
                );

        } else {
            // is there an area to fill ?
            if ( m_offset < m_ptr_container->size() ) {
                std::fill(
                    m_ptr_container->begin() + m_offset,
                    m_ptr_container->begin()
                    +
                    std::min(
                        m_offset + size_,
                        m_ptr_container->size()
                    ),
                    value_type()    // value to fill
                    );
            }
            // is there an area to resize ?
            if ( m_ptr_container->size() < m_offset + size_ ) {
                m_ptr_container->resize(
                    m_offset + size_//,
                    //value_type()
                    );
            }
        }

        return *this;
    }

#ifdef _XST_PAIR_H_INCLUDED_    // if lambda.h is included
    /**Assign data at the specified node position.*/
    template< typename LambdaT >
    inode_writer< NodeDescriptorT, ContainerT >& operator=( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef typename ContainerT::iterator container_iterator_T;
        container_iterator_T container_iterator( m_ptr_container->begin() + m_offset );
        container_iterator << lambda_;
        return *this;
    }

    /**Inserts multidimensional lambda into container at the current
    * position of the node.
    */
    template< typename LambdaT >
    inode_writer< NodeDescriptorT, ContainerT >& operator<<=( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        // is there enough space to accommodate lambda elements ?
        if ( m_ptr_container->size() < m_offset + lambda_.capacity_ ) {
            // yes
            m_ptr_container->resize( m_offset + lambda_.capacity_ );
        }

        return operator=( lambda_ );
    }
#endif // _XST_PAIR_H_INCLUDED_

    /**Positive link with another node.*/
    template< typename RhsT >
    inode_writer< NodeDescriptorT, ContainerT >& operator+= ( RhsT rhs_ )
    {
        value( next_link ) = rhs_.offset();
        return *this;
    }

    /**Negative link with another node.*/
    template< typename RhsT >
    inode_writer< NodeDescriptorT, ContainerT >& operator-= ( RhsT rhs_ )
    {
        rhs_.value( rhs_.previous_link ) = offset();
        return *this;
    }

    /**Bidirectional link between two nodes.*/
    template< typename RhsT >
    inode_writer< NodeDescriptorT, ContainerT >& operator^= ( RhsT rhs_ )
    {
        *this += rhs_;
        *this -= rhs_;
        return *this;
    }

    /**Negative many-to-one link from children to parent.*/
    template< typename RhsT >
    inode_writer< NodeDescriptorT, ContainerT >& operator*= ( RhsT child_ )
    {
        *this -= child_;         // negative link with first child
        while ( child_.value( child_.next_link )  ) {
            child_.offset( child_.value( child_.next_link ) );
            *this -= child_;     // negative link with next child
        }

        return *this;
    }

    /**Returns mutable reference to the underlying STL container.*/
    ContainerT& container()
    {
        return *m_ptr_container;
    }

    /**Returns constant reference to the underlying STL container.*/
    ContainerT const& container() const
    {
        return *m_ptr_container;
    }

protected:
    /////////////////////////////////////////////////////////////
    // inode_writer state variables
    /////////////////////////////////////////////////////////////

    /**Offset of the node.*/
    size_type m_offset;

    /**Pointer to STL container for data storage.*/
    ContainerT* m_ptr_container;

}; // inode_writer

// Overloaded binary operators

/**Inserts N copies of default values at the end of the sequence container.
*  Adjusts node position accordingly to the insertion point.
*  If N is zero, no insertions are made.
*/
template< typename NodeDescriptorT, typename ContainerT >
inode_writer< NodeDescriptorT, ContainerT > const& operator<<(
    inode_writer< NodeDescriptorT, ContainerT > const& lhs_,
    int size_
    )
{
    inode_writer< NodeDescriptorT, ContainerT >* plhs_ = const_cast< inode_writer< NodeDescriptorT, ContainerT >* >( &lhs_ );
    plhs_->offset( lhs_.container().size() );
    if ( size_ ) {
        plhs_->container().resize( lhs_.offset() + size_ );
    }

    return lhs_;
}

#ifdef _XST_PAIR_H_INCLUDED_    // if lambda.h is included
/**Set node position at end of container and
* insert lambda composite into container.
*/
template< typename NodeDescriptorT, typename ContainerT, typename LambdaT >
inode_writer< NodeDescriptorT, ContainerT > const& operator<<(
    inode_writer< NodeDescriptorT, ContainerT > const& lhs_,
    xst_lambda_wrap< LambdaT > const& lambda_
    )
{
    inode_writer< NodeDescriptorT, ContainerT >* plhs_ = const_cast< inode_writer< NodeDescriptorT, ContainerT >* >( &lhs_ );
    plhs_->offset( lhs_.container().size() );
    //container_inserter< ContainerT > inserter( plhs_->container() );
    //lambda_.traverse_top_down( inserter );
    std::back_insert_iterator< ContainerT > inserter( plhs_->container() );
    inserter << lambda_;
    return lhs_;
}
#endif // _XST_PAIR_H_INCLUDED_

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator==(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() == offset_;
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator==(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ == inode_.offset();
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator!=(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() != offset_;
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator!=(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ != inode_.offset();
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator<(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() < offset_;
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator<(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ < inode_.offset();
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator<=(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() <= offset_;
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator<=(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ <= inode_.offset();
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator>(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() > offset_;
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator>(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ > inode_.offset();
}

/**Compare offsets.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator>=(
    inode_writer< NodeDescriptorT, ContainerT > const& inode_,
    typename ContainerT::size_type offset_
    )
{
    return inode_.offset() >= offset_;
}

/**Compares offsets of two nodes.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator>=(
    typename ContainerT::size_type offset_,
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return offset_ >= inode_.offset();
}

/**Bidirectional iterator: comparison of two inode_writer objects returns true if
* positions of the nodes are equal, false otherwise.
*
*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator== (
    inode_writer< NodeDescriptorT, ContainerT > const& one_,
    inode_writer< NodeDescriptorT, ContainerT > const& another_
    )
{
    return ( one_.offset() == another_.offset() );
}

/**Bidirectional iterator: true if node positions are different.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator!= (
    inode_writer< NodeDescriptorT, ContainerT > const& one_,
    inode_writer< NodeDescriptorT, ContainerT > const& another_
    )
{
    return ( one_.offset() != another_.offset() );
}

/**Bidirectional iterator: true if node position is zero.*/
template< typename NodeDescriptorT, typename ContainerT >
bool operator! (
    inode_writer< NodeDescriptorT, ContainerT > const& inode_
    )
{
    return !inode_.offset();
}

}   // namespace cttl

#endif // _CTTL_INODE_WRITER_H_INCLUDED_
