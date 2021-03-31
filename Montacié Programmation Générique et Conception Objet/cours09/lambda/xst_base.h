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

/**@file xst_base.h
 * @brief Defines lambda expression base classes.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_base.h

#ifndef _XST_BASE_H_INCLUDED_
#define _XST_BASE_H_INCLUDED_

/**Helper macro for inline instantiation of cttl_impl::xst_const_scalar lambda primitive.*/
#define const_scalar( T ) cttl_impl::xst_lambda_wrap< cttl_impl::xst_const_scalar< T > >( cttl_impl::xst_const_scalar< T >() )

namespace cttl_impl {

// Note: assuming all assignment adaptors already forward declared earlier.

// forward declare subscript policy:
template< int RhsCapacityT, int LhsCapacityT, int PrimitiveIdT > struct xst_subscript_policy;

// forward declare constant scalar primitive required by stack interface:
template< int ValueT > struct xst_const_scalar;

/**@struct xst_lambda_wrap
 *@brief Wrapper class for C++ types implementing lambda primitive adaptors.
 *
 * @tparam LambdaT
 *        specifies type of lambda primitive.
 *
 */
template< typename LambdaT >
struct xst_lambda_wrap {

    // allow implementation of lambda compound to access implementation of any lambda primitive
    template< typename L, typename R > friend struct xst_pair;

    // allow translators to access implementation of any lambda primitive
    template< typename D, typename T > friend struct xst_translator;

    /**Defines C++ type of lambda primitive.*/
    typedef LambdaT lambda_T;

    /**Defines C++ type of object encapsulated by lambda primitive.*/
    typedef typename LambdaT::value_T value_T;

    /**Defines type of dereferenced object encapsulated by lambda primitive.*/
    typedef typename LambdaT::dereferenced_value_T dereferenced_value_T;

    /**Defines type of left primitive of lambda compound.*/
    typedef typename LambdaT::left_T left_T;

    /**Defines type of right primitive of lambda compound.*/
    typedef typename LambdaT::right_T right_T;

    /**Defines reference type for encapsulated lambda primitive.*/
    typedef xst_lambda_wrap< typename LambdaT::reference_T > reference_T;

    enum {
        /**Constant required to compile algorithms for subscript-based access to lambda compound.*/
        const_value_ = LambdaT::const_value_,

        /**Number of nodes at current level of subtree.*/
        depth_ = LambdaT::depth_,

        /**Cumulative capacity of lambda primitive.*/
        capacity_ = LambdaT::capacity_,

        /**Unique identifier of lambda primitive type for template resolution.*/
        primitive_id_ = LambdaT::primitive_id_
    };

    /**Default constructor.*/
    xst_lambda_wrap()
    :
    m_lambda( LambdaT() )
    {
    }

    /**Constructs lambda primitive from any type.*/
    template< typename GenericT >
    xst_lambda_wrap( GenericT const& x_ )
    :
    m_lambda( LambdaT( x_ ) )
    {
    }

    /**Constructs reference-based lambda primitive.*/
    template< typename GenericT >
    xst_lambda_wrap( GenericT* p_ )
    :
    m_lambda( LambdaT( *p_ ) )
    {
    }

    /**Copy constructor.*/
    xst_lambda_wrap( xst_lambda_wrap< LambdaT > const& other_ )
    : m_lambda( other_.m_lambda )
    {
    }

    /**Manufactures copy of reference object for encapsulated lambda primitive.*/
    reference_T make_reference() const
    {
        return reference_T( m_lambda.make_reference() );
    }

    /**Dereferenced value of the root lambda compound node.*/
    template< typename SubscriptLambdaT >
    dereferenced_value_T& dereferenced_value( xst_lambda_wrap< SubscriptLambdaT > subscript_ )
    {
        return m_lambda.dereferenced_value( subscript_ );
    }

    /**Dereferenced value of the root lambda compound node.*/
    dereferenced_value_T& dereferenced_value()
    {
        return dereferenced_value( const_scalar( 0 ) );
    }

