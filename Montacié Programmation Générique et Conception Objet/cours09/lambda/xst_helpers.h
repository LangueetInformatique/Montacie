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

/**@file xst_helpers.h
 * @brief Defines lambda helper functions and overloaded operators.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_helpers.h

#ifndef _XST_HELPERS_H_INCLUDED_
#define _XST_HELPERS_H_INCLUDED_

#include <utility>
#include <map>

/**@namespace cttl
 * @brief Namespace @c cttl defines publicly visible classes and
 * functions of CTTL library.
 *
 */
namespace cttl {

using namespace cttl_impl;

/**Helper function to instantiate scalar primitive.
*
* @tparam ValueT
*         specifies type of copy-constructlible object
*         to be stored in scalar lambda primitive. @c ValueT can
*         be either primitive type, or a value container, a compound
*         type exposing @c value_type @c typedef. In addition, @c ValueT
*         can be of type
*         <a href="http://www.sgi.com/tech/stl/pair.html"><tt>std::pair</tt></a>.
*
* @param value_
*        Constant reference to object to store a copy of.
*
* @return
*        Scalar lambda primitive object encapsulating the value.
*
*/
template< typename ValueT >
inline
xst_lambda_wrap< xst_scalar< ValueT > >
scalar( ValueT const& value_ )
{
    return xst_lambda_wrap< xst_scalar< ValueT > >( value_ );
}


/**Helper function to instantiate stack lambda primitive.
*
* @tparam ValueT
*         specifies type of object stored in the stack.
*
* @param value_
*        Constant reference to an object which can be stored in the stack.
*        No values are pushed into the stack by @c make_stack function:
*        actual value of @c value_ is not used.
*
* @return
*        Instance of stack lambda primitive encapsulating instance of STL
*        <a href="http://www.sgi.com/tech/stl/stack.html"><tt>std::stack</tt></a>
*        container adaptor.
*
*/
template< typename ValueT >
inline
xst_lambda_wrap< xst_stack< std::stack< ValueT > > >
make_stack( ValueT const& value_ )
{
    return xst_lambda_wrap< xst_stack< std::stack< ValueT > > >( value_ );
}

/**Helper function to instantiate stack lambda primitive.
*
* @tparam ValueT
*         specifies type of object stored in the stack.
*
* @param stack_
*        Constant reference to
*        <a href="http://www.sgi.com/tech/stl/stack.html"><tt>std::stack</tt></a>
*        container adaptor.
*
* @return
*        Instance of stack lambda primitive encapsulating copy of STL
*        stack specified by function argument.
*
*/
template< typename ValueT >
inline
xst_lambda_wrap< xst_stack< std::stack< ValueT > > >
scalar( std::stack< ValueT > const& stack_ )
{
    return xst_lambda_wrap< xst_stack< std::stack< ValueT > > >( stack_ );
}

/**Helper function to instantiate lambda reference primitive.
*
* @tparam ValueT
*         specifies type of object
*         to be referred by scalar reference primitive. @c ValueT can
*         be either primitive type, or a value container, a compound
*         type exposing @c value_type @c typedef. In addition, @c ValueT
*         can be of type
*         <a href="http://www.sgi.com/tech/stl/pair.html"><tt>std::pair</tt></a>.
*
* @param pvalue_
*        Pointer to object to refer to.
*
* @return
*        Reference lambda primitive encapsulating mutable
*        reference to the specified object.
*
*/
template< typename ValueT >
inline
xst_lambda_wrap< xst_scalar< ValueT& > >
scalar( ValueT* pvalue_ )
{
    assert( pvalue_ );
    return xst_lambda_wrap< xst_scalar< ValueT& > >( pvalue_ );
}

/**Helper function to instantiate stack reference primitive.
*
* @tparam ValueT
*         specifies type of object stored in the stack.
*
* @param pstack_
*        Pointer to
*        <a href="http://www.sgi.com/tech/stl/stack.html"><tt>std::stack</tt></a>
*        object to refer to.
*
* @return
*        Stack lambda reference primitive encapsulating mutable
*        reference to the specified stack object.
*
*/
template< typename ValueT >
inline
xst_lambda_wrap< xst_stack< std::stack< ValueT >& > >
scalar( std::stack< ValueT >* pstack_ )
{
    assert( pstack_ );
    return xst_lambda_wrap< xst_stack< std::stack< ValueT >& > >( pstack_ );
}


#ifndef CTTL_LAMBDA_SINGULAR

/**Overloaded operator to compose binary tree representing lambda compound.*/
template< typename LhsT, typename RhsT >
inline
xst_lambda_wrap<
    xst_pair<
        xst_lambda_wrap< typename LhsT::reference_T >,
        xst_lambda_wrap< typename RhsT::reference_T >
    >
>
operator^ ( // D^D
           xst_lambda_wrap< LhsT > const& lhs_expr_,
           xst_lambda_wrap< RhsT > const& rhs_expr_
           )
{
    // expression a^b^c produces the following tree:
    //     ^    //
    //    / \   //
    //   ^  c   //
    //  / \     //
    // a   b    //

    typedef
        xst_pair<
            xst_lambda_wrap< typename LhsT::reference_T >,
            xst_lambda_wrap< typename RhsT::reference_T >
        >
        pair_T;

    return xst_lambda_wrap< pair_T >(
        pair_T(
            lhs_expr_.make_reference(),
            rhs_expr_.make_reference()
        )
    );
}

/**Overloaded operator to compose binary tree representing lambda compound.*/
template< typename LhsT >
inline
xst_lambda_wrap<
    xst_pair<
        xst_lambda_wrap< typename LhsT::reference_T >,
        xst_lambda_wrap< xst_scalar< int > >
    >
>
operator^ ( // D^int
           xst_lambda_wrap< LhsT > const& lhs_expr_, int value_
           )
{
    typedef
        xst_pair<
            xst_lambda_wrap< typename LhsT::reference_T >,
            xst_lambda_wrap< xst_scalar< int > >
        >
        pair_T;

    return xst_lambda_wrap< pair_T >(
        pair_T(
            lhs_expr_.make_reference(),
            xst_lambda_wrap< xst_scalar< int > >( value_ )
            )
        );
}

/**Overloaded operator to compose binary tree representing lambda compound.*/
template< typename LhsT, typename ValueT >
inline
xst_lambda_wrap<
    xst_pair<
        xst_lambda_wrap< typename LhsT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< ValueT > > >
    >
>
operator^ ( // D^stack
           xst_lambda_wrap< LhsT > const& lhs_expr_,
           std::stack< ValueT > const& stack_
           )
{
    typedef
        xst_pair<
            xst_lambda_wrap< typename LhsT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< ValueT > > >
        >
        pair_T;

    return xst_lambda_wrap< pair_T >(
        pair_T(
            lhs_expr_.make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< ValueT > > >( stack_ )
            )
        );
}

/**Overloaded operator to compose binary tree representing lambda compound.*/
template< typename LhsT, typename ValueT >
inline
xst_lambda_wrap<
    xst_pair<
        xst_lambda_wrap< typename LhsT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< ValueT >& > >
    >
>
operator^ ( // D^stack*
           xst_lambda_wrap< LhsT > const& lhs_expr_,
           std::stack< ValueT >* pstack_
           )
{
    typedef
        xst_pair<
            xst_lambda_wrap< typename LhsT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< ValueT >& > >
        >
        pair_T;

    return xst_lambda_wrap< pair_T >(
        pair_T(
            lhs_expr_.make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< ValueT >& > >( pstack_ )
            )
        );
}

/**Overloaded operator to compose binary tree representing lambda compound.*/
template< typename LhsT >
inline
xst_lambda_wrap<
    xst_pair<
        xst_lambda_wrap< typename LhsT::reference_T >,
        xst_lambda_wrap< xst_scalar< int& > >
    >
>
operator^ ( // D^int*
           xst_lambda_wrap< LhsT > const& lhs_expr_,
           int* pvalue_
           )
{
    typedef
        xst_pair<
            xst_lambda_wrap< typename LhsT::reference_T >,
            xst_lambda_wrap< xst_scalar< int& > >
        >
        pair_T;

    return xst_lambda_wrap< pair_T >(
        pair_T(
            lhs_expr_.make_reference(),
            xst_lambda_wrap< xst_scalar< int& > >( pvalue_ )
            )
        );
}
#endif //CTTL_LAMBDA_SINGULAR

/**Overloaded operator to formulate translator for CTTL substring.*/
template< typename LambdaT, typename TranslatorT, typename PolicyT, typename StringT >
inline
xst_lambda_wrap<
    xst_translator<
        xst_lambda_wrap<
            xst_translator<
                LambdaT,
                TranslatorT
            >
        >
        ,
        xst_edge_translator< PolicyT, StringT >
    >
>
operator^ ( // T^const_edge
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
           const&
           lambda_,
           const_edge< PolicyT, StringT >
           const&
           edge_
           )
{
    typedef xst_edge_translator< PolicyT, StringT > edge_translator_T;
    typedef
        xst_translator<
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
            ,
            edge_translator_T
        >
        translator_T;

    return xst_lambda_wrap< translator_T >( translator_T( lambda_, edge_translator_T( edge_ ) ) );
}

/**Overloaded operator to formulate translator for CTTL substring.*/
template< typename LambdaT, typename TranslatorT, typename PolicyT, typename StringT >
inline
xst_lambda_wrap<
    xst_translator<
        xst_lambda_wrap<
            xst_translator<
                LambdaT,
                TranslatorT
            >
        >
        ,
        xst_edge_translator< PolicyT, StringT >
    >
>
operator^ ( // T^edge
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
           const&
           lambda_,
           edge< PolicyT, StringT >
           const&
           edge_
           )
{
    typedef xst_edge_translator< PolicyT, StringT > edge_translator_T;
    typedef
        xst_translator<
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
            ,
            edge_translator_T
        >
        translator_T;

    return xst_lambda_wrap< translator_T >( translator_T( lambda_, edge_translator_T( edge_ ) ) );
}

/**Overloaded operator to formulate translator for STL vector.*/
template< typename LambdaT, typename TranslatorT, typename ValueT >
inline
xst_lambda_wrap<
    xst_translator<
        xst_lambda_wrap<
            xst_translator<
                LambdaT,
                TranslatorT
            >
        >
        ,
        xst_sequence_translator< std::vector< ValueT > >
    >
>
operator^ ( // T^vector sequence translator
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
           const&
           lambda_,
           std::vector< ValueT >&
           vector_
           )
{
    typedef xst_sequence_translator< std::vector< ValueT > > sequence_translator_T;
    typedef
        xst_translator<
            xst_lambda_wrap<
                xst_translator<
                    LambdaT,
                    TranslatorT
                >
            >
            ,
            sequence_translator_T
        >
        translator_T;

    return xst_lambda_wrap< translator_T >( translator_T( lambda_, sequence_translator_T( vector_ ) ) );
}

/**Overloaded operator to formulate translator for STL vector.*/
template< typename LhsLambdaT, typename ValueT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_sequence_translator< std::vector< ValueT > >
    >
>
operator^ ( // D^vector: sequence translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           std::vector< ValueT >&
           vector_
           )
{
    typedef xst_sequence_translator< std::vector< ValueT > > sequence_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                sequence_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            sequence_translator_T( vector_ )
            )
        );
}

