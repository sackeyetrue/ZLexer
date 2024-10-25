#ifndef LEXER_H
#define LEXER_H

#include "error.h"
#include "token.h"

#define MAX_IDENTIFIER_LENGHT 40          // Maximun Name Length of Indetifiers.
#define LEXER_LOG_FILENAME "LexerLog.txt" // Name Of file to Write Generated Tokens to.

//  TODO: fix string not containing symbols and numbers
//  TODO: fix invalid base numbers
//  TODO: fix 0 always been invalid base
//  TODO: validate charaters tokens being more than on charater
//  TODO: fix string not containing symbols and numbers

//  TODO: add floating exponent Number Token type
//  TODO: add imaginary Number Token type

namespace ZS
{
    // Lexical Analyzer
    class Lexer
    {
    public:
        /**
         *  @brief  ZL Lexical Analyzer
         *
         *  @param  filename Name Source File.
         *  @param  text The String of text from Source File.
         */
        Lexer(std::string filename, const std::string &text)
            : filename(filename), text(text), index(0), cchar(text[index]), token(nullptr) {};

        /**
         *  @brief Tokenizes the Lexer Inputed Text.
         *  @returns std::pair<std::vector<Token *>, std::vector<Error>>
         */
        std::pair<std::vector<Token *>, std::vector<Error>> tokenize()
        {

            std::vector<Token *> tokens; // list of Tokenized Tokens.
            std::vector<Error> errors;   // list of Error when Tokenizing.

            tokens.clear(); // Clean Token Vector
            errors.clear(); // Clean Error Vector

            int line = 1;
            int start_pos = colon; // Token Start Position (Index)

            while (index < text.length())
            {
                //////////////////////////////////
                // ↓ Special Token Charaters ↓  //
                //////////////////////////////////

                if (cchar == ' ')
                { // Escape whitespace
                    advance();
                    colon++;
                    continue;
                }
                else if (cchar == '\n')
                { // New line Characters

                    line++;
                    colon = 0;
                    token = new EndOfLine();
                    advance();
                }
                else if (cchar == '[')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == ']')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '(')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == ')')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == ',')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '.')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '{')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '}')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '~')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '@')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '!')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '$')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '^')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '`')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == ';')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == ':')
                { //
                    std::string symbol = "";
                    colon++;
                    symbol += cchar;
                    token = new Symbol(symbol);
                    advance();
                }
                else if (cchar == '"')
                { // Double Quotes
                    try
                    {
                        advance();
                        colon++;
                        auto detail = getString();
                        std::string string = std::get<0>(detail);
                        int end_pos = std::get<1>(detail);

                        if (string == "Invalid")
                        {
                            Token *token = new Invalid(string);
                            throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        }
                        else
                        {
                            token = new String(string);
                        }
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        errors.push_back(error);
                    };
                }
                else if (cchar == '\'')
                {
                    try
                    {
                        advance();
                        colon++;
                        auto detail = getCharacter();
                        std::string character = std::get<0>(detail);
                        int end_pos = std::get<1>(detail);

                        if (character == "Invalid")
                        {
                            Token *token = new Invalid(character);
                            throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        }
                        else
                        {
                            token = new Char(character);
                        }
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        errors.push_back(error);
                    };
                }
                else if (cchar == '#')
                {
                    int start_pos = colon;
                    auto detail = getSingleLineComment();
                    std::string comment = std::get<0>(detail);
                    int end_pos = std::get<1>(detail);

                    token = new Comment(comment);
                }
                else if (cchar == '0')
                { // Base Numbers

                    token = getBase(line, errors);
                }
                else if (cchar == '/')
                {
                    try
                    {
                        int start_pos = colon;
                        std::string _operator = "";
                        _operator += cchar;
                        colon++;
                        advance();
                        if (cchar == '/')
                        {
                            advance();
                            colon++;
                            auto detail = getSingleLineComment();
                            std::string comment = std::get<0>(detail);
                            int end_pos = std::get<1>(detail);

                            token = new Comment(comment);
                        }
                        else if (cchar == '*')
                        { // Multiline Comments
                            try
                            {
                                advance();
                                colon++;
                                auto detail = getMultiLineComment();
                                std::string comment = std::get<0>(detail);
                                int end_pos = std::get<1>(detail);

                                if (comment == "Invalid")
                                {
                                    Token *token = new Invalid(comment);
                                    throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                                }
                                else
                                {
                                    token = new Comment(comment);
                                }
                            }
                            catch (ZS::Error error)
                            {
                                ////// HANDEL ERROR HERE /////
                                errors.push_back(error);
                            };
                        }
                        else if (cchar == ' ')
                        { // Operator (division Operator)

                            int end_pos = colon;
                            token = new Operator(_operator);
                        }
                        else
                        {
                            while (symbol.find(cchar) != std::string::npos && index < text.length())
                            {
                                _operator += cchar;
                                colon++;
                                advance();
                            };
                            int end_pos = colon;

                            token = new Invalid(_operator);
                            throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        }
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        errors.push_back(error);
                    };
                }
                else if (cchar == '*')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '*')
                    { //  (* Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '+')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '+')
                    { //  (* Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '-')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '-')
                    { //  (* Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '>')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '>')
                    { //  (* Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '<')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '<')
                    { //  (* Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '!')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }
                else if (cchar == '%')
                {
                    int start_pos = colon;
                    std::string _operator = "";
                    _operator += cchar;
                    colon++;
                    advance();
                    if (cchar == '=')
                    { //  (** Operator)
                        _operator += cchar;
                        advance();
                        token = new Operator(_operator);
                    }
                    else
                    {
                        token = new Operator(_operator);
                    }
                }

                /////////////////////////////
                // ↓ Special Word Token ↓  //
                /////////////////////////////

                else if (digits.find(cchar) != std::string::npos)
                { // Numbers

                    token = getNum(line, errors);
                }
                else if (name.find(cchar) != std::string::npos)
                { // Names | Words
                    try
                    {
                        int start_pos = colon;
                        auto detail = getWord();
                        std::string word = std::get<0>(detail);
                        int end_pos = std::get<1>(detail);

                        if (word.length() <= MAX_IDENTIFIER_LENGHT)
                        {
                            if (ZS::inContainer(keywords, word))
                            {
                                token = new Keyword(word);
                            }
                            else
                            {
                                token = new Identifier(word);
                            }
                        }
                        else
                        {
                            token = new Invalid(word);
                            throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        }
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        std::cout << error;
                    };
                }
                else if (_operators.find(cchar) != std::string::npos)
                {
                    try
                    {
                        int start_pos = colon;
                        auto detail = getOperator();
                        std::string _operator = std::get<0>(detail);
                        int end_pos = std::get<1>(detail);

                        if (ZS::inContainer(operators, _operator))
                        {
                            token = new Operator(_operator);
                        }
                        else
                        {
                            token = new Invalid(_operator);
                            // std::cout << filename << std::endl;

                            throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        }
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        errors.push_back(error);
                    };
                }
                else
                {
                    try
                    {
                        int start_pos = colon;
                        auto detail = getInvalid();
                        std::string opp = std::get<0>(detail);
                        int end_pos = std::get<1>(detail);
                        token = new Invalid(opp);
                        throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                    }
                    catch (ZS::Error error)
                    {
                        ////// HANDEL ERROR HERE /////
                        errors.push_back(error);
                    };
                }
                tokens.push_back(token);
            };
            // Add EOF token to notify the parser when the tokens vector is over
            token = new EndOfFile();
            tokens.push_back(token);

            return {tokens, errors};
        };

        /**
         *  @brief Get Tokens
         *  @returns  List of Tokens, Tokenized by Lexer.
         */
        std::pair<std::vector<Token *>, std::vector<Error>> getTokens();

    private:
        std::string text;     // Source Code
        std::string filename; // Source Code
        int index;            // Charater Index
        int line;             // Charater Line Number
        int colon = 0;        // Charater Colon
        char cchar;           // Curent Charater

        Token *token; // Current Token.

        /**
         *  @brief Output the Lexer analyzed Tokens to file
         *  @param line  Line Number Of Token.
         *  @returns Number Base Token.
         */
        Token *getBase(int &line, std::vector<ZS::Error> &errors)
        {
            // TODO: Handle invalid base
            // TODO: Else Base Error
            try
            {
                int start_pos = colon; // Token Start Position
                std::string baseNumber = "";
                int baseCount = 0;
                bool isBinary = false; // Binary Number Base.
                bool isOctal = false;  // Octal Number Base.
                bool isHex = false;    // Hexidecimal Number Base.

                while ((basedigits.find(cchar) != std::string::npos) && (index < text.length()))
                {
                    if (cchar == 'o')
                    {
                        isOctal = true;
                        baseCount++;
                    }
                    else if (cchar == 'b')
                    {
                        isBinary = true;
                        baseCount++;
                    }
                    else if (cchar == 'x')
                    {
                        isHex = true;
                        baseCount++;
                    }
                    baseNumber += cchar;
                    colon++;
                    advance();
                };

                int end_pos = colon;

                if (isHex)
                {
                    if (baseCount == 1)
                    {
                        return new Hexidecimal(baseNumber);
                    }
                    else
                    {

                        ZS::Token *token = new Invalid(baseNumber);
                        throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        return token;
                    }
                }
                else if (isOctal)
                {
                    if (baseCount == 1)
                    {
                        return new Octal(baseNumber);
                    }
                    else
                    {

                        ZS::Token *token = new Invalid(baseNumber);
                        throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        return token;
                    }
                }
                else if (isBinary)
                {
                    if (baseCount == 1)
                    {
                        return new Binary(baseNumber);
                    }
                    else
                    {

                        ZS::Token *token = new Invalid(baseNumber);
                        throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        return token;
                    }
                }
                else
                {
                    ZS::Token *token = new Invalid(baseNumber);
                    throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                    return token;
                }
            }
            catch (ZS::Error error)
            {
                ////// HANDEL ERROR HERE /////
                errors.push_back(error);
            };
        };

        /**
         *  @brief Output the Lexer analyzed Tokens to file
         *  @param line  Line Number Of Token.
         *  @returns Number Token of Integer | Float.
         */
        Token *getNum(int &line, std::vector<ZS::Error> &errors)
        {
            // TODO: Handle invalid number
            // TODO: invalid Floating Point Numbers
            try
            {
                int start_pos = colon; // Token Start Position
                std::string number = "";
                int dotCount = 0;

                bool isFloat = false;     // Floating Point Number.
                bool isExponent = false;  // Exponent Number.
                bool isImaginary = false; // Imaginary Number.

                while ((digits.find(cchar) != std::string::npos || cchar == '.') && (index < text.length()))
                {
                    if (cchar == '.')
                    {
                        isFloat = true;
                        dotCount++;
                    }
                    if (cchar == 'i')
                    {
                        isImaginary = true;
                    }
                    if (cchar == 'e')
                    {
                        isExponent = true;
                    }
                    number += cchar;
                    colon++;
                    advance();
                };

                int end_pos = colon;

                if (isFloat)
                {
                    if (dotCount == 1)
                    {
                        return new Float(number);
                    }
                    else
                    {
                        ZS::Token *token = new Invalid(number);
                        throw ZS::IllegalCharError(token, filename, line, start_pos, end_pos);
                        return token;
                    }
                }
                else
                {
                    return new Integer(number);
                }
            }
            catch (ZS::Error error)
            {
                ////// HANDEL ERROR HERE /////
                errors.push_back(error);
            };
        }

        /**
         *  @brief Get Word Token value.
         *  @returns std::pair<word, end_pos>
         */
        std::pair<std::string, int> getWord()
        {
            std::string word = "";
            while (name.find(cchar) != std::string::npos && index < text.length())
            {
                word += cchar;
                colon++;
                advance();
            };
            int end_pos = colon;
            return {word, end_pos};
        };

        /**
         *  @brief Get String Token value.
         *  @returns std::pair<string, end_pos>
         */
        std::pair<std::string, int> getString()
        {
            int end_pos = colon;

            std::string string = "";
            while (strings.find(cchar) != std::string::npos || cchar == '"' || cchar == '\\' && index < text.length())
            {
                if (cchar == '"')
                { // end of String
                    advance();
                    colon++;
                    return {string, end_pos};
                }
                // else if (cchar == '\\')
                // {
                //     colon++;
                //     string += cchar;
                // }
                string += cchar;
                colon++;
                end_pos++;
                advance();
            };
            return {"Invalid", end_pos};
        };

        /**
         *  @brief Get Character Token value.
         *  @returns std::pair<character, end_pos>
         */
        std::pair<std::string, int> getCharacter()
        {
            int end_pos = colon;

            std::string character = "";
            while (name.find(cchar) != std::string::npos || cchar == '\'' && index < text.length())
            {
                if (cchar == '\'')
                {
                    advance();
                    colon++;
                    return {character, end_pos};
                }
                character += cchar;
                colon++;
                end_pos++;
                advance();
            };
            return {"Invalid", end_pos};
        };

        /**
         *  @brief Get Operator Token value.
         *  @returns std::pair<operator, end_pos>
         */
        std::pair<std::string, int> getOperator()
        {
            std::string _operator = "";
            while (symbol.find(cchar) != std::string::npos && index < text.length())
            {
                _operator += cchar;
                colon++;
                advance();
            };
            int end_pos = colon;
            return {_operator, end_pos};
        }

        /**
         *  @brief Get Invalid Token value.
         *  @returns std::pair<invalid, end_pos>
         */
        std::pair<std::string, int> getInvalid()
        {
            std::string invalid = "";
            while (invalids.find(cchar) != std::string::npos && index < text.length())
            {
                invalid += cchar;
                advance();
                colon++;
            }
            int end_pos = colon;
            return {invalid, end_pos};
        };

        /**
         *  @brief Get SingleLine Comments Token value.
         *  @returns std::pair<comment, end_pos>
         */
        std::pair<std::string, int> getSingleLineComment()
        {
            std::string escape = "";
            advance();
            while (comment.find(cchar) != std::string::npos && index < text.length())
            {
                escape += cchar;
                colon++;
                advance();
            }
            int end_pos = colon;
            return {escape, end_pos};
        };

        /**
         *  @brief Get MultiLine Comments Token value.
         *  @returns std::pair<comment, end_pos>
         */
        std::pair<std::string, int> getMultiLineComment()
        {
            int end_pos = colon;

            std::string comments = "";
            while (comment.find(cchar) != std::string::npos && index < text.length())
            {
                if (cchar == '*')
                {
                    advance();
                    colon++;
                    if (cchar != '/')
                    {
                        advance();
                        comments += cchar;
                        colon++;
                    }
                    else
                    { // end of comment
                        advance();
                        colon++;
                        return {comments, end_pos};
                    }
                }
                comments += cchar;
                colon++;
                end_pos++;
                advance();
            };
            return {"Invalid", end_pos};
        };

        /** moves to next char | Token . */
        void advance()
        {
            index++;

            if (index < text.length())
            {
                cchar = text[index];
            }
        };
    };
};
#endif // LEXER_H