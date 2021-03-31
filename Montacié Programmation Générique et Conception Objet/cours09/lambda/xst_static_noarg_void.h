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

/**@file xst_static_noarg_void.h
 * @brief Defines implementation class for closure of free or static member function.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_static_noarg_void.h

#ifndef _XST_STATIC_NOARG_VOID_H_INCLUDED_
#define _XST_STATIC_NOARG_VOID_H_INCLUDED_

namespace cttl_impl {

/**@class xst_static_action
* @brief Implements partial specialization for closure object for void function with no arguments.
*
* @tparam StaticActionT
*        specifies type which is a function pointer to
*        global or static void function with no arguments.
*
*/
template< typename StaticActionT >
class xst_static_action< StaticActionT, /*ArgumentT*/void, /*ResultT*/void >

#ifdef CTTL_TRACE_DEPOSITS
    : public xst_traced_action_base
#endif // CTTL_TRACE_DEPOSITS

{

    /**Stores address of the function.*/
    StaticActionT m_static_action;

public:
    /**Defines type of semantic action represented by this closure object.*/
    typedef xst_static_action< StaticActionT, /*ArgumentT*/void, /*ResultT*/void > action_T;

    /**Defines return type of semantic action represented by this closure object.*/
    typedef int result_T;

    /**Defines type of dereferenced semantic action represented by this closure object.*/
    typedef typename xst_dereference_traits< action_T, result_T >::value_type value_type;

    /**Constructs and initializes the object.*/
    xst_static_action(
#ifdef CTTL_TRACE_DEPOSITS
        int line_,
        char const* action_name_,
#endif // CTTL_TRACE_DEPOSITS
        StaticActionT static_action_
        )
        :
#ifdef CTTL_TRACE_DEPOSITS
        xst_traced_action_base( line_, action_name_ ),
#endif // CTTL_TRACE_DEPOSITS
        m_static_action( static_action_ )
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
        trace_prolog();
        m_static_action();
        result_T result = result_T( 1 );
        trace_epilog( result );
        return result;
#else
        m_static_action();
        return result_T( 1 );
#endif // CTTL_TRACE_DEPOSITS
    }

};  // xst_static_action

}   // namespace cttl_impl


#endif //_XST_STATIC_NOARG_VOID_H_INCLUDED_
