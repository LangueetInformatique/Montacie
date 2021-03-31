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

/**@file xtl_op_impl.h
 * @brief Defines implementation classes for
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">overloaded operators</a>
 * of the Common Text Transformation Library.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 *  @see
 *  - cttl_impl::xtl_op_base_unary
 *  - cttl_impl::xtl_op_base_binary
 *  - cttl_impl::xtl_opunarbang
 *  - cttl_impl::xtl_opunarstar
 *  - cttl_impl::xtl_opunarminus
 *  - cttl_impl::xtl_opunarplus
 *  - cttl_impl::xtl_entity
 *  - cttl_impl::xtl_lookahead
 *  - cttl_impl::xtl_opbinplus
 *  - cttl_impl::xtl_opbinpipe
 *  - cttl_impl::xtl_opbin2pipe
 *  - cttl_impl::xtl_opbinconcat
 *  - cttl_impl::xtl_opbinminus
 *  - cttl_impl::xtl_opbinand
 *
 */

// xtl_op_impl.h

#ifndef _CTTL_XTL_OP_IMPL_H_INCLUDED_
#define _CTTL_XTL_OP_IMPL_H_INCLUDED_

namespace cttl_impl {

//////////////////////////////////////////////////////////
// Base implementation classes for overloaded operators
//////////////////////////////////////////////////////////

/**@class xtl_op_base_unary
 * @brief Base implementation class for CTTL unary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operators</a>.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
class xtl_op_base_unary {

protected:
    /** Stores grammar expression specified as operand.*/
    ExprT m_expr;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_op_base_unary( ExprT const& expr_ )
    : m_expr( expr_ )
    {
    }

protected:
    /**Helper function to exercise Kleene list after first match has been found.
    *  Finds second, third, and so on, matches for @c m_expr
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @param upper_limit_
    *       If not zero, suggests the upper limit for a number of matches.
    *       The matching stops as soon as this exact number of matches is found.
    *
    * @return
    *       Actual number of items found by the function.
    *
    * @post
    *       If function succeeds, the substring, specified
    *       by the @c edge_ parameter, is consumed accordingly to
    *       the size of the matched symbols.
    *
    */
    template< typename SubstrT >
    size_t kleene_list( SubstrT& edge_, size_t upper_limit_ = 0 )
    {
        // if this offset stops progressing, we must bail out of infinite loop
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );
        typename SubstrT::offset_guard_T match_offset( edge_.first, SubstrT::string_T::npos );

        // statically captured offset to watch mutablility of the substring.
        // substring is considered mutated if saved_end_offset no longer matches the end of the substring.
        size_t saved_end_offset = edge_.second.offset();

        size_t cnt = 0;
        while ( ( match_offset = m_expr.match( edge_ ) ) != SubstrT::string_T::npos ) {
            // If substring is mutable and the user deleted matched fragment,
            // edge_.first.offset() is brought back, therefore, it will appear here
            // as an empty (epsilon) match. In such case, if substring has mutated,
            // the search should continue.

            // Check if the substring has mutated:
            if ( saved_end_offset == edge_.second.offset() ) {
                if ( iteration_offset == edge_.first.offset() ) {
                    CTTL_TRACE_TEXT( 'i', "kleene_list: iteration made no progress: bailing out" );
                    break;  // second, third, etc., iteration hasn't made any progress: bail out
                }

                ++cnt;

                if ( match_offset == edge_.first.offset() ) {
                    // second, third, etc., iteration succeeded on an empty substring,
                    // do not count it as a match, bail out of the loop:
                    CTTL_TRACE_TEXT( 'i', "kleene_list: epsilon match: bailing out" );
                    break;
                }

            } else {
                ++cnt;
                saved_end_offset = edge_.second.offset();
            }

            if ( upper_limit_ && ( cnt == upper_limit_ ) ) {
                CTTL_TRACE_TEXT( 'i', "kleene_list: user-specified match limit: bailing out" );
                break;
            }

            iteration_offset = edge_.first.offset();
        }
        return cnt;
    }

private:
    /**Assignment is disabled.*/
    xtl_op_base_unary< ExprT >& operator=( xtl_op_base_unary< ExprT > const& );

};  // xtl_op_base_unary


/**@class xtl_op_base_binary
 * @brief Base implementation class for CTTL binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operators</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
class xtl_op_base_binary {

protected:
    /**Stores left-hand-side grammar expression.*/
    Left_exprT m_expr_lhs;

    /**Stores right-hand-side grammar expression.*/
    Right_exprT m_expr_rhs;

public:

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_op_base_binary( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : m_expr_lhs( lhs_expr_ ), m_expr_rhs( rhs_expr_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xtl_op_base_binary< Left_exprT, Right_exprT >& operator=( xtl_op_base_binary< Left_exprT, Right_exprT > const& );

};  // xtl_op_base_binary


//////////////////////////////////////////////////
// Implementation classes for unary operators
//////////////////////////////////////////////////

/**@struct xtl_opunarbang
 * @brief Implements behavior of unary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7720_find.html">search operator</a>.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
struct xtl_opunarbang : public xtl_op_base_unary< ExprT > {

    // compile-time

    /**Constructs and initializes the object.*/
    xtl_opunarbang( ExprT const& expr_ )
    : xtl_op_base_unary< ExprT >( expr_ )
    {
    }

    // run-time

    /**Promotes
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a> to <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( '!' );
        return this->m_expr.find( edge_ );
    }
    
    /**Promotes
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  to <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( '!' );
        return this->m_expr.bang_find( edge_ );
    }
    
    /**Delegates
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  to the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *  representing the operand.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
    *
    * @see
    * -  overview.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( '!' );
        return this->m_expr.bang_find( edge_ );
    }

private:
    /**Assignment is disabled.*/
    xtl_opunarbang< ExprT >& operator=( xtl_opunarbang< ExprT > const& );

};  // xtl_opunarbang


