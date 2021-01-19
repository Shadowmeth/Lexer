#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <cstring>

#define FEOF 256
#define IDENTIFIER 257
#define INTEGER 258
#define ERRONEOUS 259

#define is_end_of_input(ch)    ((ch) == '\0')
#define is_layout(ch)          (!is_end_of_input(ch) && (ch) <= ' ')
#define is_comment_starter(ch)   ((ch) == '#')
#define is_comment_stopper(ch) ((ch) == '#' || (ch) == '\n')

#define is_uc_letter(ch)       ((ch) >= 'A' && (ch) <= 'Z')
#define is_lc_letter(ch)       ((ch) >= 'a' && (ch) <= 'z')
#define is_letter(ch)          (is_uc_letter(ch) || is_lc_letter(ch))
#define is_digit(ch)           ((ch) >= '0' && (ch) <= '9')
#define is_letter_or_digit(ch) (is_letter(ch) || is_digit(ch))
#define is_underscore(ch)      ((ch) == '_')

#define is_operator(ch)        (std::strchr("+-*/", (ch)) != 0)
#define is_separator(ch)       (std::strchr(" ;,(){}", (ch)) != 0)

struct PositionInFile {
    std::string file_name;
    int line_number;
    int char_number;
};

struct TokenType {
    int token_class;
    std::string repr;
    PositionInFile pos;
};

class Lexer
{
private:
    TokenType Token;
    std::string input;
    int dot; // dot position in input -- think cursor
    int input_char; // character at dot
    
public:
    Lexer(const std::string& source);
    std::string get_token_repr(void) const { return Token.repr; }
    int get_token_class(void) const { return Token.token_class; }
    void next_char(void) { input_char = input[++dot]; }
    void start_lex(void);
    void get_next_token(void);
    void skip_layout_and_comment(void);
    void recognize_identifier(void);
    void recognize_integer(void);
    
    
};

#endif
