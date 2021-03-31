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

/**@file fileio.h
 * @brief File input/output helper functions.
 *
 * @remarks
 *        Similar to
 *        http://www.boost.org/doc/libs/1_39_0/libs/regex/example/snippets/regex_merge_example.cpp
 *        <tt>regex_merge_example.cpp</tt> sample.
*
*/

// fileio.h

#ifndef _CTTL_FILEIO_H_INCLUDED_
#define _CTTL_FILEIO_H_INCLUDED_

#include "../cttl/coreutils.h"
#include <fstream> 

/**@namespace cttl
* @brief Namespace @c cttl defines publicly visible classes and
* functions of CTTL library.
*
*/
namespace cttl {

    /**Inputs data from a text file and stores results in a string provided by the user.*/
    template < typename CharT, typename StringT >
    void file2string( StringT const& filename_, std::basic_string< CharT >& str_ )
    {
        // on windows platform \r\n are converted into single \n
#ifdef __MINGW32__
        std::ifstream fs( filename_.c_str() );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( fs.rdbuf()->in_avail() );
        typename StringT::value_type ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, CharT( ch ) );
        }
#else
        std::basic_ifstream< CharT > fs( filename_.c_str() );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( size_t( fs.rdbuf()->in_avail() ) );
        CharT ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, ch );
        }
#endif // __MINGW32__
    }

    /**Inputs data from a text file and stores results in a string provided by the user.*/
    template < typename CharT >
    void file2string( CTTL_STD_CHAR const* filename_, std::basic_string< CharT >& str_ )
    {
        // on windows platform \r\n are converted into single \n
#ifdef __MINGW32__
        std::ifstream fs( filename_ );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( fs.rdbuf()->in_avail() );
        CTTL_STD_CHAR ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, CharT( ch ) );
        }
#else
        std::basic_ifstream< CharT > fs( filename_ );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( fs.rdbuf()->in_avail() );
        CharT ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, ch );
        }
#endif // __MINGW32__
    }

    /**Inputs data from a text file and stores results in a string provided by the user.*/
    template < typename CharT >
    void file2string( CTTL_STD_CHAR filename_[], std::basic_string< CharT >& str_ )
    {
        // on windows platform \r\n are converted into single \n
#ifdef __MINGW32__
        std::ifstream fs( filename_ );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( fs.rdbuf()->in_avail() );
        CTTL_STD_CHAR ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, CharT( ch ) );
        }
#else
        std::basic_ifstream< CharT > fs( filename_ );
        assert( fs.is_open() );
        str_.erase();
        str_.reserve( fs.rdbuf()->in_avail() );
        CharT ch;
        while( fs.get( ch ) ) {
            if( str_.capacity() == str_.size() ) {
                str_.reserve( str_.capacity() * 3 );
            }
            str_.append( 1, ch );
        }
#endif // __MINGW32__
    }

    /**Reads data from a text file and returns a string containing the data.*/
    template < typename StringT >
    StringT file2string( StringT const& filename_ )
    {
        StringT str_temp;
        file2string( filename_, str_temp );
        return str_temp;
    }

    /**Writes data from string provided by the user into a text file.*/
    template < typename CharT, typename StringT >
    void string2file( StringT const& filename_, std::basic_string< CharT > const& str_ )
    {
        // on windows platform single \n are converted into \r\n
#ifdef __MINGW32__
        std::ofstream file; 
        file.open( filename_.c_str(), std::ios_base::trunc );
        file << reinterpret_cast< typename StringT::value_type const* >( str_.c_str() );
        file.close();
#else
        std::basic_ofstream< CharT > file; 
        file.open( filename_.c_str(), std::ios_base::trunc );
        file << str_;
        file.close();
#endif // __MINGW32__
    }

    /**Writes data from string provided by the user into a text file.*/
    template < typename CharT >
    void string2file( CTTL_STD_CHAR const* filename_, std::basic_string< CharT > const& str_ )
    {
        // on windows platform single \n are converted into \r\n
#ifdef __MINGW32__
        std::ofstream file; 
        file.open( filename_, std::ios_base::trunc );
        file << reinterpret_cast< CTTL_STD_CHAR const* >( str_.c_str() );
        file.close(); 
#else
        std::basic_ofstream< CharT > file; 
        file.open( filename_, std::ios_base::trunc );
        file << str_;
        file.close(); 
#endif // __MINGW32__
    }

    /**Writes data from string provided by the user into a text file.*/
    template < typename CharT >
    void string2file( CTTL_STD_CHAR filename_[], std::basic_string< CharT > const& str_ )
    {
        // on windows platform single \n are converted into \r\n
#ifdef __MINGW32__
        std::ofstream file; 
        file.open( filename_, std::ios_base::trunc );
        file << reinterpret_cast< CTTL_STD_CHAR const* >( str_.c_str() );;
        file.close(); 
#else
        std::basic_ofstream< CharT > file; 
        file.open( filename_, std::ios_base::trunc );
        file << str_;
        file.close(); 
#endif // __MINGW32__
    }

}//namespace cttl


/** @mainpage CTTL Utility Classes and Functions
* @htmlinclude banner.htm
*
* <a href="http://cttl.sourceforge.net/">CTTL</a> sample programs
* include auxiliary header files located in <tt>cttl20/utils</tt>
* distribution subdirectory. These files define helper classes
* and functions to handle syntax trees, input, output, and time.
*
* @par Utility Classes:
* - cttl::inode_reader Representation of a readable node of a <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1000_syntax_tree.html">syntax tree</a>.
* - cttl::inode_writer Representation of a writable node of a <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1000_syntax_tree.html">syntax tree</a>.
* - cttl::guard_node_stack Utility class to preserve input nodes in nested grammars.
*
* @par Utility Functions:
* - cttl::file2string() Reads data from a text file and returns a string containing the data.
* - cttl::string2file() Writes data from the string into a text file.
* - cttl::itos() Converts C++ type to string.
* - cttl::type2string() Converts C++ type to string.
* - cttl::string2type() Converts string to C++ type.
* - cttl::pipe_input_2_vector() Inputs data from standard input and stores it in a vector of strings provided by the user.
* - cttl::pipe_input_2_string() Inputs data from standard input and stores it in a string provided by the user.
* - cttl::current_time() Returns current time.
* - cttl::time2string() Converts time_t to string.
*
* <hr>
* @htmlinclude copyright2009.txt
*/
#endif // _CTTL_FILEIO_H_INCLUDED_