/**@class xtl_opunarstar
 * @brief Implements behavior of unary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star operator</a>.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
class xtl_opunarstar : public xtl_op_base_unary< ExprT > {

protected:

    /**Stores upper limit for the number of matches.*/
    size_t m_upper_limit;

public:
    // compile-time

    /**Constructs and initializes the object.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression of the operand.
    *
    * @param upper_limit_
    *       If not zero, suggests the upper limit for a number of matches.
    *
    */
    xtl_opunarstar( ExprT const& expr_, size_t upper_limit_ = 0 )
    : xtl_op_base_unary< ExprT >( expr_ ), m_upper_limit( upper_limit_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a> match algorithm,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // [R,R,R,...]_ kleene star
        CTTL_TRACE_LEVEL_MATCH( '*' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );

        // statically captured offset to watch mutablility of the substring.
        // substring is considered mutated if saved_end_offset no longer matches the end of the substring.
        size_t saved_end_offset = edge_.second.offset();
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.match( edge_ ) );

        if ( match_offset != SubstrT::string_T::npos ) {
            // If substring is mutable and the user deleted matched fragment,
            // edge_.first.offset() is brought back, therefore, it will appear here
            // as an empty (epsilon) match. In such case, if substring has mutated,
            // the search should continue.

            // Check if the substring has mutated:
            if ( saved_end_offset == edge_.second.offset() ) {
                if ( saved_first_offset == edge_.first.offset() ) {
                    // one match aleady found, no substring progress was made.
                    // No more match attemts necessary, we are done:
                    return match_offset;
                }
            }

            if ( m_upper_limit ) {
                // user wants to use upper limit on the number of matches
                // minus one accounts for the expression already found

                if ( m_upper_limit == 1 ) {
                    // one is a special case: if upper limit is one, then
                    // there is no need to search for more instances
                    return match_offset;
                }

                // it is sufficient to find only
                // zero to (m_upper_limit - 1) matches:
                this->kleene_list( edge_, m_upper_limit - 1 );

            } else
                // user doesn't care how many matches are found:
                this->kleene_list( edge_ );

        } else {
            // success offset is at the current position
            //assert( saved_first_offset == edge_.first.offset() );
            return saved_first_offset;
        }

        return match_offset;
    }
    
    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a> search algorithm,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // [!R,R,R,...]_ kleene star
        CTTL_TRACE_LEVEL_FIND( '*' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );

        // statically captured offset to watch mutablility of the substring.
        // substring is considered mutated if saved_end_offset no
        // longer matches the end of the substring.
        size_t saved_end_offset = edge_.second.offset();
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.find( edge_ ) );

        if ( match_offset != SubstrT::string_T::npos ) {
            // If substring is mutable and the user deleted matched fragment,
            // edge_.first.offset() is brought back, therefore, it will appear here
            // as an empty (epsilon) match. In such case, if substring has mutated,
            // the search should go on.
            // Check if the substring mutated:
            if ( saved_end_offset == edge_.second.offset() ) {
                if ( saved_first_offset == edge_.first.offset() ) {
                    // one match aleady found, no substring progress was made.
                    // No more match attemts necessary, we are done:
                    return match_offset;
                }
            }

            if ( m_upper_limit ) {
                // user wants to use upper limit on the number of matches
                // minus one accounts for the expression already found

                if ( m_upper_limit == 1 ) {
                    // one is a special case: if upper limit is one, then
                    // there is no need to search for more instances
                    return match_offset;
                }

                // it is sufficient to find
                // zero to (m_upper_limit - 1) more matches:
                this->kleene_list( edge_, m_upper_limit - 1 );

            } else
                // user doesn't care how many matches are found:
                this->kleene_list( edge_ );

        } else {
            // success offset is at the current position
            //assert( saved_first_offset == edge_.first.offset() );
            return saved_first_offset;
        }

        return match_offset;
    }
    
    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a>
    *  repeatable search algorithm,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // [!!R,R,R,...]_ kleene star
        CTTL_TRACE_LEVEL_BANG( '*' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        // statically captured offset to watch mutablility of the substring.
        // substring is considered mutated if saved_end_offset no
        // longer matches the end of the substring.
        size_t saved_end_offset = edge_.second.offset();
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.bang_find( edge_ ) );

        if ( match_offset != SubstrT::string_T::npos ) {
            // If substring is mutable and the user deleted matched fragment,
            // edge_.first.offset() is brought back, therefore, it will appear here
            // as an empty (epsilon) match. In such case, if substring has mutated,
            // the search should go on.
            
            // Check if the substring mutated:
            if ( saved_end_offset == edge_.second.offset() ) {
                if ( saved_first_offset == edge_.first.offset() ) {
                    // one match aleady found, no substring progress was made.
                    // No more match attemts necessary, we are done:
                    return match_offset;
                }
            }

            if ( m_upper_limit ) {
                // user wants to use upper limit on the number of matches
                // minus one accounts for the expression already found

                if ( m_upper_limit == 1 ) {
                    // one is a special case: if upper limit is one, then
                    // there is no need to search for more instances
                    return match_offset;
                }

                // it is sufficient to find
                // zero to (m_upper_limit - 1) more matches:
                this->kleene_list( edge_, m_upper_limit - 1 );

            } else
                // user doesn't care how many matches are found:
                this->kleene_list( edge_ );

        } else {
            // success offset is at the current position
            //assert( saved_first_offset == edge_.first.offset() );
            return saved_first_offset;
        }

        return match_offset;
    }

