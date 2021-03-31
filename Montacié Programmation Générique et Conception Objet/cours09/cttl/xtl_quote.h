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

/**@file xtl_quote.h
 * @brief Defines implementation classes for CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>s.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 *  @see
 *  - cttl_impl::xtl_quote_base
 *  - cttl_impl::xtl_quote_generic
 *  - cttl_impl::xtl_quote_bool
 *  - cttl_impl::xtl_quote_ansi_double_quote
 *  - cttl_impl::xtl_quote_ansi_single_quote
 *  - cttl_impl::xtl_quote_c_double_quote
 *  - cttl_impl::xtl_quote_c_single_quote
 */

// xtl_quote.h

#ifndef _CTTL_XTL_QUOTE_H_INCLUDED_
#define _CTTL_XTL_QUOTE_H_INCLUDED_

namespace cttl_impl {

/**Defines leximatic type created by
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6280_beg_tru.html"><tt>begin(true)</tt></a>
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>.
 *
 */
typedef xtl_wrap< xtl_bool< true > >
relaxed_bool_T;

/**@class xtl_quote_base
 * @brief Defines behavior of generic
 *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>.
 *
 * @tparam LeftT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing opening clause of the quote.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam RightT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing closing clause of the quote.
 *
 * @tparam DerivedT
 *        specifies C++ class that
 *        provides implementation of the @c match_pair function:
 @code
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ );
 @endcode
 *
 */
template< typename LeftT, typename MiddleT, typename RightT, typename DerivedT >
class xtl_quote_base {

protected:
    /** Stores grammar expression describing opening clause of the quote.*/
    LeftT   m_left;

    /** Stores grammar expression describing interior clause of the quote.*/
    MiddleT m_middle;

