#ifndef SHELL_H
#define SHELL_H

#include "../backend/token.h"
#include "../backend/lexer.h"
#include "../backend/error.h"
#include "../utils/utils.h"
#include "../utils/shell.h"

#include <iostream>
#include <string>

#include <fstream>
#include <string>
#include <conio.h>

namespace ZS::Shell
{

    void play()
    {
        system("cls");
        std::cout << "ZScript 0.0.09(Jun 6 2024, 19 : 30 : 16)[zslang.com / play]" << std::endl;
        while (true)
        {
            std::string code;
            std::cout << ">>> ";
            std::getline(std::cin, code);
            std::cout << "executed" << std::endl;
        };
    };

    void help(char *input = "")
    {
        std::cout << "Type help " << input << std::endl;
    };

    void license()
    {
        std::cout << "Type license " << std::endl;
    };

    void credits()
    {
        std::cout << "Type credits" << std::endl;
    };

    void copyright()
    {
        std::cout << "Type copyright" << std::endl;
    };

    void console()
    {
        std::cout << "ZScript Terminal - Created by Zeke Cora(2024)";

        std::cout << "Commands:" << std::endl;
        std::cout << "Ctrl+X: Exit" << std::endl;
        std::cout << "Ctrl+S: Save" << std::endl;
        std::cout << "Ctrl+O: Open file" << std::endl;
        std::cout << "Ctrl+N: New file" << std::endl;
        std::cout << "Ctrl+W: Write to file" << std::endl;

        char key = _getch(); // Get user input without waiting for Enter
        if (key == 24)
        {
            bool run = true;

            while (run)
            {
                char key = _getch(); // Get user input without waiting for Enter

                if (key == 24)
                { // Ctrl+X (Exit)
                    std::cout << "Exiting..." << std::endl;
                    break;
                }
                else if (key == 19)
                {             // Ctrl+S (Save)
                    _getch(); // Wait for user to press a key
                }
                else if (key == 15)
                { // Ctrl+O (Open file)

                    _getch(); // Wait for user to press a key
                }
                else if (key == 14)
                {             // Ctrl+N (New file)
                    _getch(); // Wait for user to press a key
                }
                else if (key == 23)
                { // Ctrl+W (Write to file)

                    _getch(); // Wait for user to press a key
                }
                else if (key == 3)
                {             // Ctrl+C (Help)
                    _getch(); // Wait for user to press a key
                }
                else
                {
                    std::cout << "Invalid command." << std::endl;
                    _getch(); // Wait for user to press a key
                }
            };
        };
    };
};
#endif // SHELL_H