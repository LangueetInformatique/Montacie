#ifndef _CTTL_CPP_COMMENT_H_INCLUDED_
#define _CTTL_CPP_COMMENT_H_INCLUDED_

// cpp_comment.h

using namespace cttl;

template< typename SubstrT >
struct comments_base_parser {

    // parser defines two kinds of substrings:
    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;
    typedef typename SubstrT::policy_T policy_T;

    policy_T* m_policy_ptr;

    comments_base_parser()
        :
        m_policy_ptr( NULL )
    {
    }

    void policy( policy_T* policy_ptr_ )
    {
        m_policy_ptr = policy_ptr_;
    }

    policy_T* policy()
    {
        assert( m_policy_ptr );
        return m_policy_ptr;
    }

    // default semantic actions:
    size_t cpp_comment( strict_input_T& )
    {
        return 0;
    }

    size_t c_comment( strict_input_T& )
    {
        return 0;
    }

    size_t single_quote_interior( strict_input_T& )
    {
        return 0;
    }

    size_t double_quote_interior( strict_input_T& )
    {
        return 0;
    }

};

/**Adds comments to the map of void regions.*/
template< typename SubstrT >
struct cpp_comment_parser : public comments_base_parser< SubstrT > {

    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;

    size_t cpp_comment( strict_input_T& edge_ )
    {
        this->policy()->region_insert( edge_.first.offset(), edge_.second.offset() );
        return 0;
    }

    size_t c_comment( strict_input_T& edge_ )
    {
        this->policy()->region_insert( edge_.first.offset(), edge_.second.offset() );
        return 0;
    }
};


/**Adds comments, character, string literals to the map of void regions.*/
template< typename SubstrT >
struct cpp_comment_and_literal_parser : public cpp_comment_parser< SubstrT > {

    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;

    size_t single_quote_interior( strict_input_T& edge_ )
    {
        this->policy()->region_insert( edge_.first.offset(), edge_.second.offset() );
        return 0;
    }

    size_t double_quote_interior( strict_input_T& edge_ )
    {
        this->policy()->region_insert( edge_.first.offset(), edge_.second.offset() );
        return 0;
    }

};


/**Finds comments in cpp or java file.*/
template< typename ParserT >
struct cpp_comment_lexer : public ParserT {

    // lexer defines two kinds of substrings:
    typedef typename ParserT::substr_T substr_T;
    typedef typename substr_T::strict_edge_T strict_input_T;
    typedef typename substr_T::string_T string_T;

    string_T wack_quote_quote;
    string_T wack_wack;
    string_T wack_asterisk;
    string_T asterisk_wack;

    cpp_comment_lexer()
        :
    wack_quote_quote( "/\"\'" ),
    wack_wack( "//" ),
    wack_asterisk( "/" "*" ),
    asterisk_wack( "*" "/" )
    {
    }

    bool rule_symbols( substr_T& edge_ ) {
        
        this->policy( &edge_.space_policy() );

        return (
            +!!(
                // Find closest character that can begin a comment or a literal.
                // Once found, match the rest of the symbol at the current position
                begin( &wack_quote_quote )
                ^
                (
                    c_single_quote(
                        entity() 
                        &
                        rule( *this, &cpp_comment_lexer< ParserT >::single_quote_interior )
                    )
                    |
                    c_double_quote(
                        entity()
                        &
                        rule( *this, &cpp_comment_lexer< ParserT >::double_quote_interior )
                    )
                    |
                    (   ( &wack_wack + ( !begin( '\n' ) | !end() ) )
                        &
                        rule( *this, &cpp_comment_lexer< ParserT >::cpp_comment )
                    )
                    |
                    (   ( &wack_asterisk + !symbol( &asterisk_wack ) )
                        &
                        rule( *this, &cpp_comment_lexer< ParserT >::c_comment )
                    )
                    |
                    // if none of the above matched, this can only be a division operator:
                    '/'
                )
            )

        ).match( edge_ ) != std::string::npos;
    }

};  // struct cpp_comment_lexer

#endif // _CTTL_CPP_COMMENT_H_INCLUDED_
