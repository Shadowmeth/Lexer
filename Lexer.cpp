#include "Lexer.h"

Lexer::Lexer(const std::string& source)
{
    input = source;
}


void Lexer::start_lex(void)
{
    dot = 0; input_char = input[dot];
}

void Lexer::get_next_token(void)
{
    int start_dot;
    skip_layout_and_comment();
    // note_token_position();
    
    // split on first character of token
    start_dot = dot;
    if (is_end_of_input(input_char)) {
	Token.token_class = FEOF; Token.repr = "<EOF>"; return;
    }
    
    if (is_letter(input_char)) {
	recognize_identifier();
    } else if (is_digit(input_char)) {
	recognize_integer();
    } else if (is_operator(input_char) || is_separator(input_char)) {
	Token.token_class = input_char; next_char();
    } else {
	Token.token_class = ERRONEOUS; next_char();
    }

    // save the string token representation
    Token.repr = input.substr(start_dot, dot - start_dot);
}

void Lexer::skip_layout_and_comment(void)
{
    while (is_layout(input_char)) {
	next_char();
    }

    while (is_comment_starter(input_char)) {
	next_char();
	while (!is_comment_stopper(input_char)) {
	    if (is_end_of_input(input_char)) return;
	    next_char();
	}

	next_char();
	while (is_layout(input_char)) {
	    next_char();
	}
    }
}

void Lexer::recognize_identifier(void)
{
    Token.token_class = IDENTIFIER;
    next_char();

    while (is_letter_or_digit(input_char)) { next_char(); }

    while (is_underscore(input_char) && is_letter_or_digit(input[dot + 1])) {
	next_char();
	while (is_letter_or_digit(input_char)) { next_char(); }
    }

}

void Lexer::recognize_integer(void)
{
    Token.token_class = INTEGER; next_char();
    while (is_digit(input_char)) { next_char(); }

}

