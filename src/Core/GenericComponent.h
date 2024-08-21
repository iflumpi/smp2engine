
#pragma once

#include "Smp/IComponent.h"


namespace Smp2Simulator
{
namespace Core
{

class GenericComponent : public virtual Smp::IComponent
{

public:
    // Constructor
    GenericComponent(Smp::String8 name, Smp::String8 description, Smp::IComposite* parent = nullptr)
    {
        this->name = strdup(name);
        this->description = strdup(description);
        this->parent = parent;
    }

    // Methods
    Smp::String8 GetName() const;
    Smp::String8 GetDescription() const;
    Smp::IComposite* GetParent() const;

protected:
    // Attributes
    Smp::String8 name;
    Smp::String8 description;
    Smp::IComposite* parent;

};

}
}
