
#include "Smp/Services/IEventManager.h"
#include "GenericComponent.h"


namespace Smp2Simulator
{
namespace Core
{


/*
 * EventSubscribed structure
 */

struct EventSubscribed
{
    Smp::Services::EventId event;
    const Smp::IEntryPoint* entryPoint;
};


/*
 * EventManager class
 */
class EventManager : public Smp::Services::IEventManager, public GenericComponent
{

public:
    // Constructor
    EventManager(Smp::String8 name = "EventManager", Smp::String8 description = "") : GenericComponent(name, description) { }

    // IEventManager methods
    Smp::Services::EventId GetEventId(Smp::String8 eventName);
    void Subscribe(Smp::Services::EventId event, const Smp::IEntryPoint* entryPoint);
    void Unsubscribe(Smp::Services::EventId event, const Smp::IEntryPoint* entryPoint);
    void Emit(Smp::Services::EventId event);


protected:
    // Attributes
    std::vector<EventSubscribed*> eventsSubscribed;

};

}
}