/**Overloaded operator to formulate dictionary translator.*/
template< typename LhsLambdaT, typename SequenceT, typename MapT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_dictionary_translator< SequenceT, MapT >
    >
>
operator^ ( // D^pair< SequenceT*, MapT* > dictionary translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           std::pair< SequenceT*, MapT* >&
           pair_
           )
{
    typedef xst_dictionary_translator< SequenceT, MapT > dictionary_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                dictionary_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            dictionary_translator_T( *pair_.first, *pair_.second )
            )
        );
}

/**Overloaded operator to formulate dictionary translator.*/
template< typename LhsLambdaT, typename SequenceT, typename MapT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_dictionary_translator< SequenceT, MapT >
    >
>
operator^ ( // D^pair< SequenceT, MapT > dictionary translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           std::pair< SequenceT, MapT >&
           pair_
           )
{
    typedef xst_dictionary_translator< SequenceT, MapT > dictionary_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                dictionary_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            dictionary_translator_T( pair_.first, pair_.second )
            )
        );
}

/**Overloaded operator to formulate sequence translator.*/
template< typename LhsLambdaT, typename SequenceT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_sequence_translator< SequenceT >
    >
>
operator^ ( // D^pair< SequenceT*, int > sequence translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           std::pair< SequenceT*, int >&
           pair_
           )
{
    typedef xst_sequence_translator< SequenceT > sequence_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                sequence_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            sequence_translator_T( *pair_.first )
            )
        );
}

