
#include "Interpreter.h"
#include <iostream>
#include <sstream>
#include <cstring>


namespace Smp2Simulator
{
namespace Interpreter
{

// Parse and execute a command
std::string Interpreter::processCommand(std::string strCommand)
{	
    try
    {
        auto parser = new Parser();
        Command* cmd = parser->getCommand(strCommand);

        switch (cmd->action)
        {
            case Action::LOAD_ASSEMBLY:
                return this->loadAssembly(cmd);

            case Action::RUN:
                return this->run();

            case Action::HOLD:
                return this->hold();

            case Action::GET_TIMES:
                return this->getTimes();

            case Action::GET_MODELS:
                return this->getModels();

            case Action::GET_OPERATIONS:
                return this->getOperations(cmd);

            case Action::GET_FIELDS:
                return this->getFields(cmd);

            case Action::GET_FIELD_VALUE:
                return this->getFieldValue(cmd);

            case Action::GET_ARRAY_FIELD_VALUE:
                return this->getArrayFieldValue(cmd);

            case Action::SET_FIELD_VALUE:
                return this->setFieldValue(cmd);

            case Action::SET_ARRAY_FIELD_VALUE:
                return this->setArrayFieldValue(cmd);

            case Action::SET_EPOCH_TIME:
                return this->setEpochTime(cmd);

            case Action::SET_MISSION_TIME:
                return this->setMissionTime(cmd);

            case Action::EXECUTE_OPERATION:
                return this->executeOperation(cmd);

            case Action::LOG:
                return this->log();

            case Action::HELP:
                return this->help();

            case Action::QUIT:
                return this->quit();

            default:
                return this->unknown();
        }
    }
    catch (...)
    {
        return "Unknown error.\n";
    }
}

// Check whether the simulator is running
bool Interpreter::isExecuting()
{
    return this->controller->isExecuting();
}

// Check whether an assembly is loaded
bool Interpreter::isAssemblyLoaded()
{
    return this->assemblyLoaded;
}

// Check whether the QUIT command was executed
bool Interpreter::isQuitInterpreter()
{
    return this->quitInterpreter;
}

// Load an dynamic library with an assembly of models
std::string Interpreter::loadAssembly(const char* assemblyFile)
{
    // Close previous assembly
    if (this->assemblyLoaded)
        this->controller->close();

    // Update assemblyLoaded flag
    this->assemblyLoaded = false;

    // Load assembly in the controller
    bool success = this->controller->loadAssembly(assemblyFile);
    if (!success)
    {
        return "Could not open the assembly\n";
    }
	this->assemblyLoaded = true;
    return "Assembly loaded!\n";
}

// Init the simulator
std::string Interpreter::init()
{
    this->controller->init();
    return "Assembly initialized in the simulator successfully\n";
}

// Get the controller used by the interpreter
Smp2Simulator::Controller::Controller* Interpreter::getController()
{
	return this->controller;
}

// Get the response of a command to load an assembly
std::string Interpreter::loadAssembly(Command* cmd)
{
    // Get command
    auto cmdLac = (LoadAssemblyCommand*)(cmd);

    // Load and initialize the assembly from the specified file
    this->assemblyLoaded = false;
    auto response = this->loadAssembly(cmdLac->assemblyFile.c_str());
    if (this->assemblyLoaded)
        response = this->init();
    return response;
}

// Get the response of a command to display help
std::string Interpreter::help()
{
    std::string str;
    str.append("Commands available\n");
    str.append(" + load [assembly_file]\n");
    str.append(" + run\n");
    str.append(" + get times\n");
    str.append(" + get models\n");
    str.append(" + get fields [model]\n");
    str.append(" + get operations [model]\n");
    str.append(" + get value [model] [field]\n");
    str.append(" + get array [model] [field] [position]\n");
    str.append(" + set value [model] [field] [value]\n");
    str.append(" + set array [model] [field] [position] [value]\n");
    str.append(" + set epoch [time]\n");
    str.append(" + set mission [time]\n");
    str.append(" + execute [model] [operation] [arguments]\n");
    str.append(" + log\n");
    str.append(" + help\n");
    str.append(" + quit\n");
    str.append("\n");
    return str;
}

// Run the simulation
std::string Interpreter::run()
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    this->controller->run();
    return "";
}

// Hold the simulation
std::string Interpreter::hold()
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    this->controller->hold();
    return "";
}

// Get the response of a command to get current value of different times
std::string Interpreter::getTimes()
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    std::ostringstream stream;
    stream << " + Simulation time: " << this->controller->getSimulationTime() << "\n";
    stream << " + Epoch time: " << this->controller->getEpochTime() << "\n";
    stream << " + Mission time: " << this->controller->getMissionTime() << "\n";
    return stream.str();
}

