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

/**@file xst_translator.h
 * @brief Defines lambda implementation classes for data higher-order-function expressions.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_translator.h

#ifndef _XST_TRANSLATOR_H_INCLUDED_
#define _XST_TRANSLATOR_H_INCLUDED_

namespace cttl_impl {

/**@struct xst_translator
 *@brief Placeholder for higher-order-function expression.
 *
 * Higher-order-function expression permits data transformations of different
 * types by conversion function <tt>f()</tt>:
 @code
    D ^ f 
 @endcode
 * This compile-time expression is equivalent to run-time expression
 @code
    D.push( f( x ) )
 @endcode
 * where x is the input value. Since higher-order-function
 * behaves exactly as lambda primitive, transformation functions
 * can be nested:
 @code
    D ^ f ^ g ^ ... ^ k
 @endcode
 * This type of transformation is known as <i>functional composition</i>.
 *
 * @tparam LambdaT
 *        specifies type of lambda primitive.
 *
 * @tparam TranslatorT
 *        specifies type of nested function
 *        or function object.
 *
 */
template< typename LambdaT, typename TranslatorT >
struct xst_translator {

    // allow any lambda primitive to access translator implementation
    template< typename D > friend struct xst_lambda_wrap;

    // allow all other translators to access translator implementation
    template< typename D, typename T > friend struct xst_translator;

    enum {
        /**Constant required to compile algorithms for subscript-based access to lambda compound.*/
        const_value_ = LambdaT::const_value_,

        /**Number of nodes at current level of subtree.*/
        depth_ = LambdaT::depth_,

        /**Cumulative capacity of lambda primitive.*/
        capacity_ = LambdaT::capacity_,

        /**Unique identifier of lambda primitive type for template resolution.*/
        primitive_id_ = primitive_id_translator
    };

    /**Defines C++ type of lambda primitive.*/
    typedef LambdaT lambda_T;

    /**Defines the type of the translator function or functor.*/
    typedef TranslatorT translator_T;

    /**Defines C++ type of object encapsulated by lambda primitive.*/
    typedef typename LambdaT::value_T value_T;

    /**Defines type of dereferenced object encapsulated by lambda primitive.*/
    typedef typename LambdaT::dereferenced_value_T dereferenced_value_T;

    /**Defines type of left scalar primitive of lambda compound.*/
    typedef xst_translator< LambdaT, TranslatorT > left_T;

    /**Defines type of right scalar primitive of lambda compound.*/
    typedef xst_translator< LambdaT, TranslatorT > right_T;

    /**Defines lambda reference type for this primitive.*/
    typedef xst_translator< LambdaT, TranslatorT > reference_T;

    /**Constructs translator object.*/
    xst_translator( LambdaT const& lambda_, TranslatorT const& translator_ )
    :
    m_lambda( lambda_ ),
    m_translator( translator_ )
    {
    }

    /**Copy constructor.*/
    xst_translator( xst_translator< LambdaT, TranslatorT > const& other_ )
    :
    m_lambda( other_.m_lambda ),
    m_translator( other_.m_translator )
    {
    }

    /**Manufactures lambda reference for this translator.*/
    reference_T make_reference() const
    {
        return *this;
    }
    
    /**Dereferenced value of the lambda compound node.*/
    template<
        int LocationT
    >
    dereferenced_value_T& dereferenced_value( xst_lambda_wrap< xst_const_scalar< LocationT > > subscript_ )
    {
        return m_lambda.dereferenced_value( subscript_ );
    }

    /**Direct mutable access to the left-hand-side lambda compound nodes.*/
    left_T& left_lambda()
    {
        return *this; //m_lambda; //DEBUG//.left_lambda();
    }

    /**Direct constant access to the left-hand-side lambda compound nodes.*/
    left_T const& left_lambda() const
    {
        return *this; //m_lambda; //DEBUG//.left_lambda();
    }

    /**Direct mutable access to the right-hand-side lambda compound nodes.*/
    right_T& right_lambda()
    {
        return *this; //m_lambda; //DEBUG//.right_lambda();
    }

