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

/**@file xst_const_scalar.h
 * @brief Defines lambda primitive designated as integer constant scalar.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_const_scalar.h

#ifndef _XST_CONST_SCALAR_H_INCLUDED_
#define _XST_CONST_SCALAR_H_INCLUDED_

/**Macro for abbreviated declaration of cttl_impl::xst_const_scalar lambda primitive.*/
#define const_scalar_type( T ) cttl_impl::xst_lambda_wrap< cttl_impl::xst_const_scalar< T > >

namespace cttl_impl {

/**@struct xst_const_scalar
 * @brief Implements lambda primitive representing integer constants.
 *
 * @tparam ValueT
 *        specifies compile-time value
 *        of the constant scalar lambda primitive.
 *
 */
template< int ValueT >
struct xst_const_scalar {

    // allow any lambda primitive to access const scalar implementation
    template< typename D > friend struct xst_lambda_wrap;

    // allow lambda compound to access const scalar implementation
    template< typename L, typename R > friend struct xst_pair;

    enum {
        /**Externally visible constant value of this lambda primitive.*/
        const_value_ = ValueT,

        /**Subtree node count constant.*/
        depth_ = 1,

        /**Capacity of constant scalar.*/
        capacity_ = 1,

        /**Unique identifier of constant scalar lambda primitive.*/
        primitive_id_ = primitive_id_const_scalar
    };

    /**Defines type of primitive encapsulated by constant scalar primitive.*/
    typedef int value_T;

    /**Defines type of dereferenced constant scalar primitive.*/
    typedef int dereferenced_value_T;

    /**Defines type of left subtree of lambda compound.*/
    typedef xst_const_scalar< ValueT > left_T;

    /**Defines type of right subtree of lambda compound.*/
    typedef xst_const_scalar< ValueT > right_T;

    /**Defines lambda reference type for constant scalar primitive.*/
    typedef xst_const_scalar< ValueT > reference_T;

    /**Manufactures copy of reference object for encapsulated lambda primitive.*/
    static reference_T make_reference()
    {
        return reference_T();
    }

    /**Dereferenced value of lambda primitive.*/
    template< int LocationT >
    static dereferenced_value_T dereferenced_value( xst_lambda_wrap< xst_const_scalar< LocationT > > )
    {
        return dereferenced_value_T();
    }

    //////////////////////////////////////////////////////////////
    // Direct access to lambda compound node
    //////////////////////////////////////////////////////////////
    left_T const& left_lambda() const
    {
        return xstatic_const_instance();
    }

    right_T const& right_lambda() const
    {
        return xstatic_const_instance();
    }


    //////////////////////////////////////////////////////////////
    // Subscript traversal algorithms
    //////////////////////////////////////////////////////////////
    template< typename FunctorT >
    static void subscript_top_down( FunctorT& functor_ )
    {
        functor_( const_scalar( 0 ) );
    }

    template< typename FunctorT >
    static void subscript_bottom_up( FunctorT& functor_ )
    {
        functor_( const_scalar( 0 ) );
    }

    template< typename FunctorT >
    void traverse_bottom_up( FunctorT& functor_ ) const
    {
        functor_( xstatic_const_instance() );
    }
    
    template< typename FunctorT >
    void traverse_top_down( FunctorT& functor_ ) const
    {
        functor_( xstatic_const_instance() );
    }
    

    //////////////////////////////////////////////////////////////
    // Emulation of subscript-based stack interface
    //////////////////////////////////////////////////////////////

    /**Push data to scalar primitive.*/
    template<
        int LocationT,
        typename InputValueT
    >
    static void push(
        xst_lambda_wrap< xst_const_scalar< LocationT > >,
        InputValueT const& data_
        )
    {
        xpush_descend< depth_ - LocationT - 1 >( data_ );
    }

