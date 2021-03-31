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

/**@file xst_unary_adaptor.h
 * @brief Defines implementation classes for CTTL lambda expressions.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_unary_adaptor.h

#ifndef _XST_UNARY_ADAPTOR_H_INCLUDED_
#define _XST_UNARY_ADAPTOR_H_INCLUDED_

namespace cttl_impl {

// U -> U<E,A>, where U := xst_unary_adaptor< ExprT, PolicyAdaptorT >

/**@class xst_unary_adaptor
 * @brief Lambda expression adaptor for binary operators.
 *
 * @brief Implements behavior of CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @tparam ExprT
 *        specifies type of expression operand.
 *
 * @tparam PolicyAdaptorT
 *        specifies type of policy class
 *        implementing behavior of the unary operator.
 *
 */
template< typename ExprT, typename PolicyAdaptorT >
class xst_unary_adaptor : public xtl_op_base_unary< ExprT > {

public:
    enum {
        /**Unique identifier constant of unary expression adaptor.*/
        primitive_id_ = primitive_id_unary_adaptor,

        /**Unique identifier constant of unary operator.*/
        operator_id_ = PolicyAdaptorT::operator_id_,

        /**Capacity of unary expression adaptor.*/
        capacity_ = ExprT::capacity_
    };


    /**Defines result type of unary operator expression.*/
    typedef typename xst_unary_operator_traits<
        typename ExprT::value_T,
        typename ExprT::dereferenced_value_T,
        operator_id_
    >::value_type value_T;

    /**Defines value type of unary operator expression.*/
    typedef value_T value_type;

    /**Defines type of dereferenced result of unary operator expression.*/
    typedef typename ExprT::dereferenced_value_T dereferenced_value_T; // always carried over as is

    /**Constructs and initializes the object.*/
    xst_unary_adaptor( ExprT const& expr_ )
    : xtl_op_base_unary< ExprT >( expr_ )
    {
    }

    /**Copy constructor.*/
    xst_unary_adaptor( xst_unary_adaptor< ExprT, PolicyAdaptorT > const& other_ )
    : xtl_op_base_unary< ExprT >( other_.m_expr )
    {
    }

    /**Evaluates encapsulated lambda expression.*/
    void evaluate()
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_DELAYED_CHAR( '\n' );
        PolicyAdaptorT::top( this->m_expr );
    }

    /**Implements <a href="http://cttl.sourceforge.net/">CTTL</a>
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
    *
    * @tparam SubstrT
    *        specifies type of
    *        parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @param edge_
    *        reference to the
    *        parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @pre
    *        Result of encapsulated lambda expression is integral type.
    *
    * @return
    *    <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>
    *    is determined by @c PolicyAdaptorT implementation.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'u' );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_DELAYED_CHAR( '\n' );
        return PolicyAdaptorT::match( this->m_expr, edge_ );
    }

    /**Evaluates encapsulated lambda expression and returns its result.*/
    value_T top() const
    {
        return PolicyAdaptorT::top( this->m_expr );
    }

    /**Evaluates encapsulated lambda expression and returns its result.*/
    template< typename SubscriptLambdaT >
    value_T top( SubscriptLambdaT ) const
    {
        return top();
    }

    /**Evaluates encapsulated lambda expression and returns reference to the result.*/
    value_T& lvalue_ref()
    {
        return PolicyAdaptorT::lvalue_ref( this->m_expr );
    }

    /**Returns dereferenced result of unary operator expression.*/
    dereferenced_value_T&
    dereferenced_value()
    {
        return PolicyAdaptorT::dereferenced_lvalue( this->m_expr );
    }


    /**Fulfills prefix side effects for encapsulated lambda expresion.*/
    void prefix_side_effects()
    {
        PolicyAdaptorT::prefix_side_effects( this->m_expr );
    }

    /**Fulfills postfix side effects for encapsulated lambda expresion.*/
    void postfix_side_effects()
    {
        PolicyAdaptorT::postfix_side_effects( this->m_expr );
    }

////////////////////////////////////////////////////////////////////////
// Overloaded operators
////////////////////////////////////////////////////////////////////////

// Do not modify section of code between begin_generated_code
// and end_generated_code comments. This section of code is
// maintained by gumus scripts.

//begin_generated_code
// generated by bin/gmu/gmu_lambda/gmu_common.h:626
// on Sun Aug 16 21:52:48 2009.
// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment = operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment = abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment = specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment = abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment = operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment *= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment *= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda multiplication assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda multiplication assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment *= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda multiplication assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_multiplication_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_multiplication_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda multiplication assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda multiplication assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda multiplication assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment *= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda multiplication assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda multiplication assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_multiplication_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_multiplication_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment *= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment /= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment /= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda division assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda division assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment /= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda division assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_division_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_division_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda division assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda division assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda division assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment /= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda division assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda division assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_division_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_division_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment /= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment %= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment %= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda modulus assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda modulus assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment %= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda modulus assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_modulus_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_modulus_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda modulus assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda modulus assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda modulus assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment %= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda modulus assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda modulus assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_modulus_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_modulus_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment %= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment += operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment += abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda addition assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda addition assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment += specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda addition assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_addition_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_addition_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda addition assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda addition assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda addition assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment += abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda addition assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda addition assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_addition_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_addition_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment += operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment -= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment -= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda subtraction assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda subtraction assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment -= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda subtraction assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_subtraction_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_subtraction_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda subtraction assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda subtraction assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda subtraction assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment -= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda subtraction assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda subtraction assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_subtraction_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_subtraction_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment -= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment <<= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment <<= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda left shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda left shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment <<= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda left shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_left_shift_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_left_shift_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda left shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda left shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda left shift assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment <<= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda left shift assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda left shift assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_left_shift_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_left_shift_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment <<= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment >>= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment >>= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda right shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda right shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment >>= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda right shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_right_shift_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_right_shift_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda right shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda right shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda right shift assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment >>= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda right shift assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda right shift assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_right_shift_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_right_shift_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment >>= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment &= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment &= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment &= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_and_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_and_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment &= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment &= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment |= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment |= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment |= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_ior_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_ior_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment |= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment |= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:177
////////////////////////////////////////////////////////////////////////////
// Assignment ^= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment ^= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:8
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param value_
    *        reference to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:51
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of assignment.
    *
    * @param pvalue_
    *        pointer to right-hand-side value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename RhsValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment ^= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:97
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies right-hand-side lambda primitive.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_xor_assignment_policy<
            LambdaT::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_xor_assignment_policy<
                LambdaT::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:137
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to unary policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_unary_adaptor< LambdaT, PolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, PolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_unary_adaptor< LambdaT, PolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:178
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam OtherPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename OtherPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_unary_adaptor< LambdaT, OtherPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:223
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_binary_adaptor.
    *
    * @tparam BinaryPolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda expression.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment ^= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:275
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/unary_adaptor_assign_funcs.h:320
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_unary_adaptor< ExprT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_stack capacity
            xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_unary_adaptor< ExprT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_stack capacity
                xst_unary_adaptor< ExprT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment ^= operators end
////////////////////////////////////////////////////////////////////////////

//end_generated_code

};  // xst_unary_adaptor


}   // namespace cttl_impl


#endif //_XST_UNARY_ADAPTOR_H_INCLUDED_