    /**Direct mutable access to left-hand-side lambda compound nodes.*/
    left_T& left_lambda()
    {
        return m_lambda.left_lambda();
    }

    /**Direct constant access to left-hand-side lambda compound nodes.*/
    left_T const& left_lambda() const
    {
        return m_lambda.left_lambda();
    }

    /**Direct mutable access to right-hand-side lambda compound nodes.*/
    right_T& right_lambda()
    {
        return m_lambda.right_lambda();
    }

    /**Direct constant access to right-hand-side lambda compound nodes.*/
    right_T const& right_lambda() const
    {
        return m_lambda.right_lambda();
    }

    //////////////////////////////////////////////////////////////
    // lambda compound traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Lambda compound bottom up traversal algorithm with mutable access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ )
    {
        m_lambda.traverse_bottom_up( functor_ );
    }
    
    /**Lambda compound top-down traversal algorithm with mutable access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ )
    {
        m_lambda.traverse_top_down( functor_ );
    }
    
    /**Lambda compound bottom up traversal algorithm with constant access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ ) const
    {
        m_lambda.traverse_bottom_up( functor_ );
    }
    
    /**Lambda compound top-down traversal algorithm with constant access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ ) const
    {
        m_lambda.traverse_top_down( functor_ );
    }
    
    /**Lambda compound top-down subscript traversal algorithm.*/
    template< typename FunctorT >
    void subscript_top_down( FunctorT& functor_ ) const
    {
        m_lambda.subscript_top_down( functor_ );
    }

    /**Subscript bottom-up traversal algorithm.*/
    template< typename FunctorT >
    void subscript_bottom_up( FunctorT& functor_ ) const
    {
        m_lambda.subscript_bottom_up( functor_ );
    }

    //////////////////////////////////////////////////////////////
    // Lambda primitive stack interface support
    //////////////////////////////////////////////////////////////

    /**Push data at specified lambda compound location.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void push( xst_lambda_wrap< SubscriptLambdaT > subscript_, InputValueT const& data_ )
    {
        m_lambda.push( subscript_, data_ );
    }

    /**Push data into root lambda compound node.*/
    template< typename InputValueT >
    void push( InputValueT const& data_ )
    {
        push( const_scalar( 0 ), data_ );
    }

    /**Pop data from specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    void pop( xst_lambda_wrap< SubscriptLambdaT > subscript_ )
    {
        m_lambda.pop( subscript_ );
    }

    /**Pop data from root node of lambda compound.*/
    void pop()
    {
        pop( const_scalar( 0 ) );
    }

    /**Constant access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T const& top( xst_lambda_wrap< SubscriptLambdaT > subscript_ ) const
    {
        return m_lambda.top( subscript_ );
    }

    /**Constant access to root node of lambda compound.*/
    value_T const& top() const
    {
        return top( const_scalar( 0 ) );
    }

    /**Mutable access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T& top( xst_lambda_wrap< SubscriptLambdaT > subscript_ )
    {
        return m_lambda.top( subscript_ );
    }

    /**Mutable access to root node of lambda compound.*/
    value_T& top()
    {
        return top( const_scalar( 0 ) );
    }

    /**Get size of stack at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    size_t size( xst_lambda_wrap< SubscriptLambdaT > subscript_ ) const
    {
        return m_lambda.size( subscript_ );
    }

    /**Get stack size of root node of lambda compound.*/
    size_t size() const
    {
        return size( const_scalar( 0 ) );
    }

