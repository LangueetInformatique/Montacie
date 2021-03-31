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

/**@file policy.h
 * @brief Defines pre-defined white space policy classes.
 *
 *  @see
 *  - cttl::policy_default
 *  - cttl::policy_space< flag_follow_space >
 *  - cttl::policy_space< flag_follow_region >
 *  - cttl::policy_space< flag_cpp_comments >
 *
 */

// policy.h

#ifndef _CTTL_POLICY_H_INCLUDED_
#define _CTTL_POLICY_H_INCLUDED_

#include "xtl_region_map.h"

namespace cttl {

using namespace cttl_impl;  

/**Suggests that the specialization understands conventional white space.*/
const int flag_follow_space     = 1;

/**Suggests that the specialization understands user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.*/
const int flag_follow_region    = 2;

/**Suggests that the specialization implements greedy evaluation algorithm.*/
const int flag_greedy           = 4;

/**Suggests that the specialization understands C/C++ comments.*/
const int flag_cpp_comments     = 8;

/**Shorthand for both white space and user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.*/
const int flag_follow_either    = flag_follow_space | flag_follow_region;

/**@class policy_mapped_space
 * @brief Base class for region-based white space policy classes.
 *
 */
class policy_mapped_space
{
protected:
    /**Stores instance of the region map object.*/
    xtl_region_map m_region_map;

public:
    /**Defines type of policy for strict-mode grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @remarks
    *   In strict-mode all white space and/or user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are ignored.
    *
    */
    typedef policy_default strict_policy_T;

    /**Greedy match mixer of custom white space finder
    *  with user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a> adjuster.
    *
    * @param derived_expr_
    *   grammar expression that matches white space.
    *
    * @param substr_
    *   parseable substring.
    *
    * @remarks
    * - The user wants to mix white space characters with pre-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    * - This function provides a mixer algorithm to:
    *   - evaluate white space grammar expression @c derived_expr_
    *   - advance the result past any user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a>.
    *
    * @par
    *   During grammar evaluation, <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1200_lexer.html">CTTL lexer</a>
    *   invokes match function of the derived policy class.
    *
    * @par
    *   The derived policy gets first chance to modify upper boundary
    *   of the substring according to its definition
    *   of the white space.
    *
    * @par
    *   Note: this implementation provides greedy evaluation algorithm.
    *
    */
    template< typename ExprT, typename SubstrT >
    size_t match( xtl_wrap< ExprT > derived_expr_, SubstrT& substr_ )
    {
        for( ;; ) {
            if ( derived_expr_.match( substr_ ) != SubstrT::string_T::npos ) {
                // Processed some white space...
                if ( lower_bound( substr_.first.offset(), substr_ ) )
                    // ...result was inside void region - repeat
                    continue;
                else
                    // ...result was not inside a void region, so return:
                    break;
            }
            // No white space was processed...

            if ( lower_bound( substr_.first.offset(), substr_ ) )
                // ...result was inside void region - repeat
                continue;

            // ...result was not inside a void region, so return
            break;
        }

        // Greedy evaluation returns leftmost position:
        return substr_.first.offset();
    }

    /**Moves upper boundary of the substring outside of any
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a> that was specified by the user.
    *
    * @param start_offset_
    *   specifies entry position into the map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    *
    * @param substr_
    *   specifies parseable substring.
    *
    * @return
    *   The function returns true if upper boundary of the
    *   @c substr_ was adjusted.
    *
    * @post
    *   If this function returns true, the upper boundary of the @c substr_
    *   is relocated even if the substring length becomes invalid.
    *   Therefore, the caller is responsible for checking whether
    *   the @c substr_ has valid length upon return.
    *
    */
    template< typename SubstrT >
    bool lower_bound( size_t start_offset_, SubstrT& substr_ )
    {
        size_t adjusted_offset = lower_bound( start_offset_, substr_.second.offset() );
        if ( adjusted_offset != start_offset_ ) {
            substr_.first.offset( adjusted_offset );
            return true;
        }

        return false;
    }

    /**Validates @c offset_ position against <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> and adjusts
    * the position accordigly.
    *
    * @param offset_
    *   specifies entry position into the map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    *
    * @param substr_length_
    *   specifies alternative user input position, usually the
    *   length of the input string.
    *
    * @return
    *    Adjusted position, if intersection with a <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void region</a>
    *    was found, unchanged position otherwise.
    *
    */
    size_t lower_bound( size_t offset_, size_t substr_length_ )
    {
        return m_region_map.find_not_region( offset_, substr_length_ );
    }

