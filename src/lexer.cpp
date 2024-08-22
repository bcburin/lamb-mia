#include "lexer.h"

#include <stdexcept>

Token::Token(TokenType type, const std::string& token_str)
    : _type(type), _str(token_str) {}

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

char Lexer::peek() const { return pos < input.size() ? input[pos] : '\0'; }

char Lexer::advance() { return pos < input.size() ? input[pos++] : '\0'; }

void Lexer::skip_whitespace() {
    while (std::isspace(peek())) {
        advance();
    }
}

std::shared_ptr<Token> Lexer::create_token(TokenType type,
                                           const std::string& str) {
    return std::make_shared<Token>(type, str);
}

std::shared_ptr<Token> Lexer::next_token() {
    skip_whitespace();

    if (pos >= input.size()) {
        return create_token(TokenType::EOF_TOK, "");
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

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE},
    {"let", TokenType::LET},
};
