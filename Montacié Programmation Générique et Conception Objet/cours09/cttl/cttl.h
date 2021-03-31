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

/**@file cttl.h
 * @brief Main header file of the Common Text Transformation Library.
 *
 * Include this file to make CTTL library available to your source code.
 *
 */


// cttl.h

#ifndef _CTTL_CTTL_H_INCLUDED_
#define _CTTL_CTTL_H_INCLUDED_

/**Specifies release version of the library.*/
#define CTTL_VERSION 302

//#define NDEBUG                // define to stop assertions from being compiled
//#define CTTL_TRACE_EVERYTHING // define to turn tracing on
//#define CTTL_TRACE_EXPRESSION_TYPEID  // define to show C++ specialized expression types
//#define CTTL_TRACE_EXPRESSION_IMPL    // define to show lexeme implementation file and line numbers

//#define CTTL_TRACE_RULES      // define to turn light tracing on
//#define CTTL_TRACE_TRIVIAL    // define for trace messages only mode

#ifndef CTTL_STD_STRING
/**Specifies string type to compile free functions.*/
#   define CTTL_STD_STRING std::string
#endif // CTTL_STD_STRING

#ifndef CTTL_STD_WSTRING
/**Specifies wide character string type to compile free functions.*/
#   define CTTL_STD_WSTRING std::wstring
#endif // CTTL_STD_WSTRING

#ifndef CTTL_STD_CHAR
/**Specifies character type to compile free functions.*/
#define CTTL_STD_CHAR   CTTL_STD_STRING::value_type
#endif // CTTL_STD_CHAR

#ifndef CTTL_STD_WCHAR
/**Specifies wide character type to compile free functions.*/
#define CTTL_STD_WCHAR  CTTL_STD_WSTRING::value_type
#endif // CTTL_STD_WCHAR


#include <cassert>

#include "edge.h"

#ifdef __MINGW32__
#include "mingw_specific.h"
#endif // __MINGW32__

#include "xtl_primary.h"
#include "xtl_quote.h"
#include "xtl_sym.h"
#include "xtl_quote_sym.h"
#include "xtl_op.h"
#include "xtl_op_speclzd.h"
#include "xtl_metaphor.h"
#include "xtl_quote_speclzd.h"
#include "policy.h"

#endif // _CTTL_CTTL_H_INCLUDED_

/** @mainpage Common Text Transformation Library
* @htmlinclude banner.htm
*
* <a href="http://cttl.sourceforge.net/">CTTL</a>
* is a set of C++ classes and functions to understand and modify text data.
* The library implementation is based on STL classes and algorithms.
*
* @par Text input position management:
* - cttl::node Logical position inside input string.
* - cttl::node_insert_go Substring inserter function object.
* - cttl::node_insert_stay Substring inserter function object.
*
* @par Substrings:
* - cttl::const_edge Constant parseable substring
* - cttl::edge Mutable parseable substring
* - cttl::edge_replace Substring replacer function object.
* - cttl::edge_first_insert_go Substring inserter function object.
* - cttl::edge_first_insert_stay Substring inserter function object.
* - cttl::edge_second_insert_go Substring inserter function object.
* - cttl::edge_second_insert_stay Substring inserter function object.
*
* @par Predefined space policy classes:
* - cttl::policy_default Provides default implementation of CTTL space policy
* - cttl::policy_space<flag_follow_space> Space policy specialization to skip white space characters ht, lf, vt, ff, cr, and space
* - cttl::policy_space<flag_greedy> Greedy version of the white space policy
* - cttl::policy_space<flag_cpp_comments> Space policy specialization to skip white space characters combined with C and C++ style comments
* - cttl::policy_space<flag_follow_region> Space policy specialization to skip user-defined void regions
*
* <hr>
* @htmlinclude copyright2009.txt
*/
