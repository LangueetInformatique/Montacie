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

/**@file xst_static_action.h
 * @brief Defines implementation class for closure of free or static member function.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_static_action.h

#ifndef _XST_STATIC_ACTION_H_INCLUDED_
#define _XST_STATIC_ACTION_H_INCLUDED_

namespace cttl_impl {

/**@class xst_static_action
* @brief Implements closure object for function with one argument.
*
* @tparam StaticActionT
*        specifies type which is a function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableUnaryFunction.html">adaptable unary function</a>,
*        such as
*        <a href="http://www.sgi.com/tech/stl/pointer_to_unary_function.html">pointer_to_unary_function</a>:
*
* @tparam ArgumentT
*        specifies type of function argument.
*
* @tparam ResultT
*        specifies type of function return value.
*
*/
template< typename StaticActionT, typename ArgumentT, typename ResultT >
class xst_static_action

#ifdef CTTL_TRACE_DEPOSITS
    : public xst_traced_action_base
#endif // CTTL_TRACE_DEPOSITS

{
    /**Stores function pointer adaptor to invoke.*/
    StaticActionT m_static_action;

    /**Stores reference to, or actual instance of the function argument.*/
    xst_storage_adaptor< ArgumentT > m_argument;

public:
    /**Defines type of semantic action represented by this closure object.*/
    typedef xst_static_action< StaticActionT, ArgumentT, ResultT > action_T;

    /**Defines return type of semantic action represented by this closure object.*/
    typedef typename StaticActionT::result_type result_T;

    /**Defines type of dereferenced semantic action represented by this closure object.*/
    typedef typename xst_dereference_traits< action_T, result_T >::value_type value_type;

    /**Constructs and initializes the object.*/
    xst_static_action(
#ifdef CTTL_TRACE_DEPOSITS
        int line_,
        char const* action_name_,
#endif // CTTL_TRACE_DEPOSITS
        StaticActionT static_action_,
        ArgumentT argument_
        )
        :
#ifdef CTTL_TRACE_DEPOSITS
        xst_traced_action_base( line_, action_name_ ),
#endif // CTTL_TRACE_DEPOSITS
        m_static_action( static_action_ ),
        m_argument( argument_ )
    {
    }

    /**Calls encapsulated function when invoked by cttl_impl::xst_translator.*/
    result_T operator() ( bool ) const
    {
        return operator*();
    }

    /**Overloaded dereference operator invokes encapsulated function.*/
    result_T operator* () const
    {
#ifdef CTTL_TRACE_DEPOSITS
        trace_prolog( m_argument.value() );
        result_T result = m_static_action( m_argument.value() );
        trace_epilog( result );
        return result;
#else
        return m_static_action( m_argument.value() );
#endif // CTTL_TRACE_DEPOSITS
    }

};  // xst_static_action

}   // namespace cttl_impl


#endif //_XST_STATIC_ACTION_H_INCLUDED_
