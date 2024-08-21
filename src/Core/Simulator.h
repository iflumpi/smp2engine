
#include "Smp/ISimulator.h"
#include "Smp/IModel.h"
#include "Smp/IService.h"
#include "Smp/IPublication.h"
#include "GenericComponent.h"
#include <thread>


namespace Smp2Simulator
{
namespace Core
{

class Simulator : public virtual Smp::ISimulator, public GenericComponent
{

public:
    // Constructor
    Simulator(Smp::Publication::ITypeRegistry* registry);

    // ISimulator methods
    const Smp::ContainerCollection* GetContainers() const;
    Smp::IContainer* GetContainer(Smp::String8 name) const;
    const Smp::ModelCollection* GetModels();
    Smp::IModel* GetModel(Smp::String8 name);
    void AddModel(Smp::IModel* model);
    const Smp::ServiceCollection* GetServices();
    Smp::IService* GetService(Smp::String8 name);
    void AddService(Smp::IService* service);
    Smp::Services::ILogger* GetLogger() const;
    Smp::Services::IScheduler* GetScheduler() const;
    Smp::Services::ITimeKeeper* GetTimeKeeper() const;
    Smp::Services::IEventManager* GetEventManager() const;
    Smp::SimulatorStateKind GetState() const;
    void Publish();
    void Configure();
    void Connect();
    void Initialise();
    void Hold();
    void Run();
    void Store(Smp::String8 filename);
    void Restore(Smp::String8 filename);
    void Exit();
    void Abort();
    void AddInitEntryPoint(Smp::IEntryPoint* entryPoint);

    // Methods
    Smp::IPublication* GetPublication();

protected:
    // Attributes
    Smp::SimulatorStateKind state = Smp::SimulatorStateKind::SSK_Initialising;
    Smp::ModelCollection models;
    Smp::ServiceCollection services;
    Smp::IPublication* publication;
    std::thread* ttimer = nullptr;;

    // Methods
    void RunTimer();
    void SetState(Smp::SimulatorStateKind state);


};
}
}
