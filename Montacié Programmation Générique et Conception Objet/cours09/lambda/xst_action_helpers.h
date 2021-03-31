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

/**@file xst_action_helpers.h
 * @brief Defines helper functions to instantiate CTTL closure objects.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_action_helpers.h

#ifndef _XST_ACTION_HELPERS_H_INCLUDED_
#define _XST_ACTION_HELPERS_H_INCLUDED_

namespace cttl {

/**Helper function to create closure object for free function with one mutable argument.
*
* @tparam StaticActionT
*        specifies type which is a function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableUnaryFunction.html">adaptable unary function</a>,
*        such as
*        <a href="http://www.sgi.com/tech/stl/pointer_to_unary_function.html">pointer_to_unary_function</a>.
*
* @tparam ArgumentT
*        specifies type unary function argument.
*
* @param action_
*        Instance of function pointer adaptor for global or static member unary function.
*
* @param pargument_
*        Pointer to unary function argument.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_static_action.
*
*/
template< typename StaticActionT, typename ArgumentT >
inline xst_static_action< StaticActionT, ArgumentT&, typename StaticActionT::result_type >
action(
       StaticActionT action_,
       ArgumentT* pargument_
       )
{
    return xst_static_action< StaticActionT, ArgumentT&, typename StaticActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_static_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        action_,
        *pargument_
        );
}

/**Helper function to create closure object for free function with one constant argument.
*
* @tparam StaticActionT
*        specifies type which is a function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableUnaryFunction.html">adaptable unary function</a>,
*        such as
*        <a href="http://www.sgi.com/tech/stl/pointer_to_unary_function.html">pointer_to_unary_function</a>:
*
* @tparam ArgumentT
*        specifies type of unary function argument.
*
* @param action_
*        Instance of function pointer adaptor for global or static member unary function.
*
* @param argument_
*        Constant reference to unary function argument.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_static_action.
*
*/
template< typename StaticActionT, typename ArgumentT >
inline xst_static_action< StaticActionT, ArgumentT const&, typename StaticActionT::result_type >
action(
       StaticActionT action_,
       ArgumentT const& argument_
       )
{
    return xst_static_action< StaticActionT, ArgumentT const&, typename StaticActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_static_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        action_,
        argument_
        );
}

/**Helper function to create closure object for free function with no arguments.
*
* @tparam StaticActionT
*        specifies type which is a function pointer to
*        global or static member function with no arguments.
*
* @tparam ReturnT
*        specifies function return type.
*
* @param action_
*        Function pointer.
*
* @return
*        Instance of CTTL closure specialization for cttl_impl::xst_static_action.
*
*/
template< typename ReturnT, typename StaticActionT >
inline xst_static_action< StaticActionT, void, ReturnT >
action(
       StaticActionT action_
       )
{
    return xst_static_action< StaticActionT, void, ReturnT >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_static_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        action_
        );
}




