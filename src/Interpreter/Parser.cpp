
#include "Parser.h"
#include <algorithm>
#include <iostream>
#include <cstring>


namespace Smp2Simulator
{
namespace Interpreter
{

//  Split a string in several parts according a separator
std::vector<std::string> Parser::splitArguments(const char* arguments, const char* separator)
{
    std::vector<std::string> splittedArguments;

    std::string part = std::string(arguments, strlen(arguments));
    bool commandEnd = false;
    while (!commandEnd)
    {
        auto index = part.find(separator);
        std::string token = part.substr(0, index);
        splittedArguments.push_back(token);
        if (index != -1)
            part = part.substr(index + 1, part.size());
        else
            commandEnd = true;
    }
    return splittedArguments;
}

// Parse a string to get the related command instance
Command* Parser::getCommand(std::string strCommand)
{
    if (strCommand.size() <= 0)
        return new Command(Action::UNKNOWN);

    std::vector<std::string> parsedCommand = this->splitArguments(strCommand.c_str(), " ");
    auto action = parsedCommand.at(0);
    std::transform(action.begin(), action.end(), action.begin(), ::toupper);

    if (strcmp(action.c_str(), "LOAD") == 0)
    {
        auto assemblyFile = (parsedCommand.size() >= 2) ? parsedCommand.at(1) : "";
        return new LoadAssemblyCommand(assemblyFile);
    }

    if (strcmp(action.c_str(), "RUN") == 0)
        return new Command(Action::RUN);

    if (strcmp(action.c_str(), "GET") == 0)
    {
        if (parsedCommand.size() <= 1)
            return new Command(Action::UNKNOWN);

        auto subaction = parsedCommand.at(1);
        std::transform(subaction.begin(), subaction.end(), subaction.begin(), ::toupper);

        if (strcmp(subaction.c_str(), "TIMES") == 0)
            return new Command(Action::GET_TIMES);

        if (strcmp(subaction.c_str(), "MODELS") == 0)
            return new Command(Action::GET_MODELS);

        if (strcmp(subaction.c_str(), "OPERATIONS") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            return new GetOperationsCommand(modelName);
        }

        if (strcmp(subaction.c_str(), "FIELDS") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            return new GetFieldsCommand(modelName);
        }

        if (strcmp(subaction.c_str(), "VALUE") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            auto fieldName = (parsedCommand.size() >= 4) ? parsedCommand.at(3) : "";
            return new GetFieldValueCommand(modelName, fieldName);
        }

        if (strcmp(subaction.c_str(), "ARRAY") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            auto fieldName = (parsedCommand.size() >= 4) ? parsedCommand.at(3) : "";
            auto position = (parsedCommand.size() >= 5) ? parsedCommand.at(4) : "";
            return new GetArrayFieldValueCommand(modelName, fieldName, position);
        }
    }

    if (strcmp(action.c_str(), "SET") == 0)
    {
        if (strCommand.size() <= 1)
            return new Command(Action::UNKNOWN);

        auto subaction = parsedCommand.at(1);
        std::transform(subaction.begin(), subaction.end(), subaction.begin(), ::toupper);

        if (strcmp(subaction.c_str(), "VALUE") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            auto fieldName = (parsedCommand.size() >= 4) ? parsedCommand.at(3) : "";
            auto value = (parsedCommand.size() >= 5) ? parsedCommand.at(4) : "";
            return new SetFieldValueCommand(modelName, fieldName, value);
        }

        if (strcmp(subaction.c_str(), "ARRAY") == 0)
        {
            auto modelName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            auto fieldName = (parsedCommand.size() >= 4) ? parsedCommand.at(3) : "";
            auto position = (parsedCommand.size() >= 5) ? parsedCommand.at(4) : "";
            auto value = (parsedCommand.size() >= 6) ? parsedCommand.at(5) : "";
            return new SetArrayFieldValueCommand(modelName, fieldName, position, value);
        }

        if (strcmp(subaction.c_str(), "EPOCH") == 0)
        {
            auto time = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            return new SetEpochTimeCommand(time);
        }

        if (strcmp(subaction.c_str(), "MISSION") == 0)
        {
            auto time = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
            return new SetMissionTimeCommand(time);
        }
    }

    if (strcmp(action.c_str(), "EXECUTE") == 0)
    {
        auto modelName = (parsedCommand.size() >= 2) ? parsedCommand.at(1) : "";
        auto operationName = (parsedCommand.size() >= 3) ? parsedCommand.at(2) : "";
        std::vector<std::string> parameters;
        for (int i=3; i<parsedCommand.size(); i++)
        {
            auto parameter = parsedCommand.at(i);
            parameters.push_back(parameter);
        }
        return new ExecuteOperationCommand(modelName, operationName, parameters);
    }

    if (strcmp(action.c_str(), "HELP") == 0)
    {
        return new Command(Action::HELP);
    }

    if (strcmp(action.c_str(), "QUIT") == 0)
    {
        return new Command(Action::QUIT);
    }

    return new Command(Action::UNKNOWN);
}

}
}
