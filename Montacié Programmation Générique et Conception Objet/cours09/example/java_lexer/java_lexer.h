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

/*
http://home.bredband.no/gaulyk/java/grammar/JavaGrammar1.html
http://java.sun.com/docs/books/jls/second_edition/html/syntax.doc.html
http://www.cs.uiowa.edu/~fleck/JavaBNF.htm

This chapter presents a grammar for the Java programming language. 

The grammar presented piecemeal in the preceding chapters is much better
for exposition, but it is not ideally suited as a basis for a parser.
The grammar presented in this chapter is the basis for the reference implementation. 

The grammar below uses the following BNF-style conventions:

-----------------------------------------------------------------------
18.1 The Grammar of the Java Programming Language
-----------------------------------------------------------------------
*/

// java_lexer.h
// skeleton lexer for parsing and modifying java files.

/**@mainpage CTTL Java lexer sample
 * @htmlinclude banner.htm
 *
 * @par
 * Working version of a bare lexer for the Java programming language.
 * Feel free to modify for your own Java-related needs. Java grammar
 * taken "as is", directly from Sun web site:
 * <a href="http://java.sun.com/docs/books/jls/second_edition/html/syntax.doc.html"><tt>http://java.sun.com/docs/books/jls/second_edition/html/syntax.doc.html</tt></a>
 *
 * @par
 * Java lexer source code is located in <tt>example/java_lexer</tt>
 * subdirectory. The program demonstrates various aspects of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">CTTL grammars</a>.
 *
 * <hr>
 * @htmlinclude copyright2009.txt
 */

/**@file java_lexer.h
 * @brief Defines lexer class for @ref index.
 *
 */

#ifndef _CTTL_JAVA_LEXER_H_INCLUDED_
#define _CTTL_JAVA_LEXER_H_INCLUDED_

using namespace cttl;

template< typename SubstrT >
struct base_parser {
    // parser defines two kinds of substrings:
    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;

    // semantic actions:
    size_t semantic_action( strict_input_T& ) const
    {
        return 0;
    }

};  // struct base_parser

template< typename SubstrT >
struct java_parser : public base_parser< SubstrT > {

    // parser defines two kinds of substrings:
    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;

    // semantic actions:
    size_t semantic_action( strict_input_T& substr_ )
    {
        return substr_.second.offset();
    }

};  // struct java_parser

template< typename ParserT >
struct java_lexer : public ParserT {

    // Starting symbol is "CompilationUnit"

    // lexer defines two kinds of substrings:
    typedef typename ParserT::substr_T substr_T;
    typedef typename substr_T::strict_edge_T strict_input_T;

    std::set< std::string > set_AssignmentOperators;
    std::set< std::string > set_Infixops;
    std::set< std::string > set_PrefixOps;
    std::set< std::string > set_PostfixOp;
    std::set< std::string > set_BasicTypes;
    std::set< std::string > set_Modifiers;
    std::set< std::string > set_JavaKeywords;

