
#include "../include/zeel.h"

using namespace ZS::Shell;
#define ZLEXER_INTERACTIVE 0 // Interactive Console Source Code Input

void lexToFile(std::vector<ZS::Token *> &tokens, std::string fileName = LEXER_LOG_FILENAME)
{
    fstream lexFile;
    lexFile.open(fileName, ios::out);
    if (lexFile.is_open())
    {
        lexFile << tokens;
        // lexFile.flush(); // new added
        lexFile.close();
    }
    else
    {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(EXIT_FAILURE);
    };
};

void lex(std::string &sourceCode, std::string filename)
{
    std::vector<ZS::Token *> tokens;
    std::vector<ZS::Error> errors;
    auto lexer = ZS::Lexer(filename, sourceCode).tokenize();
    tokens = std::get<0>(lexer);
    errors = std::get<1>(lexer);

#if ZLEXER_INTERACTIVE
    if (!errors.empty())
        std::cout << errors;
    else
        std::cout << tokens;
#else
    if (!errors.empty())
        std::cout << errors;
    lexToFile(tokens);

#endif // INTERACTIVE
};

int main(int argc, char *argv[])
{

    std::string first; // First CommandLine Argument
    char *second;      // Second CommandLine Argument

    if (argc == 1)
    {

#if INTERACTIVE
        while (true)
        {
            std::string code;
            std::string filename = "stdin";
            std::cout << ">>> ";
            std::getline(std::cin, code);
            // // The Lexer Tokens
            lex(code, filename);
        }
#else
#ifdef ZLEXER_SAMPLE
        std::string filename = "../test/main.zs";
#else
        std::string filename = "../test/string.zs";
#endif
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open file " << filename << endl;
        }

        // Read the file contents into a string
        string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        // The Lexer Tokens
        lex(code, filename);

#endif // INTERACTIVE
    }
};
