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

// partition_file.cpp
// utility to partition file
// arguments: full_path\file N
// note that full path is required; N is number of parts.
// expect last part to be first-part-size <= last-part-size <= 2*first-part-size

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include <iostream>
#include "cttl/cttl.h"
#include "utils/fileio.h"
//#include "utils/itos.h"
#include "utils/string_format.h"

using namespace cttl;

size_t partition_file(
                   std::string& inp_,
                   const_edge<>& substr_,
                   size_t part_start_,
                   size_t parts_requested_,
                   const std::string& base_directory_,
                   const std::string& base_file_name_
                   )
{
    assert( inp_.length() );
    assert( parts_requested_ < inp_.length() );
    static size_t part_size = inp_.length() / parts_requested_; // part size determined only once
    assert( part_size );
//  std::cout << "part size: " << part_size << std::endl;

    if ( part_size >= inp_.length() ) {
        string2file( base_directory_ + "part_" + type2string( part_start_ ) + '_' + base_file_name_, substr_.text() );
        std::cout << "\t wrote: " << ( "part_" + type2string( part_start_++ ) + '_' + base_file_name_ ) << std::endl;

    } else {

        size_t begin_part = 0;
        size_t end_part = part_size;

        for ( ;; ) {
            substr_.first.offset( begin_part );
            substr_.first.go_line_home();

            substr_.second.offset( end_part );
            begin_part = substr_.second.go_line_home();

            // adjust if last part is small; add last part to the previous part:
            if ( inp_.length() < begin_part + part_size ) {
                end_part = substr_.second.go_eof();
                assert( end_part == inp_.length() );
            }

            string2file( base_directory_ + "part_" + type2string( part_start_ ) + '_' + base_file_name_, substr_.text() );
            std::cout << "\t wrote: " << ( "part_" + type2string( part_start_++ ) + '_' + base_file_name_ ) << std::endl;
            if ( end_part == inp_.length() )
                break;

            end_part = std::min( inp_.length(), begin_part + part_size );
        }
    }

    inp_ = "";
    return part_start_;
}

const size_t item_count = 1024*1024;            // read up to 1MB at a time
const size_t max_line_size = item_count + 1024; // allow 16k for the line size
char line_buffer[ max_line_size ];              // buffer for reading the data in
const size_t item_size = 1;                     // read items of 1 byte in size
const size_t max_inp_length = item_count * 100; // do not exceed 100MB when reading input

int main(int argc, char* argv[])
{
    if ( argc != 3 ) {
        std::cout
            << "Usage: "
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " full_path/file.txt N"
            << std::endl
            << "note that full path is required; N is number of parts."
            << std::endl
            << "expect last part to be N <= last-part-size <= 2*N"
            << std::endl
            ;
        return 0;
    }

    // step 1: get base file name and directory
    std::string inp = argv[ 1 ];
    assert( inp.length() );
    const_edge<> substring( inp );
    substring.first.go_bof();
    substring.second.go_eof();

    if ( ( *quote( true, symbol( true ), symbol( '\\' ) | symbol( '/' ) ) ).match( substring ) == std::string::npos ) {
        std::cout << "*** FAILED TO PARSE FILE NAME ***" << std::endl;
        return 1;
    }

    std::string base_file_name( substring );
    substring.second.offset( substring.first.offset() );
    substring.first.go_bof();
    std::string base_directory( substring );
    std::cout << "\t: reading " << base_directory << base_file_name << std::endl;

    // step 2: partition file

    size_t parts_requested = atoi( argv[ 2 ] );
    assert( parts_requested );

    FILE *file_stream;

    inp = "";
    size_t part_start = 1;
    if( ( file_stream = fopen( ( base_directory + base_file_name ).c_str(), "r" ) ) != NULL )
    {
//      while ( fgets( line_buffer, max_line_size, file_stream ) != NULL ) {
        size_t numread = 0;
        while ( ( numread = fread( line_buffer, item_size, item_count, file_stream ) ) ) {
            line_buffer[ numread ] = 0x00;
            inp += line_buffer;
            if ( inp.length() > max_inp_length ) {
                // chunk of text that needs to be processed
                part_start = partition_file(
                   inp,
                   substring,
                   part_start,
                   parts_requested,
                   base_directory,
                   base_file_name
                   );

                std::cout << "\t: reading " << base_directory << base_file_name << std::endl;
            }
        }
        assert( feof( file_stream ) );//returns 0 if the current position is not end of file
        fclose( file_stream );
    }
    if ( inp.length() ) {
        // if file size did not exceed 100MB
        part_start = partition_file(
            inp,
            substring,
            part_start,
            parts_requested,
            base_directory,
            base_file_name
            );
    }

    return 0;
}
