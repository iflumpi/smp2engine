
#include "Logger.h"


namespace Smp2Simulator
{
namespace Core
{

// Return identifier of log message kind by name
Smp::Services::LogMessageKind Logger::GetLogMessageKind(Smp::String8 messageKindName)
{
    return Smp::Services::LMK_Information;
}

// Mechanism to log a messages
void Logger::Log(const Smp::IObject* sender, Smp::String8 message, Smp::Services::LogMessageKind messageKind)
{
    // Create instance with log message properties
    auto logMessage = new LogMessage();
    logMessage->simulationTime = this->timeKeeper->GetSimulationTime();
    logMessage->sender = sender;
    logMessage->message = std::string(message, strlen(message));
    logMessage->messageKind = messageKind;

    // Store log message
    this->logs.push_back(logMessage);

    // Print log message
    printf("%s\n", logMessage->getString().c_str());
}

// Return stored log messages
std::vector<Smp2Simulator::Core::LogMessage*> Logger::GetLogMessages()
{
    return this->logs;
}

// Set the time keeper related to the logger
void Logger::SetTimeKeeper(Smp::Services::ITimeKeeper* timeKeeper)
{
    this->timeKeeper = timeKeeper;
}


}
}