private:
    /**Assignment is disabled.*/
    xtl_opunarstar< ExprT >& operator=( xtl_opunarstar< ExprT > const& );

};  // xtl_opunarstar


/**@class xtl_opunarminus
 * @brief Implements behavior of unary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8020_not.html">negative lookahead assertion</a> operator.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
class xtl_opunarminus : public xtl_op_base_unary< ExprT > {

public:
    // compile-time

    /**Constructs and initializes the object.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression of the operand.
    *
    */
    xtl_opunarminus( ExprT const& expr_ )
    : xtl_op_base_unary< ExprT >( expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8020_not.html">negative lookahead assertion</a> match algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        The result of operand's grammar expression evaluation is reversed.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset of the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>
    *        before evaluation.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // -R_ logical not
        CTTL_TRACE_LEVEL_MATCH( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        size_t match_offset = this->m_expr.match( edge_ );

        if ( match_offset != SubstrT::string_T::npos ) {
            // encapsulated expression succeeded, we fail:
            // restore substring
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_RESULT( false, '-' );
            return SubstrT::string_T::npos;
        }

        // success offset is at the current position
        //assert( saved_first_offset == edge_.first.offset() );
        return saved_first_offset;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8020_not.html">negative lookahead assertion</a> search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        The result of operand's grammar expression evaluation is reversed.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset of the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>
    *        before evaluation.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // -!R_ logical not
        CTTL_TRACE_LEVEL_FIND( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        size_t match_offset = this->m_expr.find( edge_ );

        if ( match_offset != SubstrT::string_T::npos ) {
            // encapsulated expression succeeded, we fail:
            // restore substring
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_RESULT( false, '-' );
            return SubstrT::string_T::npos;
        }

        // success offset is at the current position
        //assert( saved_first_offset == edge_.first.offset() );
        return saved_first_offset;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8020_not.html">negative lookahead assertion</a> repeatable
    *  search algorithm.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        The result of operand's grammar expression evaluation is reversed.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset of the upper boundary of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>
    *        before evaluation.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // -!!R_ logical not
        CTTL_TRACE_LEVEL_BANG( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        size_t match_offset = this->m_expr.bang_find( edge_ );

        if ( match_offset != SubstrT::string_T::npos ) {
            // encapsulated expression succeeded, we fail:
            // restore substring
            edge_.first.offset( saved_first_offset );
            CTTL_TRACE_RESULT( false, '-' );
            return SubstrT::string_T::npos;
        }

        // success offset is at the current position
        //assert( saved_first_offset == edge_.first.offset() );
        return saved_first_offset;
    }

};  // xtl_opunarminus


/**@class xtl_opunarplus
 * @brief Implements behavior of various flavors of
 * Kleene plus
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operators</a>.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @see
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7840_1m.html">Unary Kleene plus operator</a>
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7850_1N.html">Binary Kleene plus operator</a>
 * - <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7860_NM.html.html">Greedy Kleene plus operator</a>
 *
 */
template< typename ExprT >
class xtl_opunarplus : public xtl_op_base_unary< ExprT > {

protected:
    /**Upper limit for Kleene matches.*/
    size_t m_upper_limit;

    /**Lower limit for Kleene matches.*/
    size_t m_lower_limit;

    /**Helper function to handle limits of the kleene plus evaluation.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @param saved_end_offset_
    *        Statically captured offset to watch mutablility of the substring.
    *        substring is considered mutated if saved_end_offset no longer
    *        matches the end of the substring.
    *
    * @param first_match_offset_
    *        Offset of the first matched symbol.
    *
    */
    template< typename SubstrT >
    size_t unarplus( SubstrT& edge_, size_t saved_end_offset_, size_t first_match_offset_ )
    {
        typename SubstrT::offset_guard_T match_offset( edge_.first, first_match_offset_ );
        
        if ( match_offset != SubstrT::string_T::npos ) {
            // If substring is mutable and the user deleted matched fragment,
            // edge_.first.offset() is brought back, therefore, it will appear here
            // as an empty (epsilon) match. In such case, if substring has mutated,
            // the search should continue.
            // Check if the substring has mutated:
            if ( saved_end_offset_ == edge_.second.offset() ) {
                if ( match_offset == edge_.first.offset() ) {
                    // one match aleady found, no substring progress was made.
                    // No more match attemts necessary, we are done:
                    if ( !m_upper_limit )
                        return match_offset;

                    if ( ( m_lower_limit <= 1 ) && ( 1 <= m_upper_limit ) )
                        return match_offset;

                    CTTL_TRACE_TEXT_RESULT( false, '+', "kleene plus: too few matches (one epsilon found)" );
                    return SubstrT::string_T::npos;
                }
            }

            if ( m_upper_limit ) {
                if ( m_upper_limit == 1 )
                    // case: expr + m_upper_limit, where m_upper_limit == 1
                    return match_offset;

                // user wants to use upper limit on the number of matches
                // plus one accounts for the expression already found
                if ( m_lower_limit ) {
                    // case: expr + pair( m_lower_limit, m_upper_limit )
                    //ik-7/31/2009 commented out:
                    /*
                    size_t cnt = this->kleene_list(
                        edge_,
                        ( m_upper_limit == SubstrT::string_T::npos ) ? ( m_lower_limit - 1 ) : m_upper_limit
                        ) + 1;
                    */

                    //ik-7/31/2009 replaced by:
                    size_t cnt = 0;
                    if ( m_upper_limit == SubstrT::string_T::npos ) {
                        if ( m_lower_limit == 1 ) {
                            // case: expr + pair( 1, npos )
                            // one match already found:
                            return match_offset;
                        }
                        // case: expr + pair( N, npos )
                        cnt = this->kleene_list( edge_, m_lower_limit - 1 ) + 1;
                    } else {
                        cnt = this->kleene_list( edge_, m_upper_limit ) + 1;
                    }

                    if ( cnt > m_upper_limit ) {
                        CTTL_TRACE_TEXT_RESULT( false, '+', "kleene plus: too many matches" );
                        return SubstrT::string_T::npos;

                    }

                    if ( cnt < m_lower_limit ) {
                        // user also wants to use lower limit on the number of matches
                        CTTL_TRACE_TEXT_RESULT( false, '+', "kleene plus: too few matches" );
                        return SubstrT::string_T::npos;

                    } else if ( m_upper_limit == SubstrT::string_T::npos ) {
                        //ik-7/14/2009
                        //Ungreedy request for exactly m_lower_limit matches:
                        return match_offset;
                    }

                } else {
                    // case: expr + m_upper_limit, where m_upper_limit > 1
                    // it is sufficient to find up to (m_upper_limit - 1) more matches:
                    this->kleene_list( edge_, m_upper_limit - 1 );
                }

            } else
                // case: +expr
                // user doesn't care how many matches are found:
                this->kleene_list( edge_ );

            return match_offset;
        }

        CTTL_TRACE_RESULT( false, '+' );
        return SubstrT::string_T::npos;
    }

public:

    // compile-time

    /**Constructs and initializes the object.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression of the operand.
    *
    * @param upper_limit_
    *       If not zero, suggests the upper limit for a number of matches.
    *
    * @param lower_limit_
    *       If not zero, suggests the lower limit for a number of matches.
    *
    */
    xtl_opunarplus( ExprT const& expr_, size_t upper_limit_ = 0, size_t lower_limit_ = 0 )
    : xtl_op_base_unary< ExprT >( expr_ ), m_upper_limit( upper_limit_ ), m_lower_limit( lower_limit_ )
    {
    }


    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a>
    *  match algorithm, starting at the upper boundary of
    *  the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // [R,R,R,...]_ kleene plus
        CTTL_TRACE_LEVEL_MATCH( '+' );
        size_t saved_end_offset = edge_.second.offset();
        return unarplus( edge_, saved_end_offset, this->m_expr.match( edge_ ) );
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a>
    *  algorithm, starting at the upper boundary of
    *  the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // [!R,R,R,...]_ kleene plus
        CTTL_TRACE_LEVEL_FIND( '+' );
        size_t saved_end_offset = edge_.second.offset();
        return unarplus( edge_, saved_end_offset, this->m_expr.find( edge_ ) );
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a>
    *  repeatable search algorithm,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched symbols.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched symbols.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // [!!R,R,R,...]_ kleene plus
        CTTL_TRACE_LEVEL_BANG( '+' );

        //ik-8/3/2009 added replay mode for kleene plus:
        //size_t saved_end_offset = edge_.second.offset();
        //return unarplus( edge_, saved_end_offset, this->m_expr.bang_find( edge_ ) );

        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, SubstrT::string_T::npos );
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );

        while ( ( match_lhs_offset = this->m_expr.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            size_t saved_end_offset = edge_.second.offset();
            if ( unarplus( edge_, saved_end_offset, match_lhs_offset ) != SubstrT::string_T::npos )
                return match_lhs_offset;

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( '+', "!!kleene plus: search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        // restore substring
        edge_.first.offset( saved_first_offset );
        return SubstrT::string_T::npos;
    }

private:
    /**Assignment is disabled.*/
    xtl_opunarplus< ExprT >& operator=( xtl_opunarplus< ExprT > const& );

};  // xtl_opunarplus


/**@struct xtl_entity
 * @brief Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7030_entity.html">entity expression adaptor</a>,
 * which enforces non-empty match of the encapsulated sub-expression.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
struct xtl_entity : public xtl_op_base_unary< ExprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @param expr_
    *        immutable reference to the sub-expression object.
    *
    */
    xtl_entity( ExprT const& expr_ )
    : xtl_op_base_unary< ExprT >( expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for entity match algorithm,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
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
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'E' );
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.match( edge_ ) );
        if ( match_offset != SubstrT::string_T::npos ) {
            if ( match_offset != edge_.first.offset() ) {
                CTTL_TRACE_RESULT( true, 'E' );
                return match_offset;
            } else {
                CTTL_TRACE_STATIC_RESULT( false, 'E', "epsilon match rejected" );
            }
        }

        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for symbol search algorithm,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
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
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( 'E' );
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.find( edge_ ) );
        if ( ( match_offset != SubstrT::string_T::npos ) && ( match_offset != edge_.first.offset() ) )
            return match_offset;

        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  algorithm, starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
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
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( 'E' );
        typename SubstrT::offset_guard_T match_offset( edge_.first, this->m_expr.bang_find( edge_ ) );
        if ( ( match_offset != SubstrT::string_T::npos ) && ( match_offset != edge_.first.offset() ) )
            return match_offset;

        return SubstrT::string_T::npos;
    }

};  // xtl_entity


