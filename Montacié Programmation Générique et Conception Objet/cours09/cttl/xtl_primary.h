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

/**@file xtl_primary.h
 * @brief Defines CTTL
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 * implementation classes.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 *  @see
 *  - cttl_impl::xtl_primary
 *  - cttl_impl::xtl_bool
 *  - cttl_impl::xtl_keyword
 *  - cttl_impl::xtl_char_symbol
 *  - cttl_impl::xtl_char
 *  - cttl_impl::xtl_char_begin
 *  - cttl_impl::xtl_char_end
 *  - cttl_impl::xtl_iswhat_begin
 *  - cttl_impl::xtl_iswhat_first
 *  - cttl_impl::xtl_iswhat_end
 *  - cttl_impl::xtl_iswhat_entity
 *  - cttl_impl::xtl_iswwhat_begin
 *  - cttl_impl::xtl_iswwhat_first
 *  - cttl_impl::xtl_iswwhat_end
 *  - cttl_impl::xtl_iswwhat_entity
 *  - cttl_impl::xtl_text_begin
 *  - cttl_impl::xtl_text_ref_begin
 *  - cttl_impl::xtl_text_end
 *  - cttl_impl::xtl_text_ref_end
 *  - cttl_impl::xtl_text_first
 *  - cttl_impl::xtl_text_ref_first
 *  - cttl_impl::xtl_text_entity
 *  - cttl_impl::xtl_text_ref_entity
 *  - cttl_impl::xtl_text_symbol
 *  - cttl_impl::xtl_text_ref_symbol
 *  - cttl_impl::xtl_position_bof
 *  - cttl_impl::xtl_position_eof
 *  - cttl_impl::xtl_predicate
 *  - cttl_impl::xtl_member_predicate
 *  - cttl_impl::xtl_traced_predicate_base
 *  - cttl_impl::xtl_member_traced_predicate
 *  - cttl_impl::xtl_static_traced_predicate
 *  - cttl_impl::xtl_traced_rule()
 *
 */

// xtl_primary.h

#ifndef _CTTL_XTL_PRIMARY_H_INCLUDED_
#define _CTTL_XTL_PRIMARY_H_INCLUDED_

#include <set>

namespace cttl_impl {

/**@struct xtl_primary
 * @brief Implements
 * grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
 * of terminal symbol
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 * implementation classes.
 *
 * @remarks
 *      Derived objects must implement functions
 @code
        template< typename SubstrT >
        size_t internal_match( SubstrT& edge_ );

        template< typename SubstrT >
        size_t internal_find( SubstrT& edge_ );
 @endcode
 *
 * @post
 *      If either @c internal_match(), or @c internal_find() succeed,
 *      they should:
 @code
    // 1. Set ending position of the matched symbol:
    edge_.first.offset( end_offset );

    // 2. Return starting position of the matched symbol:
    return begin_offset;
 @endcode
 *
 */
template< typename DerivedT >
struct xtl_primary {

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // check white space
        size_t saved_first_offset = edge_.space_policy().match( edge_ );

        if ( saved_first_offset == SubstrT::string_T::npos ) {
            CTTL_TRACE_STATIC_RESULT( false, 'L', "space policy failed" );
            return SubstrT::string_T::npos;
        }

        if ( edge_.length() == 0 || edge_.length() == SubstrT::string_T::npos ) {
            // restore original position
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "empty substring" );
            return SubstrT::string_T::npos;
        }

        // edge_.first is now guaranteed to be outside white space

        size_t match_offset = static_cast< DerivedT* >( this )->internal_match( edge_ );

        if ( match_offset == SubstrT::string_T::npos ) {
            // match failed:
            // restore original position
            edge_.first.offset( saved_first_offset );
            return SubstrT::string_T::npos;
        }

        if ( edge_.length() == SubstrT::string_T::npos ) {
            // although match suceeded, it is beyond substring bounds.
            // restore original position
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme match out-of-substring bounds" );
            return SubstrT::string_T::npos;
        }

        // here:
        //  match_offset is starting position (upper boundary) of the matched symbol;
        //  edge_.first.offset() is symbol ending position (lower boundary);
        //  primary_length( match_offset, edge_ ) is symbol length.

        //  if primary_length() is greater than zero, then edge_.first.offset()
        //  minus 1 is points to the last character of the matched symbol.

        // check lower boundary of the lexeme against client regions:
        if ( primary_length( match_offset, edge_.first.offset() ) ) {
            // offset of the previous character
            size_t offset_minus_one = edge_.first.offset() - 1;
            if ( offset_minus_one != edge_.space_policy().lower_bound( offset_minus_one, edge_.second.offset() ) ) {
                // No additional match attemts needed, because
                // symbol is atomic object, it cannot be split by client regions.
                // Upper bound of the symbol is inside client region.
                // Restore original position and fail:
                edge_.first.offset( saved_first_offset );
                CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme match inside void region" );
                return SubstrT::string_T::npos;
            }
        }

        // success
        return match_offset;
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol search algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        size_t saved_first_offset = edge_.first.offset();

replay_find:
        if ( edge_.length() == 0 || edge_.length() == SubstrT::string_T::npos ) {
            // proposed substring is invalid
            // restore original position
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme find: invalid substring" );
            return SubstrT::string_T::npos;
        }

        size_t offset_before_replay = edge_.first.offset();
        size_t match_offset = static_cast< DerivedT* >( this )->internal_find( edge_ );

        if ( match_offset == SubstrT::string_T::npos ) {
            // find failed:
            // restore original position
            edge_.first.offset( saved_first_offset );
            return SubstrT::string_T::npos;
        }

        // here:
        //  match_offset is starting position (upper boundary) of the matched symbol;
        //  edge_.first.offset() is symbol ending position (lower boundary);
        //  primary_length( match_offset, edge_ ) is symbol length.

        //  if primary_length() is greater than zero, then edge_.first.offset()
        //  minus 1 is points to the last character of the matched symbol.

        if ( edge_.length() == SubstrT::string_T::npos ) {
            // find suceeded beyond lower boundary of the substring:
            // restore original position
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme find: out-of-substring bounds" );
            return SubstrT::string_T::npos;
        }

        // Check if symbol boundaries are outside
        // existing client regions:

        if ( edge_.space_policy().lower_bound( match_offset, edge_ ) ) {
            // Upper boundary is inside of a client region.
            // Replay the search, if edge_.first.offset()
            // has made actual progress since last time:
            if ( offset_before_replay < edge_.first.offset() )
                goto replay_find;

            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme find: lower bound inside void region" );
            return SubstrT::string_T::npos;
        }

