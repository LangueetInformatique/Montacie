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

/**@file xst_member_alias_bitset.h
 * @brief Defines alias functions for
 *        STL <a href="http://www.sgi.com/tech/stl/bitset.html">bitset</a> collection.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_member_alias_bitset.h

#ifndef _XST_MEMBER_ALIAS_BITSET_H_INCLUDED_
#define _XST_MEMBER_ALIAS_BITSET_H_INCLUDED_


namespace cttl_impl {

/**@struct xst_non_scalar_traits
 * @brief Implements template specialization for <tt>std::bitset<N></tt> type.
 *
 */
template< size_t N >
struct xst_non_scalar_traits< std::bitset<N> >
{
    typedef std::bitset<N> value_type;

    static char identity( value_type const& )
    {
        return '?';
    }

}; // struct xst_non_scalar_traits

}   // namespace cttl_impl



namespace cttl {

using namespace cttl_impl;

namespace alias {

/**Alias helper function @c flip().
*
* Returns closure for
*
@code
    std::bitset<N>& flip();
@endcode
*
* member function. The closure object delays actual function
* call till run-time by capturing pointer to member function.
*
*/
template< size_t N, typename LambdaT >
inline
xst_unary_adaptor<
    xst_lambda_wrap<
        xst_scalar<
            xst_member_action<
                /*ObjectT*/         typename LambdaT::value_T &,
                /*MemberActionT*/   std::mem_fun_t<
                                        /*ResultT*/std::bitset<N>&,
                                        /*ObjectT*/typename LambdaT::value_T
                                    >,
                /*ArgumentT*/       void,
                /*ResultT*/         std::bitset<N>&
            >
        >
    >
    ,
    xst_dereference_policy<
        xst_dereference_traits<
            /*ObjectT*/ typename LambdaT::value_T,
            /*ResultT*/ std::bitset<N>&
        >::capacity_,
        LambdaT::primitive_id_
    >
>
flip(
    xst_lambda_wrap< LambdaT >* plambda_
    )
{
    typedef typename LambdaT::value_T object_T;
    typedef std::bitset<N>& result_T;
    typedef xst_unary_adaptor<
        xst_lambda_wrap<
            xst_scalar<
                xst_member_action<
                    /*ObjectT*/         typename LambdaT::value_T &,
                    /*MemberActionT*/   std::mem_fun_t<
                                            /*ResultT*/std::bitset<N>&,
                                            /*ObjectT*/typename LambdaT::value_T
                                        >,
                    /*ArgumentT*/       void,
                    /*ResultT*/         std::bitset<N>&
                >
            >
        >
        ,
        xst_dereference_policy<
            xst_dereference_traits<
                /*ObjectT*/ typename LambdaT::value_T,
                /*ResultT*/ std::bitset<N>&
            >::capacity_,
            LambdaT::primitive_id_
        >
    >
    xst_adaptor_T;

    return xst_adaptor_T( scalar(
#ifdef CTTL_TRACE_DEPOSITS
            xst_traced_action(
                __LINE__,
                "std::bitset<N>& alias::flip()",
#else
            action(
#endif // CTTL_TRACE_DEPOSITS
                &plambda_->top( const_scalar( 0 ) ),
                ( std::mem_fun_t<
                    result_T,
                    object_T
                    >
                    ( &object_T::flip )
                )
            )
        ))
        ;
}

/**Alias helper function @c flip().
*
* Returns closure for
*
@code
    std::bitset<N>& flip( size_t );
@endcode
*
* member function. The closure object delays actual function
* call till run-time by capturing pointer to member function.
*
*/
template< size_t N, typename LambdaT, typename ArgumentT >
inline
xst_unary_adaptor<
    xst_lambda_wrap<
        xst_scalar<
            xst_member_action<
                /*ObjectT*/         typename LambdaT::value_T &,
                /*MemberActionT*/   std::mem_fun1_t<
                                        /*ResultT*/std::bitset<N>&,
                                        /*ObjectT*/typename LambdaT::value_T,
                                        /*ArgumentT*/ArgumentT
                                    >,
                /*ArgumentT*/       ArgumentT const&,
                /*ResultT*/         std::bitset<N>&
            >
        >
    >
    ,
    xst_dereference_policy<
        xst_dereference_traits<
            /*ObjectT*/ typename LambdaT::value_T,
            /*ResultT*/ std::bitset<N>&
        >::capacity_,
        LambdaT::primitive_id_
    >
>
flip(
    xst_lambda_wrap< LambdaT >* plambda_,
    // Although flip() receives its argument by value,
    // this helper passes it by const reference.
    ArgumentT const& arg_
    )
{
    typedef typename LambdaT::value_T object_T;
    typedef std::bitset<N>& result_T;
    typedef xst_unary_adaptor<
        xst_lambda_wrap<
            xst_scalar<
                xst_member_action<
                    /*ObjectT*/         typename LambdaT::value_T &,
                    /*MemberActionT*/   std::mem_fun1_t<
                                            /*ResultT*/std::bitset<N>&,
                                            /*ObjectT*/typename LambdaT::value_T,
                                            /*ArgumentT*/ArgumentT
                                        >,
                    /*ArgumentT*/       ArgumentT const&,
                    /*ResultT*/         std::bitset<N>&
                >
            >
        >
        ,
        xst_dereference_policy<
            xst_dereference_traits<
                /*ObjectT*/ typename LambdaT::value_T,
                /*ResultT*/ std::bitset<N>&
            >::capacity_,
            LambdaT::primitive_id_
        >
    >
    xst_adaptor_T;

    return xst_adaptor_T( scalar(
#ifdef CTTL_TRACE_DEPOSITS
            xst_traced_action(
                __LINE__,
                "std::bitset<N>& alias::flip(size_t)",
#else
            action(
#endif // CTTL_TRACE_DEPOSITS
                &plambda_->top( const_scalar( 0 ) ),
                ( std::mem_fun1_t<
                    result_T,
                    object_T,
                    ArgumentT
                    >
                    ( &object_T::flip )
                ),
                arg_
            )
        ))
        ;
}

/**Alias helper function @c reset().
*
* Returns closure for
*
@code
    std::bitset<N>& reset();
@endcode
*
* member function. The closure object delays actual function
* call till run-time by capturing pointer to member function.
*
*/
template< size_t N, typename LambdaT >
inline
xst_unary_adaptor<
    xst_lambda_wrap<
        xst_scalar<
            xst_member_action<
                /*ObjectT*/         typename LambdaT::value_T &,
                /*MemberActionT*/   std::mem_fun_t<
                                        /*ResultT*/std::bitset<N>&,
                                        /*ObjectT*/typename LambdaT::value_T
                                    >,
                /*ArgumentT*/       void,
                /*ResultT*/         std::bitset<N>&
            >
        >
    >
    ,
    xst_dereference_policy<
        xst_dereference_traits<
            /*ObjectT*/ typename LambdaT::value_T,
            /*ResultT*/ std::bitset<N>&
        >::capacity_,
        LambdaT::primitive_id_
    >
>
reset(
    xst_lambda_wrap< LambdaT >* plambda_
    )
{
    typedef typename LambdaT::value_T object_T;
    typedef std::bitset<N>& result_T;
    typedef xst_unary_adaptor<
        xst_lambda_wrap<
            xst_scalar<
                xst_member_action<
                    /*ObjectT*/         typename LambdaT::value_T &,
                    /*MemberActionT*/   std::mem_fun_t<
                                            /*ResultT*/std::bitset<N>&,
                                            /*ObjectT*/typename LambdaT::value_T
                                        >,
                    /*ArgumentT*/       void,
                    /*ResultT*/         std::bitset<N>&
                >
            >
        >
        ,
        xst_dereference_policy<
            xst_dereference_traits<
                /*ObjectT*/ typename LambdaT::value_T,
                /*ResultT*/ std::bitset<N>&
            >::capacity_,
            LambdaT::primitive_id_
        >
    >
    xst_adaptor_T;

    return xst_adaptor_T( scalar(
#ifdef CTTL_TRACE_DEPOSITS
            xst_traced_action(
                __LINE__,
                "std::bitset<N>& alias::reset()",
#else
            action(
#endif // CTTL_TRACE_DEPOSITS
                &plambda_->top( const_scalar( 0 ) ),
                ( std::mem_fun_t<
                    result_T,
                    object_T
                    >
                    ( &object_T::reset )
                )
            )
        ))
        ;
}

/**Alias helper function @c reset().
*
* Returns closure for
*
@code
    std::bitset<N>& reset( size_t );
@endcode
*
* member function. The closure object delays actual function
* call till run-time by capturing pointer to member function.
*
*/
template< size_t N, typename LambdaT, typename ArgumentT >
inline
xst_unary_adaptor<
    xst_lambda_wrap<
        xst_scalar<
            xst_member_action<
                /*ObjectT*/         typename LambdaT::value_T &,
                /*MemberActionT*/   std::mem_fun1_t<
                                        /*ResultT*/std::bitset<N>&,
                                        /*ObjectT*/typename LambdaT::value_T,
                                        /*ArgumentT*/ArgumentT
                                    >,
                /*ArgumentT*/       ArgumentT const&,
                /*ResultT*/         std::bitset<N>&
            >
        >
    >
    ,
    xst_dereference_policy<
        xst_dereference_traits<
            /*ObjectT*/ typename LambdaT::value_T,
            /*ResultT*/ std::bitset<N>&
        >::capacity_,
        LambdaT::primitive_id_
    >
>
reset(
    xst_lambda_wrap< LambdaT >* plambda_,
    // Although reset() receives its argument by value,
    // this helper passes it by const reference.
    ArgumentT const& arg_
    )
{
    typedef typename LambdaT::value_T object_T;
    typedef std::bitset<N>& result_T;
    typedef xst_unary_adaptor<
        xst_lambda_wrap<
            xst_scalar<
                xst_member_action<
                    /*ObjectT*/         typename LambdaT::value_T &,
                    /*MemberActionT*/   std::mem_fun1_t<
                                            /*ResultT*/std::bitset<N>&,
                                            /*ObjectT*/typename LambdaT::value_T,
                                            /*ArgumentT*/ArgumentT
                                        >,
                    /*ArgumentT*/       ArgumentT const&,
                    /*ResultT*/         std::bitset<N>&
                >
            >
        >
        ,
        xst_dereference_policy<
            xst_dereference_traits<
                /*ObjectT*/ typename LambdaT::value_T,
                /*ResultT*/ std::bitset<N>&
            >::capacity_,
            LambdaT::primitive_id_
        >
    >
    xst_adaptor_T;

    return xst_adaptor_T( scalar(
#ifdef CTTL_TRACE_DEPOSITS
            xst_traced_action(
                __LINE__,
                "std::bitset<N>& alias::reset(size_t)",
#else
            action(
#endif // CTTL_TRACE_DEPOSITS
                &plambda_->top( const_scalar( 0 ) ),
                ( std::mem_fun1_t<
                    result_T,
                    object_T,
                    ArgumentT
                    >
                    ( &object_T::reset )
                ),
                arg_
            )
        ))
        ;
}

/**Alias helper function @c set().
*
* Returns closure for
*
@code
    std::bitset<N>& set();
@endcode
*
* member function. The closure object delays actual function
* call till run-time by capturing pointer to member function.
*
*/
template< size_t N, typename LambdaT >
inline
xst_unary_adaptor<
    xst_lambda_wrap<
        xst_scalar<
            xst_member_action<
                /*ObjectT*/         typename LambdaT::value_T &,
                /*MemberActionT*/   std::mem_fun_t<
                                        /*ResultT*/std::bitset<N>&,
                                        /*ObjectT*/typename LambdaT::value_T
                                    >,
                /*ArgumentT*/       void,
                /*ResultT*/         std::bitset<N>&
            >
        >
    >
    ,
    xst_dereference_policy<
        xst_dereference_traits<
            /*ObjectT*/ typename LambdaT::value_T,
            /*ResultT*/ std::bitset<N>&
        >::capacity_,
        LambdaT::primitive_id_
    >
>
set(
    xst_lambda_wrap< LambdaT >* plambda_
    )
{
    typedef typename LambdaT::value_T object_T;
    typedef std::bitset<N>& result_T;
    typedef xst_unary_adaptor<
        xst_lambda_wrap<
            xst_scalar<
                xst_member_action<
                    /*ObjectT*/         typename LambdaT::value_T &,
                    /*MemberActionT*/   std::mem_fun_t<
                                            /*ResultT*/std::bitset<N>&,
                                            /*ObjectT*/typename LambdaT::value_T
                                        >,
                    /*ArgumentT*/       void,
                    /*ResultT*/         std::bitset<N>&
                >
            >
        >
        ,
        xst_dereference_policy<
            xst_dereference_traits<
                /*ObjectT*/ typename LambdaT::value_T,
                /*ResultT*/ std::bitset<N>&
            >::capacity_,
            LambdaT::primitive_id_
        >
    >
    xst_adaptor_T;

    return xst_adaptor_T( scalar(
#ifdef CTTL_TRACE_DEPOSITS
            xst_traced_action(
                __LINE__,
                "std::bitset<N>& alias::set()",
#else
            action(
#endif // CTTL_TRACE_DEPOSITS
                &plambda_->top( const_scalar( 0 ) ),
                ( std::mem_fun_t<
                    result_T,
                    object_T
                    >
                    ( &object_T::set )
                )
            )
        ))
        ;
}


} // namespace alias

}   // namespace cttl


#endif //_XST_MEMBER_ALIAS_BITSET_H_INCLUDED_