    /**Pop data from specified lambda primitive.*/
    template<
        int LocationT
    >
    static void pop(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
    {
        xpop_descend< depth_ - LocationT - 1 >();
    }

    /**Returns value of lambda primitive.*/
    template< int LocationT >
    static value_T const& top( xst_lambda_wrap< xst_const_scalar< LocationT > > )
    {
        return xstatic_const_value();
    }

    /**Returns value of const scalar converted to size_t type.*/
    template<
        int LocationT
    >
    static size_t size(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
    {
        return const_value_;
    }

    /**Get stack pointer of lambda primitive.*/
    template<
        int LocationT
    >
    static std::stack< value_T > const*
    stack_ptr(
        xst_lambda_wrap< xst_const_scalar< LocationT > >
        )
    {
        assert( !LocationT );
        return NULL;
    }

#ifdef CTTL_LAMBDA_REFLECTION
    typedef xst_const_scalar< ValueT > reflection_T;

    static reflection_T reflection()
    {
        return reflection_T();
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Returns constant reference to the value of constant scalar primitive.*/
    static value_T const& xstatic_const_value()
    {
        static const value_T static_const_value = ValueT;
        CTTL_TRACE_DEPOSIT_TEXT( const_value_ );
        CTTL_TRACE_DEPOSIT_TEXT( "C " );
        return static_const_value;
    }

    /**Returns copy of constant scalar primitive.*/
    reference_T const& xstatic_const_instance() const
    {
        return *this;
    }

    /**Internal algorithm to deposit data.*/
    template< int LocationT, typename InputValueT >
    static void xpush_at_location( InputValueT const& )
    {
        assert( !LocationT );
    }

    /**Internal algorithm to pop data from scalar primitive.*/
    template< int LocationT >
    static void xpop_at_location()
    {
        assert( !LocationT );
    }

    /**Internal algorithm to access data of scalar primitive.*/
    template< int LocationT >
    static value_T const& xtop_at_location()
    {
        assert( !LocationT );
        return xstatic_const_value();
    }


    /**Internal algorithm to deposit data.*/
    template< int LocationT, typename InputValueT >
    static void xpush_descend( InputValueT const& data_ )
    {
        // LocationT can be either enum or an integer
        xpush_at_location< LocationT >( data_ );
    }

    /**Internal algorithm to pop data from scalar primitive.*/
    template< int LocationT >
    static void xpop_descend()
    {
        xpop_at_location< LocationT >();
    }

    /**Internal algorithm to access data of scalar primitive.*/
    template< int LocationT >
    static value_T const& xtop_descend()
    {
        return xstatic_const_value();
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_top_down_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_top_down_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_switch( SubscriptLambdaT subscript_, FunctorT& functor_ )
    {
        functor_( subscript_ );
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< int LocationT, typename FunctorT >
    static void xsubscript_bottom_up_descend( FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to traverse lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT, typename FunctorT >
    static void xsubscript_bottom_up_subtree_descend( SubscriptLambdaT, FunctorT& )
    {
        assert( false );
    }

    /**Internal algorithm to push data into lambda primitive.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    static void xpush_sub_split( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to push data into lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    static void xpush_sub_descend( SubscriptLambdaT, InputValueT const& )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from lambda primitive.*/
    template< typename SubscriptLambdaT >
    static void xpop_sub_split( SubscriptLambdaT )
    {
        assert( false );
    }

    /**Internal algorithm to pop data from lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    static void xpop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
    }


    /**Internal access to data of lambda primitive.*/
    template< typename SubscriptLambdaT >
    static value_T const& xtop_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return xstatic_const_value();
    }

    /**Internal access to data of lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    static value_T const& xtop_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return xstatic_const_value();
    }


    /**Internal algorithm to get stack size of lambda primitive.*/
    template< int LocationT >
    static size_t xsize_at_location()
    {
        assert( !LocationT );
        return const_value_;
    }

    /**Internal algorithm to get stack size of lambda primitive.*/
    template< int LocationT >
    static size_t xsize_descend()
    {
        assert( !LocationT );
        return const_value_;
    }

    /**Internal algorithm to get stack size of lambda primitive.*/
    template< typename SubscriptLambdaT >
    static size_t xsize_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return const_value_;
    }

    /**Internal algorithm to get stack size of lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    static size_t xsize_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return const_value_;
    }


    /////////////////////////////////////////////////////////////////////
    // functions to support constant access to the location stack
    /////////////////////////////////////////////////////////////////////

    /**Internal algorithm to obtain stack pointer of lambda primitive.*/
    template< int LocationT >
    static std::stack< value_T > const* xstack_ptr_at_location()
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer of lambda primitive.*/
    template< int LocationT >
    static std::stack< value_T > const* xstack_ptr_descend()
    {
        assert( !LocationT );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer of lambda primitive.*/
    template< typename SubscriptLambdaT >
    static std::stack< value_T > const* xstack_ptr_sub_split( SubscriptLambdaT )
    {
        assert( false );
        return NULL;
    }

    /**Internal algorithm to obtain stack pointer of lambda primitive.*/
    template< int LocationT, typename SubscriptLambdaT >
    static std::stack< value_T > const* xstack_ptr_sub_descend( SubscriptLambdaT )
    {
        assert( false );
        return NULL;
    }


    //////////////////////////////////////////////////////////////
    // deposit support
    //////////////////////////////////////////////////////////////
    /**Terminates deposit program.
    *
    * @tparam TargetLambdaT
    *       specifies lambda subscript.
    *
    * @remarks
    *       Function ends the recursive descend into deposit program.
    *
    */
    template< typename TargetLambdaT >
    static void xinstruction_opcode( TargetLambdaT& )
    {
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        CTTL_UNILOG_FLUSH;
    }

    /**Internal algorithm to execute first instruction in the program.*/
    template< int OpcodeT, typename TargetLambdaT >
    static void xinstruction_1st( TargetLambdaT& lambda_ )
    {
        xst_instruction_1_operand< const_value_, OpcodeT >::instruction( lambda_ );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        CTTL_UNILOG_FLUSH;
    }

    /**Internal algorithm to execute last instruction in the program.*/
    template< int OpcodeT, int FirstOperandT, typename TargetLambdaT >
    static void xinstruction_2nd( TargetLambdaT& lambda_ )
    {
        xst_instruction_2_operand< FirstOperandT, const_value_, OpcodeT >::instruction( lambda_ );
        CTTL_TRACE_DEPOSIT_JUSTIFY();
        CTTL_TRACE_DEPOSIT_TEXT( ';' );
        CTTL_UNILOG_FLUSH;
    }

};  // xst_const_scalar

}   // namespace cttl_impl


#endif //_XST_CONST_SCALAR_H_INCLUDED_
