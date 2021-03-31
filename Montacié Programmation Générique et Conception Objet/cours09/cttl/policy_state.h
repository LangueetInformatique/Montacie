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

/**@file policy_state.h
* @brief Defines default white space policy classes.
*
*  @see
*  - cttl::policy_default
*  - cttl::policy_space< flag_follow_space >
*  - cttl::policy_space< flag_follow_region >
*  - cttl::policy_space< flag_cpp_comments >
*
*/

// policy_state.h

#ifndef _CTTL_POLICY_STATE_H_INCLUDED_
#define _CTTL_POLICY_STATE_H_INCLUDED_

#include "xtl_bitflags.h"

namespace cttl {

    /**@struct policy_default
    *@brief Provides default implementation of CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
    *
    * @remarks
    *        All user-defined policy classes should directly or
    *        indirectly derive from this class.
    *
    *  @see
    *  - cttl::const_edge
    *  - cttl::edge
    *
    */
    struct policy_default
    {
        /**Defines space policy for strict-mode grammar evaluation.
        *
        * @remarks
        * - Strict policy must provide default constructor.
        * - Strict policy is allocated statically.
        * - For thread safety concerns, strict policy class
        * must have stateless implementation.
        *
        */
        typedef policy_default strict_policy_T;

        /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
        *   to evaluate grammar expression matching the white space.
        *
        * @tparam SubstrT
        *        specifies type of the parseable
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
        *        cttl::const_edge or cttl::edge.
        *
        * @param substr_
        *        references to the parseable substring.
        *
        * @return
        *        absolute position of the substring upper boundary
        *        after expression that matches white space is evaluated.
        *
        * @post
        *       The function must
        *       - always succeed
        *       - return a valid offset within the specified substring.
        *
        * @remarks
        *       Default policy implements strict parsing of the
        *       user input. This implementation of
        *       <tt>match</tt></A> is empty. It does
        *       no white space recognition whatsoever. 
        *
        */
        template< typename SubstrT >
        static inline size_t match( SubstrT& substr_ )
        {
            return substr_.first.offset();
        }

        /** Moves upper boundary of the parseable substring outside of
        *   a <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a> specified by the user.
        *
        * @tparam SubstrT
        *        specifies type of the parseable substring, such as
        *        @c cttl::const_edge or @c cttl::edge.
        *
        * @return
        *       true if offset is adjusted, false otherwise.
        *
        * @post
        *   If this function returns true, the upper boundary of the @c substr_
        *   is relocated even if the substring length becomes invalid.
        *   Therefore, the caller is responsible for checking whether
        *   the @c substr_ has valid length upon return.
        *  
        */
        template< typename SubstrT >
        static inline bool lower_bound( size_t, SubstrT& )
        {
            return false;
        }

        /**Validates @c offset_ position against <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> and adjusts
        * the position accordigly.
        *
        * @param offset_
        *   specifies entry position into the map of void regions.
        *
        * @return
        *    Adjusted position, if intersection with a <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a>
        *    was found, unchanged position otherwise.
        *
        */
        static inline size_t lower_bound( size_t offset_, size_t )
        {
            return offset_;
        }

        /**Adjusts map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> according to the specified
        * position and delta offset.
        *
        */
        static inline void region_adjust( size_t, int )
        {
        }

        /**Creates new <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a>.*/
        static inline void region_insert( size_t, size_t )
        {
        }

        /**Erases <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a>(s).*/
        static inline void region_erase( size_t, size_t )
        {
        }

        /**Returns substring pointed by the range of offsets,
        * excluding existing <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
        *
        */
        template< typename StringT >
        static inline StringT region_difference( StringT const& str_, size_t first_offset_, size_t second_offset_ )
        {
            return str_.substr(
                first_offset_,
                second_offset_ - first_offset_
                );
        }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
        /**Defines default run-time behavior
        * of @c runtime_match()
        * grammar evaluation algorithm.
        *
        */
        static const int xtl_flag_default = 0;

        /**Turns on runtime find mode
        * of @c runtime_match()
        * grammar evaluation algorithm.
        *
        */
        static const int xtl_flag_runtime_find = 1;

        /**Turns on runtime bang_find mode
        * of @c runtime_match()
        * grammar evaluation algorithm.
        *
        */
        static const int xtl_flag_runtime_bang_find = 2;

        /**Swiss army knife flags.*/
        cttl_impl::xtl_bitflags m_flags;
#endif //CTTL_STATEFUL_RUNTIME_MATCH

        /**Default constructor.*/
        policy_default()
#ifdef CTTL_STATEFUL_RUNTIME_MATCH
            :
        m_flags( xtl_flag_default )
#endif //CTTL_STATEFUL_RUNTIME_MATCH
        {
        }

    };  // struct policy_default


}   // namespace cttl

#endif // _CTTL_POLICY_STATE_H_INCLUDED_