    /** Stores grammar expression describing closing clause of the quote.*/
    RightT  m_right;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_quote_base( LeftT const& left_, MiddleT const& middle_, RightT const& right_ )
    : m_left( left_ ), m_middle( middle_ ), m_right( right_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for quote match algorithm.
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
    *        the size of the matched quote.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched quote.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // L+M+R_ balanced pair
        CTTL_TRACE_LEVEL_MATCH( '\"' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T left_offset( edge_.first, m_left.match( edge_ ) );

        if ( left_offset != SubstrT::string_T::npos ) {
            if ( static_cast< DerivedT* >( this )->match_pair( edge_ ) )
                return left_offset;
        }
                
        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_TEXT_RESULT( false, '\"', "xtl_quote_base: opening close failed" );
        return SubstrT::string_T::npos;
    }
    
    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for quote search algorithm.
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
    *        the size of the matched quote.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched quote.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // !L+M+R_
        CTTL_TRACE_LEVEL_FIND( '\"' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T left_offset( edge_.first, m_left.find( edge_ ) );
        if ( left_offset != SubstrT::string_T::npos ) {
            if ( static_cast< DerivedT* >( this )->match_pair( edge_ ) )
                return left_offset;
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_TEXT_RESULT( false, '\"', "xtl_quote_base: opening clause failed" );
        return SubstrT::string_T::npos;
    }
    
    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  for quote repeatable search algorithm.
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
    *        the size of the matched quote.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched quote.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // !!L+M+R_
        CTTL_TRACE_LEVEL_BANG( '\"' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );
        typename SubstrT::offset_guard_T left_offset( edge_.first, SubstrT::string_T::npos );

        while ( ( left_offset = m_left.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            if ( static_cast< DerivedT* >( this )->match_pair( edge_ ) )
                return left_offset;

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( '\"', "!!quote(left,middle,right): search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_TEXT_RESULT( false, '\"', "xtl_quote_base: LHS bang_find failed" );
        return SubstrT::string_T::npos;
    }
    
    private:
        /**Assignment is disabled.*/
        xtl_quote_base< LeftT, MiddleT, RightT, DerivedT >& operator=( xtl_quote_base< LeftT, MiddleT, RightT, DerivedT > const& );

};  // xtl_quote_base


/**@class xtl_quote_generic
 * @brief Implements behavior of generic
 *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>,
 *  defined by the @c match_pair() function.
 *
 * @tparam LeftT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing opening clause of the quote.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam RightT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing closing clause of the quote.
 *
 */
template< typename LeftT, typename MiddleT, typename RightT >
class xtl_quote_generic : public xtl_quote_base< LeftT, MiddleT, RightT, xtl_quote_generic< LeftT, MiddleT, RightT > > {
public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_quote_generic( LeftT const& left_, MiddleT const& middle_, RightT const& right_ )
    : xtl_quote_base< LeftT, MiddleT, RightT, xtl_quote_generic< LeftT, MiddleT, RightT > >( left_, middle_, right_ )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior of generic <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
        // LHS matched
        typename SubstrT::offset_guard_T middle_offset_start( edge_.first );
        size_t level = 1;   // we are inside a quote

        typename SubstrT::offset_guard_T current_offset( edge_.first );
        typename SubstrT::offset_guard_T right_offset( edge_.first, SubstrT::string_T::npos );
        typename SubstrT::offset_guard_T right_right_offset( edge_.first, SubstrT::string_T::npos );

        for (
            ;
            level && ( ( right_offset = this->m_right.bang_find( edge_ ) ) != SubstrT::string_T::npos );
            current_offset = edge_.first.offset()
            )
        {
            // RHS found
            // restart left search position
            right_right_offset = edge_.first.offset( current_offset );
            size_t left_offset = this->m_left.bang_find( edge_ );
            if ( left_offset != SubstrT::string_T::npos )
                if ( left_offset < right_offset ) {
                    // LHS found earlier, keep searching
                    ++level;
                    continue;   // ------->
                }

            // restore edge after right pos
            edge_.first.offset( right_right_offset );
            --level;
        }

        if ( level ) {
            // RHS was never found - we fail
            CTTL_TRACE_TEXT_RESULT( false, '\"', "xtl_quote_generic: closing clause not found" );
            return false;
        }

        // preserve edge
        xtl_edge_offset_guard< SubstrT > edge_guard( edge_ );
        edge_.first.offset( middle_offset_start );
        edge_.second.offset( right_offset );
        if ( this->m_middle.match( edge_ ) != SubstrT::string_T::npos ) {
            edge_guard.restore( edge_ );
            return true;
        }

        edge_guard.restore( edge_ );
        CTTL_TRACE_TEXT_RESULT( false, '\"', "xtl_quote_generic: middle clause failed" );
        return false;
    }
    
private:
    /**Assignment is disabled.*/
    xtl_quote_generic< LeftT, MiddleT, RightT >& operator=( xtl_quote_generic< LeftT, MiddleT, RightT > const& );

};  // class xtl_quote_generic


/**@class xtl_quote_bool
 * @brief Implements behavior of asymmetric
 *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam RightT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing closing clause of the quote.
 *
 */
template< typename MiddleT, typename RightT >
class xtl_quote_bool : public xtl_quote_base< relaxed_bool_T, MiddleT, RightT, xtl_quote_bool< MiddleT, RightT > > {

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_quote_bool( MiddleT const& middle_, RightT const& right_ )
    : xtl_quote_base< relaxed_bool_T, MiddleT, RightT, xtl_quote_bool< MiddleT, RightT > >( true, middle_, right_ )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior
    *  of asymmetric <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
        // LHS matched
        typename SubstrT::offset_guard_T middle_offset_start( edge_.first );
        typename SubstrT::offset_guard_T right_offset( edge_.first, this->m_right.bang_find( edge_ ) );

        if ( right_offset != SubstrT::string_T::npos ) {
            // RHS matched
            // preserve edge
            xtl_edge_offset_guard< SubstrT > edge_guard( edge_ );
            edge_.first.offset( middle_offset_start );
            edge_.second.offset( right_offset );
            if ( this->m_middle.match( edge_ ) != SubstrT::string_T::npos ) {
                edge_guard.restore( edge_ );
                return true;
            }
            edge_guard.restore( edge_ );
            CTTL_TRACE_TEXT_RESULT( false, '\"', "quote(true,M,R) middle clause failed" );
            return false;
        }

        CTTL_TRACE_TEXT_RESULT( false, '\"', "quote(true,M,R) closing clause failed" );
        return false;
    }
    
};  // class xtl_quote_bool


/**Implements
*  grammar evaluation behavior of single-character <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
*
* @tparam MiddleT
*        specifies type of
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
*        describing interior clause of the single-character quote.
*
* @tparam RightT
*        specifies type of
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
*        describing opening and closing clauses of the quote, for example,
@code
    xtl_wrap< xtl_char< CharT > >
@endcode
*
* @tparam CharT
*        specifies character type of the quote.
*
*/
template< typename SubstrT, typename MiddleT, typename RightT, typename CharT >
inline bool
xtl_match_quote( SubstrT& edge_, MiddleT& middle_, RightT& right_, CharT const* chars2find_ )
{
    typename SubstrT::string_T const& str = edge_.parent();

    // Closing quote is specified by the first character
    const CharT close_quote = chars2find_[ 0 ];
    const CharT back_whack = CharT( '\\' );
    const CharT cr = CharT( '\r' );
    const CharT lf = CharT( '\n' );

    // LHS matched.
    size_t middle_offset_start = edge_.first.offset();
    size_t current_offset = edge_.first.offset();

    // Assume we will fail
    size_t close_offset = SubstrT::string_T::npos;
    for (
        size_t temp_offset = str.find_first_of( chars2find_, current_offset );
        temp_offset != SubstrT::string_T::npos;
        temp_offset = str.find_first_of( chars2find_, temp_offset + 1 )
        )
    {
        if ( edge_.second.offset() <= temp_offset )
            // attempt to step beyond current substring
            return false;

        // make sure offset is valid, if not, keep retrying
        size_t adjusted_offset = edge_.space_policy().lower_bound( temp_offset, edge_.second.offset() );
        if ( adjusted_offset != temp_offset ) {
            temp_offset = adjusted_offset - 1;
            if ( edge_.second.offset() <= temp_offset )
                // attempt to step beyond current substring
                return false;
            continue;
        }

        // note: if open and close tokens are the same, then close token has higher priority
        if ( str[ temp_offset ] == back_whack ) {
            // this is C literal, and escape sequence was found inside:
            ++temp_offset;  // automatically skip next CTTL_STD_CHAR
            // Now we look at one more character; if it's remaining part of <cr><lf> pair,
            // eat it and go on:
            if ( str[ temp_offset ] == cr )
                ++temp_offset;  // skip cr

            else if ( str[ temp_offset ] == lf )
                ++temp_offset;  // skip lf

        } else if ( str[ temp_offset ] == close_quote ) {
            // RHS quote is found:
            close_offset = temp_offset;
            break;
        }

        // If we encounter unexpected cr or lf, halt evaluation of string literal:
        if ( ( str[ temp_offset ] == cr ) || ( str[ temp_offset ] == lf ) )
            // RHS not found on the same line - fail immediately
            return false;
    }

    if ( close_offset == SubstrT::string_T::npos )
        // RHS was never found
        return false;

    edge_.first.offset( close_offset );
    // Note: because right side is simply xtl_wrap< xtl_char< CharT > >, no
    // offset protection is used for middle_offset_start and right_offset:
    typename SubstrT::strict_edge_T strict_universe( edge_ );
    size_t right_offset = right_.match( strict_universe );

    // ik-5/17/2009
    // Linked list implementation requires update of the original
    // substring positions (the assignment of nodes takes place):
    edge_.first = strict_universe.first.offset();
    edge_.second = strict_universe.second.offset();

    if ( right_offset == SubstrT::string_T::npos ) {
        assert( false );
        return false;
    }

    xtl_edge_offset_guard< SubstrT > edge_guard( edge_ ); // preserve edge
    edge_.first.offset( middle_offset_start );
    edge_.second.offset( right_offset );
    if ( middle_.match( edge_ ) != SubstrT::string_T::npos ) {
        edge_guard.restore( edge_ );
        return true;
    }
    edge_guard.restore( edge_ );
    return false;

}   // xtl_match_quote()


/**@class xtl_quote_ansi_double_quote
 * @brief Implements behavior of
 *        ANSI double <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam CharT
 *        specifies character type of the quote.
 *
 */
template< typename MiddleT, typename CharT >
class xtl_quote_ansi_double_quote : public xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_double_quote< MiddleT, CharT > > {
public:
    // compile-time

    /**Default constructor assumes that any content inside the quotes is acceptable.*/
    xtl_quote_ansi_double_quote()
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, relaxed_bool_T, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_double_quote< relaxed_bool_T, CharT > >( CharT( '\"' ), true, CharT( '\"' ) )
    {
    }

    /**Constructs and initializes the object.*/
    xtl_quote_ansi_double_quote( MiddleT const& middle_ )
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_double_quote< MiddleT, CharT > >( CharT( '\"' ), middle_, CharT( '\"' ) )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior of ANSI double <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
//      typedef typename SubstrT::char_T char_T;
        static const CharT chars2find[] = { CharT( '\"' ), CharT( '\n' ), CharT( '\r' ), 0x00 };
        return xtl_match_quote( edge_, this->m_middle, this->m_right, chars2find ); // "\"\n\r"
    }
    
private:
    /**Assignment is disabled.*/
    xtl_quote_ansi_double_quote< MiddleT, CharT >& operator=( xtl_quote_ansi_double_quote< MiddleT, CharT > const& );

};  // class xtl_quote_ansi_double_quote


/**@class xtl_quote_ansi_single_quote
 * @brief Implements behavior of ANSI single <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam CharT
 *        specifies character type of the quote.
 *
 */
template< typename MiddleT, typename CharT >
class xtl_quote_ansi_single_quote : public xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_single_quote< MiddleT, CharT > > {

public:

