
#include "Model.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/IPublication.h"
#include <vector>


namespace Adcs
{

class ReactionWheel : virtual public Model, virtual public ::Smp::IDynamicInvocation

{

public:
    // Constructor
    ReactionWheel(::Smp::String8 name = "ReactionWheel", ::Smp::IComposite* parent = nullptr);

    // IModel methods
    void Publish(Smp::IPublication* receiver);
    void Configure(Smp::Services::ILogger* logger);
    void Connect(Smp::ISimulator* simulator);

    // IDynamicInvocation methods
    Smp::IRequest* CreateRequest(Smp::String8 operationName);
    void Invoke(Smp::IRequest* request);
    void DeleteRequest(Smp::IRequest* request);

    // Methods
    void SetTorque(Smp::Float64 t0, Smp::Float64 t1, Smp::Float64 t2);

private:
    // Attributes
    Smp::Float64 torque[3];

};

}
