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

/**@file xst_member_noarg_void.h
 * @brief Defines implementation class for closure of void member function with no arguments.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_member_noarg_void.h

#ifndef _XST_MEMBER_NOARG_VOID_H_INCLUDED_
#define _XST_MEMBER_NOARG_VOID_H_INCLUDED_

namespace cttl_impl {

/**@class xst_member_action
* @brief Implements closure object for void member function with no arguments.
*
* @tparam ObjectT
*        specifies C++ type implementing desired member function.
*
* @tparam MemberActionT
*        specifies member function pointer adaptor
*        compatible with STL
*        <a href="http://www.sgi.com/tech/stl/AdaptableBinaryFunction.html">adaptable binary function</a>.
*
*
*/
template< typename ObjectT, typename MemberActionT >
class xst_member_action< ObjectT, MemberActionT, /*ArgumentT*/void, /*ResultT*/void >

#ifdef CTTL_TRACE_DEPOSITS
    : public xst_traced_action_base
#endif // CTTL_TRACE_DEPOSITS

{
    /**Stores reference to, or actual instance of object to invoke member function.*/
    xst_storage_adaptor< ObjectT > m_object;

    /**Stores member function pointer adaptor for the member to invoke.*/
    MemberActionT m_member_action;

public:
    /**Defines type of semantic action represented by this closure object.*/
    typedef xst_member_action< ObjectT, MemberActionT, /*ArgumentT*/void, /*ResultT*/void > action_T;

    /**Defines return type of semantic action represented by this closure object.*/
    typedef int result_T;

    /**Defines type of dereferenced semantic action represented by this closure object.*/
    typedef int value_type;

    /**Constructs and initializes the object.*/
    xst_member_action(
#ifdef CTTL_TRACE_DEPOSITS
        int line_,
        char const* action_name_,
#endif // CTTL_TRACE_DEPOSITS
        ObjectT object_ref_,
        MemberActionT member_action_
        )
        :
#ifdef CTTL_TRACE_DEPOSITS
        xst_traced_action_base( line_, action_name_ ),
#endif // CTTL_TRACE_DEPOSITS
        m_object( object_ref_ ),
        m_member_action( member_action_ )
    {
    }

    /**Calls encapsulated member function when invoked by cttl_impl::xst_translator.*/
    result_T operator() ( bool ) const
    {
        return operator*();
    }

    /**Overloaded dereference operator invokes encapsulated member function.*/
    result_T operator* () const
    {
#ifdef CTTL_TRACE_DEPOSITS
        trace_prolog();
        m_member_action( &m_object.value() );
        result_T result = result_T( 1 );
        trace_epilog( result );
        return result;
#else
        m_member_action( &m_object.value() );
        return result_T( 1 );
#endif // CTTL_TRACE_DEPOSITS
    }

};  // xst_member_action

}   // namespace cttl_impl


#endif //_XST_MEMBER_NOARG_VOID_H_INCLUDED_
