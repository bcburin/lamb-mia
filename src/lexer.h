#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

enum class TokenType {
    IF,
    THEN,
    ELSE,
    LET,
    LPAREN,         // (
    RPAREN,         // )
    LBRACKET,       // [
    RBRACKET,       // ]
    COLON,          // :
    COMMA,          // ,
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
    std::string _token_str;

   public:
    using TokenValue = std::variant<std::string, char, int, float>;

    Token(TokenType type, const std::string& token_str);

    virtual ~Token() = default;

    TokenType get_type() const;

    std::string get_string() const;

    virtual TokenValue get_value() const { return get_string(); }
};

class IdVarToken : public Token {
   public:
    IdVarToken(const std::string& token_str);

    TokenValue get_value() const override;
};

class IdLambdaVarToken : public Token {
   public:
    IdLambdaVarToken(const std::string& token_str);

    TokenValue get_value() const override;
};

class CharacterToken : public Token {
   public:
    CharacterToken(const std::string& token_str);

    TokenValue get_value() const override;
};

class IntegerToken : public Token {
   public:
    IntegerToken(const std::string& token_str);

    TokenValue get_value() const override;
};

class FloatToken : public Token {
   public:
    FloatToken(const std::string& token_str);

    TokenValue get_value() const override;
};

class Lexer {
   private:
    static const std::unordered_map<std::string, TokenType> keywords;
    std::string input;
    size_t pos;
    std::shared_ptr<Token> current_token;

    char peek() const;

    char advance();

    void skip_whitespace();

    std::shared_ptr<Token> create_token(TokenType type, const std::string& str);

   public:
    Lexer(const std::string& input);

    std::shared_ptr<Token> next_token();
};

#endif  // LEXER_H
