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

/**@file xst_stack.h
 * @brief Defines stack primitive.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_stack.h

#ifndef _XST_STACK_H_INCLUDED_
#define _XST_STACK_H_INCLUDED_

namespace cttl_impl {


/**@struct xst_stack
 * @brief Implements stack lambda primitive.
 *
 * @tparam StackT
 *      specifies type of stack
 *      or reference to stack.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */
template< typename StackT >
struct xst_stack {

    // allow any lambda primitive to access stack primitive implementation
    template< typename D > friend struct xst_lambda_wrap;

    // allow any lambda primitive to access translator implementation
    template< typename D, typename T > friend struct xst_translator;

    enum {
        /**Constant required to compile algorithms for subscript-based access to lambda compound.*/
        const_value_,

        /**Number of nodes inside stack primitive.*/
        depth_ = 1,

        /**Capacity of stack primitive.*/
        capacity_ = 1,

        /**Unique identifier of stack primitive.*/
        primitive_id_ = primitive_id_stack
    };
    
    /**Defines type of encapsulated stack object.*/
    typedef typename xst_storage_adaptor< StackT >::value_type stack_T;

    /**Defines type of object stored in the stack.*/
    typedef typename stack_T::value_type value_T;

    /**Defines type of dereferenced stack primitive, which is type of object stored in the stack.*/
    typedef value_T dereferenced_value_T;

    /**Defines type of left scalar primitive of lambda compound.*/
    typedef xst_stack< StackT > left_T;

    /**Defines type of right scalar primitive of lambda compound.*/
    typedef xst_stack< StackT > right_T;
    
    /**Defines reference type for stack primitive.*/
    typedef xst_stack< typename xst_storage_adaptor< StackT >::reference > reference_T;

    /**Default constructor.*/
    xst_stack()
    {
    }

    /**Constructs stack primitive from stack or reference to stack.*/
    xst_stack( StackT stack_ )
        :
    m_stack( stack_ )
    {
    }

    /**Constructs stack primitive from type of object stored in the stack.
    *
    * @post
    *       Note that an empty stack is created, the object type
    *       is used only for template resolution.
    */
    xst_stack( value_T const& )
    {
    }

    /**Copy constructor.*/
    xst_stack( xst_stack< StackT > const& other_ )
        :
    m_stack( other_.m_stack )
    {
    }

    /**Manufactures copy of reference object for stack primitive.*/
    reference_T make_reference() const
    {
        return reference_T( const_cast< xst_stack< StackT >* >( this )->m_stack.value() );
    }
    
    /**Dereferenced stack primitive returns top stack element.*/
    template<
        int LocationT
    >
    dereferenced_value_T& dereferenced_value( xst_lambda_wrap< xst_const_scalar< LocationT > > subscript_ )
    {
        return top( subscript_ );
    }

    //////////////////////////////////////////////////////////////
    // Direct access to stack primitive
    //////////////////////////////////////////////////////////////

    /**Direct mutable access to left-hand-side stack lambda compound node.*/
    left_T& left_lambda()
    {
        return *this;
    }


    /**Direct constant access to left-hand-side stack lambda compound node.*/
    left_T const& left_lambda() const
    {
        return *this;
    }

    /**Direct mutable access to right-hand-side stack lambda compound node.*/
    right_T& right_lambda()
    {
        return *this;
    }

    /**Direct constant access to right-hand-side stack lambda compound node.*/
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

    /**Push data to stack.*/
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
        CTTL_TRACE_DEPOSIT_TEXT( "->" );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< StackT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( "push$" );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< InputValueT >::identity( data_ ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        xpush_descend< LocationT >( data_ );
    }