/**@struct xtl_lookahead
 * @brief Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
 * adaptor.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
struct xtl_lookahead : public xtl_op_base_unary< ExprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @param expr_
    *        immutable reference to the sub-expression object.
    *
    */
    xtl_lookahead( ExprT const& expr_ )
    : xtl_op_base_unary< ExprT >( expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  algorithm for
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
    *  adaptor, starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, upper substring boundary
    *        @c edge_.first is restored to the upper boundary of the
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">nearest terminal symbol</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched grammar expression.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'A' );
        typedef
            xtl_node<
                typename SubstrT::node_T,
                xtl_wrap< ExprT >
            > xtl_node_T;

        return xtl_wrap< xtl_node_T >( xtl_node_T( edge_.first, this->m_expr ) ).match( edge_ );
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  algorithm for
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
    *  adaptor, starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, upper substring boundary
    *        @c edge_.first is restored to the upper boundary of the
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">nearest terminal symbol</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched grammar expression.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( 'A' );
        typedef
            xtl_node<
                typename SubstrT::node_T,
                xtl_wrap< ExprT >
            > xtl_node_T;

        return xtl_wrap< xtl_node_T >( xtl_node_T( edge_.first, this->m_expr ) ).find( edge_ );
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  algorithm for
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
    *  adaptor, starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, upper substring boundary
    *        @c edge_.first is restored to the upper boundary of the
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">nearest terminal symbol</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched grammar expression.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( 'A' );
        typedef
            xtl_node<
                typename SubstrT::node_T,
                xtl_wrap< ExprT >
            > xtl_node_T;

        return xtl_wrap< xtl_node_T >( xtl_node_T( edge_.first, this->m_expr ) ).bang_find( edge_ );
    }

};  // xtl_lookahead


