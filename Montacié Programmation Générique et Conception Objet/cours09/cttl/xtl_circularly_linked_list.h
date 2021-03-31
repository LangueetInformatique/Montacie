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

/**@file xtl_circularly_linked_list.h
* @brief Defines cttl_impl::xtl_circular_node class.
*
*  @see
*  - cttl::node
*
*/

// xtl_circularly_linked_list.h

#ifndef _CTTL_XTL_CIRCULARLY_LINKED_LIST_H_INCLUDED_
#define _CTTL_XTL_CIRCULARLY_LINKED_LIST_H_INCLUDED_

namespace cttl_impl {

    /**@class xtl_circular_node
    * @brief Implements element of a circularly-linked list.
    *
    * @tparam LinkT
    *        specifies class of the object derived from the @c xtl_circular_node.
    *
    * @remarks
    *        CTTL substrings define @c LinkT as cttl::node.
    *
    */
    template< typename LinkT >
    class xtl_circular_node
    {
    protected:
        /**Stores pointer to the next element in the list.
        * 
        * @remarks
        *   Note that @c m_pnext is declared mutable to support common
        *   semantics when copying, assigning, and
        *   passing elements of the list by value or by reference.
        *
        * @par
        *   The client program is spared of being required to keep
        *   objects on the list mutable at all times. Instead, @c m_pnext mutates
        *   quietly on objects that are traditionally referenced
        *   in immutable manner, such as the argument of a copy constructor.
        *
        */
        mutable LinkT* m_pnext;

        /**Default constructor links the element with itself.*/
        xtl_circular_node()
            :
        m_pnext( NULL )
        {
            m_pnext = static_cast< LinkT* >( this );
        }

        /**Copy constructor quietly links elements together,
        * creating circularly-linked list.
        *
        */
        xtl_circular_node( LinkT const& other_ )
            :
        m_pnext( NULL )
        {
            m_pnext = static_cast< LinkT* >( this );
            other_.list_insert( *static_cast< LinkT* >( this ) );
        }

        /**Destructor removes element from the list.*/
        ~xtl_circular_node()
        {
            list_remove( *static_cast< LinkT* >( this ) );
            assert( list_single() );
        }

        /**Insert the other element in front of this one.
        */
        LinkT const& list_insert( LinkT const& other_ ) const
        {
            // check that other_ is not already on some list
            assert( other_.list_single() );

            // check that other_ is not already on our list
            assert( -1 == list_distance( other_ ) );

            other_.m_pnext = m_pnext;
            m_pnext = const_cast< LinkT* >( &other_ );
            return other_;
        }

        /**Returns size of the list.
        *
        * @remarks
        *     The smallest list size is 1 (one).
        *
        */
        size_t list_size() const
        {
            int size = 1 + m_pnext->list_distance( *static_cast< LinkT* >( this ) );
            assert( size > 0 );
            return size;
        }

        /**Measures distance between two elements.
        *
        * @param other_
        *     Reference to another list element.
        *
        * @return
        *     The function returns the number of hops
        *     required to reach the other list element.
        *     @n In addition, the function may return the following
        *     values:
        *     - Minus one: indicates that two elements are not on the same list.
        *     Its meaning is that the distance cannot be measured.
        *     @n @n
        *     - Zero: indicates that the element is single; no other
        *     elements are present on the list.
        *
        * @remarks
        *     The unit of measurement is the number of hops
        *     required to reach the other element.
        *
        */
        int list_distance( LinkT const& other_ ) const
        {
            if ( &other_ == static_cast< LinkT const* >( this ) && list_single() ) {
                return 0;

            } else if ( other_.list_single() ) {
                // distance cannot be measured
                return -1;
            }

            int hops = 1;

            LinkT const* previous = static_cast< LinkT const* >( this );
            LinkT const* iter = m_pnext;
            while ( iter != &other_ ) {
                previous = iter;
                if ( previous == static_cast< LinkT const* >( this ) ) {
                    return -1; // other_ element not found on our list
                }
                iter = iter->m_pnext;
                ++hops;
            }

            return hops;
        }

        /**Returns true if the element is single, false otherwise.*/
        bool list_single() const
        {
            return ( m_pnext == static_cast< LinkT const* >( this ) );
        }

        /**Removes element from the list.
        *
        * @return
        *  true if the element was removed, false otherwise.
        *
        * @post
        *  The removed element becomes single after successful removal.
        *
        */
        bool list_remove( LinkT& other_ )
        {
            if ( &other_ == static_cast< LinkT* >( this ) ) {
                // Removing itself from the list:
                if ( list_single() ) {
                    // ignore static_cast< LinkT* >( this ) call:
                    // the element is single
                    return false;
                } else {
                    // ask your sibling to remove you from the list:
                    return m_pnext->list_remove( other_ );
                }
            }

            if ( other_.list_single() ) // distance cannot be measured
                return false;

            LinkT* previous = static_cast< LinkT* >( this );
            LinkT* iter = m_pnext;
            while ( iter != &other_ ) {
                previous = iter;
                if ( previous == static_cast< LinkT* >( this ) ) {
                    assert( other_.list_single() );
                    return false;
                }
                iter = iter->m_pnext;
            }
            previous->m_pnext = iter->m_pnext;

            // make the element single after successful removal:
            other_.m_pnext = &other_;

            return true;
        }

    private:

        // Assignment is disabled:
        xtl_circular_node< LinkT >& operator=( xtl_circular_node< LinkT > const& );

    };  // class xtl_circular_node

}   // namespace cttl_impl

#endif // _CTTL_XTL_CIRCULARLY_LINKED_LIST_H_INCLUDED_