    java_lexer()
    {
        set_AssignmentOperators.insert( LITERAL_EQ );
        set_AssignmentOperators.insert( LITERAL_ADD_EQ );
        set_AssignmentOperators.insert( LITERAL_SUB_EQ );
        set_AssignmentOperators.insert( LITERAL_AST_EQ );
        set_AssignmentOperators.insert( LITERAL_DIV_EQ );
        set_AssignmentOperators.insert( LITERAL_AMP_EQ );
        set_AssignmentOperators.insert( LITERAL_OR_EQ );
        set_AssignmentOperators.insert( LITERAL_XOR_EQ );
        set_AssignmentOperators.insert( LITERAL_PCT_EQ );
        set_AssignmentOperators.insert( LITERAL_2LT_EQ );
        set_AssignmentOperators.insert( LITERAL_2GT_EQ );
        set_AssignmentOperators.insert( LITERAL_3GT_EQ );

        set_Infixops.insert( LITERAL_2OR );
        set_Infixops.insert( LITERAL_2AMP );
        set_Infixops.insert( LITERAL_2EQ );
        set_Infixops.insert( LITERAL_BANG_EQ );
        set_Infixops.insert( LITERAL_OR );
        set_Infixops.insert( LITERAL_LT_EQ );
        set_Infixops.insert( LITERAL_GT_EQ );
        set_Infixops.insert( LITERAL_2LT );
        set_Infixops.insert( LITERAL_2GT );
        set_Infixops.insert( LITERAL_3GT );
        set_Infixops.insert( LITERAL_XOR );
        set_Infixops.insert( LITERAL_AMP );
        set_Infixops.insert( LITERAL_LT );
        set_Infixops.insert( LITERAL_GT );
        set_Infixops.insert( LITERAL_ADD );
        set_Infixops.insert( LITERAL_SUB );
        set_Infixops.insert( LITERAL_AST );
        set_Infixops.insert( LITERAL_DIV );
        set_Infixops.insert( LITERAL_PCT );

        set_PrefixOps.insert( LITERAL_INC );
        set_PrefixOps.insert( LITERAL_DEC );
        set_PrefixOps.insert( LITERAL_BANG );
        set_PrefixOps.insert( LITERAL_TILDE );
        set_PrefixOps.insert( LITERAL_ADD );
        set_PrefixOps.insert( LITERAL_SUB );

        set_PostfixOp.insert( LITERAL_INC );
        set_PostfixOp.insert( LITERAL_DEC );

        set_BasicTypes.insert( LITERAL_BYTE );
        set_BasicTypes.insert( LITERAL_SHORT );
        set_BasicTypes.insert( LITERAL_CHAR );
        set_BasicTypes.insert( LITERAL_INT );
        set_BasicTypes.insert( LITERAL_LONG );
        set_BasicTypes.insert( LITERAL_FLOAT );
        set_BasicTypes.insert( LITERAL_DOUBLE );
        set_BasicTypes.insert( LITERAL_BOOLEAN );

        set_Modifiers.insert( LITERAL_PUBLIC );
        set_Modifiers.insert( LITERAL_PROTECTED );
        set_Modifiers.insert( LITERAL_PRIVATE );
        set_Modifiers.insert( LITERAL_STATIC );
        set_Modifiers.insert( LITERAL_ABSTRACT );
        set_Modifiers.insert( LITERAL_FINAL );
        set_Modifiers.insert( LITERAL_NATIVE );
        set_Modifiers.insert( LITERAL_SYNCHRONIZED );
        set_Modifiers.insert( LITERAL_TRANSIENT );
        set_Modifiers.insert( LITERAL_VOLATILE );
        set_Modifiers.insert( LITERAL_STRICTFP );

        set_JavaKeywords.insert( LITERAL_ABSTRACT );
        set_JavaKeywords.insert( LITERAL_DOUBLE );
        set_JavaKeywords.insert( LITERAL_INT );
        set_JavaKeywords.insert( LITERAL_BOOLEAN );
        set_JavaKeywords.insert( LITERAL_ELSE );
        set_JavaKeywords.insert( LITERAL_INTERFACE );
        set_JavaKeywords.insert( LITERAL_SUPER );
        set_JavaKeywords.insert( LITERAL_BREAK );
        set_JavaKeywords.insert( LITERAL_EXTENDS );
        set_JavaKeywords.insert( LITERAL_LONG );
        set_JavaKeywords.insert( LITERAL_SWITCH );
        set_JavaKeywords.insert( LITERAL_BYTE );
        set_JavaKeywords.insert( LITERAL_FINAL );
        set_JavaKeywords.insert( LITERAL_NATIVE );
        set_JavaKeywords.insert( LITERAL_SYNCHRONIZED );
        set_JavaKeywords.insert( LITERAL_CASE );
        set_JavaKeywords.insert( LITERAL_FINALLY );
        set_JavaKeywords.insert( LITERAL_NEW );
        set_JavaKeywords.insert( LITERAL_THIS );
        set_JavaKeywords.insert( LITERAL_CATCH );
        set_JavaKeywords.insert( LITERAL_FLOAT );
        set_JavaKeywords.insert( LITERAL_PACKAGE );
        set_JavaKeywords.insert( LITERAL_THROW );
        set_JavaKeywords.insert( LITERAL_CHAR );
        set_JavaKeywords.insert( LITERAL_FOR );
        set_JavaKeywords.insert( LITERAL_PRIVATE );
        set_JavaKeywords.insert( LITERAL_THROWS );
        set_JavaKeywords.insert( LITERAL_CLASS );
        set_JavaKeywords.insert( LITERAL_PROTECTED );
        set_JavaKeywords.insert( LITERAL_TRANSIENT );
        set_JavaKeywords.insert( LITERAL_IF );
        set_JavaKeywords.insert( LITERAL_PUBLIC );
        set_JavaKeywords.insert( LITERAL_TRY );
        set_JavaKeywords.insert( LITERAL_CONTINUE );
        set_JavaKeywords.insert( LITERAL_IMPLEMENTS );
        set_JavaKeywords.insert( LITERAL_RETURN );
        set_JavaKeywords.insert( LITERAL_VOID );
        set_JavaKeywords.insert( LITERAL_DEFAULT );
        set_JavaKeywords.insert( LITERAL_IMPORT );
        set_JavaKeywords.insert( LITERAL_SHORT );
        set_JavaKeywords.insert( LITERAL_VOLATILE );
        set_JavaKeywords.insert( LITERAL_DO );
        set_JavaKeywords.insert( LITERAL_INSTANCEOF );
        set_JavaKeywords.insert( LITERAL_STATIC );
        set_JavaKeywords.insert( LITERAL_WHILE );
    }

    // Grammar rules
    