/**Helper function to create closure object for constant member function with one mutable argument.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies constant member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableBinaryFunction.html">adaptable binary function</a>
*        such as <tt>std::const_mem_fun1_t</tt>.
*
* @tparam ArgumentT
*        specifies type of member function argument.
*
* @param object_
*        Reference to object.
*
* @param action_
*        Instance of function pointer adaptor for constant unary member function.
*
* @param pargument_
*        Pointer to function argument.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT, typename ArgumentT >
inline xst_member_action< ObjectT const&, MemberActionT, ArgumentT&, typename MemberActionT::result_type >
action(
       ObjectT const& object_,
       MemberActionT action_,
       ArgumentT* pargument_
       )
{
    return xst_member_action< ObjectT const&, MemberActionT, ArgumentT&, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        object_,
        action_,
        *pargument_
        );
}

/**Helper function to create closure object for member function with one mutable argument.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableBinaryFunction.html">adaptable binary function</a>
*        such as
*        <a href="http://www.sgi.com/tech/stl/mem_fun1_t.html">mem_fun1_t</a>:
*
* @tparam ArgumentT
*        specifies type of unary function argument.
*
* @param pobject_
*        Pointer to object.
*
* @param action_
*        Instance of function pointer adaptor for unary member function.
*
* @param pargument_
*        Pointer to member function argument.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT, typename ArgumentT >
inline xst_member_action< ObjectT&, MemberActionT, ArgumentT&, typename MemberActionT::result_type >
action(
       ObjectT* pobject_,
       MemberActionT action_,
       ArgumentT* pargument_
       )
{
    return xst_member_action< ObjectT&, MemberActionT, ArgumentT&, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        *pobject_,
        action_,
        *pargument_
        );
}

/**Helper function to create closure object for constant member function with one constant argument.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies constant member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableBinaryFunction.html">adaptable binary function</a>
*        such as <tt>std::const_mem_fun1_t</tt>.
*
* @tparam ArgumentT
*        specifies type of member function argument.
*
* @param object_
*        Reference to object.
*
* @param action_
*        Instance of function pointer adaptor for constant unary member function.
*
* @param argument_
*        Reference to function argument.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT, typename ArgumentT >
inline xst_member_action< ObjectT const&, MemberActionT, ArgumentT const&, typename MemberActionT::result_type >
action(
       ObjectT const& object_,
       MemberActionT action_,
       ArgumentT const& argument_
       )
{
    return xst_member_action< ObjectT const&, MemberActionT, ArgumentT const&, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        object_,
        action_,
        argument_
        );
}

/**Helper function to create closure object for member function with one constant argument.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableBinaryFunction.html">adaptable binary function</a>
*        such as
*        <a href="http://www.sgi.com/tech/stl/mem_fun1_t.html">mem_fun1_t</a>:
*
* @tparam ArgumentT
*        specifies type of unary function argument.
*
* @param pobject_
*        Pointer to object.
*
* @param action_
*        Instance of function pointer adaptor for unary member function.
*
* @param argument_
*        Reference to argument of member function.
*
* @return
*        Instance of CTTL closure implementation class cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT, typename ArgumentT >
inline xst_member_action< ObjectT&, MemberActionT, ArgumentT const&, typename MemberActionT::result_type >
action(
       ObjectT* pobject_,
       MemberActionT action_,
       ArgumentT const& argument_
       )
{
    return xst_member_action< ObjectT&, MemberActionT, ArgumentT const&, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,               // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        *pobject_,
        action_,
        argument_
        );
}

/**Helper function to create closure object for constant member function with no arguments.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies constant member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableUnaryFunction.html">adaptable unary function</a>
*        such as <tt>std::const_mem_fun_t</tt>.
*
* @param object_
*        Reference to object.
*
* @param action_
*        Instance of function pointer adaptor for constant unary member function.
*
* @return
*        Instance of CTTL closure specialization for cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT >
inline xst_member_action< ObjectT const&, MemberActionT, void, typename MemberActionT::result_type >
action(
       ObjectT const& object_,
       MemberActionT action_
       )
{
    return xst_member_action< ObjectT const&, MemberActionT, void, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,                     // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        object_,
        action_
        );
}


/**Helper function to create closure object for member function with no arguments.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableUnaryFunction.html">adaptable unary function</a>
*        such as
*        <a href="http://www.sgi.com/tech/stl/mem_fun_t.html">mem_fun_t</a>.
*
* @param pobject_
*        Pointer to object.
*
* @param action_
*        Instance of function pointer adaptor for unary member function.
*
* @return
*        Instance of CTTL closure specialization for cttl_impl::xst_member_action.
*
*/
template< typename ObjectT, typename MemberActionT >
inline xst_member_action< ObjectT&, MemberActionT, void, typename MemberActionT::result_type >
action(
       ObjectT* pobject_,
       MemberActionT action_
       )
{
    return xst_member_action< ObjectT&, MemberActionT, void, typename MemberActionT::result_type >(
#ifdef CTTL_TRACE_DEPOSITS
       __LINE__,                     // line_
       "xst_member_action", // action_name_,
#endif // CTTL_TRACE_DEPOSITS
        *pobject_,
        action_
        );
}

}   // namespace cttl

#endif //_XST_ACTION_HELPERS_H_INCLUDED_
