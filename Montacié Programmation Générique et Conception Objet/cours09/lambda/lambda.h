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

/**@file lambda.h
 * @brief Main header file for CTTL lambda expression support.
 *
 * Include this file to make lambda expressions available to your source code.
 *
 */


// lambda.h

#ifndef _CTTL_LAMBDA_H_INCLUDED_
#define _CTTL_LAMBDA_H_INCLUDED_


// The following preprocessor macros may be used to control lambda tracing levels:
//#define CTTL_TRACE_EVERYTHING    // by default automatically turns lambda tracing on
//#define CTTL_TRACE_RULES         // by default automatically turns lambda tracing on
//#define CTTL_TRACE_DEPOSITS      // turns lambda tracing on
//#define CTTL_TRACE_DEPOSITS_OFF  // turn lambda tracing off, to be used in combination with CTTL_TRACE_EVERYTHING and CTTL_TRACE_RULES
//#define CTTL_TRACE_DEPOSIT_LINE_ON // turns on tracing of lambda operator adaptors

// The following macros may be used for compatibility with older compilers:
//#define CTTL_LAMBDA_SINGULAR   // turns off lambda composites

#include <stack>
#include "xst_deposit_adaptor.h"
#include "xst_operator_traits.h"
#include "xst_binary_adaptor.h"
#include "xst_unary_adaptor.h"
#include "xst_base.h"
#include "xst_instruction_traits.h"
#include "xst_instructions.h"
#include "xst_const_scalar.h"
#include "xst_assignment_adaptors.h"
#include "xst_subscript_adaptors.h"
#include "xst_operator_adaptors.h"
#include "xst_storage_adaptor.h"
#include "xst_scalar.h"
#include "xst_stack.h"
#include "xst_dictionary_translator.h"
#include "xst_sequence_translator.h"
#include "xst_edge_translator.h"
#include "xst_literal_translator.h"
#include "xst_translator.h"
#ifndef CTTL_LAMBDA_SINGULAR
#   include "xst_pair.h"
#endif //CTTL_LAMBDA_SINGULAR
#include "xst_iterator_writer.h"
#include "xst_helpers.h"
#include "xst_operator_functions.h"
#include "xst_lambda.h"

#include "xst_traced_action_base.h"

// free functions with one argument
#include "xst_static_action.h"
#include "xst_static_void.h"

// free functions with no arguments
#include "xst_static_noarg_action.h"
#include "xst_static_noarg_void.h"

// member functions with one argument
#include "xst_member_action.h"
#include "xst_member_void.h"

// member functions with no arguments
#include "xst_member_noarg_action.h"
#include "xst_member_noarg_void.h"

#include "xst_action_helpers.h"
#include "xst_action_helpers_traced.h"
#include "xst_member_action_alias.h"
#include "xst_member_action_alias.h"
#include <bitset>
#include "xst_member_alias_bitset.h"

#endif // _CTTL_LAMBDA_H_INCLUDED_

/////////////////////////////////////////////////////////////////////////////

/** @mainpage CTTL lambda expression documentation
* @htmlinclude banner.htm
*
* <a href="http://cttl.sourceforge.net/">CTTL</a>
* lambda expression is a C++ sub-expression, embedded into CTTL grammar.
*
* @par Helper classes:
* - cttl::lambda A collection of convenience typedefs for instantiation of singular lambda primitives.
*
* @par Alias namespace reference:
* - cttl::alias Contains prefabricated helper functions to create closures for member functions of CTTL objects and STL containers.
* - cttl::alias::associative Alias helpers for @c count() and @c erase() member functions of STL associative containers.
* - cttl::alias::basic_string Alias helpers for @c std::basic_string::push_back() member function of STL string.
* - cttl::alias::bitset Alias helpers for member function templates of @c std::bitset.
* - cttl::alias::edge Alias helpers for member functions of CTTL substring classes.
* - cttl::alias::node Alias helpers for member functions of CTTL node class.
* - cttl::alias::queue Alias helpers for @c front() and @c back() member functions of STL queue container.
*
* @par Helper functions:
* - cttl <a href="namespacemembers.html">namespace members</a>
*
* <hr>
* @htmlinclude copyright2009.txt
*/
