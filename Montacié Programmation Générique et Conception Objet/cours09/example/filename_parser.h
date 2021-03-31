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

// filename_parser.h

#ifndef _FILENAME_PARSER_H_INCLUDED_
#define _FILENAME_PARSER_H_INCLUDED_

using namespace cttl;

template< typename SubstrT = const_edge<> >
struct file_name_parser {

    typedef typename SubstrT::string_T string_T;

    // construct input
    SubstrT edge_file_path;      // path includes last slash or backslash in the path, empty string if no path is given
    SubstrT edge_file_name_ext;  // file name and extension - always valid
    SubstrT edge_file_name;      // file name - empty if file name has no extension (e.g. directory name, not a file.ext)
    SubstrT edge_file_ext;       // file extension - always valid
    string_T& parent_string;

    file_name_parser( SubstrT& substr_ )
        :
        edge_file_path( substr_ ),
        edge_file_name_ext( substr_ ),
        edge_file_name( substr_ ),
        edge_file_ext( substr_ ),
        parent_string( substr_.parent() )
    {
    }

    bool grammar()
    {
        edge_file_name_ext.first.go_bof();
        edge_file_name_ext.second.go_eof();
        if (
            CTTL_RULE( file_name_parser< SubstrT >::parse_file_name ).match( edge_file_name_ext )
            !=
            string_T::npos
            )
        {
            //assert( edge_file_name_ext.length() );
            SubstrT edge_file_name_ext_saved = edge_file_name_ext;

            edge_file_ext.first = edge_file_name_ext.first.offset();
            edge_file_ext.second = edge_file_name_ext.second.offset();

            CTTL_RULE( file_name_parser< SubstrT >::parse_file_ext ).match( edge_file_ext );
            edge_file_name_ext = edge_file_name_ext_saved;
            return true;
        }

        return false;
    }

    size_t parse_file_name( SubstrT& substr_ )
    {
        return
            edge_file_path(
                symbol( true )
                +
                *!(
                    symbol( '\\' )
                    |
                    symbol( '/' )
                )
            ).match( substr_ )
            ;
    }

    size_t parse_file_ext( SubstrT& substr_ )
    {
        return
            lookbehind(
                edge_file_name( entity() ),
                *!symbol( '.' )
            ).match( substr_ )
            ;
    }

private:
    // Copy constructor and assignment are disabled:
    file_name_parser< SubstrT >( file_name_parser< SubstrT > const& );
    file_name_parser< SubstrT >& operator=( file_name_parser< SubstrT > const& );

};  // file_name_parser< SubstrT >


#endif //_FILENAME_PARSER_H_INCLUDED_
