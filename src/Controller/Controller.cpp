
#include "Controller.h"
#include "Smp/IDynamicInvocation.h"
#include "Core/Common.h"
#include "Core/Publication.h"
#include "Core/PublishOperation.h"
#include "Core/TypeRegistry.h"
#include <dlfcn.h>
#include <unistd.h>
#include <vector>


namespace Smp2Simulator
{
namespace Controller
{

// Load a dynamic library with the definition of an assembly with models
bool Controller::loadAssembly(const char* assemblyFile)
{
    // Open shared library with assembly
    this->handlerAssembly = dlopen(assemblyFile, RTLD_LAZY);
    if (!this->handlerAssembly)
        return false;

    // Get initialise method from the assembly file
    INITIALISE initialiseAssemblyMethod = reinterpret_cast<INITIALISE>(dlsym(this->handlerAssembly, "Initialise"));
    if (!initialiseAssemblyMethod)
    {
        dlclose(this->handlerAssembly);
        this->handlerAssembly = nullptr;
        return false;
    }

    // Create typeRegistry instance
    auto typeRegistry = new Smp2Simulator::Core::TypeRegistry();

    // Create simulator instance
    this->simulator = new Smp2Simulator::Core::Simulator(typeRegistry);


    // Call to the Initialise method of the assembly
    initialiseAssemblyMethod(this->simulator, typeRegistry);

    return true;
}

// Initialize the simulator
bool Controller::init()
{
    // Call to the publish methods of all models in the assembly
    this->simulator->Publish();

    // Call to the configure methods of all models in the assembly
    this->simulator->Configure();

    // Call to the connect methods of all models in the assembly
    this->simulator->Connect();

    return true;
}

// Run the simulator
void Controller::run()
{
    this->simulator->Run();
}

// Pause the simulator
void Controller::hold()
{
    this->simulator->Hold();
}

// Get all models names in the simulator
std::vector<std::string> Controller::getModelsNames()
{
    std::vector<std::string> modelsNames;
    auto models = this->simulator->GetModels();
    for (int i=0; i<models->size(); i++)
    {
        auto modelName = models->at(i)->GetName();
        auto strModelName = std::string(modelName, strlen(modelName));
        modelsNames.push_back(strModelName);
    }
    return modelsNames;
}

// Get the published field names of a model
// If model name passed as parameter is empty, get all the published field names in the simulator
std::vector<std::string> Controller::getFieldsNames(const char *modelName)
{
    std::vector<std::string> fieldsNames;
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();
    auto fields = publication->GetFieldsPublished();
    for (int i=0; i<fields.size(); i++)
    {
        auto field = fields.at(i);

        // If model name is null, get the full name of the field
        // Otherwise, if the name of the model is equal to the name passed as parameter, get the simple name of the field
        if (modelName == nullptr)
        {
            auto fieldName = publication->GetFullNameField(field);
            auto strField = std::string(fieldName, strlen(fieldName));
            fieldsNames.push_back(strField);
        }
        else if (strcmp(modelName, field->model->GetName()) == 0)
        {
            auto fieldName = field->name;
            auto strField = std::string(fieldName, strlen(fieldName));
            fieldsNames.push_back(strField);
        }
    }
    return fieldsNames;
}

// Get the published operation names of a model
// If model operation passed as parameter is empty, get all the published operation names in the simulator
std::vector<std::string> Controller::getOperationsNames(const char* operationName)
{
    std::vector<std::string> operationsNames;
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();
    auto operations = publication->GetOperationsPublished();
    for (int i=0; i<operations.size(); i++)
    {
        auto operation = operations.at(i);

        // If model name is null, get the full name of the operation
        // Otherwise, if the operation of the model is equal to the name passed as parameter, get the simple name of the operation
        if (operationName == nullptr)
        {
            auto operationName = publication->GetFullNameOperation(operation);
            auto strOperation = std::string(operationName, strlen(operationName));
            operationsNames.push_back(strOperation);
        }
        else if (strcmp(operationName, operation->model->GetName()) == 0)
        {
            auto publishOperation = dynamic_cast<Smp2Simulator::Core::PublishOperation*>(operation->publishOperation);
            auto operationName = publishOperation->GetName();
            auto strOperation = std::string(operationName, strlen(operationName));
            operationsNames.push_back(strOperation);
        }
    }
    return operationsNames;
}


// Get the value of a field in a model
std::string Controller::getFieldValue(const char* modelName, const char* fieldName)
{
    auto fullNameField = this->getFullNameField(modelName, fieldName);
    return this->getFieldValue(fullNameField.c_str());
}

// Return the value of a field by its full name
std::string Controller::getFieldValue(const char* fieldFullName)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get and return the field value
    auto any = publication->GetFieldValue(fieldFullName);
    auto value = Smp2Simulator::Core::Common::GetValue(any);
    return value;
}

// Get the value of a position of an array
std::string Controller::getArrayFieldValue(const char* modelName, const char* fieldName, int index)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get and return the array field value
    auto fullNameField = this->getFullNameField(modelName, fieldName);
    auto any = publication->GetArrayItemValue(fullNameField.c_str(), index);
    auto value = Smp2Simulator::Core::Common::GetValue(any);
    return value;
}

// Set the value of a field
bool Controller::setFieldValue(const char* modelName, const char* fieldName, const char* strValue)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get the field according the model and field name
    auto fullNameField = this->getFullNameField(modelName, fieldName);
    auto field = publication->GetField(fullNameField.c_str());

    // If the field was found or its input flag is true, update the field value and return true
    // Otherwise, return false
    if (field != nullptr && field->input)
    {
        auto anyValue = Smp2Simulator::Core::Common::CreateAnySimple(strValue, field->typeKind);
        publication->SetFieldValue(fullNameField.c_str(), anyValue);
        return true;
    }
    else
        return false;
}