        if ( primary_length( match_offset, edge_.first.offset() )
            &&
            edge_.space_policy().lower_bound( edge_.first.offset() - 1, edge_ ) )
        {
            // Lower boundary is inside a client region.
            // Replay the search, if edge_.first.offset()
            // has made actual progress since last time:
            if ( offset_before_replay < edge_.first.offset() )
                goto replay_find;

            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_TEXT_RESULT( false, 'L', "lexeme find: upper bound inside void region" );
            return SubstrT::string_T::npos;
        }

        // success
        return match_offset;
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for repeatable search algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    * @remarks
    *        CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
    *        delegates implementation of its @c bang_find() to @c find().
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        return find( edge_ );
    }

protected:
    /**Calculates length of the matched symbol.
    *
    * @param upper_offset_
    *        points to upper boundary of the matched symbol.
    *
    * @param lower_offset_
    *        points to lower boundary of the matched symbol.
    *
    * @return
    *        length of the symbol.
    *
    */
    int primary_length( size_t upper_offset_, size_t lower_offset_ ) const
    {
        return int( lower_offset_ ) - int( upper_offset_ );
    }

};  // xtl_primary

/**@class xtl_bool
 * @brief Defines behavior of true and false C++ literals
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * Template class @c xtl_bool provides implementation for family of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexemes</a>
 *
 @code
    begin( true )   xtl_bool< true >( true )     always succeeds
    begin( false )  xtl_bool< true >( false )    always fails
   symbol( true )   xtl_bool< false >( true )    succeeds unless at the end of the substring
           true     xtl_bool< false >( true )    shorthand for symbol( true )
  !symbol( true )   !xtl_bool< false >( true )   always succeeds
 !!symbol( true )   !!xtl_bool< false >( true )  always succeeds
   symbol( false )  xtl_bool< false >( false )   always fails
           false    xtl_bool< false >( false )   shorthand for symbol( false )
 @endcode
 *
 * @see
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6280_beg_tru.html">begin(true)</a>
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6290_beg_fls.html">begin(false)</a>
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6260_sym_tru.html">symbol(true)</a>
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6270_sym_fls.html">symbol(false)</a>
 *
 */
template< bool accept_empty_universe = false >
class xtl_bool {

private:
    bool m_value;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_bool( bool value_ )
    : m_value( value_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        if ( !accept_empty_universe && m_value && !edge_.length() ) {
            CTTL_TRACE_TEXT_RESULT( false, char( '0' + char( m_value ) ), "epsilon match: empty substring" );
            return SubstrT::string_T::npos;
        }

        return internal_match( edge_ );
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol search algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        return internal_match( edge_ );
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a> algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        return internal_match( edge_ );
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset of the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typedef typename SubstrT::char_T char_T;
        // edge state is ready;
        // set correct offset of this lexeme:
        if ( m_value ) {
            CTTL_TRACE_RESULT( true, char( '0' + char( m_value ) ) );
            return edge_.first.offset();
        } else {
            CTTL_TRACE_RESULT( false, char( '0' + char( m_value ) ) );
            return SubstrT::string_T::npos;
        }
    }

};  // class xtl_bool


/**@class xtl_keyword
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6300_set.html">begin std::set&lt;std::string&gt;</a>,
 *        the string set
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @remarks
 *        This lexeme implementation class supports only @c match() evaluation.
 *
 */
template< typename StringT >
class xtl_keyword {

private:
    std::set< StringT > const& m_keywords;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_keyword( std::set< StringT > const& keywords_ )
    : m_keywords( keywords_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_keyword< StringT > const& operator=( xtl_keyword< StringT > const& );

public:
    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT const& edge_ ) const
    {
        // edge state is ready;
        // return correct offset of this lexeme:
        if ( m_keywords.find( edge_.text() ) != m_keywords.end() ) {
            CTTL_TRACE_RESULT( true, 'S' );
            return edge_.first.offset();
        }

        CTTL_TRACE_RESULT( false, 'S' );
        return SubstrT::string_T::npos;
    }

};  // xtl_keyword


/**@class xtl_char_symbol
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6220_symbol.html">symbol()</a>
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_char_symbol : public xtl_primary< xtl_char_symbol > {

public:

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for symbol search algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    * @remarks
    *        This <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
    *        delegates implementation of its @c find()
    *        to @c xtl_primary<xtl_char_symbol>::match().
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        return xtl_primary< xtl_char_symbol >::match( edge_ );
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for repeatable search algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    * @remarks
    *        CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
    *        delegates implementation of its @c bang_find()
    *        to @c xtl_primary<xtl_char_symbol>::match().
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        return xtl_primary< xtl_char_symbol >::match( edge_ );
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        // successful match
        // set match starting position
        size_t match_offset = edge_.first.offset();
        // set match ending position
        edge_.first.offset( match_offset + 1 );
        CTTL_TRACE_TEXT_RESULT( true, edge_.first[ -1 ], "symbol" );
        return match_offset;
    }

};  // xtl_char_symbol


/**@class xtl_char
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6310_sym_char.html">symbol(char)</a>,
 *        character literal <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam CharT
 *        specifies character type.
 *
 */
template< typename CharT >
class xtl_char : public xtl_primary< xtl_char< CharT > > {

private:
    /**Stores character to match.*/
    CharT m_char;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_char( CharT char_ )
    : m_char( char_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( edge_.parent()[ edge_.first.offset() ] == m_char ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();
            // set match ending position
            edge_.first.offset( match_offset + 1 );
            CTTL_TRACE_TEXT_RESULT( true, m_char, "char" );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "char" );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        size_t new_offset = edge_.parent().find( m_char, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position
            edge_.first.offset( new_offset + 1 );
            CTTL_TRACE_TEXT_RESULT( true, m_char, "char" );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "char" );
        return SubstrT::string_T::npos;
    }
};  // xtl_char


/**@class xtl_char_begin
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6330_beg_char.html">begin(char)</a>,
 *        upper boundary of single character literal
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam CharT
 *        specifies character type.
 *
 */
template< typename CharT >
class xtl_char_begin : public xtl_primary< xtl_char_begin< CharT > > {

private:
    /**Stores character to match.*/
    CharT m_char;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_char_begin( CharT char_ )
    : m_char( char_ )
    {
        }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( edge_.parent()[ edge_.first.offset() ] == m_char ) {
            // successful match
            CTTL_TRACE_TEXT_RESULT( true, m_char, "begin( char )" );
            // set match starting position
            return edge_.first.offset();
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "begin( char )" );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        size_t new_offset = edge_.parent().find( m_char, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, m_char, "begin( char )" );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "begin( char )" );
        return SubstrT::string_T::npos;
    }

};  // xtl_char_begin


