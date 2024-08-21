
#include "Interpreter/Interpreter.h"
#include <vector>


auto interpreter = new Smp2Simulator::Interpreter::Interpreter();

extern "C"
{
    int loadAssembly(const char* assemblyFile)
    {
        interpreter->loadAssembly(assemblyFile);
		return 0;
    }

    bool init()
    {
        interpreter->init();
		return 0;
    }

    void run()
    {
        interpreter->run();
    }

    void hold()
    {
        interpreter->hold();
    }    

    bool isExecuting()
    {
        return interpreter->isExecuting();
    }
	
	uint64_t getLogsCount()
	{
		auto controller = interpreter->getController();
		auto logMessages = controller->getLogMessages();
		return logMessages.size();
	}

    const char* getLogs(uint64_t index)
    {
		auto controller = interpreter->getController();
        std::string strLogs = "";
        auto logMessages = controller->getLogMessages();
        for (int i=index; i<logMessages.size(); i++)
        {
            auto logMessage = logMessages.at(i);
            strLogs.append(logMessage->getString());
            strLogs.append("\n");
        }
		char* ptr = new char[strLogs.length() + 1];
		strcpy(ptr, strLogs.c_str());
        return ptr;
    }

    int64_t getSimulationTime()
    {
		auto controller = interpreter->getController();
        return controller->getSimulationTime();
    }
	
	const char* processCommand(const char* command)
	{
		auto response = interpreter->processCommand(command);		
		char* ptr = new char[response.length() + 1];
		strcpy(ptr, response.c_str());
        return ptr;
	}
	
	const char* getLastValue()
	{
		auto value = interpreter->getLastValue();
		char* ptr = new char[value.length() + 1];
		strcpy(ptr, value.c_str());
		return ptr;
	}
	
	void close()
	{
		auto controller = interpreter->getController();
		controller->close();
	}
	
}

