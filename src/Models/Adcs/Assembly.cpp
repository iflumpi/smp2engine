
#include "AdcsController.h"
#include "Smp/ISimulator.h"
#include "Smp/Publication/ITypeRegistry.h"


extern "C"
{

bool Initialise(Smp::ISimulator* simulator, Smp::Publication::ITypeRegistry* registry)
{
    // Create gyroscope instance
    auto gyroscope = new Adcs::Gyroscope();
    simulator->AddModel(gyroscope);

    // Create star tracker instance
    auto starTracker = new Adcs::StarTracker();
    simulator->AddModel(starTracker);

    // Create reaction wheel instance
    auto reactionWheel = new Adcs::ReactionWheel();
    simulator->AddModel(reactionWheel);

    // Create ADCS module instance
    auto adcsController = new Adcs::AdcsController(gyroscope, starTracker, reactionWheel);
    simulator->AddModel(adcsController);

    return true;
}

}