/**Overloaded operator to formulate STL sequence translator.*/
template< typename LhsLambdaT, typename SequenceT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_sequence_translator< SequenceT >
    >
>
operator^ ( // D^pair< SequenceT, int > sequence translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           std::pair< SequenceT, int >&
           pair_
           )
{
    typedef xst_sequence_translator< SequenceT > sequence_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                sequence_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            sequence_translator_T( pair_.first )
            )
        );
}

/**Overloaded operator to formulate translator for character literal.*/
template< typename LhsLambdaT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_literal_translator< char >
    >
>
operator^ ( // D^"text" literal translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           char const* pchar_
           )
{
    typedef xst_literal_translator< char > literal_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                literal_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            literal_translator_T( pchar_ )
            )
        );
}


/**Overloaded operator to formulate translator for wide character literal.*/
template< typename LhsLambdaT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        xst_literal_translator< wchar_t >
    >
>
operator^ ( // D^L"text" literal translator
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           wchar_t const* pwchar_
           )
{
    typedef xst_literal_translator< wchar_t > wliteral_translator_T;
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                wliteral_translator_T
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            wliteral_translator_T( pwchar_ )
            )
        );
}


/**Overloaded operator to formulate general purpose translator
*  based on functional composition.
*
* @return
* Functional composition translator which stores a reference
* to the left-hand-side lambda compound.
*
* @warning
* Translator returned by this version of overloaded @c operator^
* is designed for in-line data translations inside lambda
* expressions. Since only reference to the lambda primitive accepting
* result of translation is stored, it
* is unsuitable for user-defined helper functions which
* intend to return translator with scalar root back to the caller.
* Such functions should use cttl::make_translator() helper
* function to manufacture value-based translator, or else a reference
* to local object will be returned, resulting in a hard to catch bug.
*
*/
template< typename LhsLambdaT, typename RhsTranslatorT >
inline
xst_lambda_wrap<
    xst_translator<
        typename LhsLambdaT::reference_T,
        RhsTranslatorT
    >