    /**Inserts substring at the position specified by the node.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions equal or higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT, typename CharT >
    void text_insert_go( node< StringT >& node_, CharT const* pchar_ )
    {
        text_insert_go( node_, StringT( pchar_ ) );
    }

    /**Inserts substring at the position specified by the node.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions equal or higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT >
    void text_insert_go( node< StringT >& node_, StringT const& str_ )
    {
        size_t str_length = str_.length();

        if ( !str_.length() )
            return; // nothing to do

        size_t insertion_offset = node_.offset();

        node_.parent().insert(
            insertion_offset,
            str_
            );
        
        m_region_map.adjust(
            insertion_offset,
            int( str_length )
            );
        
        xtl_identity_insert_go< StringT > insert_go(
            insertion_offset,
            int( str_length )
            );

        node_.adjust( insert_go );
    }

    /**Inserts substring specified by the @c edge_source_ at
    * the position specified by the @c node_target_.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions equal or higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT, typename PolicyT >
    void text_insert_go( node< StringT >& node_target_, const_edge< PolicyT, StringT > const& edge_source_ )
    {
        StringT const& str = edge_source_.parent();
        size_t source_from_offset_ = edge_source_.first.offset();   // a substring of the source string
        size_t source_to_offset_ = edge_source_.second.offset();

        size_t str_length = source_to_offset_ - source_from_offset_;

        if ( !str.length() )
            return; // nothing to do

        size_t insertion_offset = node_target_.offset();

        node_target_.parent().insert(
            insertion_offset,
            str,
            source_from_offset_,
            str_length
            );
        
        m_region_map.adjust(
            insertion_offset,
            int( str_length )
            );
        
        xtl_identity_insert_go< StringT > insert_go(
            insertion_offset,
            int( str_length )
            );

        node_target_.adjust( insert_go );
    }
    

    /**Inserts substring at the position specified by the node.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT, typename CharT >
    void text_insert_stay( node< StringT >& node_, CharT const* pchar_ )
    {
        text_insert_stay( node_, StringT( pchar_ ) );
    }

    /**Inserts substring at the position specified by the node.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT >
    void text_insert_stay( node< StringT >& node_, StringT const& str_ )
    {
        size_t str_length = str_.length();

        if ( !str_length )
            return; // nothing to do

        size_t insertion_offset = node_.offset();

        node_.parent().insert(
            insertion_offset,
            str_
            );

        m_region_map.adjust(
            insertion_offset,
            int( str_length )
            );
        
        xtl_identity_insert_stay< StringT > insert_stay(
            insertion_offset,
            int( str_length )
            );

        node_.adjust( insert_stay );
    }


    /**Inserts substring at the position specified by the node.
    *
    * @warning
    *   Insertions inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are prohibited!
    *
    * @post
    *   - All nodes at positions higher than the insertion point
    *     are adjusted according to the length of the inserted text.
    *   - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> are adjusted to remain in sync with
    *     the actual content.
    *
    */
    template< typename StringT, typename PolicyT >
    void text_insert_stay( node< StringT >& node_target_, const_edge< PolicyT, StringT > const& edge_source_ )
    {
        StringT const& str = edge_source_.parent();
        size_t source_from_offset_ = edge_source_.first.offset();   // a substring of the source string
        size_t source_to_offset_ = edge_source_.second.offset();

        size_t str_length = source_to_offset_ - source_from_offset_;

        if ( !str_length )
            return; // nothing to do

        size_t insertion_offset = node_target_.offset();

        node_target_.parent().insert(
            insertion_offset,
            str,
            source_from_offset_,
            str_length
            );

        m_region_map.adjust(
            insertion_offset,
            int( str_length )
            );
        
        xtl_identity_insert_stay< StringT > insert_stay(
            insertion_offset,
            int( str_length )
            );

        node_target_.adjust( insert_stay );
    }

    /**Erases all existing <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> from the internal map.*/
    void region_clear()
    {
        m_region_map.clear();
    }

    /**Adjusts internal map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> according
    * to the specified position and delta offset.
    *
    */
    void region_adjust( size_t after_offset_, int delta_offset_ )
    {
        m_region_map.adjust( after_offset_, delta_offset_ );
    }

    /**Adds new region to the internal map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.*/
    void region_insert( size_t first_offset_, size_t second_offset_ )
    {
        m_region_map.insert(
            first_offset_,
            second_offset_
            );
    }

    /**Erase region(s) from the internal map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.*/
    void region_erase( size_t first_offset_, size_t second_offset_ )
    {
        m_region_map.erase(
            first_offset_,
            second_offset_
            );
    }