    size_t Identifier( substr_T& edge_ )
    {
        
        return (

            ( literal() - set_JavaKeywords )

            ).match( edge_ );
    }

    
    size_t QualifiedIdentifier( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            *(
                '.'
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
            )

            ).match( edge_ );
    }

    
    size_t Literal( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::CharacterLiteral )
            |
            CTTL_RULE( java_lexer< ParserT >::StringLiteral )
            |
            CTTL_RULE( java_lexer< ParserT >::BooleanLiteral )
            |
            CTTL_RULE( java_lexer< ParserT >::NullLiteral )
            |
            CTTL_RULE( java_lexer< ParserT >::FloatingPointLiteral )    
            |
            CTTL_RULE( java_lexer< ParserT >::IntegerLiteral )

            ).match( edge_ );
    }

    
    size_t Expression( substr_T& edge_ )
    {
        
        return (

            (
                CTTL_RULE( java_lexer< ParserT >::Expression1 )
                +
                *entity(
                    CTTL_RULE( java_lexer< ParserT >::AssignmentOperator )
                    +
                    CTTL_RULE( java_lexer< ParserT >::Expression1 )
                )
            )

            ).match( edge_ );
    }

    
    size_t AssignmentOperator( substr_T& edge_ )
    {
        
        return (

            &LITERAL_3GT_EQ
            |
            (
                '='
                ^
                -symbol( '=' )
            )
            |
            (
                ( symbol() ^ symbol() )
                &
                set_AssignmentOperators
            )
            |
            (
                ( symbol() ^ symbol() ^ symbol() )
                &
                set_AssignmentOperators
            )

            ).match( edge_ );
    }

    
    size_t Type( substr_T& edge_ )
    {
        
        return (

            (
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                *( '.' + CTTL_RULE( java_lexer< ParserT >::Identifier ) )
                +
                CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
                //ik-added: not a function call
                -
                '('
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::BasicType )
                +
                *CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
            )

            ).match( edge_ );
    }

    
    size_t StatementExpression( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Expression )

            ).match( edge_ );
    }

    
    size_t ConstantExpression( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Expression )

            ).match( edge_ );
    }

    
    size_t Expression1( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Expression2 )
            +
            entity( CTTL_RULE( java_lexer< ParserT >::Expression1Rest ) ) * 1

            ).match( edge_ );
    }

    
    size_t Expression1Rest( substr_T& edge_ )
    {
        
        return (

            entity(
                '?'
                +
                CTTL_RULE( java_lexer< ParserT >::Expression )
                +
                ':'
                +
                CTTL_RULE( java_lexer< ParserT >::Expression1 )
            ) * 1

            ).match( edge_ );
    }

    
    size_t Expression2( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Expression3 )
            +
            entity( CTTL_RULE( java_lexer< ParserT >::Expression2Rest ) ) * 1

            ).match( edge_ );
    }

    
    size_t Expression2Rest( substr_T& edge_ )
    {
        
        return (

            +(
                CTTL_RULE( java_lexer< ParserT >::Infixop )
                +
                CTTL_RULE( java_lexer< ParserT >::Expression3 )
                +
                *(
                    ( &LITERAL_INSTANCEOF & literal() )
                    +
                    CTTL_RULE( java_lexer< ParserT >::Type )
                )
            )
            |
            (
                ( &LITERAL_INSTANCEOF & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Type )
                +
                *CTTL_RULE( java_lexer< ParserT >::Expression2Rest )
            )

            ).match( edge_ );
    }

    
    size_t Infixop( substr_T& edge_ )
    {
        
        return (

            (
                &LITERAL_3GT
                ^
                -symbol( '=' )
            )
            |
            (
                ( symbol() ^ symbol() )
                &
                set_Infixops
            )
            |
            (
                symbol()
                &
                set_Infixops
            )

            ).match( edge_ );
    }

    
    size_t Expression3( substr_T& edge_ )
    {
        
        return (

            (
                CTTL_RULE( java_lexer< ParserT >::PrefixOp )
                +
                CTTL_RULE( java_lexer< ParserT >::Expression3 )
            )
            |
            (
                '('
                +
                (
                    CTTL_RULE( java_lexer< ParserT >::Type )
                    |
                    CTTL_RULE( java_lexer< ParserT >::Expression )
                )
                +
                ')'
                +
                entity( CTTL_RULE( java_lexer< ParserT >::Expression3 ) ) * 1
                +
                *(CTTL_RULE( java_lexer< ParserT >::Selector ))
                +
                *(CTTL_RULE( java_lexer< ParserT >::PostfixOp ))
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::Primary )
                +
                *(CTTL_RULE( java_lexer< ParserT >::Selector ))
                +
                *(CTTL_RULE( java_lexer< ParserT >::PostfixOp ))
            )

            ).match( edge_ );
    }

    
    size_t Primary( substr_T& edge_ )
    {
        
        return (

            ( '(' + CTTL_RULE( java_lexer< ParserT >::Expression ) + ')' )
            |
            ( ( &LITERAL_THIS & literal() ) + entity( CTTL_RULE( java_lexer< ParserT >::Arguments ) ) * 1 )
            |
            ( ( &LITERAL_SUPER & literal() ) + CTTL_RULE( java_lexer< ParserT >::SuperSuffix ) )
            |
            CTTL_RULE( java_lexer< ParserT >::Literal )
            |
            ( ( &LITERAL_NEW & literal() ) + CTTL_RULE( java_lexer< ParserT >::Creator ) )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                *( '.' + CTTL_RULE( java_lexer< ParserT >::Identifier ) )
                +
                entity( CTTL_RULE( java_lexer< ParserT >::IdentifierSuffix ) ) * 1
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::BasicType )
                +
                CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
                +
                '.'
                + ( &LITERAL_CLASS & literal() )
            )
            |
            ( ( &LITERAL_VOID & literal() ) + '.' + ( &LITERAL_CLASS & literal() ) )

            ).match( edge_ );
    }

    
    size_t IdentifierSuffix( substr_T& edge_ )
    {
        
        return (

            (
                symbol( '[' )
                +
                (
                    ( ']' + CTTL_RULE( java_lexer< ParserT >::BracketsOpt ) + '.' + ( &LITERAL_CLASS & literal() ) )
                    |
                    ( CTTL_RULE( java_lexer< ParserT >::Expression ) + ']' )
                )
            )
            |
            CTTL_RULE( java_lexer< ParserT >::Arguments )
            |
            (
                symbol( '.' )
                +
                (
                    ( &LITERAL_CLASS & literal() )
                    |
                    ( &LITERAL_THIS & literal() )
                    |
                    ( ( &LITERAL_SUPER & literal() ) + CTTL_RULE( java_lexer< ParserT >::Arguments ) )
                    |
                    ( ( &LITERAL_NEW & literal() ) + CTTL_RULE( java_lexer< ParserT >::InnerCreator ) )
                )
            )

            ).match( edge_ );
    }

    
    size_t PrefixOp( substr_T& edge_ )
    {
        
        return (

            (
                ( symbol() ^ symbol() )
                &
                set_PrefixOps
            )
            |
            (
                ( symbol() )
                &
                set_PrefixOps
            )
            

            ).match( edge_ );
    }

    
    size_t PostfixOp( substr_T& edge_ )
    {
        
        return (

            ( symbol() ^ symbol() )
            &
            set_PostfixOp

            ).match( edge_ );
    }

    
    size_t Selector( substr_T& edge_ )
    {
        
        return (

            (
                '.'
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                entity( CTTL_RULE( java_lexer< ParserT >::Arguments ) ) * 1
            )
            |
            ( '.' + ( &LITERAL_THIS & literal() ) )
            |
            ( '.' + ( &LITERAL_SUPER & literal() ) + CTTL_RULE( java_lexer< ParserT >::SuperSuffix ) )
            |
            ( '.' + ( &LITERAL_NEW & literal() ) + CTTL_RULE( java_lexer< ParserT >::InnerCreator ) )
            |
            ( '[' + CTTL_RULE( java_lexer< ParserT >::Expression ) + ']' )

            ).match( edge_ );
    }

    
    size_t SuperSuffix( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Arguments )
            |
            (
                '.'
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                entity( CTTL_RULE( java_lexer< ParserT >::Arguments ) ) * 1
            )

            ).match( edge_ );
    }

    
    size_t BasicType( substr_T& edge_ )
    {
        
        return (

            literal() & set_BasicTypes

            ).match( edge_ );
    }

    
    size_t ArgumentsOpt( substr_T& edge_ )
    {
        
        return (

            entity( CTTL_RULE( java_lexer< ParserT >::Arguments ) ) * 1

            ).match( edge_ );
    }

    
    size_t Arguments( substr_T& edge_ )
    {
        
        return (

            '('
            +
            entity(
                CTTL_RULE( java_lexer< ParserT >::Expression )
                +
                *( ',' + CTTL_RULE( java_lexer< ParserT >::Expression ) )
            ) * 1
            +
            ')'

            ).match( edge_ );
    }

    
    size_t BracketsOpt( substr_T& edge_ )
    {
        
        return (

            *( symbol( '[' ) + ']' )

            ).match( edge_ );
    }

    
    size_t Creator( substr_T& edge_ )
    {
        
        return (

            (
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifier )
                |
                CTTL_RULE( java_lexer< ParserT >::BasicType )   // ik-10/16/2003 added
            )
            +
            (
                CTTL_RULE( java_lexer< ParserT >::ArrayCreatorRest )
                |
                CTTL_RULE( java_lexer< ParserT >::ClassCreatorRest )
            )

            ).match( edge_ );
    }

    
    size_t InnerCreator( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::ClassCreatorRest )

            ).match( edge_ );
    }

    
    size_t ArrayCreatorRest( substr_T& edge_ )
    {
        
        return (

            '['
            +
            (
                (
                    ']'
                    +
                    CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
                    +
                    CTTL_RULE( java_lexer< ParserT >::ArrayInitializer )
                )
                |
                (
                    CTTL_RULE( java_lexer< ParserT >::Expression )
                    +
                    ']'
                    +
                    *(
                        '['
                        +
                        CTTL_RULE( java_lexer< ParserT >::Expression )
                        +
                        ']'
                    )
                    +
                    CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
                )
            )

            ).match( edge_ );
    }

    
    size_t ClassCreatorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Arguments )
            +
            entity( CTTL_RULE( java_lexer< ParserT >::ClassBody ) ) * 1

            ).match( edge_ );
    }

    
    size_t ArrayInitializer( substr_T& edge_ )
    {
        
        return (

            '{'
            +
            entity(
                CTTL_RULE( java_lexer< ParserT >::VariableInitializer )
                +
                *( ',' + CTTL_RULE( java_lexer< ParserT >::VariableInitializer ) )
                +
                ( symbol( ',' ) ) * 1
            ) * 1
            +
            '}'

            ).match( edge_ );
    }

    
    size_t VariableInitializer( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::ArrayInitializer )
            |
            CTTL_RULE( java_lexer< ParserT >::Expression )

            ).match( edge_ );
    }

    
    size_t ParExpression( substr_T& edge_ )
    {
        
        return (

            '(' + CTTL_RULE( java_lexer< ParserT >::Expression ) + ')'

            ).match( edge_ );
    }

    
    size_t Block( substr_T& edge_ )
    {
        
        return (

            '{' + CTTL_RULE( java_lexer< ParserT >::BlockStatements ) + '}'

            ).match( edge_ );
    }

    
    size_t BlockStatements( substr_T& edge_ )
    {
        
        return (

            *( CTTL_RULE( java_lexer< ParserT >::BlockStatement ) )

            ).match( edge_ );
    }

    
    size_t BlockStatement( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::LocalVariableDeclarationStatement )
            |
            CTTL_RULE( java_lexer< ParserT >::ClassOrInterfaceDeclaration )
            |
            (
                entity( CTTL_RULE( java_lexer< ParserT >::Identifier ) + ':' ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )

            ).match( edge_ );
    }

    
    size_t LocalVariableDeclarationStatement( substr_T& edge_ )
    {
        
        return (

            entity( &LITERAL_FINAL & literal() ) * 1
            +
            CTTL_RULE( java_lexer< ParserT >::Type )
            +
            CTTL_RULE( java_lexer< ParserT >::VariableDeclarators )
            +
            ';'

            ).match( edge_ );
    }

    
    size_t Statement( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Block )
            |
            (
                ( &LITERAL_IF & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::ParExpression )
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )
            |
            (
                ( &LITERAL_ELSE & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )
            |
            (
                ( &LITERAL_FOR & literal() )
                +
                '('
                +
                entity( CTTL_RULE( java_lexer< ParserT >::ForInit ) ) * 1
                +
                ';'
                +
                entity( CTTL_RULE( java_lexer< ParserT >::Expression ) ) * 1
                +
                ';'
                +
                entity( CTTL_RULE( java_lexer< ParserT >::ForUpdate ) ) * 1
                +
                ')'
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )
            |
            (
                ( &LITERAL_WHILE & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::ParExpression )
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )
            |
            (
                ( &LITERAL_DO & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
                +
                ( &LITERAL_WHILE & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::ParExpression )
                +
                ';'
            )
            |
            (
                ( &LITERAL_TRY & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Block )
                +
                (
                    entity( CTTL_RULE( java_lexer< ParserT >::Catches ) ) * 1
                    +
                    (
                        ( &LITERAL_FINALLY & literal() )
                        +
                        CTTL_RULE( java_lexer< ParserT >::Block )
                    ) * 1
                )
            )
            |
            (
                ( &LITERAL_SWITCH & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::ParExpression )
                +
                '{'
                +
                CTTL_RULE( java_lexer< ParserT >::SwitchBlockStatementGroups )
                +
                '}'
            )
            |
            (
                ( &LITERAL_SYNCHRONIZED & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::ParExpression )
                +
                CTTL_RULE( java_lexer< ParserT >::Block )
            )
            |
            (
                ( &LITERAL_RETURN & literal() )
                +
                entity( CTTL_RULE( java_lexer< ParserT >::Expression ) ) * 1
                +
                ';'
            )
            |
            ( ( &LITERAL_THROW & literal() ) + CTTL_RULE( java_lexer< ParserT >::Expression ) + ';' )
            |
            ( ( &LITERAL_BREAK & literal() ) + entity( CTTL_RULE( java_lexer< ParserT >::Identifier ) ) * 1 + ';' )
            |
            ( ( &LITERAL_CONTINUE & literal() ) + entity( CTTL_RULE( java_lexer< ParserT >::Identifier ) ) * 1 + ';' )
            |
            ';'
            |
            (
                CTTL_RULE( java_lexer< ParserT >::StatementExpression )
                +
                ';'
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                ':'
                +
                CTTL_RULE( java_lexer< ParserT >::Statement )
            )

            ).match( edge_ );
    }

    
    size_t Catches( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::CatchClause )
            +
            *( CTTL_RULE( java_lexer< ParserT >::CatchClause ) )

            ).match( edge_ );
    }

    
    size_t CatchClause( substr_T& edge_ )
    {
        
        return (

            ( &LITERAL_CATCH & literal() )
            +
            '('
            +
            CTTL_RULE( java_lexer< ParserT >::FormalParameter )
            +
            ')'
            +
            CTTL_RULE( java_lexer< ParserT >::Block )

            ).match( edge_ );
    }

    
    size_t SwitchBlockStatementGroups( substr_T& edge_ )
    {
        
        return (

            +( CTTL_RULE( java_lexer< ParserT >::SwitchBlockStatementGroup ) )

            ).match( edge_ );
    }

    
    size_t SwitchBlockStatementGroup( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::SwitchLabel )
            +
            CTTL_RULE( java_lexer< ParserT >::BlockStatements )

            ).match( edge_ );
    }

    
    size_t SwitchLabel( substr_T& edge_ )
    {
        
        return (

            ( ( &LITERAL_CASE & literal() ) + CTTL_RULE( java_lexer< ParserT >::ConstantExpression ) + ':' )
            |
            ( ( &LITERAL_DEFAULT & literal() ) + ':' )

            ).match( edge_ );
    }

    
    size_t MoreStatementExpressions( substr_T& edge_ )
    {
        
        return (

            *( ',' + CTTL_RULE( java_lexer< ParserT >::StatementExpression ) )

            ).match( edge_ );
    }

    
    size_t ForInit( substr_T& edge_ )
    {
        
        return (

            (
                entity( &LITERAL_FINAL & literal() ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::Type )
                +
                CTTL_RULE( java_lexer< ParserT >::VariableDeclarators )
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::StatementExpression )
                +
                CTTL_RULE( java_lexer< ParserT >::MoreStatementExpressions )
            )

            ).match( edge_ );
    }

    
    size_t ForUpdate( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::StatementExpression )
            +
            CTTL_RULE( java_lexer< ParserT >::MoreStatementExpressions )

            ).match( edge_ );
    }

    
    size_t ModifiersOpt( substr_T& edge_ )
    {
        
        return (

            *( CTTL_RULE( java_lexer< ParserT >::Modifier ) )

            ).match( edge_ );
    }

    
    size_t Modifier( substr_T& edge_ )
    {
        
        return (

            literal() & set_Modifiers

            ).match( edge_ );
    }

    
    size_t VariableDeclarators( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::VariableDeclarator )
            +
            *( ',' + CTTL_RULE( java_lexer< ParserT >::VariableDeclarator ) )

            ).match( edge_ );
    }

    
    size_t VariableDeclaratorsRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::VariableDeclaratorRest )
            +
            *( ',' + CTTL_RULE( java_lexer< ParserT >::VariableDeclarator ) )

            ).match( edge_ );
    }

    
    size_t ConstantDeclaratorsRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::ConstantDeclaratorRest )
            +
            *( ',' + CTTL_RULE( java_lexer< ParserT >::ConstantDeclarator ) )

            ).match( edge_ );
    }

    
    size_t VariableDeclarator( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::VariableDeclaratorRest )

            ).match( edge_ );
    }

    
    size_t ConstantDeclarator( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::ConstantDeclaratorRest )

            ).match( edge_ );
    }

    
    size_t VariableDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
            +
            entity(
                '='
                +
                CTTL_RULE( java_lexer< ParserT >::VariableInitializer )
            ) * 1

            ).match( edge_ );
    }

    
    size_t ConstantDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
            +
            '='
            +
            CTTL_RULE( java_lexer< ParserT >::VariableInitializer )

            ).match( edge_ );
    }

    
    size_t VariableDeclaratorId( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::BracketsOpt )

            ).match( edge_ );
    }

    
    size_t CompilationUnit( substr_T& edge_ )
    {
        //CTTL_TRACE_SILENT( true );
        
        return (

            entity(
                ( &LITERAL_PACKAGE & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifier )
                +
                ';'
            ) * 1
            +
            *( CTTL_RULE( java_lexer< ParserT >::ImportDeclaration ) )
            +
            *( CTTL_RULE( java_lexer< ParserT >::TypeDeclaration ) )
            +
            end()

            ).match( edge_ );
    }

    
    size_t ImportDeclaration( substr_T& edge_ )
    {
        //CTTL_TRACE_SILENT( false );
        
        return (

            ( &LITERAL_IMPORT & literal() )
            +
            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            *(
                '.'
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
            )
            +
            entity( symbol( '.' ) + '*' ) * 1 + ';'

            ).match( edge_ );
    }

    
    size_t TypeDeclaration( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::ClassOrInterfaceDeclaration )
            |
            ';'

            ).match( edge_ );
    }

    
    size_t ClassOrInterfaceDeclaration( substr_T& edge_ )
    {
        
        return (

            *CTTL_RULE( java_lexer< ParserT >::Modifier )
            +
            (
                CTTL_RULE( java_lexer< ParserT >::ClassDeclaration )
                |
                CTTL_RULE( java_lexer< ParserT >::InterfaceDeclaration )
            )

            ).match( edge_ );
    }

    
    size_t ClassDeclaration( substr_T& edge_ )
    {
        
        return (

            ( &LITERAL_CLASS & literal() )
            +
            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            entity(
                ( &LITERAL_EXTENDS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Type )
            ) * 1
            +
            entity(
                ( &LITERAL_IMPLEMENTS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::TypeList )
            ) * 1
            +
            CTTL_RULE( java_lexer< ParserT >::ClassBody )

            ).match( edge_ );
    }

    
    size_t InterfaceDeclaration( substr_T& edge_ )
    {
        
        return (

            ( &LITERAL_INTERFACE & literal() )
            +
            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            entity(
                ( &LITERAL_EXTENDS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::TypeList )
            ) * 1
            +
            CTTL_RULE( java_lexer< ParserT >::InterfaceBody )

            ).match( edge_ );
    }

    
    size_t TypeList( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Type )
            +
            *( ',' + CTTL_RULE( java_lexer< ParserT >::Type ) )

            ).match( edge_ );
    }

    
    size_t ClassBody( substr_T& edge_ )
    {
        
        return (

            '{' + *( CTTL_RULE( java_lexer< ParserT >::ClassBodyDeclaration ) ) + '}'

            ).match( edge_ );
    }

    
    size_t InterfaceBody( substr_T& edge_ )
    {
        
        return (

            '{' + *( CTTL_RULE( java_lexer< ParserT >::InterfaceBodyDeclaration ) ) + '}'

            ).match( edge_ );
    }

    
    size_t ClassBodyDeclaration( substr_T& edge_ )
    {
        
        return (

            ';'
            |
            (
                entity( &LITERAL_STATIC & literal() ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::Block )
            )
            |
            (
                *CTTL_RULE( java_lexer< ParserT >::Modifier )
                +
                CTTL_RULE( java_lexer< ParserT >::MemberDecl )
            )

            ).match( edge_ );
    }

    
    size_t MemberDecl( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::MethodOrFieldDecl )
            |
            (
                ( &LITERAL_VOID & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                CTTL_RULE( java_lexer< ParserT >::MethodDeclaratorRest )
            )
            |
            (
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                CTTL_RULE( java_lexer< ParserT >::ConstructorDeclaratorRest )
            )
            |
            CTTL_RULE( java_lexer< ParserT >::ClassOrInterfaceDeclaration )

            ).match( edge_ );
    }

    
    size_t MethodOrFieldDecl( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Type )
            +
            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::MethodOrFieldRest )

            ).match( edge_ );
    }

    
    size_t MethodOrFieldRest( substr_T& edge_ )
    {
        
        return (

            entity( CTTL_RULE( java_lexer< ParserT >::VariableDeclaratorsRest ) )
            |
            CTTL_RULE( java_lexer< ParserT >::MethodDeclaratorRest )
            |
            true

            ).match( edge_ );
    }

    
    size_t InterfaceBodyDeclaration( substr_T& edge_ )
    {
        
        return (

            ';'
            |
            (
                *CTTL_RULE( java_lexer< ParserT >::Modifier )
                +
                CTTL_RULE( java_lexer< ParserT >::InterfaceMemberDecl )
            )

            ).match( edge_ );
    }

    
    size_t InterfaceMemberDecl( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::InterfaceMethodOrFieldDecl )
            |
            (
                ( &LITERAL_VOID & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::Identifier )
                +
                CTTL_RULE( java_lexer< ParserT >::VoidInterfaceMethodDeclaratorRest )
            )
            |
            CTTL_RULE( java_lexer< ParserT >::ClassOrInterfaceDeclaration )

            ).match( edge_ );
    }

    
    size_t InterfaceMethodOrFieldDecl( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Type )
            +
            CTTL_RULE( java_lexer< ParserT >::Identifier )
            +
            CTTL_RULE( java_lexer< ParserT >::InterfaceMethodOrFieldRest )

            ).match( edge_ );
    }

    
    size_t InterfaceMethodOrFieldRest( substr_T& edge_ )
    {
        
        return (

            ( CTTL_RULE( java_lexer< ParserT >::ConstantDeclaratorsRest ) + ';' )
            |
            CTTL_RULE( java_lexer< ParserT >::InterfaceMethodDeclaratorRest )

            ).match( edge_ );
    }

    
    size_t MethodDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::FormalParameters )
            +
            CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
            +
            entity(
                ( &LITERAL_THROWS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifierList )
            ) * 1
            +
            (
                CTTL_RULE( java_lexer< ParserT >::MethodBody )
                |
                ';'
            )

            ).match( edge_ );
    }

    
    size_t VoidMethodDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::FormalParameters )
            +
            entity(
                ( &LITERAL_THROWS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifierList )
            ) * 1
            +
            (
                CTTL_RULE( java_lexer< ParserT >::MethodBody )
                |
                ';'
            )

            ).match( edge_ );
    }

    
    size_t InterfaceMethodDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::FormalParameters )
            +
            CTTL_RULE( java_lexer< ParserT >::BracketsOpt )
            +
            entity(
                ( &LITERAL_THROWS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifierList )
            ) * 1
            +
            ';'

            ).match( edge_ );
    }

    
    size_t VoidInterfaceMethodDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::FormalParameters )
            +
            entity(
                ( &LITERAL_THROWS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifierList )
            ) * 1
            +
            ';'

            ).match( edge_ );
    }

    
    size_t ConstructorDeclaratorRest( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::FormalParameters )
            +
            entity(
                ( &LITERAL_THROWS & literal() )
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifierList )
            ) * 1
            +
            CTTL_RULE( java_lexer< ParserT >::MethodBody )

            ).match( edge_ );
    }

    
    size_t QualifiedIdentifierList( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifier )
            +
            *(
                ','
                +
                CTTL_RULE( java_lexer< ParserT >::QualifiedIdentifier )
            )

            ).match( edge_ );
    }

    
    size_t FormalParameters( substr_T& edge_ )
    {
        
        return (

            '('
            +
            entity(
                CTTL_RULE( java_lexer< ParserT >::FormalParameter )
                +
                *( ',' + CTTL_RULE( java_lexer< ParserT >::FormalParameter ) )
            ) * 1
            +
            ')'

            ).match( edge_ );
    }

    
    size_t FormalParameter( substr_T& edge_ )
    {
        
        return (

            entity( &LITERAL_FINAL & literal() ) * 1
            +
            CTTL_RULE( java_lexer< ParserT >::Type )
            +
            CTTL_RULE( java_lexer< ParserT >::VariableDeclaratorId )

            ).match( edge_ );
    }

    
    size_t MethodBody( substr_T& edge_ )
    {
        
        return (

            CTTL_RULE( java_lexer< ParserT >::Block )

            ).match( edge_ );
    }

    // The folllowing Token-level definitions were taken from
    // http://www.cs.uiowa.edu/~fleck/JavaBNF.htm
    
    size_t IntegerLiteral( substr_T& edge_ )
    {
        
        return (

            (
                (
                    symbol( '0' )
                    ^
                    ( symbol( 'x' ) | 'X' )
                    ^
                    entity( isxdigit )
                )
                |
                // simplified: this is either <decimal integer literal> or <octal numeral>,
                // are defined as zero followed by octal digits:
                entity( isdigit )
            )
            +
            entity( symbol( 'l' ) | 'L' ) * 1

            ).match( edge_ );
    }

    
    
    size_t FloatingPointLiteral( substr_T& edge_ )
    {
        
        return (
            (
                entity( isdigit )
                +
                symbol( '.' )
                +
                entity( isdigit ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::FloatingPointExponentPart ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::FloatTypeSuffix ) * 1
            )
            |
            (
                '.'
                +
                entity( isdigit )
                +
                CTTL_RULE( java_lexer< ParserT >::FloatingPointExponentPart ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::FloatTypeSuffix ) * 1
            )
            |
            (
                entity( isdigit )
                +
                CTTL_RULE( java_lexer< ParserT >::FloatingPointExponentPart )
                +
                CTTL_RULE( java_lexer< ParserT >::FloatTypeSuffix ) * 1
            )
            |
            (
                entity( isdigit )
                +
                CTTL_RULE( java_lexer< ParserT >::FloatingPointExponentPart ) * 1
                +
                CTTL_RULE( java_lexer< ParserT >::FloatTypeSuffix )
            )

            ).match( edge_ );
    }

    
    size_t FloatingPointExponentPart( substr_T& edge_ )
    {
        
        return (

            ( symbol( 'e' ) | 'E' )
            +
            ( symbol( '-' ) ) * 1
            +
            entity( isdigit )

            ).match( edge_ );
    }

    
    size_t FloatTypeSuffix( substr_T& edge_ )
    {
        
        return (

            symbol( 'f' ) | 'F' | 'd' | 'D'

            ).match( edge_ );
    }

    
    size_t CharacterLiteral( substr_T& edge_ )
    {
        
        return (

            c_single_quote()

            ).match( edge_ );
    }

    
    size_t StringLiteral( substr_T& edge_ )
    {
        
        return (

            c_double_quote()

            ).match( edge_ );
    }

    
    size_t BooleanLiteral( substr_T& edge_ )
    {
        
        return (

            (
                symbol( &LITERAL_TRUE )
                |
                &LITERAL_FALSE
            )
            &
            literal()

            ).match( edge_ );
    }

    
    size_t NullLiteral( substr_T& edge_ )
    {
        
        return (

            ( &LITERAL_NULL & literal() )

            ).match( edge_ );
    }

};  // struct java_lexer

#endif //_CTTL_JAVA_LEXER_H_INCLUDED_
