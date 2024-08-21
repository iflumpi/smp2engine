
#include "Model.h"
#include "Gyroscope.h"
#include "StarTracker.h"
#include "ReactionWheel.h"
#include "EntryPoint.h"
#include "Smp/IPublication.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/Publication/IPublishOperation.h"
#include <vector>
#include "Pid/QuaternionFeedbackPd.h"


namespace Adcs
{

class AdcsController : virtual public Model, virtual public ::Smp::IDynamicInvocation

{

public:
    // Constructor and destructor
    AdcsController(Gyroscope* gyroscope, StarTracker* starTracker, ReactionWheel* reactionWheel,
               ::Smp::String8 name = "AdcsController", ::Smp::IComposite* parent = nullptr);
    ~AdcsController();

    // IModel methods
    void Publish(Smp::IPublication* receiver);
    void Configure(Smp::Services::ILogger* logger);
    void Connect(Smp::ISimulator* simulator);

    // IDynamicInvocation methods
    Smp::IRequest* CreateRequest(Smp::String8 operationName);
    void Invoke(Smp::IRequest* request);
    void DeleteRequest(Smp::IRequest* request);

    // Selector methods
    Gyroscope* GetGyroscope();
    StarTracker* GetStarTracker();
    ReactionWheel* GetReactionWheel();

    // Methods
    void AcquireSensorsData(std::vector<Smp::Float64>& quaternion, std::vector<Smp::Float64>& omega);
    std::vector<Smp::Float64> executePd(std::vector<Smp::Float64> quaternion, std::vector<Smp::Float64> omega);
    void SendTorqueRw(std::vector<Smp::Float64> torque);
    void ExecuteControlStep();
    void SetPdParameters(Smp::Float64 kw, Smp::Float64 kq);
    void SetTargetOrientation(Smp::Float64 t0, Smp::Float64 t1, Smp::Float64 t2, Smp::Float64 t3);
    void EnableCyclicalControlEvent(Smp::Float64 period);
    void DisableCyclicalControlEvent();

protected:
    // Attributes
    EntryPoint<AdcsController>* entryPointStep;
    Gyroscope* gyroscope;
    StarTracker* starTracker;
    ReactionWheel* reactionWheel;
    Pid::QuaternionFeedbackPd* pdController;
    std::vector<Smp::Float64> targetOrientation;
    Smp::Services::EventId controlEventId;

    // Constants
    const double INITIAL_KW_PID_VALUE = 1;
    const double INITIAL_KQ_PID_VALUE = 1;
    const double INITIAL_DELTA_PID_VALUE = 0.25;

};

}