>
operator^ ( // D^T
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           RhsTranslatorT translator_
           )
{
    typedef
            xst_translator<
                typename LhsLambdaT::reference_T,
                RhsTranslatorT
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda().make_reference(),
            translator_
            )
        );
}

/**Helper function to formulate general purpose translator
*  based on functional composition.
*
* @return
*    General purpose translator retaining
*    physical copy of the return value.
*
*/
template< typename LhsLambdaT, typename RhsTranslatorT >
inline
xst_lambda_wrap<
    xst_translator<
        LhsLambdaT,
        RhsTranslatorT
    >
>
make_translator( // D^T
           xst_lambda_wrap< LhsLambdaT > const& lambda_,
           RhsTranslatorT translator_
           )
{
    typedef
            xst_translator<
                LhsLambdaT,
                RhsTranslatorT
            >
        translator_T;

    return xst_lambda_wrap< translator_T >(
        translator_T(
            lambda_.right_lambda(),
            translator_
            )
        );
}

////////////////////////////////////////////////////////////////////////////
// Sequence operators for connecting lambda and grammar expressions
// via grammar sequence operators.
////////////////////////////////////////////////////////////////////////////

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinplus<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
    >
>
operator+ (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinplus<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinplus<
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator+ (
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinplus<
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinplus<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
    >
>
operator+ (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinplus<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7920_seq.html">sequence</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinplus<
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator+ (
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinplus<
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


////////////////////////////////////////////////////////////////////////////
// Intersection operators for connecting lambda and grammar expressions
// via set intersection operators.
////////////////////////////////////////////////////////////////////////////

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinand<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
    >
>
operator& (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinand<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinand<
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator& (
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinand<
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinand<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
    >
>
operator& (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinand<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8050_intersect.html">set intersection</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* expressions.
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinand<
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator& (
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinand<
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


////////////////////////////////////////////////////////////////////////////
// Operators for connecting lambda and grammar expressions
// via set union operators.
////////////////////////////////////////////////////////////////////////////

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinpipe<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
    >
>
operator| (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinpipe<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the unary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinpipe<
        xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator| (
           xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinpipe<
            xtl_wrap< xst_unary_adaptor< LambdaExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}

/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain CTTL
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* and lambda expressions.
*
* @tparam LeftExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side grammar expression object.
*
* @param rhs_expr_
*        reference to right-hand-side lambda compound expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename LeftExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinpipe<
        xtl_wrap< LeftExprT >,
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
    >
>
operator| (
           xtl_wrap< LeftExprT > const& lhs_expr_,
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinpipe<
            xtl_wrap< LeftExprT >,
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


/**Overloads binary
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8070_union.html">set union</a>
* <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">operator</a>
* allowing to chain lambda expression and
* CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar</a>
* expressions.
*
* @tparam RightExprT
*        specifies type of left-hand-side expression
*        representing grammar of the input language.
*
* @tparam LambdaLhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam LambdaRhsExprT
*        specifies type of
*        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
*
* @tparam PolicyAdaptorT
*        specifies type of policy class
*        implementing behavior of the binary operator.
*
* @param lhs_expr_
*        reference to left-hand-side lambda compound expression object.
*
* @param rhs_expr_
*        reference to right-hand-side grammar expression object.
*
* @return
*        Instance of CTTL grammar expression object.
*
*/
template< typename RightExprT, typename LambdaLhsExprT, typename LambdaRhsExprT, typename PolicyAdaptorT >
inline
xtl_wrap<
    xtl_opbinpipe<
        xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
        xtl_wrap< RightExprT >
    >
>
operator| (
           xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > const& lhs_expr_,
           xtl_wrap< RightExprT > const& rhs_expr_
           )
{
    typedef
        xtl_opbinpipe<
            xtl_wrap< xst_binary_adaptor< LambdaLhsExprT, LambdaRhsExprT, PolicyAdaptorT > >,
            xtl_wrap< RightExprT >
        >
        opplus_T;

    return xtl_wrap< opplus_T >( opplus_T( lhs_expr_, rhs_expr_ ) );
}


/**Overloaded operator to write data of lambda compound to output iterator.*/
template< typename OutputIteratorT, typename LambdaT >
OutputIteratorT const& operator<<(
                                  OutputIteratorT const& iterator_,
                                  xst_lambda_wrap< LambdaT > const& lambda_
                                  )
{
    OutputIteratorT* p_mutable_iterator_ = const_cast< OutputIteratorT* >( &iterator_ );
    xst_iterator_writer< OutputIteratorT > writer( *p_mutable_iterator_ );
    lambda_.traverse_top_down( writer );
    return iterator_;
}

}   // namespace cttl


#endif //_XST_HELPERS_H_INCLUDED_
