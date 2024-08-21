
#include "Smp/Services/ILogger.h"
#include "Smp/Services/ITimeKeeper.h"
#include "GenericComponent.h"

namespace Smp2Simulator
{
namespace Core
{

/*
 * Struct LogMessage
 */

struct LogMessage
{
    Smp::Duration simulationTime;
    const Smp::IObject* sender;
    std::string message;
    Smp::Services::LogMessageKind messageKind;

    std::string getString()
    {		
        std::string str;		
        str.append(std::to_string(this->simulationTime));
        str.append(" | ");
        str.append(sender->GetName());
        str.append(" | ");
        str.append(this->getNameLogMessageKind());
        str.append(" | ");
        str.append(message);
        return str;
    }

    Smp::String8 getNameLogMessageKind()
    {
        switch (this->messageKind)
        {
            case Smp::Services::LMK_Information:
                return Smp::Services::LMK_InformationName;
            case Smp::Services::LMK_Debug:
                return Smp::Services::LMK_DebugName;
            case Smp::Services::LMK_Warning:
                return Smp::Services::LMK_WarningName;
            case Smp::Services::LMK_Error:
                return Smp::Services::LMK_ErrorName;
            default:
                return Smp::Services::LMK_InformationName;
        }
    }
};


/*
 * Class Logger
 */

class Logger : public Smp::Services::ILogger, public GenericComponent
{

public:
    // Constructor
    Logger(Smp::String8 name = "Logger", Smp::String8 description = "") : GenericComponent(name, description) { }

    // ILogger methods
    Smp::Services::LogMessageKind GetLogMessageKind(Smp::String8 messageKindName);
    void Log(const IObject* sender, Smp::String8 message, Smp::Services::LogMessageKind messageKind = Smp::Services::LMK_Information);
    std::vector<LogMessage*> GetLogMessages();

    // Methods
    void SetTimeKeeper(Smp::Services::ITimeKeeper* timeKeeper);

protected:
    // Attributes
    std::vector<LogMessage*> logs;
    Smp::Services::ITimeKeeper* timeKeeper = nullptr;

};

}
}
