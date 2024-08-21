
#include "Model.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/IPublication.h"
#include <vector>


namespace Adcs
{

class Gyroscope : virtual public Model, virtual public ::Smp::IDynamicInvocation

{

public:
    // Constructor
    Gyroscope(::Smp::String8 name = "Gyroscope", ::Smp::IComposite* parent = nullptr);

    // IModel methods
    void Publish(Smp::IPublication* receiver);
    void Configure(Smp::Services::ILogger* logger);
    void Connect(Smp::ISimulator* simulator);

    // IDynamicInvocation methods
    Smp::IRequest* CreateRequest(Smp::String8 operationName);
    void Invoke(Smp::IRequest* request);
    void DeleteRequest(Smp::IRequest* request);

    // Methods
    void SetOmega(Smp::Float64 w0, Smp::Float64 w1, Smp::Float64 w2);
    Smp::Float64* GetOmega();

private:
    // Attributes
    Smp::Float64 omega[3];

};

}
