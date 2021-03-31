// sample code: arithmetics.cpp
// demonstrates stateful cttl parser and lexer

//#define NDEBUG    // must appear before assert.h is included to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING
//#define CTTL_TRACE_RULES  //define to turn light tracing on
//#define CTTL_TRACE_TRIVIAL    //define for trace messages only mode

#include <iostream>
#include <iomanip>
#include "cttl/cttl.h"

using namespace cttl;

template< typename SubstrT >
struct parser {
    int ip_cnt;

    parser( int ip_cnt_ = 0 )
        :   ip_cnt( ip_cnt_ )
    {
    }

    size_t numeric_literal( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t " << substr_ << std::endl;
        return substr_.second.offset();
    }

    size_t divide( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R1" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R2" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t DIV \t R2, R1 \t; R2 = R2 " << substr_ << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t R2" << std::endl;
        return substr_.second.offset();
    }

    size_t multiply( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R1" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R2" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t MUL \t R2, R1 \t; R2 = R2 " << substr_ << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t R2" << std::endl;
        return substr_.second.offset();
    }

    size_t add( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R1" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R2" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t ADD \t R2, R1 \t; R2 = R2 " << substr_ << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t R2" << std::endl;
        return substr_.second.offset();
    }

    size_t subtract( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R1" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R2" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t SUB \t R2, R1 \t; R2 = R2 " << substr_ << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t R2" << std::endl;
        return substr_.second.offset();
    }

    size_t unary_minus( SubstrT& substr_ )
    {
        std::cout << "\t" << ++ip_cnt << "\t ;" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t POP \t R1" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t NEG \t R1 \t\t; R1 = -(" << substr_ << ")" << std::endl;
        std::cout << "\t" << ++ip_cnt << "\t PUSH \t R1" << std::endl;
        return substr_.second.offset();
    }

};//struct parser

template< typename SubstrT >
struct lexer : public parser< typename SubstrT::strict_edge_T > {

    /*  Arithmetic expression grammar production rules in EBNF form:
     *
     *    <expr> -->   <term> ( '+' <term>   | '-' <term>   )*
     *    <term> --> <factor> ( '*' <factor> | '/' <factor> )*
     *  <factor> --> <primary> | '(' <expr> ')' | '-' <factor> | '+' <factor>
     * <primary> --> ( '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' )+
     * 
     */

    // Type of substring for strict-mode grammar evaluation:
    typedef typename SubstrT::strict_edge_T strict_substr_T;


    // Grammar rule: arithmetic expression.
    // Description: expr is a starting rule of the grammar, it represents the arithmetic expression.
    // EBNF syntax: <expr> --> <term> ( '+' <term> | '-' <term> )*
    size_t rule_expr( SubstrT& substr_ )
    {
        return (

            CTTL_RULE( lexer< SubstrT >::rule_term )
            +
            *(
                (
                    ( '+' + CTTL_RULE( lexer< SubstrT >::rule_term ) )
                    &
                    CTTL_RULE( parser< strict_substr_T >::add )
                )
                |
                (
                    ( '-' + CTTL_RULE( lexer< SubstrT >::rule_term ) )
                    &
                    CTTL_RULE( parser< strict_substr_T >::subtract )
                )
            )

        ).match( substr_ )
        ;
    }


    // Grammar rule: term.
    // Description: term is an operand of an addition or subtraction operation.
    // EBNF syntax: <term> --> <factor> ( '*' <factor> | '/' <factor> )*
    size_t rule_term( SubstrT& substr_ )
    {
        return (

            CTTL_RULE( lexer< SubstrT >::rule_factor )
            +
            *(
                (
                    ( '*' + CTTL_RULE( lexer< SubstrT >::rule_factor ) )
                    &
                    CTTL_RULE( parser< strict_substr_T >::multiply )
                )
                |
                (
                    ( '/' + CTTL_RULE( lexer< SubstrT >::rule_factor ) )
                    &
                    CTTL_RULE( parser< strict_substr_T >::divide )
                )
            )

        ).match( substr_ )
        ;
    }


    // Grammar rule: factor.
    // Description: factor is an operand of a division or multiplication operation.
    // EBNF syntax: <factor> --> <primary> | '(' <expr> ')' | '-' <factor> | '+' <factor>
    size_t rule_factor( SubstrT& substr_ )
    {
        return (

            (
                // Primary is simply a numeric literal:
                isdigit
                &
                CTTL_RULE( parser< strict_substr_T >::numeric_literal )
            )
            |
            (
                // (Expression)
                '(' + CTTL_RULE( lexer< SubstrT >::rule_expr ) + ')'
            )
            |
            (
                // Unary minus
                '-'
                +
                (
                    CTTL_RULE( lexer< SubstrT >::rule_factor )
                    &
                    CTTL_RULE( parser< strict_substr_T >::unary_minus )
                )
            )
            |
            (
                // Unary plus is simply ignored:
                '+' + CTTL_RULE( lexer< SubstrT >::rule_factor )
            )
            |
            // Or it's an error:
            CTTL_RULE( lexer< SubstrT >::parse_error )

        ).match( substr_ )
        ;
    }

    // Semantic action to report a syntax error.
    // Function always returns error code to the lexer, therefore
    // it acts as a stop symbol in the grammar.
    size_t parse_error( SubstrT& substr_ ) const
    {
        std::cout
            << "*** syntax error ***"
            << std::endl
            << substr_.parent()
            << std::endl
            << std::setw( substr_.first.offset() + 1 ) << '^'
            << "-- at position " << substr_.first.offset()
            << std::endl
            ;
        return std::string::npos;
    }

};


int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout << "\t usage: enter arithmetic expression to parse" << std::endl;
        return 1;
    }

    // Construct input string from arguments on the command line:
    std::string inp;
    string_array2string( inp, argv + 1, ' ' );

    // Construct substring to parse:
    typedef const_edge< policy_space<> > substr_T;
    substr_T substring( inp );

    // Construct the parser:
    lexer< substr_T > arithmetic_parser;

    // Evaluate arithmetic expression:
    if (
        CTTL_MEMBER_RULE(
            arithmetic_parser,
            &lexer< substr_T >::rule_expr
        ).match( substring ) != std::string::npos
    )
    {
        if( substring.length() ) {
            std::cout
                << std::endl
                << "*** error: parser terminated: ***"
                << std::endl
                << inp
                << std::endl
                << std::setw( substring.first.offset() + 1 ) << '^'
                << "-- at position "
                << substring.first.offset()
                << std::endl
                ;
        }

    } else
        std::cout << "*** parser terminated" << std::endl;

    return 0;
}
