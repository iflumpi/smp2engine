
#include <string>
#include <map>
#include <vector>


namespace Smp2Simulator
{
namespace Interpreter
{


/*
 * Action enumerated type
 */

enum Action
{
    LOAD_ASSEMBLY,
    RUN,
    HOLD,
    GET_MODELS,
    GET_FIELDS,
    GET_OPERATIONS,
    GET_FIELD_VALUE,
    GET_ARRAY_FIELD_VALUE,
    SET_FIELD_VALUE,
    SET_ARRAY_FIELD_VALUE,
    EXECUTE_OPERATION,
    GET_TIMES,
    SET_EPOCH_TIME,
    SET_MISSION_TIME,
    LOG,
    HELP,
    QUIT,
    UNKNOWN
};


/*
 * Command structures
 */

// Generic command
struct Command
{
    Action action;

    Command(Action action)
    {
        this->action = action;
    }
};

// Command to load an assembly
struct LoadAssemblyCommand : Command
{
    std::string assemblyFile;

    LoadAssemblyCommand(std::string assemblyFile) : Command(Action::LOAD_ASSEMBLY)
    {
        this->assemblyFile = assemblyFile;
    }
};

// Command to get fields of a model
struct GetFieldsCommand : Command
{
    std::string model;

    GetFieldsCommand(std::string model) : Command(Action::GET_FIELDS)
    {
        this->model = model;
    }
};

// Command to get operations of a model
struct GetOperationsCommand : Command
{
    std::string model;

    GetOperationsCommand(std::string model) : Command(Action::GET_OPERATIONS)
    {
        this->model = model;
    }
};

// Command to get a value of a field
struct GetFieldValueCommand : Command
{
    std::string model;
    std::string field;

    GetFieldValueCommand(std::string model, std::string field) : Command(Action::GET_FIELD_VALUE)
    {
        this->model = model;
        this->field = field;
    }
};

// Command to get a value of an array field
struct GetArrayFieldValueCommand : Command
{
    std::string model;
    std::string field;
    std::string position;

    GetArrayFieldValueCommand(std::string model, std::string field, std::string position) : Command(Action::GET_ARRAY_FIELD_VALUE)
    {
        this->model = model;
        this->field = field;
        this->position = position;
    }
};

// Command to set the value of a field
struct SetFieldValueCommand : Command
{
    std::string model;
    std::string field;
    std::string value;

    SetFieldValueCommand(std::string model, std::string field, std::string value) : Command(Action::SET_FIELD_VALUE)
    {
        this->model = model;
        this->field = field;
        this->value = value;
    }
};

// Command to set the value of a position of an array field
struct SetArrayFieldValueCommand : Command
{
    std::string model;
    std::string field;
    std::string position;
    std::string value;

    SetArrayFieldValueCommand(std::string model, std::string field, std::string position, std::string value) : Command(Action::SET_ARRAY_FIELD_VALUE)
    {
        this->model = model;
        this->field = field;
        this->position = position;
        this->value = value;
    }
};

// Command to set the initial value of epoch time
struct SetEpochTimeCommand : Command
{
    std::string time;

    SetEpochTimeCommand(std::string time) : Command(Action::SET_EPOCH_TIME)
    {
        this->time = time;
    }
};

// Command to set the start value of mission time
struct SetMissionTimeCommand : Command
{
    std::string time;

    SetMissionTimeCommand(std::string time) : Command(Action::SET_MISSION_TIME)
    {
        this->time = time;
    }
};

// Command to execute an operation
struct ExecuteOperationCommand : Command
{
    std::string model;
    std::string operation;
    std::vector<std::string> parameters;

    ExecuteOperationCommand(std::string model, std::string operation, std::vector<std::string> parameters) : Command(Action::EXECUTE_OPERATION)
    {
        this->model = model;
        this->operation = operation;
        this->parameters = parameters;
    }
};


/*
 * Parser class
 */

class Parser
{

public:
    std::vector<std::string> splitArguments(const char* arguments, const char* separator = ";");
    Command* getCommand(std::string strCommand);

protected:

};

}
}
