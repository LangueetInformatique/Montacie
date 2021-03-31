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

/**@file xst_scalar.h
 * @brief Defines scalar primitive.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_scalar.h

#ifndef _XST_SCALAR_H_INCLUDED_
#define _XST_SCALAR_H_INCLUDED_

namespace cttl_impl {


/**@struct xst_scalar
 * @brief Implements scalar lambda primitive.
 *
 * @tparam ValueT
 *        specifies C++ type adapted
 *        by scalar primitive or reference to type.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */
template< typename ValueT >
struct xst_scalar {

    // allow any lambda primitive to access scalar implementation
    template< typename D > friend struct xst_lambda_wrap;

    // allow any lambda primitive to access translator implementation
    template< typename D, typename T > friend struct xst_translator;

    /**Defines C++ type of lambda primitive.*/
    typedef typename xst_storage_adaptor< ValueT >::value_type value_T;

    /**Defines value type of compound objects.
    *
    * @remarks
    *      @c unmodified_dereferenced_T
    *      can be if encapsulated type is output iterator.
    *
    */
    typedef typename xst_non_scalar_traits< value_T >::value_type unmodified_dereferenced_T;

    /**Defines type of dereferenced object encapsulated by lambda primitive.*/
    typedef typename xst_dereference_traits< value_T, unmodified_dereferenced_T >::value_type dereferenced_value_T;

    /**Defines type of left scalar primitive of lambda compound.*/
    typedef xst_scalar< ValueT > left_T;

    /**Defines type of right scalar primitive of lambda compound.*/
    typedef xst_scalar< ValueT > right_T;
    
    enum {
        /**Constant required to compile algorithms for subscript-based access to lambda compound.*/
        const_value_,

        /**Number of nodes inside scalar primitive.*/
        depth_ = 1,

        /**Capacity of scalar primitive.
        *
        * @remarks
        *      @c capacity_
        *      can be zero if encapsulated type is output iterator.
        *
        */
        capacity_ = xst_dereference_traits< value_T, unmodified_dereferenced_T >::capacity_,

        /**Unique identifier of scalar primitive.*/
        primitive_id_ = primitive_id_scalar
    };

    /**Defines reference type for scalar primitive.*/
    typedef xst_scalar< typename xst_storage_adaptor< ValueT >::reference > reference_T;

    /**Default constructor.*/
    xst_scalar()
    {
    }

    /**Constructs scalar from its value or reference to value.*/
    xst_scalar( ValueT data_ )
    :
    m_value( data_ )
    {
    }

    /**Copy constructor.*/
    xst_scalar( xst_scalar< ValueT > const& other_ )
    :
    m_value( other_.m_value )
    {
    }

    /**Manufactures copy of reference object for scalar primitive.*/
    reference_T make_reference() const
    {
        return reference_T( const_cast< xst_scalar< ValueT >* >( this )->m_value.value() );
    }
    
    /**Dereferenced value of scalar lambda compound node.*/
    template<
        int LocationT
    >
    dereferenced_value_T&
    dereferenced_value( xst_lambda_wrap< xst_const_scalar< LocationT > > subscript_ )
    {
        // if unmodified_dereferenced_T is void, no dereference is attempted
        return xst_dereference_traits< value_T, unmodified_dereferenced_T >::dereference( top( subscript_ ) );
    }

    //////////////////////////////////////////////////////////////
    // Direct access to scalar primitive
    //////////////////////////////////////////////////////////////

    /**Direct mutable access to left-hand-side scalar lambda compound node.*/
    left_T& left_lambda()
    {
        return *this;
    }

    /**Direct constant access to left-hand-side scalar lambda compound node.*/
    left_T const& left_lambda() const
    {
        return *this;
    }

    /**Direct mutable access to right-hand-side scalar lambda compound node.*/
    right_T& right_lambda()
    {
        return *this;
    }

    /**Direct constant access to right-hand-side scalar lambda compound node.*/
    right_T const& right_lambda() const
    {
        return *this;
    }


    //////////////////////////////////////////////////////////////
    // subscript traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Subscript top-down subscript traversal algorithm.*/
    template< typename FunctorT >
    static void subscript_top_down( FunctorT& functor_ )
    {
        functor_( const_scalar( 0 ) );
    }

    /**Subscript bottom-up traversal algorithm.*/
    template< typename FunctorT >
    static void subscript_bottom_up( FunctorT& functor_ )
    {
        functor_( const_scalar( 0 ) );
    }

    //////////////////////////////////////////////////////////////
    // lambda compound traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Lambda compound bottom up traversal algorithm with mutable access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ )
    {
        functor_( *this );
    }
    
