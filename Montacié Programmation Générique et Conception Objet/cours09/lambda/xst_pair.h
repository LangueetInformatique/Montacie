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

/**@file xst_pair.h
 * @brief Defines binary connector class for lambda compound.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_pair.h

#ifndef _XST_PAIR_H_INCLUDED_
#define _XST_PAIR_H_INCLUDED_

namespace cttl_impl {


/**@struct xst_pair
 * @brief Implements binary connector for lambda compounds.
 *
 * @tparam LhsT
 *        specifies type of
 *        left subtree of lambda compound.
 *
 * @tparam RhsT
 *        specifies type of
 *        right subtree of lambda compound.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */
template< typename LhsT, typename RhsT >
struct xst_pair : public xtl_op_base_binary< LhsT, RhsT > {

    // allow any lambda primitive to access lambda compound implementation
    template< typename D > friend struct xst_lambda_wrap;

    // allow any lambda compound to access any lambda compound implementation
    template< typename L, typename R > friend struct xst_pair;

    // allow translators to access any lambda compound implementation
    template< typename D, typename T > friend struct xst_translator;

    enum {
        /**Constant value required to compile algorithms relying on subscript-type access.*/
        const_value_ = LhsT::const_value_,

        /**Subtree node count constant.*/
        depth_ = LhsT::depth_ + 1,

        /**Cumulative capacity of lambda compound.*/
        capacity_ = LhsT::capacity_ + RhsT::capacity_,

        /**Unique identifier of lambda primitive, taken from root element.*/
        primitive_id_ = LhsT::primitive_id_
    };

    /**Defines type of primitive encapsulated by lambda compound nodes.*/
    typedef typename LhsT::value_T value_T;

    /**Defines type of dereferenced primitive encapsulated by lambda compound nodes.*/
    typedef typename LhsT::dereferenced_value_T dereferenced_value_T;

    /**Defines type of left subtree of lambda compound.*/
    typedef LhsT left_T;

    /**Defines type of right subtree of lambda compound.*/
    typedef RhsT right_T;

    /**Defines reference type for this lambda compound.*/
    typedef xst_pair< LhsT, RhsT > reference_T;

    /**Object constructor.*/
    xst_pair( LhsT const& lhs_expr_, RhsT const& rhs_expr_ )
    : xtl_op_base_binary< LhsT, RhsT >( lhs_expr_, rhs_expr_ )
    {
    }

    /**Default constructor.*/
    xst_pair()
    : xtl_op_base_binary< LhsT, RhsT >( LhsT(), RhsT() )
    {
    }

    /**Copy constructor.*/
    xst_pair( xst_pair< LhsT, RhsT > const& other_ )
    : xtl_op_base_binary< LhsT, RhsT >( other_.m_expr_lhs, other_.m_expr_rhs )
    {
    }

    /**Manufactures copy of lambda compound.*/
    reference_T make_reference() const
    {
        return *this;
    }
    
    /**Dereferenced value of the root lambda compound node.*/
    template< typename SubscriptLambdaT >
    dereferenced_value_T& dereferenced_value( xst_lambda_wrap< SubscriptLambdaT > subscript_ )
    {
        // When lambda compound is dereferenced, its
        // root element is dereferenced:
        return this->m_expr_lhs.dereferenced_value( subscript_ );
    }

    /**Direct mutable access to left-hand-side subtree of lambda compound.*/
    left_T& left_lambda()
    {
        return this->m_expr_lhs;
    }

    /**Direct constant access to left-hand-side subtree of lambda compound.*/
    left_T const& left_lambda() const
    {
        return this->m_expr_lhs;
    }
    
    /**Direct mutable access to right-hand-side subtree of lambda compound.*/
    right_T& right_lambda()
    {
        return this->m_expr_rhs;
    }

    /**Direct constant access to right-hand-side subtree of lambda compound.*/
    right_T const& right_lambda() const
    {
        return this->m_expr_rhs;
    }

    //////////////////////////////////////////////////////////////
    // lambda compound traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Algorithm for bottom-up traversal of lambda compound nodes with mutable access.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ )
    {
        this->m_expr_rhs.traverse_bottom_up( functor_ );
        this->m_expr_lhs.traverse_bottom_up( functor_ );
    }
    
