////////////////////////////////////////////////////////////////////////
// Common Text Transformation Library
// Copyright (C) 1997-2006 by Igor Kholodov. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// mailto:cttl@users.sourceforge.net
// http://sourceforge.net/projects/cttl/
////////////////////////////////////////////////////////////////////////

/**@file pipe_input.h
* @brief Rudimentary functions to handle pipe input.
*
*/

// pipe_input.h

#ifndef _CTTL_PIPE_INPUT_H_INCLUDED_
#define _CTTL_PIPE_INPUT_H_INCLUDED_

#include <iostream>
#include <string>
#include <vector>

namespace cttl {

    /**Inputs data from standard input and stores it in a vector provided by the user.*/
    template <typename CharT>
    inline size_t pipe_input_2_vector( std::vector< std::basic_string< CharT > >& vect_input_, std::basic_string< CharT > filter_ )
    {
        std::basic_string< CharT > inp_text;
        while ( std::cin >> inp_text ) {
            // line by line:
            if ( filter_.length() ) {
                if ( inp_text.find( filter_ ) != std::basic_string< CharT >::npos ) {
                    vect_input_.push_back( inp_text );
                } else {
                }
            } else {
                // no filter was specified
                vect_input_.push_back( inp_text );
            }
        }
        return vect_input_.size();
    }

    /**Inputs data from standard input and stores it in a vector provided by the user.*/
    template <typename CharT>
    inline size_t pipe_input_2_vector( std::vector< std::basic_string< CharT > >& vect_input_, CharT const* filter_ )
    {
        return pipe_input_2_vector( vect_input_, std::basic_string< CharT >( filter_ ) );
    }

    /**Inputs data from standard input and stores it in a vector provided by the user.*/
    template <typename CharT>
    inline size_t pipe_input_2_vector( std::vector< std::basic_string< CharT > >& vect_input_ )
    {
        std::basic_string< CharT > inp_text;
        while ( std::cin >> inp_text ) {
            vect_input_.push_back( inp_text );
        }
        return vect_input_.size();
    }

    /**Inputs data from standard input and stores it in a string provided by the user.*/
    template <typename CharT>
    inline size_t pipe_input_2_string( std::basic_string< CharT >& str_output_, CharT delimiter_ )
    {
        std::basic_string< char > inp_text;
        while ( std::cin >> inp_text ) {
            // line by line:
            str_output_ += inp_text;
            str_output_ += delimiter_;
        }

        return str_output_.length();
    }

    /**Inputs data from standard input and stores it in a string provided by the user.*/
    template <typename CharT>
    inline size_t pipe_input_2_string( std::basic_string< CharT >& str_output_ )
    {
        return pipe_input_2_string( str_output_, CharT( '\t' ) );
    }

}//namespace cttl

#endif //_CTTL_PIPE_INPUT_H_INCLUDED_