//////////////////////////////////////////////////
// Implementation classes for binary operators
//////////////////////////////////////////////////

/**@struct xtl_opbinplus
 * @brief Implements behavior of binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbinplus : public xtl_op_base_binary< Left_exprT, Right_exprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbinplus( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence operator</a>,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched sequence.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched sequence.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // L+R_ relaxed sequence
        // if L succeeds, and R fails, substring needs to be restored
        CTTL_TRACE_LEVEL_MATCH( ';' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.match( edge_ ) );
        
        if (
            ( match_lhs_offset != SubstrT::string_T::npos )
            &&
            ( this->m_expr_rhs.match( edge_ ) != SubstrT::string_T::npos )
            )
                return match_lhs_offset;

        // restore substring
        edge_.first.offset( saved_first_offset );
        return SubstrT::string_T::npos;
    }


    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence operator</a>,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched sequence.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched sequence.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // !L+R_
        CTTL_TRACE_LEVEL_FIND( ';' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.find( edge_ ) );

        if (
            ( match_lhs_offset != SubstrT::string_T::npos )
            &&
            ( this->m_expr_rhs.match( edge_ ) != SubstrT::string_T::npos )
            )
                return match_lhs_offset;

        edge_.first.offset( saved_first_offset );       // restore substring
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence operator</a>,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched sequence.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched sequence.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // !!L+R_
        CTTL_TRACE_LEVEL_BANG( ';' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, SubstrT::string_T::npos );
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );

        while ( ( match_lhs_offset = this->m_expr_lhs.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            if ( this->m_expr_rhs.match( edge_ ) != SubstrT::string_T::npos )
                return match_lhs_offset;

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( ';', "!!(R1+R2): search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        // restore substring
        edge_.first.offset( saved_first_offset );
        return SubstrT::string_T::npos;
    }

private:
    /**Assignment is disabled.*/
    xtl_opbinplus< Left_exprT, Right_exprT >& operator=( xtl_opbinplus< Left_exprT, Right_exprT > const& );

};  // xtl_opbinplus


/**@struct xtl_opbinpipe
 * @brief Implements behavior of binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbinpipe : public xtl_op_base_binary< Left_exprT, Right_exprT > {
    // implements behavior of binary expr | expr operator

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbinpipe( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // (L|R)_ logical "if L; else R;"
        // first-of( L, R )_
        CTTL_TRACE_LEVEL_MATCH( '|' );
        size_t match_offset = this->m_expr_lhs.match( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        match_offset = this->m_expr_rhs.match( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        CTTL_TRACE_RESULT( false, '|' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union operator</a>,
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
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // ( !L | !R )_
        // first-of( !L, !R )_
        CTTL_TRACE_LEVEL_FIND( '|' );
        size_t match_offset = this->m_expr_lhs.find( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        match_offset = this->m_expr_rhs.find( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        CTTL_TRACE_RESULT( false, '|' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // ( !!L | !!R )_
        // first-of( !!L, !!R )_
        CTTL_TRACE_LEVEL_BANG( '|' );
        size_t match_offset = this->m_expr_lhs.bang_find( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        match_offset = this->m_expr_rhs.bang_find( edge_ );
        if ( match_offset != SubstrT::string_T::npos )
            return match_offset;

        CTTL_TRACE_RESULT( false, '|' );
        return SubstrT::string_T::npos;
    }

private:
    /**Assignment is disabled.*/
    xtl_opbinpipe< Left_exprT, Right_exprT >& operator=( xtl_opbinpipe< Left_exprT, Right_exprT > const& );

};  // xtl_opbinpipe


