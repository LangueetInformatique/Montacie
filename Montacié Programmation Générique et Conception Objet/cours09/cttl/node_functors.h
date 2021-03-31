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

/**@file node_functors.h
* @brief Defines functor objects to execute mutating operations
* on collections of cttl::node objects.
*
*  @see
*  - cttl::node_insert_go
*  - cttl::node_insert_stay
*
*/

// node_functors.h

#ifndef _CTTL_NODE_FUNCTORS_H_INCLUDED_
#define _CTTL_NODE_FUNCTORS_H_INCLUDED_

#include "node.h"

namespace cttl {


    /**@struct node_insert_go
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts substring specified when the function object
    *        was constructed, at the offset pointed by the node.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename StringT = CTTL_STD_STRING >
    struct node_insert_go : public std::unary_function< node< StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        node_insert_go( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        *  inserts substring at the position pointed by the node.
        *
        * @post
        *        All nodes at the insertion position, as well as
        *        at the higher offset positions, are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( node< StringT >& node_ )
        {
            node_.insert_go( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };

    /**@struct node_insert_stay
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts substring specified when the function object
    *        was constructed, at the offset pointed by the node.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename StringT = CTTL_STD_STRING >
    struct node_insert_stay : public std::unary_function< node< StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        node_insert_stay( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        *  inserts substring specified when the function object
        *  was constructed, at the offset pointed by the node.
        *
        * @post
        *        All nodes at higher offset positions are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( node< StringT >& node_ )
        {
            node_.insert_stay( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };


}   // namespace cttl

#endif // _CTTL_NODE_FUNCTORS_H_INCLUDED_
