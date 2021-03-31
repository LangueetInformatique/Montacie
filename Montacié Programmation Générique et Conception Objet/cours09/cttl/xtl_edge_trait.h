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

/**@file xtl_edge_trait.h
*@brief Defines utility classes for CTTL internal offset management.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*  @see
*      - cttl_impl::xtl_const_offset_guard
*      - cttl_impl::xtl_mutable_offset_guard
*      - cttl_impl::xtl_edge_offset_guard
*
*/

// xtl_edge_trait.h

#ifndef _CTTL_XTL_EDGE_TRAIT_H_INCLUDED_
#define _CTTL_XTL_EDGE_TRAIT_H_INCLUDED_

#include "node.h"

namespace cttl_impl {

    /**@class xtl_const_offset_guard
    *@brief Models behavior of @c size_t.
    *
    */
    class xtl_const_offset_guard
    {
        /**Stores offset preserved by the guard.*/
        size_t m_offset;
    public:
        /**Constructs new guard and specifies its initial offset.
        *
        * @tparam StringT
        *        specifies type of the
        *        string referenced by cttl::node.
        *
        */
        template< typename StringT >
        xtl_const_offset_guard( cttl::node< StringT > const& node_ )
            :
        m_offset( node_.offset() )
        {
        }

        /**Constructs new guard and specifies its initial offset.
        *
        * @tparam StringT
        *        specifies type of the
        *        string referenced by cttl::node.
        *
        */
        template< typename StringT >
        xtl_const_offset_guard( cttl::node< StringT > const&, size_t offset_ )
            :
        m_offset( offset_ )
        {
        }

        /**Assigns new position preserved by the guard.*/
        xtl_const_offset_guard& operator=( size_t offset_ )
        {
            m_offset = offset_;
            return *this;
        }

        /**Returns position preserved by the guard.*/
        operator size_t() const
        {
            return m_offset;
        }
    };

    /**@class xtl_mutable_offset_guard
    *@brief Models behavior of @c size_t.
    *
    *       The class delegates actual
    *       storage to the private copy of cttl::node.
    *
    * @tparam StringT
    *        specifies type of the
    *        string referenced by cttl::node.
    *
    */
    template< typename StringT >
    class xtl_mutable_offset_guard
    {
        /**Stores instance cttl::node.*/
        cttl::node< StringT > m_node;

    public:

        /**Constructs offset guard from existing cttl::node.
        *
        */
        xtl_mutable_offset_guard( cttl::node< StringT >& node_ )
            :
        m_node( node_ )
        {
        }

        /**Constructs guard object and specifies its initial position.
        *
        */
        xtl_mutable_offset_guard( cttl::node< StringT >& node_, size_t offset_ )
            :
        m_node( node_, offset_ )
        {
        }

        /**Assigns new position preserved by the guard.*/
        xtl_mutable_offset_guard< StringT >& operator=( size_t offset_ )
        {
            m_node.offset( offset_ );
            return *this;
        }

        /**Overloaded assignment operator.*/
        xtl_mutable_offset_guard< StringT >& operator=( xtl_mutable_offset_guard< StringT > const& other_ )
        {
            m_node.offset( other_.m_node.offset() );
            return *this;
        }

        /**Returns position preserved by the guard.*/
        operator size_t() const
        {
            return m_node.offset();
        }

    };


    /**@class xtl_edge_offset_guard
    *@brief Models behavior of a repository for logical positions
    *       of nodes representing <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> boundaries.
    *
    * @tparam EdgeT
    *        specifies CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>
    *        type, either @c cttl::const_edge, or @c cttl::edge
    *        template class.
    *
    */
    template< typename EdgeT >
    struct xtl_edge_offset_guard
    {
        /**Stores logical position
        * of the upper <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> boundary,
        * @c cttl::const_edge::first.
        */
        typename EdgeT::offset_guard_T first;

        /**Stores logical position
        * of the lower <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> boundary,
        * @c cttl::const_edge::second.
        */
        typename EdgeT::offset_guard_T second;

        /**Constructs new objects and initializes storage guards
        *  corresponding to the encapsulated offset boundaries.
        *
        * @param edge_
        *        Reference to CTTL
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>,
        *        either @c cttl::const_edge or @c cttl::edge.
        *
        */
        xtl_edge_offset_guard( EdgeT& edge_ )
            :
        first( edge_.first ),
            second( edge_.second )
        {
        }

        /**Updates stored substring positons.
        *
        * @param edge_
        *        Reference to CTTL
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>,
        *        either @c cttl::const_edge or @c cttl::edge.
        *
        */
        void save( EdgeT& edge_ )
        {
            first = edge_.first.offset();
            second = edge_.second.offset();
        }

        /**Swaps preserved positions with boundaries of another substring.
        *
        * @param edge_
        *        Reference to CTTL
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>,
        *        either @c cttl::const_edge or @c cttl::edge.
        *
        */
        void swap( EdgeT& edge_ )
        {
            size_t temp = first;
            first = edge_.first.offset();
            edge_.first.offset( temp );

            temp = second;
            second = edge_.second.offset();
            edge_.second.offset( temp );
        }

        /**Restores preserved posiotions.
        *
        * @param edge_
        *        Reference to mutable CTTL
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>,
        *        either @c cttl::const_edge or @c cttl::edge.
        *
        */
        void restore( EdgeT& edge_ )
        {
            edge_.first.offset( first );
            edge_.second.offset( second );
        }
    };  // struct xtl_edge_offset_guard

}   // namespace cttl_impl

#endif // _CTTL_XTL_EDGE_TRAIT_H_INCLUDED_
