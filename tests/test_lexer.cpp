#include <cassert>
#include <iostream>
#include <vector>

#include "../src/lexer.h"

void test_lexer(const std::string& input,
                const std::vector<TokenType>& expected_tokens) {
    Lexer lexer(input);
    std::vector<std::shared_ptr<Token>> tokens;

    std::shared_ptr<Token> token;
    while ((token = lexer.next_token())->get_type() != TokenType::EOF_TOK) {
        tokens.push_back(token);
    }

    // Add EOF token to the tokens list
    tokens.push_back(token);

    assert(tokens.size() == expected_tokens.size() &&
           "Mismatch in the number of tokens.");

    for (size_t i = 0; i < tokens.size(); ++i) {
        assert(tokens[i]->get_type() == expected_tokens[i] &&
               "Token type mismatch.");
    }

    std::cout << "All tests passed for input: " << input << std::endl;
}

int main() {
    // Test 1: Simple keyword and identifier test
    std::string input1 = "if then else X y 123 45.67 'c'";
    std::vector<TokenType> expected_tokens1 = {
        TokenType::IF,     TokenType::THEN,
        TokenType::ELSE,   TokenType::ID_LAMBDA_VAR,
        TokenType::ID_VAR, TokenType::INTEGER,
        TokenType::FLOAT,  TokenType::CHARACTER,
        TokenType::EOF_TOK};
    test_lexer(input1, expected_tokens1);

    // Test 2: Parentheses, brackets, and colon
    std::string input2 = "( ) [ ] :";
    std::vector<TokenType> expected_tokens2 = {
        TokenType::LPAREN,   TokenType::RPAREN, TokenType::LBRACKET,
        TokenType::RBRACKET, TokenType::COLON,  TokenType::EOF_TOK};
    test_lexer(input2, expected_tokens2);

    // Test 3: Mixed input with identifiers and literals
    std::string input3 = "if X [123, 45.67, 'a']";
    std::vector<TokenType> expected_tokens3 = {
        TokenType::IF,      TokenType::ID_LAMBDA_VAR, TokenType::LBRACKET,
        TokenType::INTEGER, TokenType::COMMA,         TokenType::FLOAT,
        TokenType::COMMA,   TokenType::CHARACTER,     TokenType::RBRACKET,
        TokenType::EOF_TOK};
    test_lexer(input3, expected_tokens3);

    // Test 4: Testing edge cases - empty input
    std::string input4 = "";
    std::vector<TokenType> expected_tokens4 = {TokenType::EOF_TOK};
    test_lexer(input4, expected_tokens4);

    return 0;
}
