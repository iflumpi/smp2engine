
#include "GenericComponent.h"

namespace Smp2Simulator
{
namespace Core
{

Smp::String8 GenericComponent::GetName() const
{
    return this->name;
}

Smp::String8 GenericComponent::GetDescription() const
{
    return this->description;
}

Smp::IComposite* GenericComponent::GetParent() const
{
    return this->parent;
}

}
}