/**@struct xtl_opbin2pipe
 * @brief Implements behavior of binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8080_posix.html">POSIX union operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbin2pipe : public xtl_op_base_binary< Left_exprT, Right_exprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbin2pipe( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }

    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8080_posix.html">POSIX union operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // ( L || R )_
        // first-of( nearest-of( !L, !R ), longest-of( !L, !R ) )_
        CTTL_TRACE_LEVEL_MATCH( '|' );

        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.match( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos )
            // LHS succeeded
            // save current position and restart search from the same position
            saved_lhs_edge.swap( edge_ );

        // position of the right side of the substring after RHS expression succeeds:
        typename SubstrT::offset_guard_T match_rhs_offset( edge_.first, this->m_expr_rhs.match( edge_ ) );
        if ( match_rhs_offset != SubstrT::string_T::npos ) {
            // RHS succeeded
            if ( match_lhs_offset == SubstrT::string_T::npos )
                // F,T case
                return match_rhs_offset;

            // T,T case
            // find longest-of( L, R ) )_
            if (
                ( match_lhs_offset == match_rhs_offset )
                &&
                ( /*lhs_length*/saved_lhs_edge.first - match_lhs_offset < /*rhs_length*/edge_.first.offset() - match_rhs_offset )
                )
                // RHS is longer
                return match_rhs_offset;

            // find nearest-of( L, R )
            else if ( match_rhs_offset < match_lhs_offset )
                // RHS is closer
                return match_rhs_offset;

            // LHS is closer or longer, or has exactly the same size and location
        }

        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            // LHS succeeded
            // T,F case
            saved_lhs_edge.restore( edge_ );
            return match_lhs_offset;
        }

        // F,F case
        // note that because both sides have failed, they already restored original substring
        CTTL_TRACE_TEXT_RESULT( false, '|', "||" );
        return SubstrT::string_T::npos;
    }   // match()
    
    
    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8080_posix.html">POSIX union operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // ( !L || !R )_
        // first-of( nearest-of( !L, !R ), longest-of( !L, !R ) )_
        CTTL_TRACE_LEVEL_FIND( '|' );

        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.find( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos )
            // LHS succeeded
            // save current position and restart search from the same position
            saved_lhs_edge.swap( edge_ );

        // position of the right side of the substring after RHS expression succeeds:
        typename SubstrT::offset_guard_T match_rhs_offset( edge_.first, this->m_expr_rhs.find( edge_ ) );
        if ( match_rhs_offset != SubstrT::string_T::npos ) {
            // RHS succeeded
            if ( match_lhs_offset == SubstrT::string_T::npos )
                // F,T case
                return match_rhs_offset;

            // T,T case
            // find longest-of( !L, !R ) )_
            if (
                ( match_lhs_offset == match_rhs_offset )
                &&
                ( /*lhs_length*/saved_lhs_edge.first - match_lhs_offset < /*rhs_length*/edge_.first.offset() - match_rhs_offset )
                )
                // RHS is longer
                return match_rhs_offset;

            // find nearest-of( !L, !R )
            else if ( match_rhs_offset < match_lhs_offset )
                // RHS is closer
                return match_rhs_offset;

            // LHS is closer or longer, or has exactly the same size and location.
            // if so, LHS is the answer
        }

        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            // LHS succeeded
            // T,F case
            saved_lhs_edge.restore( edge_ );
            return match_lhs_offset;
        }

        // F,F case
        // note that because both sides have failed, they already restored original substring
        CTTL_TRACE_TEXT_RESULT( false, '|', "||" );
        return SubstrT::string_T::npos;

    }   // find()
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8080_posix.html">POSIX union operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // ( !!L || !!R )_
        // first-of( nearest-of( !!L, !!R ), longest-of( !!L, !!R ) )_
        CTTL_TRACE_LEVEL_BANG( '|' );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.bang_find( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos )
            // LHS succeeded
            // save current position and restart search from the same position
            saved_lhs_edge.swap( edge_ );

        // position of the right side of the substring after RHS expression succeeds:
        typename SubstrT::offset_guard_T match_rhs_offset( edge_.first, this->m_expr_rhs.bang_find( edge_ ) );
        if ( match_rhs_offset != SubstrT::string_T::npos ) {
            // RHS succeeded
            if ( match_lhs_offset == SubstrT::string_T::npos )
                // F,T case
                return match_rhs_offset;

            // T,T case
            // longest-of( !!L, !!R ) )_
            if (
                ( match_lhs_offset == match_rhs_offset )
                &&
                ( /*lhs_length*/saved_lhs_edge.first - match_lhs_offset < /*rhs_length*/edge_.first.offset() - match_rhs_offset )
                )
                // RHS is longer
                return match_rhs_offset;

            // nearest-of( !!L, !!R )
            else if ( match_rhs_offset < match_lhs_offset )
                // RHS is closer
                return match_rhs_offset;

            // LHS is closer or longer, or has exactly the same size and location.
            // if so, LHS is the answer
        }

        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            // LHS succeeded
            // T,F case
            saved_lhs_edge.restore( edge_ );
            return match_lhs_offset;
        }

        // F,F case
        // note that because both sides have failed, they already restored original substring
        CTTL_TRACE_TEXT_RESULT( false, '|', "||" );
        return SubstrT::string_T::npos;

    }   // bang_find()

};  // xtl_opbin2pipe