/**@class xtl_char_end
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6340_end_char.html">end(char)</a>,
 *        lower boundary of the character literal <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam CharT
 *        specifies character type.
 *
 */
template< typename CharT >
class xtl_char_end : public xtl_primary< xtl_char_end< CharT > > {

private:
    /**Stores character to match.*/
    CharT m_char;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_char_end( CharT char_ )
    : m_char( char_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( edge_.parent()[ edge_.first.offset() ] == m_char ) {
            // match starting and ending position are the same
            edge_.first.offset( edge_.first.offset() + 1 );
            CTTL_TRACE_TEXT_RESULT( true, m_char, "end( char )" );
            return edge_.first.offset();
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "end( char )" );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        size_t new_offset = edge_.parent().find( m_char, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position
            edge_.first.offset( ++new_offset );
            CTTL_TRACE_TEXT_RESULT( true, m_char, "end( char )" );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, m_char, "end( char )" );
        return SubstrT::string_T::npos;
    }
};  // xtl_char_end



/**@class xtl_iswhat_begin
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6360_beg_is.html">begin(iswhat_T)</a>
 *        upper boundary of character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswhat_begin : public xtl_primary< xtl_iswhat_begin > {

private:
    /**Stores address of C character classification routine.*/
    iswhat_T m_iswhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswhat_begin( iswhat_T iswhat_ )
    : m_iswhat( iswhat_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT const& edge_ )
    {
        if ( m_iswhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match: ending position is current:
            CTTL_TRACE_TEXT_RESULT( true, '<', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return edge_.first.offset();
        }
        CTTL_TRACE_TEXT_RESULT( false, '<', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswhat );
        if ( it == str.end() ) {
            CTTL_TRACE_TEXT_RESULT( false, '<', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        edge_.first.offset( new_offset );
        CTTL_TRACE_TEXT_RESULT( true, '<', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return new_offset;
    }

};  // xtl_iswhat_begin


/**@class xtl_iswhat_first
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6380_fst_is.html">first(iswhat_T)</a>,
 *        first character of a character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswhat_first : public xtl_primary< xtl_iswhat_first > {

private:
    /**Stores address of C character classification routine.*/
    iswhat_T m_iswhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswhat_first( iswhat_T iswhat_ )
    : m_iswhat( iswhat_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();
            // ending position:
            // at least one character in this entity is present
            edge_.first.offset( edge_.first.offset() + 1 );
            CTTL_TRACE_TEXT_RESULT( true, 'F', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return match_offset;
        }
        CTTL_TRACE_TEXT_RESULT( false, 'F', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswhat );
        if ( it == str.end() ) {
            CTTL_TRACE_TEXT_RESULT( false, 'F', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        // set find ending position:
        // at least one character in this entity is present
        edge_.first.offset( new_offset + 1 );
        CTTL_TRACE_TEXT_RESULT( true, 'F', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return new_offset;
    }

};  // xtl_iswhat_first


/**@class xtl_iswhat_end
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6370_end_is.html">end(iswhat_T)</a>,
 *        lower boundary of character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswhat_end : public xtl_primary< xtl_iswhat_end > {

private:
    /**Stores address of C character classification routine.*/
    iswhat_T m_iswhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswhat_end( iswhat_T iswhat_ )
    : m_iswhat( iswhat_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched entity.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        size_t match_offset = xtl_primary< xtl_iswhat_end >::match( edge_ );

        if ( match_offset != SubstrT::string_T::npos ) {
            return edge_.first.offset();
        }
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            typename SubstrT::string_T const& str = edge_.parent();
            typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();
            it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswhat ) ) );
            // set ending position
            if ( it != str.end() )
                edge_.first.offset( std::distance( str.begin(), it ) );
            else
                edge_.first.offset( str.length() );

            CTTL_TRACE_TEXT_RESULT( true, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return match_offset;

        } else if ( edge_.first.offset() ) {
            // check if we are at the entity-end position:
            // offset of the previous character
            size_t offset_minus_one = edge_.first.offset() - 1;
            if ( offset_minus_one != edge_.space_policy().lower_bound( offset_minus_one, edge_.second.offset() ) ) {
                // offset_minus_one is in the void region
                CTTL_TRACE_TEXT_RESULT( false, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
                return SubstrT::string_T::npos;
            }

            if ( m_iswhat( edge_.parent()[ offset_minus_one ] ) ) {
                // successful match
                CTTL_TRACE_TEXT_RESULT( true, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
                return edge_.first.offset();
            }
        }
        CTTL_TRACE_TEXT_RESULT( false, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswhat );
        if ( it == str.end() ) {
            CTTL_TRACE_TEXT_RESULT( false, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return SubstrT::string_T::npos;
        }

        // find ending position
        size_t new_offset = SubstrT::string_T::npos;
        it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswhat ) ) );
        if ( it != str.end() )
            new_offset = std::distance( str.begin(), it );
        else
            new_offset = str.length();

        // set find ending position
        edge_.first.offset( new_offset );
        CTTL_TRACE_TEXT_RESULT( true, '>', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return new_offset;
    }

};  // xtl_iswhat_end


/**@class xtl_iswhat_entity
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6350_ent_is.html">entity(iswhat_T)</a>,
 *        character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswhat_entity : public xtl_primary< xtl_iswhat_entity > {

private:
    /**Stores address of C character classification routine.*/
    iswhat_T m_iswhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswhat_entity( iswhat_T iswhat_ )
    : m_iswhat( iswhat_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched entity.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            typename SubstrT::string_T const& str = edge_.parent();
            typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();
            it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswhat ) ) );
            // set ending position
            if ( it != str.end() )
                edge_.first.offset( std::distance( str.begin(), it ) );
            else
                edge_.first.offset( str.length() );

            CTTL_TRACE_TEXT_RESULT( true, '$', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return match_offset;
        }
        CTTL_TRACE_TEXT_RESULT( false, '$', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswhat );
        if ( it == str.end() ) {
            CTTL_TRACE_TEXT_RESULT( false, '$', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        // set find starting position
        size_t match_offset = new_offset;

        // find ending position
        it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswhat ) ) );
        if ( it != str.end() )
            new_offset = std::distance( str.begin(), it );
        else
            new_offset = str.length();

        // set find ending position
        edge_.first.offset( new_offset );
        CTTL_TRACE_TEXT_RESULT( true, '$', xtl_trace_grammar::cttl_trace_iswhat( m_iswhat ) );
        return match_offset;
    }

};  // xtl_iswhat_entity


