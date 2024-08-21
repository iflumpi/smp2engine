
#include "Interpreter.h"
#include <iostream>


void displayLogo()
{
    std::cout << "   _____ __  __ _____ ___     _____ _                 _       _             " << "\n";
    std::cout << "  / ____|  \\/  |  __ \\__ \\   / ____(_)               | |     | |            " << "\n";
    std::cout << " | (___ | \\  / | |__) | ) | | (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __ " << "\n";
    std::cout << "  \\___ \\| |\\/| |  ___/ / /   \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|" << "\n";
    std::cout << "  ____) | |  | | |    / /_   ____) | | | | | | | |_| | | (_| | || (_) | |   " << "\n";
    std::cout << " |_____/|_|  |_|_|   |____| |_____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|   " << "\n";
    std::cout << "\n";
    std::cout << "                   SMP2 interpreter based on command line " << "\n";
    std::cout << "\n";
}

int main(int argc, char* argv[])
{
    // Display logo
    displayLogo();

    // Create instance of interpreter
    auto interpreter = new Smp2Simulator::Interpreter::Interpreter();

    // Get assembly for arguments
    if (argc >= 2)
    {
        // Get assembly file from first argument
        auto assemblyFile = argv[1];

        // Load assembly
        std::cout << "Loading assembly from " << assemblyFile << " ..." << "\n";
        auto response = interpreter->loadAssembly(assemblyFile);
        std::cout << response << "\n";

        // Initialize assembly
        if (interpreter->isAssemblyLoaded())
        {
            std::cout << "Initializing assembly ..." << "\n";
            response = interpreter->init();
            std::cout << response << "\n";
        }
    }

    // Start program
    std::cout << "\n";
    std::cout << "Write 'help' to display commands available" << "\n";
    std::string strCommand;
    while (!interpreter->isQuitInterpreter())
    {
        if (!interpreter->isAssemblyLoaded() || !interpreter->isExecuting())
        {
            std::cout << ">> ";
            std::getline(std::cin, strCommand);
            auto response = interpreter->processCommand(strCommand);
            std::cout << response << "\n";
        }
        else
        {
            std::getline(std::cin, strCommand);
            interpreter->hold();
            std::cout << "\n";
        }
    }
}
