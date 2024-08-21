
#include "Model.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/IPublication.h"
#include <vector>


namespace Adcs
{

class StarTracker : virtual public Model, virtual public ::Smp::IDynamicInvocation

{

public:
    // Constructor
    StarTracker(::Smp::String8 name = "StarTracker", ::Smp::IComposite* parent = nullptr);

    // IModel methods
    void Publish(Smp::IPublication* receiver);
    void Configure(Smp::Services::ILogger* logger);
    void Connect(Smp::ISimulator* simulator);

    // IDynamicInvocation methods
    Smp::IRequest* CreateRequest(Smp::String8 operationName);
    void Invoke(Smp::IRequest* request);
    void DeleteRequest(Smp::IRequest* request);

    // Methods
    void SetQuaternion(Smp::Float64 q0, Smp::Float64 q1, Smp::Float64 q2, Smp::Float64 q3);
    Smp::Float64* GetQuaternion();

private:
    // Attributes
    Smp::Float64 quaternion[4];

};

}