/**@class xtl_iswwhat_begin
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6360_beg_is.html">begin(iswwhat_T)</a>,
 *        upper boundary of wide character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswwhat_begin : public xtl_primary< xtl_iswwhat_begin > {

private:
    /**Stores address of C wide character classification routine.*/
    iswwhat_T m_iswwhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswwhat_begin( iswwhat_T iswwhat_ )
    : m_iswwhat( iswwhat_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT const& edge_ )
    {
        if ( m_iswwhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match: ending position is current:
            CTTL_TRACE_RESULT( true, '<' );
            return edge_.first.offset();
        }
        CTTL_TRACE_RESULT( false, '<' );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswwhat );
        if ( it == str.end() ) {
            CTTL_TRACE_RESULT( false, '<' );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        // ending position is the same
        edge_.first.offset( new_offset );
        CTTL_TRACE_RESULT( true, '<' );
        return new_offset;
    }

};  // xtl_iswwhat_begin


/**@class xtl_iswwhat_first
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6380_fst_is.html">first(iswwhat_T)</a>,
 *        first character of a wide character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswwhat_first : public xtl_primary< xtl_iswwhat_first > {

private:
    /**Stores address of C character classification routine.*/
    iswwhat_T m_iswwhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswwhat_first( iswwhat_T iswwhat_ )
    : m_iswwhat( iswwhat_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswwhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();
            // ending position: at least one character in this entity is present
            edge_.first.offset( edge_.first.offset() + 1 );
            CTTL_TRACE_RESULT( true, 'F' );
            return match_offset;
        }
        CTTL_TRACE_RESULT( false, 'F' );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswwhat );
        if ( it == str.end() ) {
            CTTL_TRACE_RESULT( false, 'F' );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        // set find ending position: at least one character
        // in this entity is present
        edge_.first.offset( new_offset + 1 );
        CTTL_TRACE_RESULT( true, 'F' );
        return new_offset;
    }

};  // xtl_iswwhat_first


/**@class xtl_iswwhat_end
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6370_end_is.html">end(iswwhat_T)</a>,
 *        lower boundary of wide character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswwhat_end : public xtl_primary< xtl_iswwhat_end > {

private:
    /**Stores address of C wide character classification routine.*/
    iswwhat_T m_iswwhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswwhat_end( iswwhat_T iswwhat_ )
    : m_iswwhat( iswwhat_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched entity.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        size_t match_offset = xtl_primary< xtl_iswwhat_end >::match( edge_ );

        if ( match_offset != SubstrT::string_T::npos ) {
            return edge_.first.offset();
        }
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswwhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            typename SubstrT::string_T const& str = edge_.parent();
            typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();
            it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswwhat ) ) );
            // set ending position
            if ( it != str.end() )
                edge_.first.offset( std::distance( str.begin(), it ) );
            else
                edge_.first.offset( str.length() );

            CTTL_TRACE_RESULT( true, '>' );
            return match_offset;

        } else if ( edge_.first.offset() ) {
            // check if we are at the entity-end position:
            // offset of the previous character
            size_t offset_minus_one = edge_.first.offset() - 1;
            if ( offset_minus_one != edge_.space_policy().lower_bound( offset_minus_one, edge_.second.offset() ) ) {
                // offset_minus_one is in the void region
                CTTL_TRACE_RESULT( false, '>' );
                return SubstrT::string_T::npos;
            }

            if ( m_iswwhat( edge_.parent()[ offset_minus_one ] ) ) {
                // successful match
                CTTL_TRACE_RESULT( true, '>' );
                return edge_.first.offset();
            }
        }
        CTTL_TRACE_RESULT( false, '>' );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswwhat );
        if ( it == str.end() ) {
            CTTL_TRACE_RESULT( false, '>' );
            return SubstrT::string_T::npos;
        }

        // find ending position
        size_t new_offset = SubstrT::string_T::npos;
        it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswwhat ) ) );
        if ( it != str.end() )
            new_offset = std::distance( str.begin(), it );
        else
            new_offset = str.length();

        // set find ending position
        edge_.first.offset( new_offset );
        // note: LHS is always checked for void region.
        // because the length of this lexeme is zero,
        // test for RHS void region is never
        // attempted, which is the desired behavior
        CTTL_TRACE_RESULT( true, '>' );
        return new_offset;
    }

};  // xtl_iswwhat_end


/**@class xtl_iswwhat_entity
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6350_ent_is.html">entity(iswwhat_T)</a>,
 *        wide character entity <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_iswwhat_entity : public xtl_primary< xtl_iswwhat_entity > {

private:
    /**Stores address of C character classification routine.*/
    iswwhat_T m_iswwhat;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_iswwhat_entity( iswwhat_T iswwhat_ )
    : m_iswwhat( iswwhat_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for wide character entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched entity.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        if ( m_iswwhat( edge_.parent()[ edge_.first.offset() ] ) ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            typename SubstrT::string_T const& str = edge_.parent();
            typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();
            it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswwhat ) ) );
            // set ending position
            if ( it != str.end() )
                edge_.first.offset( std::distance( str.begin(), it ) );
            else
                edge_.first.offset( str.length() );

            CTTL_TRACE_RESULT( true, '$' );
            return match_offset;
        }
        CTTL_TRACE_RESULT( false, '$' );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        typename SubstrT::string_T::const_iterator it = str.begin() + edge_.first.offset();

        // find starting position
        it = std::find_if( it, str.end(), m_iswwhat );
        if ( it == str.end() ) {
            CTTL_TRACE_RESULT( false, '$' );
            return SubstrT::string_T::npos;
        }

        size_t new_offset = std::distance( str.begin(), it );
        // set find starting position
        size_t match_offset = new_offset;

        // find ending position
        it = std::find_if( it, str.end(), std::not1( std::ptr_fun( m_iswwhat ) ) );
        if ( it != str.end() )
            new_offset = std::distance( str.begin(), it );
        else
            new_offset = str.length();

        // set find ending position
        edge_.first.offset( new_offset );
        CTTL_TRACE_RESULT( true, '$' );
        return match_offset;
    }

};  // xtl_iswwhat_entity


