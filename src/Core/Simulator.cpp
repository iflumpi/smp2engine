
#include "Simulator.h"
#include "TimeKeeper.h"
#include "Logger.h"
#include "Scheduler.h"
#include "EventManager.h"
#include "Publication.h"
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef WINDOWS
	#include <windows.h>
#else
	#include <chrono>
#endif


namespace Smp2Simulator
{
namespace Core
{

// Constructor
Simulator::Simulator(Smp::Publication::ITypeRegistry* registry) : GenericComponent("Simulator", "")
{
    // Initialization of SMP2 services
    auto logger = new Logger();
    auto timeKeeper = new TimeKeeper();
    auto scheduler = new Scheduler();
    auto eventManager = new EventManager();
    logger->SetTimeKeeper(timeKeeper);
    scheduler->SetTimeKeeper(timeKeeper);


    // Add SMP2 services to the service collection
    this->services.push_back(logger);
    this->services.push_back(timeKeeper);
    this->services.push_back(scheduler);
    this->services.push_back(eventManager);

    // Initialization of publication
    this->publication = new Publication(registry);

    // Set state to building
    this->SetState(Smp::SimulatorStateKind::SSK_Building);


}

// Run the timer related to the simulator
void Simulator::RunTimer()
{
	TimeKeeper* timeKeeper = (TimeKeeper *)this->GetTimeKeeper();
    auto scheduler = (Scheduler *)this->GetScheduler();
    auto initialTime = timeKeeper->GetSimulationTime();
	
	#ifdef WINDOWS    
		LARGE_INTEGER start, end, elapseMcs;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency); 
		QueryPerformanceCounter(&start);
		while(this->state == Smp::SimulatorStateKind::SSK_Executing)
		{
			QueryPerformanceCounter(&end);		
			elapseMcs.QuadPart = end.QuadPart - start.QuadPart;
			elapseMcs.QuadPart *= 1000000;
			elapseMcs.QuadPart /= frequency.QuadPart;		
			timeKeeper->SetSimulationTime(initialTime + elapseMcs.QuadPart*1e3);
			scheduler->ExecuteEntryPoints();
		}    
	#else
		auto start = std::chrono::high_resolution_clock::now();	
		while(this->state == Smp::SimulatorStateKind::SSK_Executing)
		{
	        timeKeeper->SetSimulationTime(
            initialTime +
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()*1e3);				
			scheduler->ExecuteEntryPoints();
		}
	#endif
}

// Return the publication instance
Smp::IPublication* Simulator::GetPublication()
{
    return this->publication;
}

// Get all containers
const Smp::ContainerCollection* Simulator::GetContainers() const
{
    // NOT IMPLEMENTED
    return nullptr;
}

// Get a container by name
Smp::IContainer* Simulator::GetContainer(Smp::String8 name) const
{
    // NOT IMPLEMENTED
    return nullptr;
}

// Get all models
const Smp::ModelCollection* Simulator::GetModels()
{
    return &this->models;
}

// Get a root model by name
Smp::IModel* Simulator::GetModel(Smp::String8 name)
{
    for (int i=0; i<this->models.size(); i++)
    {
        if (strcmp(this->models.at(i)->GetName(), name) == 0)
            return this->models[i];
    }
    return nullptr;
}

// Add a root model
void Simulator::AddModel(Smp::IModel* model)
{
    if (this->GetModel(model->GetName()) != nullptr)
    {
        throw Smp::DuplicateName(model->GetName());
    }

    this->models.push_back(model);
}

// Get all services
const Smp::ServiceCollection* Simulator::GetServices()
{
    return &this->services;
}

// Get a service by name
Smp::IService* Simulator::GetService(Smp::String8 name)
{
    for (int i=0; i<this->services.size(); i++)
    {
        if (strcmp(this->services.at(i)->GetName(), name) == 0)
            return this->services[i];
    }

    return nullptr;
}

// Add a user-defined service
void Simulator::AddService(Smp::IService* service)
{
    this->services.push_back(service);
}

// Get logger service
Smp::Services::ILogger* Simulator::GetLogger() const
{
    return dynamic_cast<Smp::Services::ILogger*>(this->services.at(0));
}

// Get scheduler service
Smp::Services::IScheduler* Simulator::GetScheduler() const
{
    return dynamic_cast<Smp::Services::IScheduler*>(this->services.at(2));
}

// Get time keeper service
Smp::Services::ITimeKeeper* Simulator::GetTimeKeeper() const
{
    return dynamic_cast<Smp::Services::ITimeKeeper*>(this->services.at(1));
}

// Get event manager service
Smp::Services::IEventManager* Simulator::GetEventManager() const
{
    return dynamic_cast<Smp::Services::IEventManager*>(this->services.at(3));
}

// Get simulator state
Smp::SimulatorStateKind Simulator::GetState() const
{
    return this->state;
}

// Call Publish() methods of models
void Simulator::Publish()
{
    auto publication = (Publication*)this->publication;
    for (int i=0; i<this->models.size(); i++)
    {
        auto model = this->models.at(i);
        publication->SetCurrentPublisherModel(model);
        model->Publish(publication);
    }
    publication->SetCurrentPublisherModel(nullptr);
}

// Call Configure() method of models
void Simulator::Configure()
{
    for (int i=0; i<this->models.size(); i++)
    {
        auto model = this->models.at(i);
        model->Configure(this->GetLogger());
    }
}

// Enter Connecting state
void Simulator::Connect()
{
    for (int i=0; i<this->models.size(); i++)
    {
        auto model = this->models.at(i);
        model->Connect(this);
    }
    this->SetState(Smp::SimulatorStateKind::SSK_Connecting);
}

// Enter initialising state
void Simulator::Initialise()
{
    this->SetState(Smp::SimulatorStateKind::SSK_Initialising);
}

// Enter standby state
void Simulator::Hold()
{
    this->SetState(Smp::SimulatorStateKind::SSK_Standby);
    this->ttimer->join();

    this->GetLogger()->Log(this, "Simulation paused", Smp::Services::LMK_Information);
}

// Enter executing state
void Simulator::Run()
{
    this->SetState(Smp::SimulatorStateKind::SSK_Executing);
    ttimer = new std::thread([this]()
    {
        this->RunTimer();
    } );

    this->GetLogger()->Log(this, "Simulation executing", Smp::Services::LMK_Information);
}

// Enter storing state
void Simulator::Store(Smp::String8 filename)
{
    // NOT IMPLEMENTED
}

// Enter restoring state
void Simulator::Restore(Smp::String8 filename)
{
    // NOT IMPLEMENTED
}

// Enter exiting state
void Simulator::Exit()
{
}

// Enter aborting state
void Simulator::Abort()
{
}

// Add initialisation entry point
void Simulator::AddInitEntryPoint(Smp::IEntryPoint* entryPoint)
{
    // NOT IMPLEMENTED
}

// Set simulation state
void Simulator::SetState(Smp::SimulatorStateKind state)
{
    if (this->state != state)
    {
        // Get event manager
        auto eventManager = this->GetEventManager();

        // Emit leaving state event
        switch (this->state)
        {
            case Smp::SimulatorStateKind::SSK_Connecting:
                eventManager->Emit(Smp::Services::SMP_LeaveConnectingId);
                break;
            case Smp::SimulatorStateKind::SSK_Executing:
                eventManager->Emit(Smp::Services::SMP_LeaveExecutingId);
                break;
            case Smp::SimulatorStateKind::SSK_Initialising:
                eventManager->Emit(Smp::Services::SMP_LeaveInitialisingId);
                break;
            case Smp::SimulatorStateKind::SSK_Restoring:
                eventManager->Emit(Smp::Services::SMP_LeaveRestoringId);
                break;
            case Smp::SimulatorStateKind::SSK_Standby:
                eventManager->Emit(Smp::Services::SMP_LeaveStandbyId);
                break;
            case Smp::SimulatorStateKind::SSK_Storing:
                eventManager->Emit(Smp::Services::SMP_LeaveStoringId);
                break;
        }

        // Set state
        this->state = state;

        // Emit entering state event
        switch (state)
        {
            case Smp::SimulatorStateKind::SSK_Aborting:
                eventManager->Emit(Smp::Services::SMP_EnterAbortingId);
                break;
            case Smp::SimulatorStateKind::SSK_Executing:
                eventManager->Emit(Smp::Services::SMP_EnterExecutingId);
                break;
            case Smp::SimulatorStateKind::SSK_Exiting:
                eventManager->Emit(Smp::Services::SMP_EnterExitingId);
                break;
            case Smp::SimulatorStateKind::SSK_Initialising:
                eventManager->Emit(Smp::Services::SMP_EnterInitialisingId);
                break;
            case Smp::SimulatorStateKind::SSK_Restoring:
                eventManager->Emit(Smp::Services::SMP_EnterRestoringId);
                break;
            case Smp::SimulatorStateKind::SSK_Standby:
                eventManager->Emit(Smp::Services::SMP_EnterStandbyId);
                break;
            case Smp::SimulatorStateKind::SSK_Storing:
                eventManager->Emit(Smp::Services::SMP_EnterStoringId);
                break;
        }
    }
}

}
}
