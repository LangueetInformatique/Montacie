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

/**@file edge_functors.h
* @brief Defines functor objects to execute mutating operations
* on collections of CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substrings</a>.
*
*  @see
*  - cttl::edge_replace
*  - cttl::edge_first_insert_go
*  - cttl::edge_first_insert_stay
*  - cttl::edge_second_insert_go
*  - cttl::edge_second_insert_stay
*
*/

// edge_functors.h

#ifndef _CTTL_EDGE_FUNCTORS_H_INCLUDED_
#define _CTTL_EDGE_FUNCTORS_H_INCLUDED_

#include "edge.h"

namespace cttl {

    /**@struct edge_replace
    * @brief Substring replacer.
    *
    *        Function object, which, if called as a function,
    *        replaces substring with the string
    *        specified when the function object was constructed.
    *
    * @tparam PolicyT
    *        specifies
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *        The default policy is cttl::policy_default.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    struct edge_replace : public std::unary_function< edge< PolicyT, StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        edge_replace( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        *  replaces substring with the string
        *  specified when the function object was constructed.
        *
        */
        void operator()( edge< PolicyT, StringT >& edge_ )
        {
            edge_.text( m_str );
        }

        /**Stores source string to replace targets.*/
        StringT m_str;
    };

    /**@struct edge_first_insert_go
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts substring specified when the function object
    *        was constructed, at the offset pointed by the
    *        upper boundary, cttl::const_edge::first.
    *
    * @tparam PolicyT
    *        specifies
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *        The default policy is cttl::policy_default.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    struct edge_first_insert_go : public std::unary_function< edge< PolicyT, StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        edge_first_insert_go( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**      Function call operator
        *        inserts substring specified when the function object
        *        was constructed, at the offset pointed by the
        *        upper boundary cttl::const_edge::first.
        *
        * @post
        *        All nodes at the insertion position, as well as
        *        at the higher offset positions, are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( edge< PolicyT, StringT >& edge_ )
        {
            edge_.first.insert_go( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };

    /**@struct edge_first_insert_stay
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts string specified when the function object
    *        was constructed, at the offset pointed by the
    *        upper boundary cttl::const_edge::first.
    *
    * @tparam PolicyT
    *        specifies
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *        The default policy is cttl::policy_default.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    struct edge_first_insert_stay : public std::unary_function< edge< PolicyT, StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        edge_first_insert_stay( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        *  inserts string specified when the function object
        *  was constructed, at the offset pointed by the
        *  upper boundary cttl::const_edge::first.
        *
        * @post
        *        All nodes at higher offset positions are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( edge< PolicyT, StringT >& edge_ )
        {
            edge_.first.insert_stay( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };

    /**@struct edge_second_insert_go
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts substring specified when the function object
    *        was constructed, at the offset pointed by the
    *        upper boundary cttl::const_edge::second.
    *
    * @tparam PolicyT
    *        specifies
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *        The default policy is cttl::policy_default.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    struct edge_second_insert_go : public std::unary_function< edge< PolicyT, StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        edge_second_insert_go( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        *  inserts substring specified when the function object
        *  was constructed, at the offset pointed by the
        *  lower boundary cttl::const_edge::second.
        *
        * @post
        *        All nodes at the insertion position, as well as
        *        at the higher offset positions, are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( edge< PolicyT, StringT >& edge_ )
        {
            edge_.second.insert_go( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };

    /**@struct edge_second_insert_stay
    * @brief Substring inserter.
    *
    *        Function object, which, if called as a function,
    *        inserts string specified when the function object
    *        was constructed, at the offset pointed by the
    *        lower boundary cttl::const_edge::second.
    *
    * @tparam PolicyT
    *        specifies
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *        The default policy is cttl::policy_default.
    *
    * @tparam StringT
    *        specifies type of the encapsulated string.
    *        The default is
    *        <a href="http://www.cplusplus.com/reference/string/">std::string</a>
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    struct edge_second_insert_stay : public std::unary_function< edge< PolicyT, StringT >, void >
    {
        /**Constructs function object and initializes it with the source substring.*/
        edge_second_insert_stay( StringT const& str_ )
            :
        m_str( str_ )
        {
        }

        /**Function call operator,
        * inserts string specified when the function object
        * was constructed, at the offset pointed by the
        * lower boundary cttl::const_edge::second.
        *
        * @post
        *        All nodes at the higher offset positions are adjusted forward
        *        according to the length of the inserted substring.
        *
        */
        void operator() ( edge< PolicyT, StringT >& edge_ )
        {
            edge_.second.insert_stay( m_str );
        }

        /**Stores string to insert.*/
        StringT m_str;
    };

}   // namespace cttl

#endif // _CTTL_EDGE_FUNCTORS_H_INCLUDED_