/**@struct xtl_opbinconcat
 * @brief Implements behavior of binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7930_concat.html">concatenation operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbinconcat : public xtl_op_base_binary< Left_exprT, Right_exprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbinconcat( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }


    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7930_concat.html">concatenation operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // L^R_ strict sequence
        // if L succeeds, and R fails, substring needs to be restored
        CTTL_TRACE_LEVEL_MATCH( '^' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        // saved_lhs_offset is required because LHS and RHS can be the same object:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.match( edge_ ) );

        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            typename SubstrT::offset_guard_T unadjusted_first_offset( edge_.first );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // ik-5/17/2009
                // Update parseable substring boundaries:
                if ( unadjusted_first_offset == edge_.first.offset() ) {
                    // Only if user has not already modified the upper boundary
                    // by node expression adapter edge_.first(R)
                    edge_.first = strict_universe.first.offset();
                }
                edge_.second = strict_universe.second.offset();
                return match_lhs_offset;
            }
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_RESULT( false, '^' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7930_concat.html">concatenation operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // !L^R_
        CTTL_TRACE_LEVEL_FIND( '^' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        // match_lhs_offset is required because LHS and RHS can be the same object:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.find( edge_ ) );

        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            typename SubstrT::offset_guard_T unadjusted_first_offset( edge_.first );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // ik-5/17/2009
                // Update parseable substring boundaries:
                if ( unadjusted_first_offset == edge_.first.offset() ) {
                    // Only if user has not already modified the upper boundary,
                    // by node expression adapter edge_.first(R)
                    edge_.first = strict_universe.first.offset();
                }
                edge_.second = strict_universe.second.offset();
                return match_lhs_offset;
            }
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_RESULT( false, '^' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7930_concat.html">concatenation operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // !!L^R_
        CTTL_TRACE_LEVEL_BANG( '^' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, SubstrT::string_T::npos );
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );

        while ( ( match_lhs_offset = this->m_expr_lhs.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            typename SubstrT::offset_guard_T unadjusted_first_offset( edge_.first );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // ik-5/17/2009
                // Update parseable substring boundaries:
                if ( unadjusted_first_offset == edge_.first.offset() ) {
                    // Only if user has not already modified the upper boundary,
                    // by node expression adapter edge_.first(R)
                    edge_.first = strict_universe.first.offset();
                }
                edge_.second = strict_universe.second.offset();
                return match_lhs_offset;
            }

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( '^', "!!(R1^R2): search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_RESULT( false, '^' );
        return SubstrT::string_T::npos;
    }

private:
    /**Assignment is disabled.*/
    xtl_opbinconcat< Left_exprT, Right_exprT >& operator=( xtl_opbinconcat< Left_exprT, Right_exprT > const& );

};  // xtl_opbinconcat


/**@struct xtl_opbinminus
 * @brief Implements behavior of binary
 * the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8030_complem.html">set complement operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbinminus : public xtl_op_base_binary< Left_exprT, Right_exprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbinminus( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }


    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8030_complem.html">set complement operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // L-R_ strict set-difference
        // if L succeeds, and R fails, substring needs to be restored
        CTTL_TRACE_LEVEL_MATCH( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.match( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) == SubstrT::string_T::npos ) {
                // RHS did not match, we succeed:
                saved_lhs_edge.restore( edge_ );        // restore LHS edge
                return match_lhs_offset;
            }
        }

        // RHS matched, we fail:
        edge_.first.offset( saved_first_offset );       // restore substring
        edge_.second.offset( saved_lhs_edge.second );
        CTTL_TRACE_RESULT( false, '-' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8030_complem.html">set complement operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // !L-R_
        CTTL_TRACE_LEVEL_FIND( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.find( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) == SubstrT::string_T::npos ) {
                // RHS did not match, we succeed:
                saved_lhs_edge.restore( edge_ );            // restore LHS edge
                return match_lhs_offset;
            }
        }

        // RHS matched, we fail:
        edge_.first.offset( saved_first_offset );       // restore substring
        edge_.second.offset( saved_lhs_edge.second );
        CTTL_TRACE_RESULT( false, '-' );
        return SubstrT::string_T::npos;
    }


    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8030_complem.html">set complement operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // !!(L_-R)
        CTTL_TRACE_LEVEL_BANG( '-' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, SubstrT::string_T::npos );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );

        while ( ( match_lhs_offset = this->m_expr_lhs.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) == SubstrT::string_T::npos ) {
                // RHS did not match, we succeed:
                saved_lhs_edge.restore( edge_ );            // restore LHS edge
                return match_lhs_offset;
            }

            // RHS matched, continue searching:
            saved_lhs_edge.restore( edge_ );                // restore LHS edge

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( '-', "!!(R1-R2): search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_RESULT( false, '-' );
        return SubstrT::string_T::npos;
    }

};  // xtl_opbinminus


/**@struct xtl_opbinand
 * @brief Implements behavior of binary
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection operator</a>.
 *
 * @tparam Left_exprT
 *        specifies type of left-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 * @tparam Right_exprT
 *        specifies type of right-hand-side
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        object, determined by the C++ compiler at compile time.
 *
 *
 */