    /**Push data from stack.*/
    template<
        int LocationT
    >
    void
    pop(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        
    {
        xpop_descend< LocationT >();
    }

    /**Constant access to top element of stack.*/
    template<
        int LocationT
    >
    value_T const& top(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
         const
    {
        return xtop_descend< LocationT >();
    }

    /**Mutable access to top element of stack.*/
    template<
        int LocationT
    >
    value_T& top(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        
    {
        return xtop_descend< LocationT >();
    }

    /**Get stack size.*/
    template<
        int LocationT
    >
    size_t
    size(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        const
    {
        return xsize_at_location< LocationT >();
    }

    /**Get constant pointer to stack encapsulated by lambda compound node.*/
    template<
        int LocationT
    >
    stack_T const*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
        const
    {
        return xstack_ptr_at_location< LocationT >();
    }

    /**Get mutable pointer to stack encapsulated by lambda compound node.*/
    template<
        int LocationT
    >
    stack_T*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
    {
        return xstack_ptr_at_location< LocationT >();
    }

#ifdef CTTL_LAMBDA_REFLECTION
    /**Defines reflection type for stack primitive.*/
    typedef xst_stack< StackT > reflection_T;

    /**Create lambda reflection for stack primitive.*/
    reflection_T reflection() const
    {
        return *this;
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Stores encapsulated stack object or reference to stack object.*/
    xst_storage_adaptor< StackT > m_stack;

    /**Internal algorithm to push data to stack.*/
    template< int LocationT, typename InputValueT >
    void xpush_at_location( InputValueT const& data_ )
    {
        assert( !LocationT );
        m_stack.value().push( data_ );
    }

    /**Internal algorithm to pop data from stack.*/
    template< int LocationT >
    void xpop_at_location()
    {
        assert( !LocationT );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< StackT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( "pop$" );
        assert( m_stack.const_value().size() );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< value_T >::identity( m_stack.const_value().top() ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        m_stack.value().pop();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT >
    value_T const& xtop_at_location() const
    {
        assert( !LocationT );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< StackT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( '$' );
        assert( m_stack.const_value().size() );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< value_T >::identity( m_stack.const_value().top() ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        return m_stack.const_value().top();
    }

    /**Internal algorithm to push data to stack.*/
    template< int LocationT, typename InputValueT >
    void xpush_descend( InputValueT const& data_ )
    {
        xpush_at_location< LocationT >( data_ );
    }

    /**Internal algorithm to pop data from stack.*/
    template< int LocationT >
    void xpop_descend()
    {
        xpop_at_location< LocationT >();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT >
    value_T const& xtop_descend() const
    {
        return xtop_at_location< LocationT >();
    }

    //////////////////////////////////////////////////////////////
    // subscript traversal algorithms
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse subscript.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse subscript.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_top_down_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse subscript.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    //////////////////////////////////////////////////////////////
    // subscript bottom up traversal
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to traverse subscript.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse subscript.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_bottom_up_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse subscript.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    //////////////////////////////////////////////////////////////
    // Lambda primitive stack interface support
    //////////////////////////////////////////////////////////////

    /**Internal algorithm to push data to stack.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_split( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to push data to stack.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_descend( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from stack.*/
    template< typename SubscriptLambdaT >
    void xpop_sub_split( SubscriptLambdaT )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from stack.*/
    template< int LocationT, typename SubscriptLambdaT >
    void xpop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
    }

    /**Internal algorithm to access top element of stack.*/
    template< typename SubscriptLambdaT >
    value_T const& xtop_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return m_stack.const_value().top();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T const& xtop_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return m_stack.const_value().top();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT >
    value_T& xtop_at_location()
    {
        assert( !LocationT );
        CTTL_TRACE_DEPOSIT_TEXT( "->" );
        CTTL_TRACE_DEPOSIT_TEXT( xst_storage_adaptor< StackT >::trace_char() );
        CTTL_TRACE_DEPOSIT_TEXT( '$' );
        assert( m_stack.const_value().size() );
        CTTL_TRACE_DEPOSIT_TEXT( xst_non_scalar_traits< value_T >::identity( m_stack.const_value().top() ) );
        CTTL_TRACE_DEPOSIT_TEXT( ' ' );
        return m_stack.value().top();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT >
    value_T& xtop_descend()
    {
        return xtop_at_location< LocationT >();
    }

    /**Internal algorithm to access top element of stack.*/
    template< typename SubscriptLambdaT >
    value_T& xtop_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return xtop_descend< 0 >();
    }

    /**Internal algorithm to access top element of stack.*/
    template< int LocationT, typename SubscriptLambdaT >
    value_T& xtop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return xtop_descend< 0 >();
    }

    /**Internal algorithm to get stack size.*/
    template< int LocationT >
    size_t xsize_at_location() const
    {
        assert( !LocationT );
        return m_stack.const_value().size();
    }

    /**Internal algorithm to get stack size.*/
    template< int LocationT >
    size_t xsize_descend() const
    {
        return xsize_at_location< LocationT >();
    }

    /**Internal algorithm to get stack size.*/
    template< typename SubscriptLambdaT >
    size_t xsize_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return 0;   // compile time optimization
    }

    /**Internal algorithm to get stack size.*/
    template< int LocationT, typename SubscriptLambdaT >
    size_t xsize_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return 0;   // compile time optimization
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT >
    stack_T const* xstack_ptr_at_location() const
    {
        assert( !LocationT );
        return &m_stack.const_value();
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT >
    stack_T const* xstack_ptr_descend() const
    {
        return xstack_ptr_at_location< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< typename SubscriptLambdaT >
    stack_T const* xstack_ptr_sub_split( SubscriptLambdaT ) const
    {
        assert( false );
        return NULL;    // compile time optimization
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT, typename SubscriptLambdaT >
    stack_T const* xstack_ptr_sub_descend( SubscriptLambdaT ) const
    {
        assert( false );
        return NULL;    // compile time optimization
    }


    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT >
    stack_T* xstack_ptr_at_location()
    {
        assert( !LocationT );
        return &m_stack.value();
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT >
    stack_T* xstack_ptr_descend()
    {
        return xstack_ptr_at_location< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< typename SubscriptLambdaT >
    stack_T* xstack_ptr_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return NULL;    // compile time optimization
    }

    /**Internal algorithm to obtain stack pointer.*/
    template< int LocationT, typename SubscriptLambdaT >
    stack_T* xstack_ptr_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return NULL;    // compile time optimization
    }


};  // xst_stack


}   // namespace cttl_impl


#endif //_XST_STACK_H_INCLUDED_
