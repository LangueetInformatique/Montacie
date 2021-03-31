// make_translator_demo.cpp
// Program demonstrates usage of make_translator()
// helper function.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename TranslatorT >
typename TranslatorT::value_T auto_Cpp0X( TranslatorT translator_, char const* value_ )
{
    translator_.push( value_ );
    return translator_.top();
}

int main(/*int argc, char* argv[]*/)
{
    cttl::lambda< int >::scalar var = 1234;
    assert( var.top() == 1234 );

    // Under C++0x a standalone translator can be instantiated:
    //   auto atoi_translator = make_translator( var, atoi );
    // For now, using a surrogate function auto_Cpp0X()
    // to demo the make_translator() helper:

    auto_Cpp0X( make_translator( var, atoi ), "5678" );
    assert( var.top() == 1234 ); // var remains unchanged, because make_translator()
                                 // creates and retains a copy of var scalar.

    auto_Cpp0X( make_translator( var.make_reference(), atoi ), "9999" );
    assert( var.top() == 9999 ); // var now changes, because this time make_translator()
                                 // captures a copy of the reference-scalar.

    auto_Cpp0X( var^atoi, "8888" );
    assert( var.top() == 8888 ); // var changes again, because operator^()
                                 // retains a reference-scalar that refers to var.

    return 0;
}
