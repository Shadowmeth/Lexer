#include <iostream>
#include "Lexer.h"

int main()
{
    Lexer l{"#*# 8; ##abc__dd_8;zz_#/"};
    l.start_lex();

    do {
	l.get_next_token();
	switch (l.get_token_class()) {
	case IDENTIFIER: std::cout << "Identifier: "; break;
	case INTEGER: std::cout << "Integer: "; break;
	case ERRONEOUS: std::cout << "Erroneous Token: "; break;
	case FEOF: std::cout << "End of File Token: "; break;
        default:
	    std::cout << "Operator or Separator: "; break;

	}
	std::cout << l.get_token_repr() << std::endl;

    } while(l.get_token_class() != FEOF);
    
}

