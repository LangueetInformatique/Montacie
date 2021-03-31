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

/**@file dump_lambda.h
 * @brief Defines lambda diagnostic structures.
 *
 */

// dump_lambda.h

#ifndef _DUMP_LAMBDA_H_INCLUDED_
#define _DUMP_LAMBDA_H_INCLUDED_

struct dump_subscript_terminal
{
    size_t position;

    dump_subscript_terminal()
        :
    position( 0 )
    {
    }

    template< typename TerminalT >
    void operator() ( TerminalT const& )
    {
        std::cout
            << ( position++ ? "^" : "" )
            << TerminalT::const_value_
            ;
    }
}; // struct dump_subscript_terminal

template< typename LambdaT >
struct dump_lambda_terminals
{
    LambdaT const& lambda;

    dump_lambda_terminals( LambdaT const& lambda_ )
        :   lambda( lambda_ )
    {
    }

private:
    /**Assignment is disabled.*/
    dump_lambda_terminals< LambdaT >& operator=( dump_lambda_terminals< LambdaT > const& );

public:
    static void dump_header()
    {
        std::cout
            << std::endl
            << "--------------------------------------------------------------"
            << std::endl
            << "subscript" <<'\t'<< "size"  <<'\t'<< "stack_ptr"  <<'\t'<<'\t'<< "top"         
            << std::endl
            << "---------" <<'\t'<< "-----" <<'\t'<< "----------" <<'\t'<< "----------------------"
            << std::endl
            ;
    }

    template< typename SubscriptLambdaT >
    void operator() ( SubscriptLambdaT subscript_ ) const
    {
        dump_subscript_terminal dump_sub;
        subscript_.traverse_top_down( dump_sub );
        //subscript_.traverse_bottom_up( dump_sub );

        std::cout
            << '\t'
            << '\t'
            << lambda.size( subscript_ )
            << '\t'
            << lambda.stack_ptr( subscript_ )
            << '\t'
            << '\t'
            ;

        if ( lambda.size( subscript_ ) ) {
#if ( defined( CTTL_TRACE_DEPOSITS ) )
            lambda.top( subscript_ );
#else
            std::cout
                << lambda.top( subscript_ )
                ;
#endif // CTTL_TRACE_DEPOSITS

        } else {
            std::cout
                << "empty\t"
                ;
        }

        std::cout
            << std::endl
            ;
    }
}; // struct dump_lambda_terminals

template< typename LambdaT >
void dump_lambda( LambdaT const& lambda_ )
{
    dump_lambda_terminals< LambdaT > dump_dep( lambda_ );
    dump_dep.dump_header();
    lambda_.subscript_top_down( dump_dep );
}

template< typename LambdaT >
struct lambda_size
{
    LambdaT const& lambda;
    size_t size;

    lambda_size( LambdaT const& lambda_ )
        :
    lambda( lambda_ ),
        size( 0 )
    {
    }

private:
    /**Assignment is disabled.*/
    lambda_size< LambdaT >& operator=( lambda_size< LambdaT > const& );

public:
    template< typename SubscriptLambdaT >
    void operator() ( SubscriptLambdaT subscript_ )
    {
        size += lambda.size( subscript_ );
    }

}; // struct lambda_size

template< typename LambdaT >
size_t get_lambda_size( LambdaT const& lambda_ )
{
    lambda_size< LambdaT > size_functor( lambda_ );
    lambda_.subscript_top_down( size_functor );
    return size_functor.size;
}

#endif //_DUMP_LAMBDA_H_INCLUDED_
