
#include "Example.h"
#include "Smp/ISimulator.h"
#include "Smp/Publication/ITypeRegistry.h"


extern "C"
{

bool Initialise(Smp::ISimulator* simulator, Smp::Publication::ITypeRegistry* registry)
{
    Example* example = new Example("Example_SMP2", nullptr);
    simulator->AddModel(example);

    return true;
}

}