/**@class xtl_text_begin
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6410_btext.html">begin(text)</a>,
 *        upper boundary of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_begin : public xtl_primary< xtl_text_begin< StringT > > {

private:
    /**Stores text to match.*/
    StringT m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_begin( StringT const& any_text_ )
        : m_any_text( any_text_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched text.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // ending position is the same
            CTTL_TRACE_TEXT_RESULT( true, '<', m_any_text.c_str() );
            return edge_.first.offset();
        }

        CTTL_TRACE_TEXT_RESULT( false, '<', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched text.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // ending position is the same
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '<', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '<', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_begin


/**@class xtl_text_ref_begin
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6410_btext.html">begin(text)</a>,
 *        upper boundary of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_ref_begin : public xtl_primary< xtl_text_ref_begin< StringT > > {

private:
    /**Stores reference to text to match.*/
    StringT const& m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_ref_begin( StringT const* str_ptr_ )
        : m_any_text( *str_ptr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_text_ref_begin< StringT >& operator=( xtl_text_ref_begin< StringT > const& );

public:
    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched text.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // ending position is current
            CTTL_TRACE_TEXT_RESULT( true, '<', m_any_text.c_str() );
            return edge_.first.offset();
        }

        CTTL_TRACE_TEXT_RESULT( false, '<', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched text.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // ending position is the same
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '<', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '<', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_ref_begin


/**@class xtl_text_end
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6420_etext.html">end(text)</a>,
 *        lower boundary of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_end : public xtl_primary< xtl_text_end< StringT > > {

private:
    /**Stores text to match.*/
    StringT m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_end( StringT const& any_text_ )
        : m_any_text( any_text_ )
    {
    }

    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for multi-character entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        size_t match_offset = xtl_primary< xtl_text_end >::match( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            return edge_.first.offset();
        }
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            size_t new_offset = str.find_first_not_of( m_any_text, edge_.first.offset() );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set match ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
            return match_offset;

        } else if ( edge_.first.offset() ) {
            // check if we are at the entity-end position:
            // offset of the previous character
            size_t offset_minus_one = edge_.first.offset() - 1;
            if ( offset_minus_one != edge_.space_policy().lower_bound( offset_minus_one, edge_.second.offset() ) ) {
                // offset_minus_one is in the void region
                CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
                return SubstrT::string_T::npos;
            }

            if ( m_any_text.find( str[ offset_minus_one ] ) != SubstrT::string_T::npos ) {
                // successful match
                CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
                return edge_.first.offset();
            }
        }

        CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // find ending position
            new_offset = str.find_first_not_of( m_any_text, new_offset );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_end


/**@class xtl_text_ref_end
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6420_etext.html">end(text)</a>,
 *        lower boundary of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_ref_end : public xtl_primary< xtl_text_ref_end< StringT > > {

private:
    /**Stores reference to the text to match.*/
    StringT const& m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_ref_end( StringT const* str_ptr_ )
        : m_any_text( *str_ptr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_text_ref_end< StringT >& operator=( xtl_text_ref_end< StringT > const& );

public:
    // run-time

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for multi-character entity match algorithm,
    *  starting at the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbol.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        size_t match_offset = xtl_primary< xtl_text_ref_end >::match( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            return edge_.first.offset();
        }
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            size_t new_offset = str.find_first_not_of( m_any_text, edge_.first.offset() );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set match ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
            return match_offset;

        } else if ( edge_.first.offset() ) {
            // check if we are at the entity end position:
            // offset of the previous character
            size_t offset_minus_one = edge_.first.offset() - 1;
            if ( offset_minus_one != edge_.space_policy().lower_bound( offset_minus_one, edge_.second.offset() ) ) {
                // offset_minus_one is in the void region
                CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
                return SubstrT::string_T::npos;
            }

            if ( m_any_text.find( str[ offset_minus_one ] ) != SubstrT::string_T::npos ) {
                // successful match
                CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
                return edge_.first.offset();
            }
        }

        CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // find ending position
            new_offset = str.find_first_not_of( m_any_text, new_offset );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '>', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '>', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_ref_end


/**@class xtl_text_first
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6430_ftext.html">first(text)</a>,
 *        first character of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_first : public xtl_primary< xtl_text_first< StringT > > {

private:
    /**Stores text to match.*/
    StringT m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_first( StringT const& any_text_ )
        : m_any_text( any_text_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();
            // ending position: at least one character in this entity is present
            edge_.first.offset( edge_.first.offset() + 1 );
            CTTL_TRACE_TEXT_RESULT( true, 'F', m_any_text.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'F', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position: at least one
            // character in this entity is present
            edge_.first.offset( new_offset + 1 );
            CTTL_TRACE_TEXT_RESULT( true, 'F', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'F', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_first


/**@class xtl_text_ref_first
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6430_ftext.html">first(text)</a>,
 *        first character of the user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_ref_first : public xtl_primary< xtl_text_ref_first< StringT > > {

private:
    /**Stores reference to text to match.*/
    StringT const& m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_ref_first( StringT const* str_ptr_ )
        : m_any_text( *str_ptr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_text_ref_first< StringT >& operator=( xtl_text_ref_first< StringT > const& );

public:
    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();
            // ending position: at least one character
            // in this entity is present
            edge_.first.offset( edge_.first.offset() + 1 );
            CTTL_TRACE_TEXT_RESULT( true, 'F', m_any_text.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'F', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position: at least one character
            // in this entity is present
            edge_.first.offset( new_offset + 1 );
            CTTL_TRACE_TEXT_RESULT( true, 'F', m_any_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'F', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_ref_first


/**@class xtl_text_entity
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6400_ntext.html">entity(text)</a>,
 *        user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_entity : public xtl_primary< xtl_text_entity< StringT > > {

private:
    /**Stores text to match.*/
    StringT m_any_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_entity( typename StringT::value_type const* any_text_ )
        : m_any_text( any_text_ )
    {
    }

    /**Constructs and initializes the object.*/
    xtl_text_entity( StringT const& any_text_ )
        : m_any_text( any_text_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_any_text.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            size_t new_offset = str.find_first_not_of( m_any_text, edge_.first.offset() );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set match ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '$', m_any_text.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '$', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_any_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find starting position
            size_t match_offset = new_offset;

            // find ending position
            new_offset = str.find_first_not_of( m_any_text, new_offset );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '$', m_any_text.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '$', m_any_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_entity


/**@class xtl_text_ref_entity
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6400_ntext.html">entity(text)</a>,
 *        user-defined multi-character entity
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_ref_entity : public xtl_primary< xtl_text_ref_entity< StringT > > {

private:
    /**Stores reference to text to match.*/
    StringT const& m_str_ref;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_ref_entity( StringT const* str_ptr_ )
        : m_str_ref( *str_ptr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_text_ref_entity< StringT >& operator=( xtl_text_ref_entity< StringT > const& );

public:
    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( m_str_ref.find( str[ edge_.first.offset() ] ) != SubstrT::string_T::npos ) {
            // successful match
            // set match starting position
            size_t match_offset = edge_.first.offset();

            // find ending position
            size_t new_offset = str.find_first_not_of( m_str_ref, edge_.first.offset() );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            // set match ending position
            edge_.first.offset( new_offset );
            CTTL_TRACE_TEXT_RESULT( true, '$', m_str_ref.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '$', m_str_ref.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched entity.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        size_t new_offset = str.find_first_of( m_str_ref, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find starting position
            size_t match_offset = new_offset;

            // find ending position
            new_offset = str.find_first_not_of( m_str_ref, new_offset );
            if ( new_offset == SubstrT::string_T::npos )
                new_offset = str.length();

            edge_.first.offset( new_offset );   // set ending position
            CTTL_TRACE_TEXT_RESULT( true, '$', m_str_ref.c_str() );
            return match_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, '$', m_str_ref.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_ref_entity


/**@class xtl_text_symbol
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6390_stext.html">symbol(text)</a>,
 *        string literal <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_symbol : public xtl_primary< xtl_text_symbol< StringT > > {

private:
    /**Stores text to match.*/
    StringT m_text;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_symbol( StringT const& str_ref_ )
        : m_text( str_ref_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( edge_.first.offset() + m_text.length() <= str.length() ) {
            if ( str.substr( edge_.first.offset(), m_text.length() ) == m_text ) {
                // successful match
                // set match starting position
                size_t match_offset = edge_.first.offset();
                // set match ending position
                edge_.first.offset( edge_.first.offset() + m_text.length() );
                CTTL_TRACE_TEXT_RESULT( true, 'T', m_text.c_str() );
                return match_offset;
            }
        }
        
        CTTL_TRACE_TEXT_RESULT( false, 'T', m_text.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        size_t new_offset = edge_.parent().find( m_text, edge_.first.offset() );
        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position
            edge_.first.offset( new_offset + m_text.length() );
            CTTL_TRACE_TEXT_RESULT( true, 'T', m_text.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'T', m_text.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_symbol


/**@class xtl_text_ref_symbol
 * @brief Implements behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6390_stext.html">symbol(text)</a>,
 *        string literal <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam StringT
 *        specifies type of the encapsulated string.
 *
 */
template< typename StringT >
class xtl_text_ref_symbol : public xtl_primary< xtl_text_ref_symbol< StringT > > {

private:
    /**Stores reference to text to match.*/
    StringT const& m_text_ref;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_text_ref_symbol( StringT const* str_ptr_ )
        : m_text_ref( *str_ptr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_text_ref_symbol< StringT >& operator=( xtl_text_ref_symbol< StringT > const& );

public:
    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_match( SubstrT& edge_ )
    {
        typename SubstrT::string_T const& str = edge_.parent();
        if ( edge_.first.offset() + m_text_ref.length() <= str.length() ) {
            if ( str.substr( edge_.first.offset(), m_text_ref.length() ) == m_text_ref ) {
                // successful match
                // set match starting position
                size_t match_offset = edge_.first.offset();
                // set match ending position
                edge_.first.offset( edge_.first.offset() + m_text_ref.length() );
                CTTL_TRACE_TEXT_RESULT( true, 'T', m_text_ref.c_str() );
                return match_offset;
            }
        }

        CTTL_TRACE_TEXT_RESULT( false, 'T', m_text_ref.c_str() );
        return SubstrT::string_T::npos;
    }

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>, specified
    *        by the @c edge_ parameter, is consumed accordingly to
    *        the size of the matched symbol:
    @code
    // 1. The ending position of the matched symbol is set:
    edge_.first.offset( end_offset );

    // 2. Starting position of the matched symbol is returned:
    return begin_offset;
    @endcode
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbol.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t internal_find( SubstrT& edge_ )
    {
        size_t new_offset = edge_.parent().find(
            m_text_ref,
            edge_.first.offset()
            );

        if ( new_offset != SubstrT::string_T::npos ) {
            // successful find
            // set find ending position
            edge_.first.offset( new_offset + m_text_ref.length() );
            CTTL_TRACE_TEXT_RESULT( true, 'T', m_text_ref.c_str() );
            return new_offset;
        }

        CTTL_TRACE_TEXT_RESULT( false, 'T', m_text_ref.c_str() );
        return SubstrT::string_T::npos;
    }
};  // xtl_text_ref_symbol


/**@class xtl_position_bof
 * @brief Defines behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6240_begin.html">begin()</a>,
 *        beginning of the user input <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_position_bof {

public:
    // compile-time
    // nothing to do

    // run-time

    /**Implements match algorithm for beginning of the user input.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset zero.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& edge_ )
    {
        if ( edge_.first.offset() == 0 ) {
            CTTL_TRACE_RESULT( true, 'A' );
            return 0;
        }
        
        CTTL_TRACE_RESULT( false, 'A' );
        return SubstrT::string_T::npos;
    }

    /**Implements search algorithm for beginning of the user input.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: this algorithm always succeeds and returns absolute
    *        offset zero.
    *
    */
    template< typename SubstrT >
    static size_t find( SubstrT& edge_ )
    {
        // set beginning of the substring
        edge_.first.offset( 0 );
        CTTL_TRACE_RESULT( true, 'A' );
        return 0;
    }

    /**Implements repeatable search algorithm for beginning of the user input.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: this algorithm always succeeds and returns absolute
    *        offset zero.
    *
    */
    template< typename SubstrT >
    static size_t bang_find( SubstrT& edge_ )
    {
        return find( edge_ );
    }

};  // xtl_position_bof


/**@class xtl_position_eof
 * @brief Defines behavior of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6250_end.html">end()</a>,
 *        parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> lower boundary <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a>
 *        inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 */
class xtl_position_eof {

public:
    // compile-time
    // nothing to do

    // run-time

    /**Implements match algorithm for parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> lower boundary position.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the lower boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    * @post
    *        If algorithm succeeds, the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> becomes empty.
    *
    */
    template< typename SubstrT >
    static size_t match( SubstrT& edge_ )
    {
        if ( !edge_.length() ) {
            CTTL_TRACE_STATIC_RESULT( true, 'Z', "EOF" );
            return edge_.second.offset();
        }

        if ( edge_.length() == SubstrT::string_T::npos )
            return find( edge_ );

        // check for void/white space
        size_t saved_first_offset = edge_.space_policy().match( edge_ );

        if ( saved_first_offset == SubstrT::string_T::npos ) {
            CTTL_TRACE_STATIC_RESULT( false, 'Z', "EOF: space policy failed" );
            return SubstrT::string_T::npos;
        }

        if ( !edge_.length() ) {
            CTTL_TRACE_STATIC_RESULT( true, 'Z', "EOF" );
            return edge_.second.offset();
        }

        // restore original position
        edge_.first.offset( saved_first_offset );
        CTTL_TRACE_STATIC_RESULT( false, 'Z', "EOF" );
        return SubstrT::string_T::npos;
    }

    /**Implements search algorithm for parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> lower boundary position.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: this algorithm always succeeds and returns absolute
    *        offset corresponding to the lower boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        The parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> becomes empty.
    *
    */
    template< typename SubstrT >
    static size_t find( SubstrT& edge_ )
    {
        // set find ending position
        edge_.first.offset( edge_.second.offset() );
        CTTL_TRACE_STATIC_RESULT( true, 'Z', "EOF" );
        return edge_.second.offset();
    }

    /**Implements repeatable search algorithm for parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> lower boundary position.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: this algorithm always succeeds and returns absolute
    *        offset corresponding to the lower boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        The parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a> becomes empty.
    *
    */
    template< typename SubstrT >
    static size_t bang_find( SubstrT& edge_ )
    {
        return find( edge_ );
    }

};  // xtl_position_eof


/**@class xtl_predicate
 * @brief Implements behavior of CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>
 *        named <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a>.
 *
 * @tparam Static_predicateT
 *        specifies type which is copy-constructible,
 *        and also, if @c SubstrT is a typename that represents
 *        @c cttl::const_edge or @c cttl::edge, then @c Static_predicateT
 *        can be invoked as
 @code
        size_t operator()( SubstrT& );
 @endcode
 *
 */
template< typename Static_predicateT >
class xtl_predicate {

    /**Stores address of the rule implementation function.*/
    Static_predicateT m_predicate;

public:

    /**Constructs and initializes the object.*/
    xtl_predicate( Static_predicateT const& predicate_ )
        :
    m_predicate( predicate_ )
    {
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  match algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'R' );
        return m_predicate( edge_ );
    }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( 'R' );
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_find );
        return m_predicate( edge_ );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  repeatable search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( 'R' );
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_bang_find );
        return m_predicate( edge_ );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

};  // xtl_predicate


/**@class xtl_member_predicate
 * @brief Implements behavior of CTTL member
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>,
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a>.
 *
 * @tparam ObjectT
 *        specifies type of C++ class that defines
 *        non-static member function @c Member_predicateT.
 *
 * @tparam Member_predicateT
 *        specifies type of a non-static member function,
 *        accepting specialization of @c cttl::const_edge or @c cttl::edge
 *        as a parameter, and returning @c size_t <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
 *
 */
template< typename ObjectT, typename Member_predicateT >
class xtl_member_predicate {

    /**Stores reference to an instance of the implementation class.*/
    ObjectT& m_object;

    /**Stores address of the rule implementation member function.*/
    Member_predicateT m_predicate;

public:

    /**Constructs and initializes the object.*/
    xtl_member_predicate(
        ObjectT& object_ref_,
        Member_predicateT& predicate_
        )
        :
    m_object( object_ref_ ),
        m_predicate( predicate_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_member_predicate< ObjectT, Member_predicateT >& operator=( xtl_member_predicate< ObjectT, Member_predicateT > const& );

public:
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  match algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'R' );
        return std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ );
    }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( 'R' );
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_find );
        return std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  repeatable search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( 'R' );
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_bang_find );
        return std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

};  // xtl_member_predicate


/**@struct xtl_traced_predicate_base
 * @brief Base class for
 *        traced <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptors</a>.
 *
 */
struct xtl_traced_predicate_base {

    /**Stores source line that invokes the rule.*/
    int m_line;

    /**Stores rule name.*/
    std::string m_rule_name;

    /**Constructs and initializes the object.*/
    xtl_traced_predicate_base( int line_, char const* rule_name_ )
        :
    m_line( line_ ),
        m_rule_name( rule_name_ )
    {
    }

    /**Displays prolog of the trace message.*/
    template< typename SubstrT >
    void trace_prolog( SubstrT& edge_, char const* mode_ )
    {
        xtl_trace_grammar::depth( +1 );
        CTTL_UNILOG_STREAM << xtl_trace_grammar::exact_edge2text( edge_, true ).c_str();
        xtl_trace_grammar::build_skyline( '-' );

        CTTL_UNILOG_STREAM
            << m_line
            << "->"
            << mode_
            << m_rule_name
            << '@'
            << edge_.first.offset()
            << '-'
            << edge_.second.offset()
            ;
        CTTL_UNILOG_FLUSH;
    }

    /**Displays epilog of the trace message.*/
    template< typename SubstrT >
    size_t trace_epilog( SubstrT& edge_, size_t result_ )
    {
        using std::min;
        using std::max;
        if ( result_ != CTTL_STD_STRING::npos ) {
            size_t begin_offset = result_;
            size_t end_offset = min(
                begin_offset + xtl_trace_grammar::fragment_length,
                edge_.first.offset()
                );

            // needed in case if underlying fragment mutates:
            begin_offset = min( begin_offset, end_offset );
            end_offset = max( begin_offset, end_offset );

            //ik-6/6/2009 removed text_absolute_substring()
            //std::string str_temp = edge_.text_absolute_substring(
            //  begin_offset,
            //  end_offset
            //  ).c_str();
            assert( begin_offset <= end_offset );
            assert( end_offset <= edge_.parent().length() );
            //if ( begin_offset != end_offset ) (
            //  return StringT();
            //)
            //ik-12/1/2012//std::string str_temp = edge_.parent().substr(
            typename SubstrT::string_T str_temp = edge_.parent().substr(
                begin_offset,
                end_offset - begin_offset
                );
            //ik-6/6/2009

            CTTL_UNILOG_STREAM << xtl_trace_grammar::exact_edge2text( edge_, true ).c_str();
            xtl_trace_grammar::build_skyline( '+' );
            CTTL_UNILOG_STREAM
                << m_line
                << "<-"
                << m_rule_name
                << '@'
                << begin_offset
                << '-'
                << max( end_offset, edge_.first.offset() )
                << '\t'
                << '\''
                << xtl_trace_grammar::whitespace2monospace( str_temp )
                << '\''
                ;
            CTTL_UNILOG_FLUSH;

        } else {
            CTTL_UNILOG_STREAM << xtl_trace_grammar::exact_edge2text( edge_, false ).c_str();
            xtl_trace_grammar::build_skyline( '~' );
            CTTL_UNILOG_STREAM
                << m_line
                << "<-"
                << m_rule_name
                << '@'
                << edge_.first.offset()
                ;
            CTTL_UNILOG_FLUSH;
        }
        xtl_trace_grammar::depth( -1 );
        return result_;
    }

};  // xtl_traced_predicate_base


/**@class xtl_member_traced_predicate
 * @brief Implements behavior of CTTL member
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>,
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a>.
 *
 * @tparam ObjectT
 *        specifies type of C++ class that defines
 *        non-static member function @c Member_predicateT.
 *
 * @tparam Member_predicateT
 *        specifies type of a non-static member function,
 *        accepting specialization of @c cttl::const_edge or @c cttl::edge
 *        as a parameter, and returning @c size_t <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
 *
 */
template< typename ObjectT, typename Member_predicateT >
class xtl_member_traced_predicate : public xtl_traced_predicate_base {

    /**Stores reference to an instance of the implementation class.*/
    ObjectT& m_object;

    /**Stores address of the rule implementation member function.*/
    Member_predicateT m_predicate;

public:

    /**Constructs and initializes the object.*/
    xtl_member_traced_predicate(
        int line_,
        char const* rule_name_,
        ObjectT& object_ref_,
        Member_predicateT& predicate_
        )
        :
    xtl_traced_predicate_base( line_, rule_name_ ),
        m_object( object_ref_ ),
        m_predicate( predicate_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_member_traced_predicate< ObjectT, Member_predicateT >&  operator=( xtl_member_traced_predicate< ObjectT, Member_predicateT > const& );

public:
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  match algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        trace_prolog( edge_, "" );
        return trace_epilog(
            edge_,
            std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ )
            );
    }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_find );
        trace_prolog( edge_, "!" );
        return trace_epilog(
            edge_,
            std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ )
            );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  repeatable search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_bang_find );
        trace_prolog( edge_, "!!" );
        return trace_epilog(
            edge_,
            std::mem_fun< size_t, ObjectT, SubstrT& >( m_predicate )( &m_object, edge_ )
            );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

};  // xtl_member_traced_predicate


/**@class xtl_static_traced_predicate
 * @brief Implements behavior of CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>,
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a>.
 *
 * @tparam Static_predicateT
 *        specifies type which is copy-constructible,
 *        and, if @c SubstrT is a typename that represents
 *        @c cttl::const_edge or @c cttl::edge, @c Static_predicateT can be invoked as
 @code
        size_t operator()( SubstrT& );
 @endcode
 *
 */
template< typename Static_predicateT >
class xtl_static_traced_predicate : public xtl_traced_predicate_base {

    /**Stores address of the rule implementation function.*/
    Static_predicateT m_predicate;

public:

    /**Constructs and initializes the object.*/
    xtl_static_traced_predicate(
        int line_,
        char const* rule_name_,
        Static_predicateT const& predicate_
        )
        :
    xtl_traced_predicate_base( line_, rule_name_ ),
        m_predicate( predicate_ )
    {
    }

    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  match algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        trace_prolog( edge_, "" );
        return trace_epilog( edge_, m_predicate( edge_ ) );
    }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_find );
        trace_prolog( edge_, "!" );
        return trace_epilog( edge_, m_predicate( edge_ ) );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Implements
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">rule()</a> function adaptor
    *  repeatable search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a> of the encapsulated rule.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        edge_.space_policy().m_flags.set( cttl::policy_default::xtl_flag_runtime_bang_find );
        trace_prolog( edge_, "!!" );
        return trace_epilog( edge_, m_predicate( edge_ ) );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

};  // xtl_static_traced_predicate


/**Creator helper function that makes an instance of @c cttl_impl::xtl_static_traced_predicate.
*
* @tparam Static_predicateT
*        specifies type which is copy-constructible,
*        and, if @c SubstrT is a typename that represents
*        @c cttl::const_edge or @c cttl::edge, @c Static_predicateT can be invoked as
@code
size_t operator()( SubstrT& );
@endcode
*
* @param line_
*        Source code line that invokes the rule.
*
* @param rule_name_
*        Name of the grammar rule.
*
* @param pred_
*        Address of the rule implementation function, which can be
*        either global, or static member function.
*
* @return
*        Instance of C++ implementation class for CTTL
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6820_static.html">static grammar rule adaptor</a>.
*
*/
template< typename Static_predicateT >
inline xtl_wrap< xtl_static_traced_predicate< Static_predicateT > >
xtl_traced_rule( int line_, char const* rule_name_, const Static_predicateT pred_ )
{
    return xtl_wrap< xtl_static_traced_predicate< Static_predicateT > >(
        xtl_static_traced_predicate< Static_predicateT >(
            line_,
            rule_name_,
            pred_
            )
        );
}

/**Creator helper function that makes an instance of @c cttl_impl::xtl_member_traced_predicate.
*
* @tparam ObjectT
*        specifies type of C++ class that defines
*        non-static member function @c Member_predicateT.
*
* @tparam Member_predicateT
*        specifies type of a non-static member function,
*        accepting specialization of @c cttl::const_edge or @c cttl::edge
*        as a parameter, and returning @c size_t <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
*
* @param line_
*        Source code line that invokes the rule.
*
* @param rule_name_
*        Name of the grammar rule function.
*
* @param object_ref_
*        Object reference.
*
* @param pred_
*        Address of the rule implementation member function,
*        which can be declared either @c const or mutable.
*
* @return
*        Instance of C++ implementation class for CTTL
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6830_mem.html">member function adaptor</a>.
*
*/
template< typename ObjectT, typename PredicateT >
inline xtl_wrap< xtl_member_traced_predicate< ObjectT, PredicateT > >
xtl_traced_rule( int line_, char const* rule_name_, ObjectT& object_ref_, PredicateT pred_ )
{
    return xtl_wrap< xtl_member_traced_predicate< ObjectT, PredicateT > >(
        xtl_member_traced_predicate< ObjectT, PredicateT >(
            line_,
            rule_name_,
            object_ref_,
            pred_ 
            )
        );
}

}   // namespace cttl_impl

#endif // _CTTL_XTL_PRIMARY_H_INCLUDED_
