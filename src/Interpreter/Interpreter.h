
#include "Controller/Controller.h"
#include "Parser.h"


namespace Smp2Simulator
{
namespace Interpreter
{

class Interpreter
{

public:
    // Constructor
    Interpreter()
    {
        this->controller = new Smp2Simulator::Controller::Controller();
        this->parser = new Parser();
        this->assemblyLoaded = false;
        this->quitInterpreter = false;
    }
    
    // Methods
    std::string processCommand(std::string cmd);
    std::string loadAssembly(const char* assemblyFile);
    std::string init();
    std::string run();
    std::string hold();	
    bool isAssemblyLoaded();
    bool isExecuting();
    bool isQuitInterpreter();
	Smp2Simulator::Controller::Controller* getController();
	std::string getLastValue();


protected:
	// Attributes
    Smp2Simulator::Controller::Controller* controller;
    Parser* parser;
    bool assemblyLoaded;
    bool quitInterpreter;
    std::string lastValue;

    // Constants for messages
    const char* SUCCESS_FIELD_UPDATED = "The field was updated successfully\n";
    const char* SUCCESS_EPOCH_TIME_UPDATED = "The initial epoch time was updated successfully\n";
    const char* SUCCESS_MISSION_TIME_UPDATED = "The start mission time was updated successfully\n";
    const char* ERROR_ASSEMBLY_NOT_LOADED = "Assembly not loaded\n";
    const char* ERROR_MODEL_NOT_SPECIFIED = "The model was not specified\n";
    const char* ERROR_FIELD_NOT_SPECIFIED = "The field was not specified\n";
    const char* ERROR_OPERATION_NOT_SPECIFIED = "The field was not specified\n";
    const char* ERROR_ARRAY_POSITION_NOT_SPECIFIED = "The position of the array was not specified.\n";
    const char* ERROR_FIELD_VALUE_NOT_SPECIFIED = "The value was not specified.\n";
    const char* ERROR_TIME_NOT_SPECIFIED = "The time was not specified.\n";
    const char* ERROR_FIELD_CANNOT_BE_UPDATED = "The field cannot be updated\n";
    const char* ERROR_COMMAND_NOT_RECOGNIZED = "Command not recognized\n";

    // Methods to return messages
    std::string getSuccessResponseOperationExecuted(std::string operation);
    std::string getErrorResponseModelNotLoaded(std::string model);
    std::string getErrorResponseFieldNotPublished(std::string model, std::string field);
    std::string getErrorResponseOperationNotPublished(std::string model, std::string operation);
    std::string getErrorResponseOperationInvalidSizeParameters(std::string model, std::string operation, int parametersCount, int operationParametersCount);
    std::string getErrorResponseFieldNotArray(std::string model, std::string field);

    // Methods to process commands
    std::string loadAssembly(Command* cmd);
    std::string help();
    std::string getTimes();
    std::string getModels();
    std::string getFields(Command* cmd);
    std::string getOperations(Command* cmd);
    std::string getFieldValue(Command* cmd);
    std::string getArrayFieldValue(Command* cmd);
    std::string setFieldValue(Command* cmd);
    std::string setArrayFieldValue(Command* cmd);
    std::string setEpochTime(Command* cmd);
    std::string setMissionTime(Command* cmd);
    std::string executeOperation(Command* cmd);
    std::string log();
    std::string quit();
    std::string unknown();

};

}
}
