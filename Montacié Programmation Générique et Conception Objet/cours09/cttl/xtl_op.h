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

/**@file xtl_op.h
* @brief Defines namespace-scope
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">overloaded operators</a>
* of the Common Text Transformation Library.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*/

// xtl_op.h

#ifndef _CTTL_XTL_OP_H_INCLUDED_
#define _CTTL_XTL_OP_H_INCLUDED_

#include "xtl_op_impl.h"

namespace cttl {

    ////////////////////////////////////////////////////////////
    // compile time functions overloading unary operators 
    ////////////////////////////////////////////////////////////

    /**Overloads unary 
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7720_find.html">search</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam ExprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename ExprT >
    inline
        xtl_wrap<
        xtl_opunarbang<
        xtl_wrap< ExprT >
        >
        >
        operator! ( xtl_wrap< ExprT > const& expr_ )
    {
        typedef
            xtl_opunarbang<
            xtl_wrap< ExprT >
            >
            opfind_T;

        return xtl_wrap< opfind_T >( opfind_T( expr_ ) );
    }


    /**Overloads unary 
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7820_0m.html">Kleene star</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam ExprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename ExprT >
    inline
        xtl_wrap<
        xtl_opunarstar<
        xtl_wrap< ExprT >
        >
        >
        operator* ( xtl_wrap< ExprT > const& expr_ )
    {
        typedef
            xtl_opunarstar<
            xtl_wrap< ExprT >
            >
            opstar_T;

        return xtl_wrap< opstar_T >( opstar_T( expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7830_0N.html">Kleene star</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam Left_exprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @param upper_limit_
    *        upper limit of requested number of matches.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT >
    inline
        xtl_wrap<
        xtl_opunarstar<
        xtl_wrap< Left_exprT >
        >
        >
        operator* ( xtl_wrap< Left_exprT > const& lhs_expr_, int upper_limit_ )
    {
        typedef
            xtl_opunarstar<
            xtl_wrap< Left_exprT >
            >
            opstar_T;

        return xtl_wrap< opstar_T >( opstar_T( lhs_expr_, upper_limit_ ) );
    }

    /**Overloads unary 
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7840_1m.html">Kleene plus</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam ExprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename ExprT >
    inline
        xtl_wrap<
        xtl_opunarplus<
        xtl_wrap< ExprT >
        >
        >
        operator+ ( xtl_wrap< ExprT > const& expr_ )
    {
        typedef
            xtl_opunarplus<
            xtl_wrap< ExprT >
            >
            opplus_T;

        return xtl_wrap< opplus_T >( opplus_T( expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7850_1N.html">Kleene plus</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam Left_exprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @param upper_limit_
    *        upper limit of requested number of matches.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT >
    inline
        xtl_wrap<
        xtl_opunarplus<
        xtl_wrap< Left_exprT >
        >
        >
        operator+ ( xtl_wrap< Left_exprT > const& lhs_expr_, int upper_limit_ )
    {
        typedef
            xtl_opunarplus<
            xtl_wrap< Left_exprT >
            >
            opplus_T;

        return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, upper_limit_ ) );
    }


    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7860_NM.html">greedy Kleene plus</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam Left_exprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param lhs_expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @param limits_
    *        STL pair specifying lower and upper limits for the requested matches, for example,
    @code
    std::make_pair( lower_limit, upper_limit )
    @endcode
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT >
    inline
        xtl_wrap<
        xtl_opunarplus<
        xtl_wrap< Left_exprT >
        >
        >
        operator+ ( xtl_wrap< Left_exprT > const& lhs_expr_, std::pair< int, int > limits_ )
    {
        typedef
            xtl_opunarplus<
            xtl_wrap< Left_exprT >
            >
            opplus_T;

        return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, limits_.second, limits_.first ) );
    }

    /**Overloads unary 
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8020_not.html">negative lookahead assertion</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
    *
    * @tparam ExprT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        object, determined by the C++ compiler at compile time.
    *
    * @param expr_
    *        immutable reference to CTTL grammar expression object.
    *
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename ExprT >
    inline
        xtl_wrap<
        xtl_opunarminus<
        xtl_wrap< ExprT >
        >
        >
        operator- ( xtl_wrap< ExprT > const& expr_ )
    {
        typedef
            xtl_opunarminus<
            xtl_wrap< ExprT >
            >
            opminus_T;

        return xtl_wrap< opminus_T >( opminus_T( expr_ ) );
    }

    ////////////////////////////////////////////////////////////
    // compile time functions overloading binary operators 
    ////////////////////////////////////////////////////////////

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbinplus<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator+ ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbinplus<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            opplus_T;

        return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbinpipe<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator| ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbinpipe<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            oppipe_T;

        return xtl_wrap< oppipe_T >( oppipe_T( lhs_expr_, rhs_expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8080_posix.html">POSIX union</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbin2pipe<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator|| ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbin2pipe<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            oppipe_T;

        return xtl_wrap< oppipe_T >( oppipe_T( lhs_expr_, rhs_expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7930_concat.html">concatenation</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbinconcat<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator^ ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbinconcat<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            opconcat_T;

        return xtl_wrap< opconcat_T >( opconcat_T( lhs_expr_, rhs_expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8030_complem.html">set complement</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbinminus<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator- ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbinminus<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            opbinminus_T;

        return xtl_wrap< opbinminus_T >( opbinminus_T( lhs_expr_, rhs_expr_ ) );
    }

    /**Overloads binary
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection</a>
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>.
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
    * @return
    *        Instance of C++ implementation class for the overloaded operator.
    *
    */
    template< typename Left_exprT, typename Right_exprT >
    inline
        xtl_wrap<
        xtl_opbinand<
        xtl_wrap< Left_exprT >,
        xtl_wrap< Right_exprT >
        >
        >
        operator& ( xtl_wrap< Left_exprT > const& lhs_expr_, xtl_wrap< Right_exprT > const& rhs_expr_ )
    {
        typedef
            xtl_opbinand<
            xtl_wrap< Left_exprT >,
            xtl_wrap< Right_exprT >
            >
            opbinand_T;

        return xtl_wrap< opbinand_T >( opbinand_T( lhs_expr_, rhs_expr_ ) );
    }

}   // namespace cttl

#endif // _CTTL_XTL_OP_H_INCLUDED_