template< typename Left_exprT, typename Right_exprT >
struct xtl_opbinand : public xtl_op_base_binary< Left_exprT, Right_exprT > {

    // compile-time

    /**Constructs and initializes the object.
    *
    * @tparam Left_exprT
    *        specifies type of left-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @tparam Right_exprT
    *        specifies type of right-hand-side
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to left-hand-side grammar expression object.
    *
    * @param rhs_expr_
    *        immutable reference to right-hand-side grammar expression object.
    *
    */
    xtl_opbinand( Left_exprT const& lhs_expr_, Right_exprT const& rhs_expr_ )
    : xtl_op_base_binary< Left_exprT, Right_exprT >( lhs_expr_, rhs_expr_ )
    {
    }


    // run-time

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1310_match.html">match evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        // L&R_ strict set-intersection
        // if L succeeds, and R fails, substring needs to be restored
        CTTL_TRACE_LEVEL_MATCH( '&' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.match( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // LHS & RHS intersection succeeded
                saved_lhs_edge.restore( edge_ );        // restore LHS edge
                return match_lhs_offset;
            }
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        edge_.second.offset( saved_lhs_edge.second );
        CTTL_TRACE_RESULT( false, '&' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1320_find.html">search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        // !L&R_
        CTTL_TRACE_LEVEL_FIND( '&' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring

        // position of the left side of the substring after LHS succeeds:
        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, this->m_expr_lhs.find( edge_ ) );
        if ( match_lhs_offset != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // LHS & RHS intersection succeeded
                saved_lhs_edge.restore( edge_ );            // restore LHS edge
                return match_lhs_offset;
            }
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        edge_.second.offset( saved_lhs_edge.second );
        CTTL_TRACE_RESULT( false, '&' );
        return SubstrT::string_T::npos;
    }
    

    /**Implements
    *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1330_bang.html">repeatable search evaluation</a>
    *  for the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection operator</a>,
    *  starting at the upper boundary of the
    *  parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam SubstrT
    *        specifies type of the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to the parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @post
    *        If algorithm succeeds, the substring, specified
    *        by the @c edge_ parameter, is consumed according to
    *        the size of the matched fragment.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>: if algorithm succeeds, it returns absolute
    *        offset corresponding to the upper boundary of the matched fragment.
    *        Otherwise, it returns @c SubstrT::string_T::npos,
    *        indicating that the evaluation algorithm has failed.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        // !!L&R_
        CTTL_TRACE_LEVEL_BANG( '&' );
        typename SubstrT::offset_guard_T saved_first_offset( edge_.first );
        xtl_edge_offset_guard< SubstrT > saved_lhs_edge( edge_ );   // preserve current substring
        // if this offset stops progressing, we must bail out of infinite loop:
        typename SubstrT::offset_guard_T iteration_offset( edge_.first, SubstrT::string_T::npos );

        typename SubstrT::offset_guard_T match_lhs_offset( edge_.first, SubstrT::string_T::npos );
        while ( ( match_lhs_offset = this->m_expr_lhs.bang_find( edge_ ) ) != SubstrT::string_T::npos ) {
            saved_lhs_edge.save( edge_ );                   // preserve LHS edge
            edge_.second.offset( edge_.first.offset() );    // restrict RHS substring
            edge_.first.offset( match_lhs_offset );
            typename SubstrT::strict_edge_T strict_universe( edge_ );
            if ( this->m_expr_rhs.match( strict_universe ) != SubstrT::string_T::npos ) {
                // LHS & RHS intersection succeeded
                saved_lhs_edge.restore( edge_ );            // restore LHS edge
                return match_lhs_offset;
            }

            // RHS did not match, continue searching:
            saved_lhs_edge.restore( edge_ );                // restore LHS edge

            if ( iteration_offset == edge_.first.offset() ) {
                CTTL_TRACE_TEXT( '&', "!!(R1&R2): search made no progress: bailing out" );
                break;  // second, third, etc., iteration hasn't made any progress: bail out
            }

            iteration_offset = edge_.first.offset();
        }

        edge_.first.offset( saved_first_offset );       // restore substring
        CTTL_TRACE_RESULT( false, '&' );
        return SubstrT::string_T::npos;
    }

private:
    /**Assignment is disabled.*/
    xtl_opbinand< Left_exprT, Right_exprT >& operator=( xtl_opbinand< Left_exprT, Right_exprT > const& );

};  // xtl_opbinand

//////////////////////////////////////////////////
// Typedefs for metaphors support
//////////////////////////////////////////////////

/**Defines type of epsilon symbol which succeeds on empty substring.*/
typedef xtl_wrap< xtl_opbinplus< relaxed_bool_T, xtl_wrap< xtl_opunarbang< xtl_wrap< xtl_position_eof > > > > >
universe_T;

}   // namespace cttl_impl

#endif // _CTTL_XTL_OP_IMPL_H_INCLUDED_
