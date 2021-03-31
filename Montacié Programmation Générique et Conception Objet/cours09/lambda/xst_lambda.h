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

/**@file xst_lambda.h
 * @brief Defines helper @c struct for a collection of convenience @c typedefs
 *        for instantiation of singular lambda primitives.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// lambda.h

#ifndef _XST_LAMBDA_H_INCLUDED_
#define _XST_LAMBDA_H_INCLUDED_

namespace cttl {


/**@struct lambda
 * @brief A collection of convenience @c typedefs
 *        for instantiation of singular lambda primitives.
 *
 * @tparam ValueT
 *        specifies type of singular lambda primitive.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */
template< typename ValueT = int >
struct lambda {

    /**Defines scalar type to instantiate singular lambda primitive.*/
    typedef xst_lambda_wrap< xst_scalar< ValueT > > scalar;

    /**Defines reference-to-scalar type to instantiate singular lambda primitive.*/
    typedef xst_lambda_wrap< xst_scalar< ValueT& > > scalar_reference;

    /**Defines stack type to instantiate singular lambda primitive.*/
    typedef xst_lambda_wrap< xst_stack< std::stack< ValueT > > > stack;

    /**Defines reference-to-stack type to instantiate singular lambda primitive.*/
    typedef xst_lambda_wrap< xst_stack< std::stack< ValueT >& > > stack_reference;

};  // struct lambda


}   // namespace cttl


#endif //_XST_LAMBDA_H_INCLUDED_