// Get the response of a command to get models
std::string Interpreter::getModels()
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    auto modelsNames = this->controller->getModelsNames();
    std::ostringstream stream;
    for (int i=0; i<modelsNames.size(); i++)
        stream << " + " << modelsNames.at(i) << "\n";
    return stream.str();
}

// Get the response of a command to get operations
std::string Interpreter::getOperations(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdGo = (GetOperationsCommand*)(cmd);

    // If a model is specified and it is not loaded in the simulator, return a error
    if (cmdGo->model.length() > 0 and !this->controller->isModelLoaded(cmdGo->model.c_str()))
        return this->getErrorResponseModelNotLoaded(cmdGo->model);

    // Get the response from operation names list returned by the controller
    auto operationsNames = this->controller->getOperationsNames(cmdGo->model.length() > 0 ? cmdGo->model.c_str() : nullptr);
    std::ostringstream stream;
    for (int i=0; i<operationsNames.size(); i++)
        stream << " + " << operationsNames.at(i) << "\n";
    return stream.str();
}

// Get the response of a command to get fields
std::string Interpreter::getFields(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdGf = (GetFieldsCommand*)(cmd);

    // If a model is specified and it is not loaded in the simulator, return a error
    if (cmdGf->model.length() > 0 and !this->controller->isModelLoaded(cmdGf->model.c_str()))
        return this->getErrorResponseModelNotLoaded(cmdGf->model);

    // Get the response from fields names list returned by the controller
    auto fieldsNames = this->controller->getFieldsNames(cmdGf->model.length() > 0 ? cmdGf->model.c_str() : nullptr);
    std::ostringstream stream;
    for (int i=0; i<fieldsNames.size(); i++)
        stream << " + " << fieldsNames.at(i) << "\n";

    return stream.str();
}