    /**Get stack pointer at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T >* stack_ptr( SubscriptLambdaT subscript_ )
    {
        return m_lambda.stack_ptr( subscript_ );
    }

    /**Get constant stack pointer at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T > const* stack_ptr( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.stack_ptr( subscript_ );
    }

    /**Update data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    void update( SubscriptLambdaT program_ )
    {
        m_lambda.update( program_ );
    }

    /**Update data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    inline
    xtl_wrap<
        xst_deposit_adaptor<
            xst_lambda_wrap< LambdaT >,
            xst_lambda_wrap< SubscriptLambdaT >
        >
    >
    deposit( xst_lambda_wrap< SubscriptLambdaT > program_ )
    {
        typedef
            xst_deposit_adaptor<
                xst_lambda_wrap< LambdaT >,
                xst_lambda_wrap< SubscriptLambdaT >
        > xst_deposit_adaptor_T;

        return xtl_wrap< xst_deposit_adaptor_T >( xst_deposit_adaptor_T( *this, program_ ) );
    }

#ifdef CTTL_LAMBDA_REFLECTION
    /**Defines lambda reflection type for this lambda compound.*/
    typedef xst_lambda_wrap< typename LambdaT::reflection_T > reflection_T;

    /**Returns lambda reflection for this lambda compound.*/
    reflection_T reflection() const
    {
        return reflection_T( m_lambda.reflection() );
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Stores encapsulated lambda primitive.*/
    LambdaT m_lambda;

    /**Internal algorithm to deposit data at specified location.
    *
    * @tparam LocationT
    *        specifies lambda compound location: 0, 1, 2, 3, etc.
    *
    * @tparam InputValueT
    *        specifies data type.
    *
    * @param data_
    *        reference to the data.
    *
    */
    template< int LocationT, typename InputValueT >
    void xpush_at_location( InputValueT const& data_ )
    {
        m_lambda.xpush_at_location< LocationT >( data_ );
    }

    /**Internal algorithm to pop data at specified location.
    *
    * @tparam LocationT
    *       specifies location at the
    *       current level of lambda compound.
    *
    */
    template< int LocationT >
    void xpop_at_location()
    {
        m_lambda.xpop_at_location< LocationT >();
    }

    /**Internal algorithm for constant access to data at specified lambda compound location.
    *
    * @tparam LocationT
    *       specifies location at the
    *       current level of encapsulated lambda primitive.
    *
    */
    template< int LocationT >
    value_T const& xtop_at_location() const
    {
        return m_lambda.xtop_at_location< LocationT >();
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename InputValueT >
    void xpush_descend( InputValueT const& data_ )
    {
        m_lambda.xpush_descend< LocationT >( data_ );
    }

    /**Internal algorithm to pop data from stack at specified location.*/
    template< int LocationT >
    void xpop_descend()
    {
        m_lambda.xpop_descend< LocationT >();
    }


    /**Internal algorithm to access data at specified lambda compound location.*/
    template< int LocationT >
    value_T const& xtop_descend() const
    {
        return m_lambda.xtop_descend< LocationT >();
    }

    //////////////////////////////////////////////////////////////
    // subscript traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_top_down_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_top_down_subtree_switch( subscript_, functor_ );
    }

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< int LocationT, typename FunctorT >
    void xsubscript_top_down_descend( FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_top_down_descend< LocationT >( functor_ );
    }

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_top_down_subtree_descend( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_top_down_subtree_descend< LocationT >( subscript_, functor_ );
    }

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_bottom_up_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_bottom_up_subtree_switch( subscript_, functor_ );
    }

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< int LocationT, typename FunctorT >
    void xsubscript_bottom_up_descend( FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_bottom_up_descend< LocationT >( functor_ );
    }

    /**Internal algorithm to traverse encapsulated lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_bottom_up_subtree_descend( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        m_lambda.xsubscript_bottom_up_subtree_descend< LocationT >( subscript_, functor_ );
    }


    //////////////////////////////////////////////////////////////
    // Lambda primitive stack interface support
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to push data into lambda compound node.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_split( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        m_lambda.xpush_sub_split( subscript_, data_ );
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_descend( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        m_lambda.xpush_sub_descend< LocationT >( subscript_, data_ );
    }

    /**Internal algorithm to pop data at specified location.*/
    template< typename SubscriptLambdaT >
    void xpop_sub_split( SubscriptLambdaT subscript_ )
    {
        m_lambda.xpop_sub_split( subscript_ );
    }