    /**Algorithm for top-down traversal of lambda compound nodes with mutable access.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ )
    {
        this->m_expr_lhs.traverse_top_down( functor_ );
        this->m_expr_rhs.traverse_top_down( functor_ );
    }
    
    /**Algorithm for bottom-up traversal of lambda compound nodes with constant access.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ ) const
    {
        this->m_expr_rhs.traverse_bottom_up( functor_ );
        this->m_expr_lhs.traverse_bottom_up( functor_ );
    }
    
    /**Algorithm for top-down traversal of lambda compound nodes with constant access.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ ) const
    {
        this->m_expr_lhs.traverse_top_down( functor_ );
        this->m_expr_rhs.traverse_top_down( functor_ );
    }
    
    /**Algorithm for top-down traversal of subscript compounds.*/
    template< typename FunctorT >
    void subscript_top_down( FunctorT& functor_ ) const
    {
        // Switch to internal version of subscript_top_down using locations
        // Here, the smallest depth_ value is 2.
        // To descend all the way into leftmost terminal node, use depth_ - 1
        // To descend all the way into leftmost non-terminal node, use depth_ - 2

        // Switch to descent version of subscript_top_down
        xsubscript_top_down_descend< depth_ - 2 >( functor_ );
    }

    /**Algorithm for bottom-up traversal of subscript compounds.*/
    template< typename FunctorT >
    void subscript_bottom_up( FunctorT& functor_ ) const
    {
        // switch to descent version of subscript_bottom_up using locations
        xsubscript_bottom_up_descend< depth_ - 2 >( functor_ );
    }

    //////////////////////////////////////////////////////////////
    // Subscript-based stack interface
    //////////////////////////////////////////////////////////////

    /**Deposit data at specified lambda compound location.
    *
    * @tparam LocationT
    *        specifies data location: 0, 1, 2, 3, etc.
    *
    * @tparam InputValueT
    *        specifies type of data.
    *
    * @param data_
    *        reference to the data.
    *
    */
    template<
        int LocationT,
        typename InputValueT
    >
    void
    push(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        InputValueT const& data_
        )
    {
        xpush_descend< depth_ - LocationT - 1 >( data_ );
    }

