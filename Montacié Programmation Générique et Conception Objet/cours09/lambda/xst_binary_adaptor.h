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

/**@file xst_binary_adaptor.h
 * @brief Defines implementation classes for CTTL lambda expressions.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_adaptor.h

#ifndef _XST_BINARY_ADAPTOR_H_INCLUDED_
#define _XST_BINARY_ADAPTOR_H_INCLUDED_

namespace cttl_impl {

// forward declare lambda primitive required by assignment operators
template< typename LambdaT > struct xst_lambda_wrap;
template< typename ExprT, typename PolicyAdaptorT > class xst_unary_adaptor;

// forward declare lambda primitives required by abbreviated assignment operators
template< typename ValueT > struct xst_scalar;
template< typename ValueT > struct xst_stack;

// forward declare all assignment policies
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_multiplication_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_division_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_modulus_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_addition_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_subtraction_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_left_shift_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_right_shift_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_bitwise_and_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_bitwise_ior_assignment_policy;
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_bitwise_xor_assignment_policy;

// B -> B<L,R,A>, where B := xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >

/**@class xst_binary_adaptor
 * @brief Lambda expression adaptor for binary operators.
 *
 * @tparam LhsT
 *        specifies type of expression on the left
 *        hand side of binary operator.
 *
 * @tparam RhsT
 *        specifies type of expression on the right
 *        hand side of binary operator.
 *
 * @tparam PolicyAdaptorT
 *        specifies type of policy class
 *        implementing behavior of the binary operator.
 *
 */
template< typename LhsT, typename RhsT, typename PolicyAdaptorT >
class xst_binary_adaptor : public xtl_op_base_binary< LhsT, RhsT > {

public:

    enum {
        /**Unique identifier constant of binary expression adaptor.*/
        primitive_id_ = primitive_id_binary_adaptor,

        /**Unique identifier constant of binary operator.*/
        operator_id_ = PolicyAdaptorT::operator_id_,

        /**Capacity of binary expression adaptor.*/
        capacity_ = 1
    };


    /**Defines result type of binary operator expression.*/
    typedef typename xst_binary_operator_traits<
        typename RhsT::value_T,
        typename LhsT::value_T,
        operator_id_
    >::value_type value_T;

    /**Defines value type of binary operator expression.*/
    typedef value_T value_type;

    /**Defines type of dereferenced result of binary operator expression.*/
    typedef typename LhsT::dereferenced_value_T dereferenced_value_T;

    /**Constructs and initializes the object.*/
    xst_binary_adaptor( LhsT const& lhs_, RhsT const& rhs_ )
    : xtl_op_base_binary< LhsT, RhsT >( lhs_, rhs_ )
    {
    }

    /**Copy constructor.*/
    xst_binary_adaptor( xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT > const& other_ )
    : xtl_op_base_binary< LhsT, RhsT >( other_.m_expr_lhs, other_.m_expr_rhs )
    {
    }

    /**Evaluates encapsulated lambda expression.*/
    void evaluate()
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_DELAYED_CHAR( '\n' );
        PolicyAdaptorT::top( this->m_expr_lhs, this->m_expr_rhs );
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
        CTTL_TRACE_LEVEL_MATCH( 'b' );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_DELAYED_CHAR( '\n' );
        return PolicyAdaptorT::match( this->m_expr_lhs, this->m_expr_rhs, edge_ );
    }
        
    /**Evaluates encapsulated lambda expression and returns its result.*/
    value_T top() const
    {
        return PolicyAdaptorT::top( this->m_expr_lhs, this->m_expr_rhs );
    }

    /**Evaluates encapsulated lambda expression and returns its result.*/
    template< typename SubscriptLambdaT >
    value_T top( SubscriptLambdaT ) const
    {
        return top();
    }

    /**Evaluates encapsulated lambda expression and returns reference to the result.*/
    template< typename SubscriptLambdaT >
    value_T& top( SubscriptLambdaT )
    {
        prefix_side_effects();
        value_T& tmp_value_ref = lvalue_ref();
        postfix_side_effects();
        return tmp_value_ref;
    }

    /**Returns reference to the result of lambda expression.*/
    value_T& lvalue_ref()
    {
        return PolicyAdaptorT::lvalue_ref( this->m_expr_lhs, this->m_expr_rhs );
    }

    /**Fulfills prefix side effects for encapsulated lambda expresion.*/
    void prefix_side_effects()
    {
        PolicyAdaptorT::prefix_side_effects( this->m_expr_lhs, this->m_expr_rhs );
    }

    /**Fulfills postfix side effects for encapsulated lambda expresion.*/
    void postfix_side_effects()
    {
        PolicyAdaptorT::postfix_side_effects( this->m_expr_lhs );
    }

////////////////////////////////////////////////////////////////////////
// Overloaded operators
////////////////////////////////////////////////////////////////////////

// Do not modify section of code between begin_generated_code
// and end_generated_code comments. This section of code is
// maintained by gumus scripts.

//begin_generated_code
// generated by bin/gmu/gmu_lambda/gmu_common.h:704
// on Sun Aug 16 21:52:48 2009.
// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment = operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment = abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More = assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment *= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment *= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda multiplication assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_multiplication_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_multiplication_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda multiplication assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More *= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_multiplication_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator*= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_multiplication_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment /= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment /= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda division assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_division_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_division_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda division assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More /= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_division_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator/= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_division_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment %= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment %= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda modulus assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_modulus_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_modulus_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda modulus assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More %= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_modulus_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator%= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_modulus_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment += operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment += abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda addition assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_addition_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_addition_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda addition assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More += assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_addition_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator+= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_addition_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment -= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment -= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda subtraction assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_subtraction_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_subtraction_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda subtraction assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More -= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_subtraction_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator-= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_subtraction_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment <<= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment <<= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda left shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_left_shift_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_left_shift_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda left shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More <<= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_left_shift_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator<<= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_left_shift_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment >>= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment >>= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda right shift assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_right_shift_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_right_shift_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda right shift assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More >>= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_right_shift_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator>>= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_right_shift_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment &= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment &= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_and_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_and_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More &= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator&= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment |= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment |= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_ior_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_ior_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More |= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator|= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

// generated by bin/gmu/gmu_lambda/gmu_common.h:187
////////////////////////////////////////////////////////////////////////////
// Assignment ^= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment ^= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:8
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam RhsValueT
    *        specifies right-hand-side type of the operator expression.
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:51
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:98
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_xor_assignment_policy<
            LambdaT::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_xor_assignment_policy<
                LambdaT::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:138
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam LambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param lambda_
    *        reference to right-hand-side lambda operand policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaT, typename UnaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_unary_adaptor< LambdaT, UnaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:183
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
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename BinaryPolicyAdaptorT >
    xst_binary_adaptor<
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, BinaryPolicyAdaptorT >::capacity_,
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        return xst_adaptor_T( *this, lambda_ );
    }

////////////////////////////////////////////////////////////////////////////
// More ^= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:235
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
                primitive_id_unary_adaptor
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            *this,
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/binary_adaptor_assign_funcs.h:280
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
        xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_stack capacity
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
            primitive_id_unary_adaptor
        >
    >
    operator^= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_stack capacity
                xst_binary_adaptor< LhsT, RhsT, PolicyAdaptorT >::capacity_,
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

};  // xst_binary_adaptor

}   // namespace cttl_impl


#endif //_XST_BINARY_ADAPTOR_H_INCLUDED_