    /**Extracts and returns the substring specified by two offsets.
    *
    * @remarks
    *  The algorithm excludes <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> intersecting with the
    *  offset range specified by @c first_offset_ and @c second_offset_.
    *
    */
    template< typename StringT >
    StringT region_difference( StringT const& str_, size_t first_offset_, size_t second_offset_ )
    {
        return m_region_map.text_difference(
            str_,
            first_offset_,
            second_offset_
            );
    }

};  // class policy_mapped_space

/**Generic version of pre-defined policy.
*
* @see
*  - cttl::policy_space<flag_follow_space>
*
*/
template< int White_spaceT = flag_follow_space >
struct policy_space
{
};  // struct policy_space<>

/**Space policy specialization to skip white space
* characters ht, lf, vt, ff, cr, and space. 
*
*/
template<>
struct policy_space< flag_follow_space > : public policy_default
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is ungreedy.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        CTTL_TRACE_SILENT( true );
        typedef typename SubstrT::char_T char_T;
        size_t ungreedy_offset = substr_.first.offset();
        (
            true
            ^
            +(
                symbol( char_T( ' ' ) )
                |
                symbol( char_T( '\n' ) )
                |
                symbol( char_T( '\r' ) )
                |
                symbol( char_T( '\t' ) )
                |
                symbol( char_T( '\v' ) )
                |
                symbol( char_T( '\f' ) )
            )
        ).match( substr_ );
        // policy_space is ungreedy:
        return ungreedy_offset;
    }
};  // struct policy_space< flag_follow_space >

/**Space policy specialization to skip user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
*
* @par
* Makes user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> "invisible"
* to the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1200_lexer.html">CTTL lexer</a>.
*
* @par
* The region-based policy is typically used in two-pass algorithms.
* For example,
* - Programming language comments can be detected by the first
*   pass through the input.
*   @n During the first pass, the boundaries of
*   comments are added to the internal map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
*   @n The map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> is kept and maintained by the policy.
*   @n @n
* - During the second pass, the internal map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> is
*   looked up and automatically bypassed by the lexer.
*
*/
template<>
struct policy_space< flag_follow_region > : public policy_mapped_space
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space
    *   defined by the map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is ungreedy.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        size_t ungreedy_offset = substr_.first.offset();
        lower_bound( ungreedy_offset, substr_ );
        // policy_space is ungreedy:
        return ungreedy_offset;
    }
};  // struct policy_space< flag_follow_region >


/**Space policy specialization to skip user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>
* combined with white space characters ht, lf, vt, ff, cr, and space.
*
*/
template<>
struct policy_space< flag_follow_space | flag_follow_region > : public policy_space< flag_follow_region >
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space
    *   defined as a combination of white space characters
    *   and a map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a> provided by
    *   the user.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is ungreedy.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        CTTL_TRACE_SILENT( true );
        typedef typename SubstrT::char_T char_T;
        size_t ungreedy_offset = substr_.first.offset();
        policy_mapped_space::match(
            true
            ^
            +(
                symbol( char_T( ' ' ) )
                |
                symbol( char_T( '\n' ) )
                |
                symbol( char_T( '\r' ) )
                |
                symbol( char_T( '\t' ) )
                |
                symbol( char_T( '\v' ) )
                |
                symbol( char_T( '\f' ) )
            ),
            substr_
        );
        // policy_space is ungreedy:
        return ungreedy_offset;
    }
};  // struct policy_space< flag_follow_space | flag_follow_region >


/**Space policy specialization to skip white space
* characters ht, lf, vt, ff, cr, and space.
*
* @remarks
* This is greedy version of the corresponding space policy.
*
*/
template<>
struct policy_space< flag_greedy | flag_follow_space > : public policy_space< flag_follow_space >
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is greedy.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        CTTL_TRACE_SILENT( true );
        typedef typename SubstrT::char_T char_T;
        (
            true
            ^
            +(
                symbol( char_T( ' ' ) )
                |
                symbol( char_T( '\n' ) )
                |
                symbol( char_T( '\r' ) )
                |
                symbol( char_T( '\t' ) )
                |
                symbol( char_T( '\v' ) )
                |
                symbol( char_T( '\f' ) )
            )
        ).match( substr_ );
        // greedy evaluation:
        return substr_.first.offset();
    }
};  // struct policy_space< flag_greedy | flag_follow_space >


/**Greedy version of the white space policy
*
* @see
*  - cttl::policy_space<flag_greedy|flag_follow_space>
*
*/
template<>
struct policy_space< flag_greedy > : public policy_space< flag_greedy | flag_follow_space >
{
};  // struct policy_space< flag_greedy >


