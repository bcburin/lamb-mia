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
        TokenType type = tokens[i]->get_type();
        TokenType expected = expected_tokens[i];
        assert(type == expected && "Token type mismatch.");
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

    // Test 5: Testing other terminal symbols
    std::string input5 = R"(LVar1 = \x y.(LVar2 x (LVar3 y) \z.z);)";
    std::vector<TokenType> expected_tokens5 = {
        TokenType::ID_LAMBDA_VAR, TokenType::EQ_SIGN,
        TokenType::BACK_SLASH,    TokenType::ID_VAR,
        TokenType::ID_VAR,        TokenType::DOT,
        TokenType::LPAREN,        TokenType::ID_LAMBDA_VAR,
        TokenType::ID_VAR,        TokenType::LPAREN,
        TokenType::ID_LAMBDA_VAR, TokenType::ID_VAR,
        TokenType::RPAREN,        TokenType::BACK_SLASH,
        TokenType::ID_VAR,        TokenType::DOT,
        TokenType::ID_VAR,        TokenType::RPAREN,
        TokenType::SEMI_COLON,    TokenType::EOF_TOK};
    test_lexer(input5, expected_tokens5);

    // Test 6: Testing let expression
    std::string input6 =
        R"(F = \f l. let T = Tail l in if IsEmpty l then l else f (Head l) : T;)";
    std::vector<TokenType> expected_tokens6 = {
        TokenType::ID_LAMBDA_VAR,
        TokenType::EQ_SIGN,
        TokenType::BACK_SLASH,
        TokenType::ID_VAR,
        TokenType::ID_VAR,
        TokenType::DOT,
        TokenType::LET,
        TokenType::ID_LAMBDA_VAR,
        TokenType::EQ_SIGN,
        TokenType::ID_LAMBDA_VAR,
        TokenType::ID_VAR,
        TokenType::IN,
        TokenType::IF,
        TokenType::ID_LAMBDA_VAR,
        TokenType::ID_VAR,
        TokenType::THEN,
        TokenType::ID_VAR,
        TokenType::ELSE,
        TokenType::ID_VAR,
        TokenType::LPAREN,
        TokenType::ID_LAMBDA_VAR,
        TokenType::ID_VAR,
        TokenType::RPAREN,
        TokenType::COLON,
        TokenType::ID_LAMBDA_VAR,
        TokenType::SEMI_COLON,
        TokenType::EOF_TOK,
    };
    test_lexer(input6, expected_tokens6);

    return 0;
}
