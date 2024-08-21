
#include <inttypes.h>


int loadAssembly(const char* assemblyFile);
bool init();
void run();
void hold();
bool isExecuting();
int64_t getSimulationTime();
uint64_t getLogsCount();
const char* getLogs(uint64_t index);
const char* processCommand(const char* command);
const char* getLastValue();
void close();