/**Space policy specialization to skip user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
*
* @remarks
* This is greedy version of the corresponding space policy.
*
*/
template<>
struct policy_space< flag_greedy | flag_follow_region > : public policy_space< flag_follow_region >
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space
    *   defined by the map of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is greedy.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        lower_bound( substr_.first.offset(), substr_ );
        // greedy evaluation:
        return substr_.first.offset();
    }
};  // struct policy_space< flag_greedy | flag_follow_region >


/**Space policy specialization to skip user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>
* combined with white space characters ht, lf, vt, ff, cr, and space.
*
* @remarks
* This is greedy version of the corresponding space policy.
*
*/
template<>
struct policy_space< flag_greedy | flag_follow_space | flag_follow_region > : public policy_space< flag_follow_space | flag_follow_region >
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching the white space
    *   defined as a combination of white space characters
    *   combined with the map of user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is greedy.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        CTTL_TRACE_SILENT( true );
        typedef typename SubstrT::char_T char_T;
        policy_mapped_space::match(
            true
            ^
            +(
                symbol( char_T( ' ' ) )
                |
                symbol( char_T( '\n' ) )
                |
                symbol( char_T( '\r' ) )
                |
                symbol( char_T( '\t' ) )
                |
                symbol( char_T( '\v' ) )
                |
                symbol( char_T( '\f' ) )
            ),
            substr_
        );
        // greedy evaluation:
        return substr_.first.offset();
    }
};  // struct policy_space< flag_greedy | flag_follow_space | flag_follow_region >


/**Space policy specialization to skip white space characters
* combined with C and C++ style comments.
*
* @remarks
* This is ungreedy version of the corresponding space policy.
*
*/
template<>
struct policy_space< flag_cpp_comments > : public policy_default
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching white space
    *   characters combined with C and C++ comments.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is ungreedy.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        CTTL_TRACE_SILENT( true );
        size_t ungreedy_offset = substr_.first.offset();
        (
            true ^ rule( policy_space< flag_cpp_comments >::space_and_comment )

        ).match( substr_ );

        // policy_space is ungreedy:
        return ungreedy_offset;
    }

    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   matching white space characters combined with C and C++ comments.
    *
    * @param substr_
    *        references parseable substring.
    *
    * @return
    *        absolute position of the substring upper boundary
    *        after expression is evaluated.
    *
    */
    static size_t space_and_comment( const_edge< policy_default, CTTL_STD_STRING >& substr_ )
    {
        return (
            (
                entity( isspace )
                +
                (
                    (
                        rule( policy_space< flag_cpp_comments >::comment )
                        +
                        rule( policy_space< flag_cpp_comments >::space_and_comment )
                    )
                    |
                    begin( true )
                )
            )
            |
            (
                rule( policy_space< flag_cpp_comments >::comment )
                +
                (
                    rule( policy_space< flag_cpp_comments >::space_and_comment )
                    |
                    begin( true )
                )
            )
            |
            begin( true )

        ).match( substr_ );
    }

    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   matching C and C++ comments.
    *
    * @param substr_
    *        references parseable substring.
    *
    * @return
    *        absolute position of the substring upper boundary
    *        after expression is evaluated.
    *
    */
    static size_t comment( const_edge< policy_default, CTTL_STD_STRING >& substr_ )
    {
        typedef const_edge< policy_default, CTTL_STD_STRING >::char_T char_T;
        return (
            begin( char_T( '/' ) )
            +
            (
                ( symbol( char_T( '/' ) ) + symbol( char_T( '/' ) ) + !begin( symbol( char_T( '\n' ) ) | end() ) )
                |
                ( symbol( char_T( '/' ) ) + symbol( char_T( '*' ) ) + !!( symbol( char_T( '*' ) ) + symbol( char_T( '/' ) ) ) )
            )
        ).match( substr_ );
    }

};  // struct policy_space< flag_cpp_comments >


/**Space policy specialization to skip white space characters
* combined with C and C++ style comments.
*
* @remarks
* This is greedy version of the corresponding space policy.
*
*/
template<>
struct policy_space< flag_greedy | flag_cpp_comments > : public policy_space< flag_cpp_comments >
{
    /** Defines CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a> production rule
    *   to evaluate grammar expression matching white space
    *   characters combined with C and C++ comments.
    *
    * @tparam SubstrT
    *        specifies type of the parseable
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, such as
    *        cttl::const_edge or cttl::edge.
    *
    * @param substr_
    *        references parseable substring.
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
    *       This implementation is greedy.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        policy_space< flag_cpp_comments >::match( substr_ );
        return substr_.first.offset();
    }
};  // struct policy_space< flag_greedy | flag_cpp_comments >

}   // namespace cttl

#endif // _CTTL_POLICY_H_INCLUDED_
