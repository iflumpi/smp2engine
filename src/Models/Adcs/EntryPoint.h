
#include "Smp/IEntryPoint.h"


namespace Adcs
{

template<class EntryPointPublisherType>
class EntryPoint : public Smp::IEntryPoint
{

public:
EntryPoint(Smp::String8 name, Smp::String8 description, EntryPointPublisherType* publisher, void (EntryPointPublisherType::*entryPoint)(void))
{
    this->name = name;
    this->description = description;
    this->publisher = publisher;
    this->entryPoint = entryPoint;
}

virtual Smp::String8 GetName() const
{
    return name;
}

virtual Smp::String8 GetDescription() const
{
    return description;
}

virtual Smp::IComponent* GetOwner() const
{
    return publisher;
}

void Execute() const
{
    (publisher->*entryPoint)();
}

protected:
    Smp::String8 name; // Name of entry point
    Smp::String8 description; // Description of entry point
    EntryPointPublisherType* publisher; // Entry point publisher
    void (EntryPointPublisherType::*entryPoint)(void); // Instance method

};

};