    // compile-time

    /**Default constructor assumes that any content inside the quotes is acceptable.*/
    xtl_quote_ansi_single_quote()
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, relaxed_bool_T, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_single_quote< relaxed_bool_T, CharT > >( CharT( '\'' ), true, CharT( '\'' ) )
    {
    }

    /**Constructs and initializes the object.*/
    xtl_quote_ansi_single_quote( MiddleT const& middle_ )
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_ansi_single_quote< MiddleT, CharT > >( CharT( '\'' ), middle_, CharT( '\'' ) )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior of ANSI single <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
//      typedef typename SubstrT::char_T char_T;
        static const CharT chars2find[] = { CharT( '\'' ), CharT( '\n' ), CharT( '\r' ), 0x00 };
        return xtl_match_quote( edge_, this->m_middle, this->m_right, chars2find ); // "\'\n\r"
    }
    
    private:
        /**Assignment is disabled.*/
        xtl_quote_ansi_single_quote< MiddleT, CharT >& operator=( xtl_quote_ansi_single_quote< MiddleT, CharT > const& );

};  // class xtl_quote_ansi_single_quote


/**@class xtl_quote_c_double_quote
 * @brief Implements behavior of
 *  C double <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam CharT
 *        specifies character type of the quote.
 *
 */
template< typename MiddleT, typename CharT >
class xtl_quote_c_double_quote : public xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_c_double_quote< MiddleT, CharT > > {

public:

    // compile-time

    /**Default constructor assumes that any content inside the quotes is acceptable.*/
    xtl_quote_c_double_quote()
    : xtl_quote_base<
        xtl_wrap< xtl_char< CharT > >,
        relaxed_bool_T,
        xtl_wrap< xtl_char< CharT > >,
        xtl_quote_c_double_quote< xtl_wrap< xtl_bool< true > >, CharT >
        >( CharT( '\"' ), true, CharT( '\"' ) )
    {
    }

    /**Constructs and initializes the object.*/
    xtl_quote_c_double_quote( MiddleT const& middle_ )
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_c_double_quote< MiddleT, CharT > >( CharT( '\"' ), middle_, CharT( '\"' ) )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior of C double <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
//      typedef typename SubstrT::char_T char_T;
        static const CharT chars2find[] = { CharT( '\"' ), CharT( '\n' ), CharT( '\r' ), CharT( '\\' ), 0x00 };
        return xtl_match_quote( edge_, this->m_middle, this->m_right, chars2find ); // "\"\n\r\\"
    }
    
private:
    /**Assignment is disabled.*/
    xtl_quote_c_double_quote< MiddleT, CharT >& operator=( xtl_quote_c_double_quote< MiddleT, CharT > const& );

};  // class xtl_quote_c_double_quote


