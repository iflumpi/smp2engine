
#include "Core/Simulator.h"
#include "Core/Logger.h"
#include <string>
#include <vector>


namespace Smp2Simulator
{
namespace Controller
{

class Controller
{

// Type definition for initialise method in assembly
typedef void (*INITIALISE)(Smp::ISimulator*, Smp::Publication::ITypeRegistry*);

public:
    // Methods
    bool loadAssembly(const char* assemblyFile);
    bool init();
    void run();
    void hold();
    std::vector<std::string> getModelsNames();
    std::vector<std::string> getFieldsNames(const char* modelName = nullptr);
    std::vector<std::string> getOperationsNames(const char* operationName = nullptr);
    std::string getFieldValue(const char* modelName, const char* fieldName);
    std::string getFieldValue(const char* fieldName);
    std::string getArrayFieldValue(const char* modelName, const char* fieldName, int index);
    bool setFieldValue(const char* modelName, const char* fieldName, const char* strValue);
    bool setArrayFieldValue(const char* modelName, const char* fieldName, int index, const char* strValue);
    std::string executeOperation(const char* modelName, const char* operationName, std::vector<std::string> parametersValues);
    bool isExecuting();
    Smp::Duration getSimulationTime();
    Smp::DateTime getEpochTime();
    Smp::Duration getMissionTime();
    bool setEpochTime(Smp::DateTime time);
    bool setMissionTime(Smp::DateTime time);
    std::vector<Smp2Simulator::Core::LogMessage*> getLogMessages();
    bool isModelLoaded(const char* modelName);
    bool isFieldPublished(const char* modelName, const char* fieldName);
    bool isOperationPublished(const char* modelName, const char* fieldName);
    bool isArrayField(const char* modelName, const char* fieldName);
    int getOperationParametersCount(const char* modelName, const char* operationName);
    void close();


protected:
    // Attributes
    void* handlerAssembly = nullptr;
    Smp2Simulator::Core::Simulator* simulator = nullptr;

    // Methods
    std::string getFullNameField(const char* modelName, const char* fieldName);
    std::string getFullNameOperation(const char* modelName, const char* operationName);

};

}
}