    /**Internal algorithm to pop data at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    void xpop_sub_descend( SubscriptLambdaT subscript_ )
    {
        m_lambda.xpop_sub_descend< LocationT >( subscript_ );
    }

    /**Internal access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T const& xtop_sub_split( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xtop_sub_split( subscript_ );
    }

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T const& xtop_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xtop_sub_descend< LocationT >( subscript_ );
    }


    /////////////////////////////////////////////////////////////////////
    // mutable data access
    /////////////////////////////////////////////////////////////////////

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T& xtop_at_location()
    {
        return m_lambda.xtop_at_location< LocationT >();
    }

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T& xtop_descend()
    {
        return m_lambda.xtop_descend< LocationT >();
    }

    /**Internal access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T& xtop_sub_split( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xtop_sub_split( subscript_ );
    }

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T& xtop_sub_descend( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xtop_sub_descend< LocationT >( subscript_ );
    }


    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT >
    size_t xsize_at_location() const
    {
        return m_lambda.xsize_at_location< LocationT >();
    }

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT >
    size_t xsize_descend() const
    {
        return m_lambda.xsize_descend< LocationT >();
    }

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    size_t xsize_sub_split( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xsize_sub_split( subscript_ );
    }

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    size_t xsize_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xsize_sub_descend< LocationT >( subscript_ );
    }


    /////////////////////////////////////////////////////////////////////
    // functions to support mutable access to the location stack
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_at_location()
    {
        return m_lambda.xstack_ptr_at_location< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_descend()
    {
        return m_lambda.xstack_ptr_descend< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_split( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xstack_ptr_sub_split( subscript_ );
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xstack_ptr_sub_descend< LocationT >( subscript_ );
    }


    /////////////////////////////////////////////////////////////////////
    // functions to support constant access to the location stack
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_at_location() const
    {
        return m_lambda.xstack_ptr_at_location< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_descend() const
    {
        return m_lambda.xstack_ptr_descend< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_split( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xstack_ptr_sub_split( subscript_ );
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xstack_ptr_sub_descend< LocationT >( subscript_ );
    }

public:
////////////////////////////////////////////////////////////////////////
// Overloaded operators
////////////////////////////////////////////////////////////////////////

// Do not modify section of code delimited by comments contaning
// begin_generated_code/end_generated_code labels. This section of code is
// maintained by gumus scripts.

//begin_generated_code
// generated by bin/gmu/gmu_lambda/gmu_common.h:529
// on Sun Aug 16 21:52:48 2009.
// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment = operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment = abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment = specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More = assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment = operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment *= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment *= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment *= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda multiplication assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_multiplication_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_multiplication_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda multiplication assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_multiplication_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_multiplication_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda multiplication assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_multiplication_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_multiplication_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_multiplication_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More *= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_multiplication_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_multiplication_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_multiplication_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator*= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_multiplication_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment *= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment /= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment /= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment /= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda division assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_division_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_division_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda division assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_division_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_division_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda division assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_division_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_division_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_division_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More /= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_division_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_division_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_division_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator/= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_division_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment /= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment %= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment %= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment %= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda modulus assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_modulus_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_modulus_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda modulus assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_modulus_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_modulus_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda modulus assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_modulus_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_modulus_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_modulus_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More %= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_modulus_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_modulus_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_modulus_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator%= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_modulus_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment %= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment += operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment += abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment += specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda addition assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_addition_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_addition_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda addition assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_addition_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_addition_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda addition assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_addition_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_addition_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_addition_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More += assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_addition_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_addition_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_addition_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator+= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_addition_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment += operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment -= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment -= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment -= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda subtraction assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_subtraction_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_subtraction_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda subtraction assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_subtraction_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_subtraction_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda subtraction assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subtraction_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_subtraction_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_subtraction_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More -= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_subtraction_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_subtraction_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_subtraction_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator-= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_subtraction_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment -= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment <<= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment <<= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment <<= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda left shift assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_left_shift_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_left_shift_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda left shift assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_left_shift_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_left_shift_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda left shift assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_left_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_left_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_left_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More <<= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_left_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_left_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_left_shift_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator<<= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_left_shift_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment <<= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment >>= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment >>= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment >>= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda right shift assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_right_shift_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_right_shift_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda right shift assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_right_shift_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_right_shift_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda right shift assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_right_shift_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_right_shift_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_right_shift_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More >>= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_right_shift_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_right_shift_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_right_shift_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator>>= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_right_shift_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment >>= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment &= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment &= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment &= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda bitwise and assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_bitwise_and_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_bitwise_and_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda bitwise and assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_and_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_and_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda bitwise and assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_and_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_bitwise_and_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_bitwise_and_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More &= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_and_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator&= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_and_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment &= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment |= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment |= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment |= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_bitwise_ior_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_bitwise_ior_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda bitwise inclusive or assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_ior_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_ior_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda bitwise inclusive or assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_ior_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_bitwise_ior_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_bitwise_ior_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More |= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_ior_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator|= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_ior_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment |= operators end
////////////////////////////////////////////////////////////////////////////

// generated by bin/gmu/gmu_lambda/gmu_common.h:157
////////////////////////////////////////////////////////////////////////////
// Assignment ^= operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Assignment ^= abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:8
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( RhsValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:51
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< RhsValueT& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( RhsValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< RhsValueT& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< RhsValueT& > >( pvalue_ )
            );
    }


////////////////////////////////////////////////////////////////////////////
// Assignment ^= specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:98

    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam OtherLambdaT
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
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_bitwise_xor_assignment_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_bitwise_xor_assignment_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:139
    /**Lambda bitwise exclusive or assignment operator support.
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
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_bitwise_xor_assignment_policy<
            LambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( xst_lambda_wrap< LambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_bitwise_xor_assignment_policy<
                LambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:175
    /**Lambda bitwise exclusive or assignment operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression encapsulated by cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:220
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
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression policy instance.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_bitwise_xor_assignment_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_bitwise_xor_assignment_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_bitwise_xor_assignment_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }

////////////////////////////////////////////////////////////////////////////
// More ^= assignment abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:272
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/assign/assign_funcs.h:317
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
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_bitwise_xor_assignment_policy<
            1, // xst_stack capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator^= ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_bitwise_xor_assignment_policy<
                1, // xst_stack capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Assignment ^= operators end
////////////////////////////////////////////////////////////////////////////


// generated by bin/gmu/gmu_lambda/gmu_common.h:607
// on Sun Aug 16 21:52:48 2009.
// generated by bin/gmu/gmu_lambda/gmu_common.h:167
////////////////////////////////////////////////////////////////////////////
// Subscript [] operators begin
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Subscript abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:8
    /**Lambda subscript operator support.
    *
    * @tparam SubscriptValueT
    *        specifies type of subscript.
    *
    * @param value_
    *        reference to subscript value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename SubscriptValueT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< SubscriptValueT > >,
        xst_subscript_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( SubscriptValueT const& value_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< SubscriptValueT > >,
            xst_subscript_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< SubscriptValueT > >( value_ )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:51
    /**Lambda subscript operator support.
    *
    * @tparam SubscriptValueT
    *        specifies type of subscript.
    *
    * @param pvalue_
    *        pointer to subscript value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename SubscriptValueT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< SubscriptValueT& > >,
        xst_subscript_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( SubscriptValueT* pvalue_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< SubscriptValueT& > >,
            xst_subscript_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< SubscriptValueT& > >( pvalue_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Subscript [] specializations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:97

    /**Lambda subscript operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of subscript.
    *
    * @param lambda_
    *        subscript lambda operand.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename OtherLambdaT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< typename OtherLambdaT::reference_T >,
        xst_subscript_policy<
            OtherLambdaT::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( xst_lambda_wrap< OtherLambdaT > const& lambda_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< typename OtherLambdaT::reference_T >,
            xst_subscript_policy<
                OtherLambdaT::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), lambda_.make_reference() );
    }

// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:138
    /**Lambda subscript operator support.
    *
    * @tparam OtherLambdaT
    *        specifies type of
    *        lambda expression cttl_impl::xst_unary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_unary_adaptor.
    *
    * @param unary_adaptor_
    *        reference to lambda expression representing subscript.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename OtherLambdaT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
        xst_subscript_policy<
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT > const& unary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >,
            xst_subscript_policy<
                xst_unary_adaptor< OtherLambdaT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), unary_adaptor_ );
    }

// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:183
    /**Lambda subscript operator support.
    *
    * @tparam LambdaLhsT
    *        specifies type of
    *        left lambda expression inside cttl_impl::xst_binary_adaptor.
    *
    * @tparam LambdaRhsT
    *        specifies type of
    *        right lambda expression inside cttl_impl::xst_binary_adaptor.
    *
    * @tparam PolicyAdaptorT
    *        specifies policy type of
    *        cttl_impl::xst_binary_adaptor.
    *
    * @param binary_adaptor_
    *        reference to lambda expression representing subscript.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename LambdaLhsT, typename LambdaRhsT, typename PolicyAdaptorT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
        xst_subscript_policy<
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT > const& binary_adaptor_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >,
            xst_subscript_policy<
                xst_binary_adaptor< LambdaLhsT, LambdaRhsT, PolicyAdaptorT >::capacity_,
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T( make_reference(), binary_adaptor_ );
    }


////////////////////////////////////////////////////////////////////////////
// More subscript abbreviations
////////////////////////////////////////////////////////////////////////////
// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:236
    /**Lambda subscript operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param stack_
    *        reference to stack.
    *
    * @pre
    *        value on top of the stack will be used as subscript value.
    *        Therefore, stack must not be empty.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_scalar< StackValueT > >,
        xst_subscript_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( std::stack< StackValueT > const& stack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_scalar< StackValueT > >,
            xst_subscript_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        assert( !stack_.empty() );  // have you forgot to pass stack by address, instead of passing it by value?
        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_scalar< StackValueT > >( stack_.top() )
            );
    }

// generated by bin\gmu\gmu_lambda\operators/subscript/subscript_funcs.h:285
    /**Lambda subscript operator support.
    *
    * @tparam StackValueT
    *        specifies value type of
    *        <a href="http://www.sgi.com/tech/stl/stack.html">stack</a>.
    *
    * @param pstack_
    *        pointer to stack.
    *
    * @remarks
    *        At run time, value on top of the stack is used as subscript value.
    *
    * @return
    *        Instance of lambda expression policy
    *        cttl_impl::xst_binary_adaptor, parameterized by
    *        cttl_impl::xst_subscript_policy operator policy.
    *
    */
    template< typename StackValueT >
    xst_binary_adaptor<
        xst_lambda_wrap< typename LambdaT::reference_T >,
        xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
        xst_subscript_policy<
            1, // xst_scalar capacity
            LambdaT::capacity_,
            LambdaT::primitive_id_
        >
    >
    operator[] ( std::stack< StackValueT >* pstack_ )
    {
        typedef xst_binary_adaptor<
            xst_lambda_wrap< typename LambdaT::reference_T >,
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >,
            xst_subscript_policy<
                1, // xst_scalar capacity
                LambdaT::capacity_,
                LambdaT::primitive_id_
            >
        > xst_adaptor_T;

        return xst_adaptor_T(
            make_reference(),
            xst_lambda_wrap< xst_stack< std::stack< StackValueT >& > >( pstack_ )
            );
    }

////////////////////////////////////////////////////////////////////////////
// Subscript [] operators end
////////////////////////////////////////////////////////////////////////////

//end_generated_code


};  // xst_lambda_wrap


}   // namespace cttl_impl


#endif //_XST_BASE_H_INCLUDED_