// Get the response of a command to get field value
std::string Interpreter::getFieldValue(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdGfv = (GetFieldValueCommand*)(cmd);

    // Get model and field names
    auto model = cmdGfv->model;
    auto field = cmdGfv->field;

    // If the model is not specified, return an error
    if (model.length() == 0)
        return this->ERROR_MODEL_NOT_SPECIFIED;

    // If the field is not specified, return an error
    if (field.length() == 0)
        return this->ERROR_FIELD_NOT_SPECIFIED;

    // If the model is not loaded, return an error
    if (!this->controller->isModelLoaded(model.c_str()))
        return this->getErrorResponseModelNotLoaded(model);

    // If the specified field is not published, return an error
    if (!this->controller->isFieldPublished(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotPublished(model, field);

    try
    {
        // Get the response from the field valued returned by the controller
        auto value = this->controller->getFieldValue(model.c_str(), field.c_str());
        std::ostringstream stream;
        stream << " + Value: " << value << "\n";

        // Store value
        this->lastValue = value;

        // Return response
        return stream.str();
    }
    catch(int)
    {
        return "An error occurred while trying to get the value of the field";
    }
}

// Get the response of a command to get a value from an array field
std::string Interpreter::getArrayFieldValue(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdGafv = (GetArrayFieldValueCommand*)cmd;

    // Get model, field and position
    auto model = cmdGafv->model;
    auto field = cmdGafv->field;
    auto position = cmdGafv->position;

    // If the model is not specified, return an error
    if (model.length() == 0)
        return this->ERROR_MODEL_NOT_SPECIFIED;

    // If the array field is not specified, return an error
    if (field.length() == 0)
        return this->ERROR_FIELD_NOT_SPECIFIED;

    // If the position is not specified, return an error
    if (position.length() == 0)
        return this->ERROR_ARRAY_POSITION_NOT_SPECIFIED;

    // If the model is not loaded, return an error
    if (!this->controller->isModelLoaded(model.c_str()))
        return this->getErrorResponseModelNotLoaded(model);

    // If the specified field is not published, return an error
    if (!this->controller->isFieldPublished(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotPublished(model, field);

    // If the specified field is not an array, return an error
    if (!this->controller->isArrayField(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotArray(model, field);

    // If the specified position is not an number, return an error
    // NOT IMPLEMENTED

    // If the specified position is greater than array size, return an error
    // NOT IMPLEMENTED

    // Convert position argument to a integer
    auto index = std::atoi(position.c_str());

    // Get the response from the field valued returned by the controller
    auto value = this->controller->getArrayFieldValue(model.c_str(), field.c_str(), index);
    std::ostringstream stream;
    stream << " + Value: " << value << "\n";

    // Store value
    this->lastValue = value;

    // Return response
    return stream.str();
}

// Set the value of a field and get the response to the command
std::string Interpreter::setFieldValue(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdSfv = (SetFieldValueCommand*)cmd;

    // Get field and value
    auto model = cmdSfv->model;
    auto field = cmdSfv->field;
    auto value = cmdSfv->value;

    // If the model is not specified, return an error
    if (model.length() == 0)
        return this->ERROR_MODEL_NOT_SPECIFIED;

    // If the field is not specified, return an error
    if (field.length() == 0)
        return this->ERROR_FIELD_NOT_SPECIFIED;

    // If the field is not specified, return an error
    if (value.length() == 0)
        return this->ERROR_FIELD_VALUE_NOT_SPECIFIED;

    // If the model is not loaded, return an error
    if (!this->controller->isModelLoaded(model.c_str()))
        return this->getErrorResponseModelNotLoaded(model);

    // If the specified field is not published, return an error
    if (!this->controller->isFieldPublished(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotPublished(model, field);

    // Set the value of the field
    try
    {
        auto success = this->controller->setFieldValue(model.c_str(), field.c_str(), value.c_str());
        if (success)
            return this->SUCCESS_FIELD_UPDATED;
        else
            return this->ERROR_FIELD_CANNOT_BE_UPDATED;
    }
    catch(int)
    {
        return "An error occurred while trying to set the value of the field";
    }
}

// Set the value of a array field and get the response to the command
std::string Interpreter::setArrayFieldValue(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdSafv = (SetArrayFieldValueCommand*)cmd;

    // Get field and value
    auto model = cmdSafv->model;
    auto field = cmdSafv->field;
    auto position = cmdSafv->position;
    auto value = cmdSafv->value;

    // If the model is not specified, return an error
    if (model.length() == 0)
        return this->ERROR_MODEL_NOT_SPECIFIED;

    // If the field is not specified, return an error
    if (field.length() == 0)
        return this->ERROR_FIELD_NOT_SPECIFIED;

    // If the position is not specified, return an error
    if (position.length() == 0)
        return this->ERROR_ARRAY_POSITION_NOT_SPECIFIED;;

    // If the field is not specified, return an error
    if (value.length() == 0)
        return this->ERROR_FIELD_VALUE_NOT_SPECIFIED;

    // If the model is not loaded, return an error
    if (!this->controller->isModelLoaded(model.c_str()))
        return this->getErrorResponseModelNotLoaded(model);

    // If the specified field is not published, return an error
    if (!this->controller->isFieldPublished(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotPublished(model, field);

    // If the specified field is not an array, return an error
    if (!this->controller->isArrayField(model.c_str(), field.c_str()))
        return this->getErrorResponseFieldNotArray(model, field);

    // If the specified position is not an number, return an error
    // NOT IMPLEMENTED

    // If the specified position is greater than array size, return an error
    // NOT IMPLEMENTED

    // Convert position argument to a integer
    auto index = std::atoi(position.c_str());

    // Set the value of the field
    try
    {
        auto success = this->controller->setArrayFieldValue(model.c_str(), field.c_str(), index, value.c_str());
        if (success)
            return this->SUCCESS_FIELD_UPDATED;
        else
            return this->ERROR_FIELD_CANNOT_BE_UPDATED;
    }
    catch(int)
    {
        return "An error occurred while trying to set the value of the field";
    }
}


// Set the initial epoch time
std::string Interpreter::setEpochTime(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdSet = (SetEpochTimeCommand*)cmd;

    // Get time
    auto time = cmdSet->time;

    // If the time is not specified, return an error
    if (time.length() == 0)
        return this->ERROR_TIME_NOT_SPECIFIED;

    // If the time is not a number, return an error
    // NOT IMPLEMENTED

    // Convert time to a long integer
    auto lTime = std::atol(time.c_str());

    // Set the value of epoch time
    this->controller->setEpochTime(lTime);

    // Return success message
    return this->SUCCESS_EPOCH_TIME_UPDATED;
}

// Set the start mission time
std::string Interpreter::setMissionTime(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdSmt = (SetMissionTimeCommand*)cmd;

    // Get time
    auto time = cmdSmt->time;

    // If the time is not specified, return an error
    if (time.length() == 0)
        return this->ERROR_TIME_NOT_SPECIFIED;

    // If the time is not a number, return an error
    // NOT IMPLEMENTED

    // Convert time to a long integer
    auto lTime = std::atol(time.c_str());

    // Set the value of epoch time
    this->controller->setMissionTime(lTime);

    // Return success message
    return this->SUCCESS_MISSION_TIME_UPDATED;
}


// Execute an operation and get the response to the command
std::string Interpreter::executeOperation(Command* cmd)
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    // Get command
    auto cmdEo = (ExecuteOperationCommand*)cmd;

    // Get model, operation and parameters
    auto model = cmdEo->model;
    auto operation = cmdEo->operation;
    auto parameters = cmdEo->parameters;

    // If the model is not specified, return an error
    if (model.length() == 0)
        return this->ERROR_MODEL_NOT_SPECIFIED;

    // If the operation is not specified, return an error
    if (operation.length() == 0)
        return this->ERROR_OPERATION_NOT_SPECIFIED;

    // If the model is not loaded, return an error
    if (!this->controller->isModelLoaded(model.c_str()))
        return this->getErrorResponseModelNotLoaded(model);

    // If the specified operation is not published, return an error
    if (!this->controller->isOperationPublished(model.c_str(), operation.c_str()))
        return this->getErrorResponseOperationNotPublished(model, operation);

    // If the number of parameters is not equal to the operation parameters, return an error
    int operationParametersCount = this->controller->getOperationParametersCount(model.c_str(), operation.c_str());
    if (operationParametersCount != parameters.size())
    {
        return this->getErrorResponseOperationInvalidSizeParameters(model, operation, parameters.size(), operationParametersCount);
    }

    // Execute operation
    auto value = this->controller->executeOperation(model.c_str(), operation.c_str(), parameters);

    // Create and return response
    auto response = this->getSuccessResponseOperationExecuted(operation);
    if (value.length() > 0)
    {
        this->lastValue = value;
        std::ostringstream stream;
        stream << " + Returned value: " << value << "\n";
        return stream.str();
    }
    return response;

}

// Get a string with the union of all the logs stored in the simulator
std::string Interpreter::log()
{
    // Check whether an assembly is loaded
    if (!this->assemblyLoaded)
        return this->ERROR_ASSEMBLY_NOT_LOADED;

    std::string strLogs;
    auto logMessages = controller->getLogMessages();
    for (int i=0; i<logMessages.size(); i++)
    {
        auto logMessage = logMessages.at(i);
        strLogs.append(logMessage->getString());
        strLogs.append("\n");
    }
    return strLogs;
}

// Close the interpreter
std::string Interpreter::quit()
{
    if (this->assemblyLoaded)
        this->controller->close();

    this->quitInterpreter = true;
    return "Bye!\n";
}

// Get the response of a unknown command
std::string Interpreter::unknown()
{
    return this->ERROR_COMMAND_NOT_RECOGNIZED;
}

// Get the string related to the success response returned when a operation is executed
std::string Interpreter::getSuccessResponseOperationExecuted(std::string operation)
{
    std::ostringstream stream;
    stream << "The operation '" << operation << "' was executed successfully" << "\n";
    return stream.str();
}

// Get the string related to the error response returned when a specified model is not loaded
std::string Interpreter::getErrorResponseModelNotLoaded(std::string model)
{
    std::ostringstream stream;
    stream << "The model '" << model << "' is not loaded in the simulator" << "\n";
    return stream.str();
}

// Get the string related to the error response returned when a specified field is not published by a model
std::string Interpreter::getErrorResponseFieldNotPublished(std::string model, std::string field)
{
    std::ostringstream stream;
    stream << "The model '" << model << "' does not contain the field '" << field << "'" << "\n";
    return stream.str();
}

// Get the string related to the error response returned when a specified operation is not published by a model
std::string Interpreter::getErrorResponseOperationNotPublished(std::string model, std::string operation)
{
    std::ostringstream stream;
    stream << "The model '" << model << "' does not contain the operation '" << operation << "'" << "\n";
    return stream.str();
}

// Get the string related to the error response returned when a specified field is not an array
std::string Interpreter::getErrorResponseFieldNotArray(std::string model, std::string field)
{
    std::ostringstream stream;
    stream << "The field '" << field << "' of the model '" << model << "' is not an array" << "\n";
    return stream.str();
}

// Get the string related to the error response returned when size of specified parameters for a operation is not correct
std::string Interpreter::getErrorResponseOperationInvalidSizeParameters(std::string model, std::string operation, int parametersCount, int operationParametersCount)
{
    std::ostringstream stream;
    stream << "The operation '" << operation << "' of the model '" << model << "' has " << operationParametersCount << " parameters ";
    stream << "(specified " << parametersCount <<  " parameters)" << "\n";
    return stream.str();
}

// Get last value returned by the controller
std::string Interpreter::getLastValue()
{
    return this->lastValue;
}


}
}