    /**Direct constant access to the right-hand-side lambda compound nodes.*/
    right_T const& right_lambda() const
    {
        return *this; //m_lambda; //DEBUG//.right_lambda();
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
    void push( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        m_lambda.push( subscript_, m_translator( data_ ) );
    }

    /**Pop data from specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    void pop( SubscriptLambdaT subscript_ )
    {
        m_lambda.pop( subscript_ );
    }

    /**Constant access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T const& top( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.top( subscript_ );
    }

    /**Mutable access to data at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    value_T& top( SubscriptLambdaT subscript_ )
    {
        return m_lambda.top( subscript_ );
    }

    /**Get size of stack at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    size_t size( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.size( subscript_ );
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

#ifdef CTTL_LAMBDA_REFLECTION
    /**Defines type of translator which is reflection of this translator.*/
    typedef xst_translator< typename LambdaT::reflection_T, TranslatorT > reflection_T;

    /**Algorithm to manufacture reflection object.*/
    reflection_T reflection() const
    {
        return reflection_T( m_lambda.reflection() );
    }
#endif // CTTL_LAMBDA_REFLECTION

private:
    /////////////////////////////////////////////////////////////////////////
    // Implementation
    /////////////////////////////////////////////////////////////////////////

    /**Stores encapsulated lambda primitive primitive.*/
    LambdaT m_lambda;

    /**Stores translator function or functor.*/
    TranslatorT m_translator;

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

    //////////////////////////////////////////////////////////////
    // subscript bottom up traversal
    //////////////////////////////////////////////////////////////

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
        m_lambda.xpush_at_location< LocationT >( m_translator( data_ ) );
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename InputValueT >
    void xpush_descend( InputValueT const& data_ )
    {
        m_lambda.xpush_descend< LocationT >( m_translator( data_ ) );
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_split( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        m_lambda.xpush_sub_split( subscript_, m_translator( data_ ) );
    }

    /**Internal algorithm to push data into lambda compound node.*/
    template< int LocationT, typename SubscriptLambdaT, typename InputValueT >
    void xpush_sub_descend( SubscriptLambdaT subscript_, InputValueT const& data_ )
    {
        m_lambda.xpush_sub_descend< LocationT >( subscript_, m_translator( data_ ) );
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

    /**Internal algorithm to pop data from stack at specified location.*/
    template< int LocationT >
    void xpop_descend()
    {
        m_lambda.xpop_descend< LocationT >();
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

    /**Internal algorithm to access data at specified lambda compound location.*/
    template< int LocationT >
    value_T const& xtop_descend() const
    {
        return m_lambda.xtop_descend< LocationT >();
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

    /**Internal algorithm for constant access to data at specified lambda compound location.
    *
    * @tparam LocationT
    *       specifies location at the
    *       current level of encapsulated lambda primitive.
    *
    */
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

    //////////////////////////////////////////////////////////////
    // subscript access to lambda primitive
    //////////////////////////////////////////////////////////////

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

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_split( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xstack_ptr_sub_split( subscript_ );
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T >* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ )
    {
        return m_lambda.xstack_ptr_sub_descend< LocationT >( subscript_ );
    }


    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_at_location() const
    {
        return m_lambda.xstack_ptr_at_location< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT >
    std::stack< value_T > const* xstack_ptr_descend() const
    {
        return m_lambda.xstack_ptr_descend< LocationT >();
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_split( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xstack_ptr_sub_split( subscript_ );
    }

    /**Internal algorithm to obtain stack pointer at specified lambda compound location.*/
    template< int LocationT, typename SubscriptLambdaT >
    std::stack< value_T > const* xstack_ptr_sub_descend( SubscriptLambdaT subscript_ ) const
    {
        return m_lambda.xstack_ptr_sub_descend< LocationT >( subscript_ );
    }


};  // xst_translator


}   // namespace cttl_impl


#endif //_XST_TRANSLATOR_H_INCLUDED_
