#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <memory>
#include <string>
#include <unordered_map>

enum class TokenType {
    IF,
    THEN,
    ELSE,
    LET,
    IN,
    LPAREN,         // (
    RPAREN,         // )
    LBRACKET,       // [
    RBRACKET,       // ]
    COLON,          // :
    COMMA,          // ,
    DOT,            // .
    SEMI_COLON,     // ;
    BACK_SLASH,     //
    EQ_SIGN,        // =
    EOF_TOK,        // End of file
    ID_VAR,         // <id-var>
    ID_LAMBDA_VAR,  // <id-lambda-var>
    CHARACTER,      // <character>
    INTEGER,        // <integer>
    FLOAT           // <float>
};

class Token {
   protected:
    TokenType _type;
    std::string _str;

   public:
    Token(TokenType type, const std::string& token_str);

    TokenType get_type() const { return _type; };

    std::string get_string() const { return _str; };
};

class Lexer {
   private:
    static const std::unordered_map<std::string, TokenType> keywords;
    std::string input;
    size_t pos;

    char peek() const;

    char advance();

    void skip_whitespace();

    std::shared_ptr<Token> create_token(TokenType type, const std::string& str);

   public:
    Lexer(const std::string& input);

    std::shared_ptr<Token> next_token();
};

#endif  // LEXER_H