// Set the value of an array field
bool Controller::setArrayFieldValue(const char* modelName, const char* fieldName, int index, const char* strValue)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get the field according the model and field name
    auto fullNameField = this->getFullNameField(modelName, fieldName);
    auto field = publication->GetField(fullNameField.c_str());

    // If the field was found or its input flag is true, update the field value and return true
    // Otherwise, return false
    if (field != nullptr && field->input)
    {
        auto anyValue = Smp2Simulator::Core::Common::CreateAnySimple(strValue, field->typeKind);
        publication->SetArrayItemValue(fullNameField.c_str(), index, anyValue);
        return true;
    }
    else
        return false;
}

// Execute a published operation
std::string Controller::executeOperation(const char* modelName, const char* operationName, std::vector<std::string> parametersValues)
{
    // Create operation request
    auto model = dynamic_cast<Smp::IDynamicInvocation *>(this->simulator->GetModel(modelName));
    auto request = model->CreateRequest(operationName);

    // Set parameters to the request instance
    for (int i=0; i<request->GetParameterCount(); i++)
    {
        auto parameterType = request->GetParameterValue(i).type;
        auto parameterValue = Smp2Simulator::Core::Common::CreateAnySimple(parametersValues.at(i).c_str(), parameterType);
        request->SetParameterValue(i, parameterValue);
    }

    // Invoke operation
    model->Invoke(request);

    // Get response of the operation
    auto value = request->GetReturnValue();
    auto response = Smp2Simulator::Core::Common::GetValue(value);

    // Delete request instance
    model->DeleteRequest(request);

    return response;
}

// Check whether the simulator is running
bool Controller::isExecuting()
{
    return this->simulator->GetState() == Smp::SimulatorStateKind::SSK_Executing;
}

// Check whether a model is loaded in the simulator
bool Controller::isModelLoaded(const char* modelName)
{
    auto models = this->getModelsNames();
    for (int i=0; i<models.size(); i++)
    {
        auto model = models.at(i);
        if (strcmp(model.c_str(), modelName) == 0)
            return true;
    }
    return false;
}

// Check whether a field is published by a model
bool Controller::isFieldPublished(const char* modelName, const char* fieldName)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get full name of the field
    auto fullNameField = this->getFullNameField(modelName, fieldName);

    // Return if the field is published
    return publication->GetField(fullNameField.c_str()) != nullptr;
}

// Check whether a operation is published by a model
bool Controller::isOperationPublished(const char* modelName, const char* fieldName)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get full name of the operation
    auto fullNameOperation = this->getFullNameOperation(modelName, fieldName);

    // Return if the field is published
    return publication->GetOperation(fullNameOperation.c_str()) != nullptr;
}

// Check whether a field is an array
bool Controller::isArrayField(const char* modelName, const char* fieldName)
{
    // Get publication instance
    auto publication = (Smp2Simulator::Core::Publication*)this->simulator->GetPublication();

    // Get field
    auto fullNameField = this->getFullNameField(modelName, fieldName);
    auto field = publication->GetField(fullNameField.c_str());

    // Return if the field is an array
    return publication->IsArrayField(field);
}

// Return the number of parameters of an operation
int Controller::getOperationParametersCount(const char* modelName, const char* operationName)
{
    // Create operation request
    auto model = dynamic_cast<Smp::IDynamicInvocation *>(this->simulator->GetModel(modelName));
    auto request = model->CreateRequest(operationName);

    // Get parameters count
    int count = request->GetParameterCount();

    // Delete request
    model->DeleteRequest(request);

    // Return parameters count
    return count;

}

// Get the current value of the simulation time
Smp::Duration Controller::getSimulationTime()
{
    return this->simulator->GetTimeKeeper()->GetSimulationTime();
}

// Get the current value of the epoch time
Smp::DateTime Controller::getEpochTime()
{
    return this->simulator->GetTimeKeeper()->GetEpochTime();
}

// Get the current value of the mission time
Smp::DateTime Controller::getMissionTime()
{
    return this->simulator->GetTimeKeeper()->GetMissionTime();
}

// Set the value of epoch time
bool Controller::setEpochTime(Smp::DateTime time)
{
    this->simulator->GetTimeKeeper()->SetEpochTime(time);
    return true;
}

// Set the value of mission time
bool Controller::setMissionTime(Smp::DateTime time)
{
    this->simulator->GetTimeKeeper()->SetMissionStart(time);
    return true;
}

// Get all log messages stored in the logger
std::vector<Smp2Simulator::Core::LogMessage*> Controller::getLogMessages()
{
    auto logger = (Smp2Simulator::Core::Logger*)this->simulator->GetLogger();
    return logger->GetLogMessages();
}

// Get a full name of a field
std::string Controller::getFullNameField(const char* modelName, const char* fieldName)
{
    std::string fullNameField;
    fullNameField.append(modelName);
    fullNameField.append(".");
    fullNameField.append(fieldName);
    return fullNameField;
}

// Get a full name of a operation
std::string Controller::getFullNameOperation(const char* modelName, const char* operationName)
{
    std::string fullNameOperation;
    fullNameOperation.append(modelName);
    fullNameOperation.append(".");
    fullNameOperation.append(operationName);
    return fullNameOperation;
}

// Close the handler
void Controller::close()
{
    dlclose(this->handlerAssembly);
}

}
}