/**@class xtl_quote_c_single_quote
 * @brief Implements behavior of
 *        C single <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
 *
 * @tparam MiddleT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        describing interior clause of the quote.
 *
 * @tparam CharT
 *        specifies character type of the quote.
 *
 */
template< typename MiddleT, typename CharT >
class xtl_quote_c_single_quote : public xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_c_single_quote< MiddleT, CharT > > {

public:

    // compile-time

    /**Default constructor assumes that any content inside the quotes is acceptable.*/
    xtl_quote_c_single_quote()
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, relaxed_bool_T, xtl_wrap< xtl_char< CharT > >, xtl_quote_c_single_quote< relaxed_bool_T, CharT > >( CharT( '\'' ), true, CharT( '\'' ) )
    {
    }

    /**Constructs and initializes the object.*/
    xtl_quote_c_single_quote( MiddleT const& middle_ )
    : xtl_quote_base< xtl_wrap< xtl_char< CharT > >, MiddleT, xtl_wrap< xtl_char< CharT > >, xtl_quote_c_single_quote< MiddleT, CharT > >( CharT( '\'' ), middle_, CharT( '\'' ) )
    {
    }

    // run-time

    /**Implements
    *  grammar evaluation behavior of C single <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>.
    *
    */
    template< typename SubstrT >
    bool match_pair( SubstrT& edge_ )
    {
//      typedef typename SubstrT::char_T char_T;
        static const CharT chars2find[] = { CharT( '\'' ), CharT( '\n' ), CharT( '\r' ), CharT( '\\' ), 0x00 };
        return xtl_match_quote( edge_, this->m_middle, this->m_right, chars2find ); // "\'\n\r\\"
    }
    
private:
    /**Assignment is disabled.*/
    xtl_quote_c_single_quote< MiddleT, CharT >& operator=( xtl_quote_c_single_quote< MiddleT, CharT > const& );

};  // class xtl_quote_c_single_quote

/**Defines leximatic type created by @c cttl::ansi_single_quote().*/
typedef xtl_wrap< xtl_quote_ansi_single_quote< relaxed_bool_T, CTTL_STD_CHAR > >
ansi_single_quote_T;

/**Defines leximatic type created by @c cttl::ansi_double_quote().*/
typedef xtl_wrap< xtl_quote_ansi_double_quote< relaxed_bool_T, CTTL_STD_CHAR > >
ansi_double_quote_T;

/**Defines leximatic type created by @c cttl::c_single_quote().*/
typedef xtl_wrap< xtl_quote_c_single_quote< relaxed_bool_T, CTTL_STD_CHAR > >
c_single_quote_T;

/**Defines leximatic type created by @c cttl::c_double_quote().*/
typedef xtl_wrap< xtl_quote_c_double_quote< relaxed_bool_T, CTTL_STD_CHAR > >
c_double_quote_T;


/**Defines leximatic type created by @c cttl::wchar_ansi_single_quote().*/
typedef xtl_wrap< xtl_quote_ansi_single_quote< relaxed_bool_T, CTTL_STD_WCHAR > >
wchar_ansi_single_quote_T;

/**Defines leximatic type created by @c cttl::wchar_ansi_double_quote().*/
typedef xtl_wrap< xtl_quote_ansi_double_quote< relaxed_bool_T, CTTL_STD_WCHAR > >
wchar_ansi_double_quote_T;

/**Defines leximatic type created by @c cttl::wchar_c_single_quote().*/
typedef xtl_wrap< xtl_quote_c_single_quote< relaxed_bool_T, CTTL_STD_WCHAR > >
wchar_c_single_quote_T;

/**Defines leximatic type created by @c cttl::wchar_c_double_quote().*/
typedef xtl_wrap< xtl_quote_c_double_quote< relaxed_bool_T, CTTL_STD_WCHAR > >
wchar_c_double_quote_T;

}   // namespace cttl_impl


#endif // _CTTL_XTL_QUOTE_H_INCLUDED_
