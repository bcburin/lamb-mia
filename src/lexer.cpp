#include "lexer.h"

#include <stdexcept>

Token::Token(TokenType type, const std::string& token_str)
    : _type(type), _token_str(token_str) {}

TokenType Token::get_type() const { return _type; }

std::string Token::get_string() const { return _token_str; }

IdVarToken::IdVarToken(const std::string& token_str)
    : Token(TokenType::ID_VAR, token_str) {}

Token::TokenValue IdVarToken::get_value() const { return _token_str; }

IdLambdaVarToken::IdLambdaVarToken(const std::string& token_str)
    : Token(TokenType::ID_LAMBDA_VAR, token_str) {}

Token::TokenValue IdLambdaVarToken::get_value() const { return _token_str; }

CharacterToken::CharacterToken(const std::string& token_str)
    : Token(TokenType::CHARACTER, token_str) {}

Token::TokenValue CharacterToken::get_value() const { return _token_str[0]; }

IntegerToken::IntegerToken(const std::string& token_str)
    : Token(TokenType::INTEGER, token_str) {}

Token::TokenValue IntegerToken::get_value() const {
    return std::stoi(_token_str);
}

FloatToken::FloatToken(const std::string& token_str)
    : Token(TokenType::FLOAT, token_str) {}

Token::TokenValue FloatToken::get_value() const {
    return std::stof(_token_str);
}

Lexer::Lexer(const std::string& input)
    : input(input), pos(0), current_token(nullptr) {}

char Lexer::peek() const { return pos < input.size() ? input[pos] : '\0'; }

char Lexer::advance() { return pos < input.size() ? input[pos++] : '\0'; }

void Lexer::skip_whitespace() {
    while (std::isspace(peek())) {
        advance();
    }
}

std::shared_ptr<Token> Lexer::create_token(TokenType type,
                                           const std::string& str) {
    switch (type) {
        case TokenType::ID_VAR:
            return std::make_shared<IdVarToken>(str);
        case TokenType::ID_LAMBDA_VAR:
            return std::make_shared<IdLambdaVarToken>(str);
        case TokenType::CHARACTER:
            return std::make_shared<CharacterToken>(str);
        case TokenType::INTEGER:
            return std::make_shared<IntegerToken>(str);
        case TokenType::FLOAT:
            return std::make_shared<FloatToken>(str);
        default:
            return std::make_shared<Token>(type, str);
    }
}

std::shared_ptr<Token> Lexer::next_token() {
    skip_whitespace();

    if (pos >= input.size()) {
        current_token = std::make_shared<Token>(TokenType::EOF_TOK, "");
        return current_token;
    }

    char current_char = peek();

    // Recognizing single-character tokens
    switch (current_char) {
        case '(':
            advance();
            return create_token(TokenType::LPAREN, "(");
        case ')':
            advance();
            return create_token(TokenType::RPAREN, ")");
        case '[':
            advance();
            return create_token(TokenType::LBRACKET, "[");
        case ']':
            advance();
            return create_token(TokenType::RBRACKET, "]");
        case ':':
            advance();
            return create_token(TokenType::COLON, ":");
        case ',':
            advance();
            return create_token(TokenType::COMMA, ",");
    }

    // Keywords and Identifiers
    if (std::isalpha(current_char)) {
        std::string id;
        id += advance();
        while (std::isalnum(peek()) || peek() == '_') {
            id += advance();
        }

        // Check if the identifier is a keyword
        auto it = keywords.find(id);
        if (it != keywords.end()) {
            return create_token(it->second, id);
        }

        if (std::isupper(id[0])) {
            return create_token(TokenType::ID_LAMBDA_VAR, id);
        } else {
            return create_token(TokenType::ID_VAR, id);
        }
    }

    // Number literals
    if (std::isdigit(current_char) || current_char == '-') {
        std::string number;
        number += advance();
        while (std::isdigit(peek()) || peek() == '.') {
            number += advance();
        }

        if (number.find('.') != std::string::npos) {
            return create_token(TokenType::FLOAT, number);
        } else {
            return create_token(TokenType::INTEGER, number);
        }
    }

    // Character literals
    if (current_char == '\'') {
        advance();  // skip the opening quote
        char ch = advance();
        advance();  // skip the closing quote
        return create_token(TokenType::CHARACTER, std::string(1, ch));
    }

    throw std::runtime_error("Unknown token encountered");
}

std::shared_ptr<Token> Lexer::get_token() const { return current_token; }

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE}};