    /**Lambda compound top-down traversal algorithm with mutable access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ )
    {
        functor_( *this );
    }
    
    /**Lambda compound bottom up traversal algorithm with constant access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ ) const
    {
        functor_( *this );
    }
    
    /**Lambda compound top-down traversal algorithm with constant access to terminal nodes.*/
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ ) const
    {
        functor_( *this );
    }
    

    //////////////////////////////////////////////////////////////
    // Lambda primitive stack interface support
    //////////////////////////////////////////////////////////////

    /**Push data to scalar primitive.*/
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

    /**Pop data from scalar primitive.*/
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

    /**Constant access to scalar data.*/
    template<
        int LocationT
    >
    value_T const& top(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
         const
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    /**Mutable access to scalar data.*/
    template<
        int LocationT
    >
    value_T& top(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        
    {
        return xtop_descend< depth_ - LocationT - 1 >();
    }

    /**Get stack size of scalar primitive.*/
    template<
        int LocationT
    >
    size_t
    size(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        const
    {
        return 1;
    }

    /**Get constant stack pointer for scalar primitive.*/
    template<
        int LocationT
    >
    std::stack< value_T > const*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        const
    {
        assert( !LocationT );
        return NULL;
    }

    /**Get stack pointer for scalar primitive.*/
    template<
        int LocationT
    >
    std::stack< value_T >*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
    {
        assert( !LocationT );
        return NULL;
    }

#ifdef CTTL_LAMBDA_REFLECTION
    /**Defines reflection type for scalar primitive.*/
    typedef xst_scalar< ValueT > reflection_T;

    /**Create lambda reflection for scalar primitive.*/
    reflection_T reflection() const
    {
        return *this;
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Stores encapsulated scalar value or reference.*/
    xst_storage_adaptor< ValueT > m_value;

    /**Internal algorithm to deposit data.*/
    template< int LocationT, typename InputValueT >
    void xpush_at_location( InputValueT const& data_ )
    {
        assert( !LocationT );
        m_value.value() = data_;
    }

    /**Internal algorithm to pop scalar data.*/
    template< int LocationT >
    void xpop_at_location()
    {
        assert( !LocationT );
    }

    /**Internal algorithm for constant access to scalar data.*/
    template< int LocationT >
    value_T const& xtop_at_location() const
    {
        assert( !LocationT );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< ValueT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< value_T >::identity( m_value.const_value() ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        return m_value.const_value();
    }

    /**Internal algorithm to push scalar data.*/
    template< int LocationT, typename InputValueT >
    void xpush_descend( InputValueT const& data_ )
    {
        xpush_at_location< LocationT >( data_ );
    }

    /**Internal algorithm to pop scalar data.*/
    template< int LocationT >
    void xpop_descend()
    {
        xpop_at_location< LocationT >();
    }

    /**Internal algorithm to access scalar data.*/
    template< int LocationT >
    value_T const& xtop_descend() const
    {
        return xtop_at_location< LocationT >();
    }

    //////////////////////////////////////////////////////////////
    // subscript traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse scalar.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse scalar.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_top_down_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse scalar.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    //////////////////////////////////////////////////////////////
    // subscript bottom up traversal
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse scalar.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse scalar.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_bottom_up_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse scalar.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    //////////////////////////////////////////////////////////////
    // Lambda primitive stack interface support
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to push data into scalar node.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_split( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to push data into scalar node.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_descend( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from scalar node.*/
    template< typename SubscriptLambdaT >
    void xpop_sub_split( SubscriptLambdaT )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from scalar node.*/
    template< int LocationT, typename SubscriptLambdaT >
    void xpop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
    }



    /**Internal access to scalar data.*/
    template< typename SubscriptLambdaT >
    value_T const& xtop_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return m_value.const_value();
    }

    /**Internal access to scalar data.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T const& xtop_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return m_value.const_value();
    }

    /////////////////////////////////////////////////////////////////////
    // mutable data access
    /////////////////////////////////////////////////////////////////////

    /**Internal access to scalar data.*/
    template< int LocationT >
    value_T& xtop_at_location()
    {
        assert( !LocationT );
        CTTL_TRACE_DEPOSIT_TEXT( "->" );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< ValueT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< value_T >::identity( m_value.const_value() ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        return m_value.value();
    }

    /**Internal access to scalar data.*/
    template< int LocationT >
    value_T& xtop_descend()
    {
        return xtop_at_location< LocationT >();
    }

    /**Internal access to scalar data.*/
    template< typename SubscriptLambdaT >
    value_T& xtop_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return m_value.value();
    }

    /**Internal access to scalar data.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T& xtop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return m_value.value();
    }


    /**Internal algorithm to get stack size for scalar primitive.*/
    template< int LocationT >
    size_t xsize_at_location() const
    {
        assert( !LocationT );
        return 1;
    }

    /**Internal algorithm to get stack size for scalar primitive.*/
    template< int LocationT >
    size_t xsize_descend() const
    {
        assert( !LocationT );
        return 1;
    }

    /**Internal algorithm to get stack size for scalar primitive.*/
    template< typename SubscriptLambdaT >
    size_t xsize_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return 1;
    }

    /**Internal algorithm to get stack size for scalar primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    size_t xsize_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return 1;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_at_location() const
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_descend() const
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return NULL;
    }


    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_at_location()
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT >
    std::stack< value_T >* xstack_ptr_descend()
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer for scalar primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return NULL;
    }

};  // xst_scalar


}   // namespace cttl_impl


#endif //_XST_SCALAR_H_INCLUDED_