    /**Internal algorithm to deposit data into lambda compound node.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename InputValueT
    >
    void
    push(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_,
        InputValueT const& data_
        )
    {
        xpush_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >(),
            data_
            );
    }

    /**Pop data at specified lambda compound location.*/
    template<
        int LocationT
    >
    void
    pop(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        
    {
        xpop_descend< depth_ - LocationT - 1 >();
    }

    /**Pop data at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    void
    pop(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
        
    {
        xpop_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Constant access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T const& top( xst_lambda_wrap< xst_const_scalar< LocationT > > ) const
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    /**Constant access to data at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    value_T const& top(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
         const
    {
        return xtop_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Mutable access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T& top( xst_lambda_wrap< xst_const_scalar< LocationT > > )
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    /**Mutable access to data at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    value_T& top(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
        
    {
        return xtop_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Get size of stack at specified lambda compound location.*/
    template<
        int LocationT
    >
    size_t
    size(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
         const
    {
        return xsize_descend< depth_ - LocationT - 1 >();
    }

    /**Get size of stack at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    size_t
    size(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
         const
    {
        return xsize_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Get stack pointer at specified lambda compound location.*/
    template<
        int LocationT
    >
    std::stack< value_T >*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        
    {
        return xstack_ptr_descend< depth_ - LocationT - 1 >();
    }

    /**Get stack pointer at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    std::stack< value_T >*
    stack_ptr(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
        
    {
        return xstack_ptr_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Get constant stack pointer at specified lambda compound location.*/
    template<
        int LocationT
    >
    std::stack< value_T > const*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
         const
    {
        return xstack_ptr_descend< depth_ - LocationT - 1 >();
    }

    /**Get constant stack pointer at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    std::stack< value_T > const*
    stack_ptr(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > subscript_
        )
         const
    {
        return xstack_ptr_sub_rotate(
            subscript_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


    /**Update data at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT
    >
    void
    update(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > program_
        )
        
    {
        xupdate_sub_rotate(
            program_.left_lambda(),
            xst_const_scalar< LocationT >()
            );
    }


#ifdef CTTL_LAMBDA_REFLECTION
    /**Left subtree reflection type.*/
    typedef typename LhsT::reflection_T lhs_reflection_T;

    /**Right subtree reflection type.*/
    typedef typename RhsT::reflection_T rhs_reflection_T;

    /**Lambda compound reflection type.*/
    typedef xst_pair< rhs_reflection_T, lhs_reflection_T > reflection_T;

    /**Construct and return reflection object for this lambda compound.*/
    reflection_T reflection() const
    {
        return reflection_T( this->m_expr_rhs.reflection(), this->m_expr_lhs.reflection() );
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Internal algorithm to push data.*/
    template< int LocationT, typename InputValueT >
    void xpush_at_location( InputValueT const& data_ )
    {
        xpush_descend< depth_ - LocationT - 1 >( data_ );
    }

    /**Internal algorithm to pop data from stack at specified location.*/
    template< int LocationT >
    void xpop_at_location()
    {
        xpop_descend< depth_ - LocationT - 1 >();
    }

    /**Internal algorithm to access data at specified lambda compound location.*/
    template< int LocationT >
    value_T const& xtop_at_location() const
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    ///////////////////////////////////////////////////////
    // private element accessor functions
    ///////////////////////////////////////////////////////
    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename InputValueT >
    void xpush_descend( InputValueT const& data_ )
    {
        if ( LocationT )
            this->m_expr_lhs.xpush_descend< LocationT - 1 >( data_ );
        else
            this->m_expr_rhs.xpush_at_location< LocationT >( data_ );
    }

    /**Internal algorithm to pop data from stack at specified location.*/
    template< int LocationT >
    void xpop_descend()
    {
        if ( LocationT )
            this->m_expr_lhs.xpop_descend< LocationT - 1 >();
        else
            this->m_expr_rhs.xpop_at_location< LocationT >();
    }

    /**Internal algorithm to access data at specified lambda compound location.*/
    template< int LocationT >
    value_T const& xtop_descend() const
    {
        if ( LocationT )
            return this->m_expr_lhs.xtop_descend< LocationT - 1 >();

        return this->m_expr_rhs.xtop_at_location< LocationT >();
    }

    //////////////////////////////////////////////////////////////
    // subscript traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse subscript compounds.*/
    template< int LocationT, typename FunctorT >
    void xsubscript_top_down_descend( FunctorT& functor_ ) const
    {
        if ( LocationT ) {
            // continue descend to lowest non-terminal node:
            this->m_expr_lhs.xsubscript_top_down_descend< LocationT - 1>( functor_ );
            // on ascend, traverse right-hand-side subtree:
            this->m_expr_rhs.xsubscript_top_down_subtree_switch( const_scalar( LocationT + 1 ), functor_ );
            return;
        }

        // traverse leftmost terminal node first, then leftmost subtree:
        this->m_expr_lhs.xsubscript_top_down_subtree_switch( const_scalar( LocationT ), functor_ );
        this->m_expr_rhs.xsubscript_top_down_subtree_switch( const_scalar( LocationT + 1 ), functor_ );
    }

    /**Internal algorithm to traverse subscript compounds.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_top_down_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        // Switch to internal version of subscript_top_down using locations
        // Here, the smallest depth_ value is 2.
        // To descend all the way into leftmost terminal node, use depth_ - 1
        // To descend all the way into leftmost non-terminal node, use depth_ - 2

        // switch to descent version of subscript_top_down
        xsubscript_top_down_subtree_descend< depth_ - 2 >( subscript_, functor_ );
    }

    /**Internal algorithm to traverse subscript compounds.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_top_down_subtree_descend( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        typedef
            xst_pair<
                SubscriptLambdaT,
                const_scalar_type( LocationT )
            >
        lhs_pair_T;
        typedef xst_lambda_wrap< lhs_pair_T > lhs_subscript_lambda_T;

        typedef
            xst_pair<
                SubscriptLambdaT,
                const_scalar_type( LocationT + 1 )
            >
        rhs_pair_T;
        typedef xst_lambda_wrap< rhs_pair_T > rhs_subscript_lambda_T;

        if ( LocationT ) {
            // continue descend to lowest non-terminal node:
            this->m_expr_lhs.xsubscript_top_down_subtree_descend< LocationT - 1 >( subscript_, functor_ );
            // on ascend, traverse the right-hand-side subtree:
            this->m_expr_rhs.xsubscript_top_down_subtree_switch( rhs_subscript_lambda_T( rhs_pair_T( subscript_, const_scalar( LocationT + 1 ) ) ), functor_ );
            return;
        }

        // traverse leftmost terminal node, then leftmost subtree:
        this->m_expr_lhs.xsubscript_top_down_subtree_switch( lhs_subscript_lambda_T( lhs_pair_T( subscript_, const_scalar( LocationT ) ) ), functor_ );
        this->m_expr_rhs.xsubscript_top_down_subtree_switch( rhs_subscript_lambda_T( rhs_pair_T( subscript_, const_scalar( LocationT + 1 ) ) ), functor_ );
    }

    /**Internal algorithm to traverse subscript compounds.*/
    template< int LocationT, typename FunctorT >
    void xsubscript_bottom_up_descend( FunctorT& functor_ ) const
    {
        if ( LocationT ) {
            // continue descend to lowest non-terminal node:
            // on descend, traverse right-hand-side subtree first:
            this->m_expr_rhs.xsubscript_bottom_up_subtree_switch( const_scalar( LocationT + 1 ), functor_ );
            this->m_expr_lhs.xsubscript_bottom_up_descend< LocationT - 1>( functor_ );
            return;
        }

        // traverse rightmost subtree, then leftmost terminal node:
        this->m_expr_rhs.xsubscript_bottom_up_subtree_switch( const_scalar( LocationT + 1 ), functor_ );
        this->m_expr_lhs.xsubscript_bottom_up_subtree_switch( const_scalar( LocationT ), functor_ );
    }

    /**Internal algorithm to traverse subscript compounds.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_bottom_up_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        // switch to descent version of subscript_bottom_up using locations
        xsubscript_bottom_up_subtree_descend< depth_ - 2 >( subscript_, functor_ );
    }

    /**Internal algorithm to traverse subscript compounds.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    void xsubscript_bottom_up_subtree_descend( SubscriptLambdaT subscript_, FunctorT& functor_ ) const
    {
        typedef
            xst_pair<
                SubscriptLambdaT,
                const_scalar_type( LocationT )
            >
        lhs_pair_T;
        typedef xst_lambda_wrap< lhs_pair_T > lhs_subscript_lambda_T;

        typedef
            xst_pair<
                SubscriptLambdaT,
                const_scalar_type( LocationT + 1 )
            >
        rhs_pair_T;
        typedef xst_lambda_wrap< rhs_pair_T > rhs_subscript_lambda_T;

        if ( LocationT ) {
            // continue descend to lowest non-terminal node:
            // on descend, traverse right-hand-side subtree first:
            this->m_expr_rhs.xsubscript_bottom_up_subtree_switch( rhs_subscript_lambda_T( rhs_pair_T( subscript_, const_scalar( LocationT + 1 ) ) ), functor_ );
            this->m_expr_lhs.xsubscript_bottom_up_subtree_descend< LocationT - 1 >( subscript_, functor_ );
            return;
        }

        // traverse leftmost subtree first, then leftmost terminal node:
        this->m_expr_rhs.xsubscript_bottom_up_subtree_switch( rhs_subscript_lambda_T( rhs_pair_T( subscript_, const_scalar( LocationT + 1 ) ) ), functor_ );
        this->m_expr_lhs.xsubscript_bottom_up_subtree_switch( lhs_subscript_lambda_T( lhs_pair_T( subscript_, const_scalar( LocationT ) ) ), functor_ );
    }


    /**Internal algorithm (final rotation) to deposit data into lambda compound node.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT,
        typename InputValueT
    >
    void
    xpush_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_,
        InputValueT const& data_
        )
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        xpush_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                ),
            data_
            );
    }

    /**Internal algorithm (internal rotation) to deposit data into lambda compound node.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT,
        typename InputValueT
    >
    void
    xpush_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_,
        InputValueT const& data_
        )
    {
        // Rotation works like a cork scrue:
        // Expression A^B^C^D could be written as
        //  ((A^B)^C)^D
        //
        // Internal binary tree representation of this expression is
        //
        //  ^-D
        //  |
        //  ^-C
        //  |
        //  ^-B
        //  |
        //  A
        //  
        // Rotation steps in this example are:
        //  LHS         RHS
        //  ----------- --------
        //  ((A^B)^C)   D       RHS^LHS.rhs <-- internal rotation
        //  (A^B)       D^C     RHS^LHS.rhs <-- internal rotation
        //  A           (D^C)^B RHS^LHS     <-- final rotation
        //  ((D^C)^B)^A                     <-- result
        //  
        //  ^-A
        //  |
        //  ^-B
        //  |
        //  ^-C
        //  |
        //  D


        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        xpush_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                ),
            data_
            );
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_split( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        // rotated subscript_ contains binary tree of constant scalar objects:
        //
        //  /\    ; SubscriptLambdaT::right_T::depth_ == 2  SubscriptLambdaT::left_T::const_value_ == 3
        // 3 /\   ; SubscriptLambdaT::right_T::depth_ == 2  SubscriptLambdaT::left_T::const_value_ == 2
        //  2 /\  ; SubscriptLambdaT::right_T::depth_ == 1  SubscriptLambdaT::left_T::const_value_ == 1  SubscriptLambdaT::right_T::const_value_ == 0, but not used.
        //   1  0 ; SubscriptLambdaT::depth_ == 1 ( all of the above have SubscriptLambdaT::depth_ == 2 ).
        //

        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend-push to find the requested terminal:
            xpush_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( data_ );

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            xpush_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda(), data_ );
        }
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_descend( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            this->m_expr_lhs.xpush_sub_descend< LocationT - 1 >( subscript_, data_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            this->m_expr_rhs.xpush_sub_split( subscript_, data_ );
        }
    }

    /**Internal algorithm (final rotation) to pop data at specified location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    void
    xpop_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        xpop_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (internal rotation) to pop data at specified location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    void
    xpop_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        xpop_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to pop data at specified location.*/
    template< typename SubscriptLambdaT >
    void xpop_sub_split( SubscriptLambdaT subscript_ )
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend-pop to find the requested terminal:
            xpop_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            xpop_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal algorithm to pop data from stack at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    void xpop_sub_descend( SubscriptLambdaT subscript_ )
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            this->m_expr_lhs.xpop_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            this->m_expr_rhs.xpop_sub_split( subscript_ );
        }
    }

    /**Internal algorithm (rotation) to access data at specified lambda compound location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    value_T const& xtop_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        return xtop_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (rotation) to access data at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    value_T const& xtop_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        return xtop_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T const& xtop_sub_split( SubscriptLambdaT subscript_ ) const
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to descend algorithm to locate requested terminal:
            return xtop_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            return xtop_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T const& xtop_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            return this->m_expr_lhs.xtop_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            return this->m_expr_rhs.xtop_sub_split( subscript_ );
        }
    }


    /////////////////////////////////////////////////////////////////////
    // mutable data access
    /////////////////////////////////////////////////////////////////////

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T& xtop_at_location()
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    /**Internal access to data at specified lambda compound location.*/
    template< int LocationT >
    value_T& xtop_descend()
    {
        if ( LocationT )
            return this->m_expr_lhs.xtop_descend< LocationT - 1 >();
        else
            return this->m_expr_rhs.xtop_at_location< LocationT >();
    }

    //////////////////////////////////////////////////////////////
    // Subscript-based access to lambda compound
    //////////////////////////////////////////////////////////////

    /**Internal algorithm (final rotation) to access data at specified location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    value_T& xtop_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        return xtop_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (rotation) to access data at specified location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    value_T& xtop_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        return xtop_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to access data at specified location.*/
    template< typename SubscriptLambdaT >
    value_T& xtop_sub_split( SubscriptLambdaT subscript_ )
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend algorithm to locate requested terminal:
            return xtop_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            return xtop_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal algorithm to access data at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T& xtop_sub_descend( SubscriptLambdaT subscript_ )
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            return this->m_expr_lhs.xtop_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            return this->m_expr_rhs.xtop_sub_split( subscript_ );
        }
    }


    /////////////////////////////////////////////////////////////////////
    // Stack size of lambda compound locations
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT >
    size_t xsize_at_location() const
    {
        return xsize_descend< depth_ - LocationT - 1 >();
    }

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT >
    size_t xsize_descend() const
    {
        if ( LocationT )
            return this->m_expr_lhs.xsize_descend< LocationT - 1 >();
        else
            return this->m_expr_rhs.xsize_at_location< LocationT >();
    }

    /**Internal algorithm (final rotation) to get stack size at specified lambda compound location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    size_t
    xsize_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        return xsize_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (rotation) to get stack size at specified lambda compound location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    size_t
    xsize_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        return xsize_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    size_t xsize_sub_split( SubscriptLambdaT subscript_ ) const
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend-size to find the requested terminal:
            return xsize_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            return xsize_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal algorithm to get stack size at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    size_t xsize_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            return this->m_expr_lhs.xsize_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            return this->m_expr_rhs.xsize_sub_split( subscript_ );
        }
    }


    /////////////////////////////////////////////////////////////////////
    // Direct mutable access to stack locations via stack pointer
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_at_location()
    {
        return xstack_ptr_descend< depth_ - LocationT - 1 >();
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_descend()
    {
        if ( LocationT )
            return this->m_expr_lhs.xstack_ptr_descend< LocationT - 1 >();
        else
            return this->m_expr_rhs.xstack_ptr_at_location< LocationT >();
    }


    /**Internal algorithm (final rotation) to obtain stack pointer at specified location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    std::stack< value_T >*
    xstack_ptr_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        return xstack_ptr_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (rotation) to obtain stack pointer at specified location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    std::stack< value_T >*
    xstack_ptr_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        return xstack_ptr_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_split( SubscriptLambdaT subscript_ )
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend-stack_ptr to find the requested terminal:
            return xstack_ptr_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            return xstack_ptr_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ )
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            return this->m_expr_lhs.xstack_ptr_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            return this->m_expr_rhs.xstack_ptr_sub_split( subscript_ );
        }
    }


    /////////////////////////////////////////////////////////////////////
    // Constant access to stack locations via stack pointer
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_at_location() const
    {
        return xstack_ptr_descend< depth_ - LocationT - 1 >();
    }

    /**Internal algorithm to obtain stack pointer at specified location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_descend() const
    {
        if ( LocationT )
            return this->m_expr_lhs.xstack_ptr_descend< LocationT - 1 >();
        else
            return this->m_expr_rhs.xstack_ptr_at_location< LocationT >();
    }


    /**Internal algorithm (final rotation) to obtain constant stack pointer at specified location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    std::stack< value_T > const*
    xstack_ptr_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        return xstack_ptr_sub_split(
            pair_final_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (rotation) to obtain constant stack pointer at specified location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    std::stack< value_T > const*
    xstack_ptr_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_subscript_,
        SubscriptRightLambdaT rhs_subscript_
        )
         const
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        return xstack_ptr_sub_rotate(
            lhs_subscript_.left_lambda(),
            pair_internal_T(
                rhs_subscript_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to obtain constant stack pointer at specified location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_split( SubscriptLambdaT subscript_ ) const
    {
        // Is split needed ?
        if ( SubscriptLambdaT::depth_ == 1 ) {
            // No,
            // the subscript compound is a singular const scalar,
            // so switch to the descend-stack_ptr to find the requested terminal:
            return xstack_ptr_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >();

        } else {
            // Yes,
            // split out current subscript and pass the lower right-hand-side
            // subscript to the descent algorithm:
            return xstack_ptr_sub_descend< depth_ - SubscriptLambdaT::right_T::const_value_ - 1 >( subscript_.left_lambda() );
        }
    }


    /**Internal algorithm to obtain constant stack pointer at specified location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        // subscript descent to non-terminal node:
        if ( LocationT ) {
            // continue descend at the current level:
            return this->m_expr_lhs.xstack_ptr_sub_descend< LocationT - 1 >( subscript_ );

        } else {
            // step into the right-hand-side subtree and process remaining subscripts:
            return this->m_expr_rhs.xstack_ptr_sub_split( subscript_ );
        }
    }


    //////////////////////////////////////////////////////////////
    // Instruction-based deposits
    //////////////////////////////////////////////////////////////

    /**Internal algorithm (final rotation) to update data at specified location.*/
    template<
        int LocationT,
        typename SubscriptRightLambdaT
    >
    void
    xupdate_sub_rotate(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        SubscriptRightLambdaT rhs_program_
        )
        
    {
        // Note that rotated program does not include wraps by xst_lambda_wrap.
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_final_T;

        xupdate_sub_split(
            pair_final_T(
                rhs_program_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm (cork scrue recursive rotation) to update data at specified location.*/
    template<
        typename SubscriptLeftLambdaLhsT,
        int LocationT,
        typename SubscriptRightLambdaT
    >
    void
    xupdate_sub_rotate(
        xst_lambda_wrap<
            xst_pair<
                SubscriptLeftLambdaLhsT,
                xst_lambda_wrap< xst_const_scalar< LocationT > >
            >
        > lhs_program_,
        SubscriptRightLambdaT rhs_program_
        )
        
    {
        typedef
            xst_pair<
                SubscriptRightLambdaT,
                xst_const_scalar< LocationT >
            >
        pair_internal_T;

        xupdate_sub_rotate(
            lhs_program_.left_lambda(),
            pair_internal_T(
                rhs_program_,
                xst_const_scalar< LocationT >()
                )
            );
    }

    /**Internal algorithm to update data at specified location (final rotation).*/
    template< typename SubscriptLambdaT >
    void xupdate_sub_split( SubscriptLambdaT program_ )
    {
        program_.xinstruction_opcode( *this );
    }


    /**Internal algorithm to start instruction deposit.*/
    template< typename TargetLambdaT >
    void xinstruction_opcode( TargetLambdaT& lambda_ )
    {
        // descend to the lhs, the 1st operand:
        this->m_expr_lhs.xinstruction_1st< RhsT::const_value_ >( lambda_ );
    }


    /**Internal algorithm to process first operand of deposit instruction.*/
    template< int OpcodeT, typename TargetLambdaT >
    void xinstruction_1st( TargetLambdaT& lambda_ )
    {
        if ( xst_instruction_traits< OpcodeT >::length_ == 1 ) {
            // execute the instruction
            xst_instruction_1_operand< RhsT::const_value_, OpcodeT >::instruction( lambda_ );

            // continue the execution:
            this->m_expr_lhs.xinstruction_opcode( lambda_ );

        } else if ( xst_instruction_traits< OpcodeT >::length_ == 2 ) {
            // descend to the 2nd operand node, pass opcode and 1st operand:
            this->m_expr_lhs.xinstruction_2nd< OpcodeT, RhsT::const_value_ >( lambda_ );

        } else {
            assert( false );
        }
    }


    /**Internal algorithm to process second operand (right hand side operand) of deposit instruction.*/
    template< int OpcodeT, int FirstOperandT, typename TargetLambdaT >
    void xinstruction_2nd( TargetLambdaT& lambda_ )
    {
        // execute the instruction
        xst_instruction_2_operand< FirstOperandT, RhsT::const_value_, OpcodeT >::instruction( lambda_ );

        // continue execution of remaining program:
        this->m_expr_lhs.xinstruction_opcode( lambda_ );
    }


};  // xst_pair


}   // namespace cttl_impl


#endif //_XST_PAIR_H_INCLUDED_
