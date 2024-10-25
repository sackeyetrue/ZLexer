#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>

// would be using ( std::string ) instead of std::string
// would be using ( "\n" ) instead of std::endl

using std::string;

namespace ZS
{

    class Token
    {
    public:
        std::string type; // The token type.

        std::string value; // The string value of token.

        /**
         *  @brief Token.
         *  @param  type Type of Token.
         */
        Token(std::string type) : type(type) { /* std::cout << type << " "; */ };

        /**
         *  @brief   Token.
         *  @param  type Type of Token.
         *  @param  value String Value of Token.
         */
        Token(std::string type, std::string value)
            : type(type), value(value) {
              };

        ~Token() {};
    };

    ///////////////////////////
    // ↓ Main Token Types ↓  //
    ///////////////////////////

    class Char : public Token
    {
    public:
        // Char Token
        Char(std::string value)
            : Token("CHAR", value) {};
    };

    class String : public Token
    {
    public:
        // String Token
        String(std::string value)
            : Token("STR", value) {};
    };

    class Symbol : public Token
    {
    public:
        // Inavlid Token
        Symbol(std::string value)
            : Token("SYM", value) {};
    };

    class Operator : public Token
    {
    public:
        // Operator Token
        Operator(std::string value)
            : Token("OP", value) {};
    };

    class Keyword : public Token
    {
    public:
        // Keyword Token
        Keyword(std::string value)
            : Token("KEY", value) {};
    };

    class Identifier : public Token
    {
    public:
        // Identifier Token
        Identifier(std::string value)
            : Token("ID", value) {};
    };

    class Comment : public Token
    {
    public:
        // Comment Token
        Comment(std::string value)
            : Token("COM", value) {};
    };

    class Invalid : public Token
    {
    public:
        // Inavlid Token
        Invalid(std::string value)
            : Token("IVD", value) {};
    };

    /////////////////////////////
    // ↓ Number Token Types ↓  //
    /////////////////////////////

    class Integer : public Token
    {
    public:
        // Integer Token
        Integer(std::string value)
            : Token("INT", value) {};
    };

    class Float : public Token
    {
    public:
        // Float Token
        Float(std::string value)
            : Token("FLT", value) {};
    };

    class Hexidecimal : public Token
    {
    public:
        // Hex Number Token
        Hexidecimal(std::string value)
            : Token("HEX", value) {};
    };

    class Binary : public Token
    {
    public:
        // Binary Number Token
        Binary(std::string value)
            : Token("BIN", value) {};
    };

    class Octal : public Token
    {
    public:
        // Octal Number Token
        Octal(std::string value)
            : Token("OCT", value) {};
    };

    class Exponent : public Token
    {
    public:
        // Exponent Number Token
        Exponent(std::string value)
            : Token("EXP", value) {};
    };

    class Imaginary : public Token
    {
    public:
        // Imaginary Number Token
        Imaginary(std::string value)
            : Token("IMG", value) {};
    };

    class FloatImg : public Token
    {
    public:
        // Floating Imaginary Number Token
        FloatImg(std::string value)
            : Token("FIMG", value) {};
    };

    //////////////////////////////
    // ↓ Special Token Types ↓  //
    //////////////////////////////

    class EndOfFile : public Token
    {
    public:
        // EndOfFile Token
        EndOfFile()
            : Token("EOF") {};
    };

    class EndOfLine : public Token
    {
    public:
        // EndOfLine Token
        EndOfLine()
            : Token("EOL") {};
    };

    class Dedent : public Token
    {
    public:
        // Dedent Token
        Dedent()
            : Token("DND") {};
    };

    class Indent : public Token
    {
    public:
        // Indent Token
        Indent()
            : Token("IND") {};
    };

};

////////////////////////////
// ↓ Token << Operator ↓  //
////////////////////////////

std::ostream &operator<<(std::ostream &ostream, ZS::Token &token)
{
    if (token.value == "")
        // ostream << "\n{ T: " << token.type << " }" << std::endl;
        ostream << token.type << std::endl;

    else
        ostream << token.type << ":" << token.value << " ";
    // ostream << "{ T:" << token.type << " ,  V:" << token.value << " ,  L:" << token.line << " , S:" << token.start_pos << " , E:" << token.end_pos << " } ";
    return ostream;
};

std::ostream &operator<<(std::ostream &ostream, std::vector<ZS::Token *> tokens)
{
    for (auto token : tokens)
    {
        ostream << *token;
    }
    return ostream;
};

namespace ZS
{
    /////////////////////////////////////
    // ↓ ZSCRIPT SUPORTED CHARATERS ↓  //
    /////////////////////////////////////

    // TODO: change to regex
    // TODO: work without whitespace

    const std::string digits = "0123456789";
    const std::string basedigits = digits + "ABCDEF" + "boxie";
    const std::string uppercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string lowercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string letters = uppercase + lowercase + "_";
    const std::string _operators = "+=/<>!%*-=";
    const std::string symbol = "+_=/:<>!%*-=,;$&`@.#|~_\"'";

    const std::string name = letters + digits;
    const std::string comment = name + " " + symbol;
    const std::string strings = comment + symbol;
    const std::string invalids = name + symbol;

    const std::vector<std::string> specials = {
        "\t",
        "\0",
        "\n",
        "\b",
        "\r",
        "\f",
        "EOL",
        "EOF",
    };

    ////////////////////////////
    // ↓ ZSCRIPT SYMBOLS ↓    //
    ////////////////////////////

    const std::vector<std::string> operators = {
        // ↓ basic arithmetics ↓  //
        "+",
        "-",
        "/",
        "*",
        "%",
        "^",
        // ↓ complex arithmetics ↓  //
        "+=",
        "++",
        "-=",
        "--",
        "*=",
        "**",
        "/=",
        // ↓ comparisions ↓  //
        ">",
        "<",
        "=",
        // ↓ complex comparisions ↓  //
        ">=",
        "<=",
        "==",
        "!=",
        // ↓ conditionals ↓  //
        "&&",
        "||",
        "!",
        // ↓ others ↓  //
        ">>", "<<", "&"

    };

    ///////////////////////////
    // ↓ ZSCRIPT KEYWORDS ↓  //
    ///////////////////////////

    const std::vector<std::string> keywords = {
        // ↓ data types ↓  //
        "int",
        "hex",
        "bin",
        "oct",
        "char",
        "float",
        "string",

        "if",
        "elif",
        "else",
        "do",
        "while",
        "and",
        "or",
        "not",
        "break",
        "for",
        "not",
        "except",
        "lambda",
        "finally",
        "true",
        "def",
        "if",
        "raise",
        "as",
        "elif",
        "in",
        "try",
        "none",
        "continue",
        "pass",
        "and",
        "delete",
        "include",
        "false",
        "class",
        "from",
        "return",
    };

};
#endif // TOKEN_H
