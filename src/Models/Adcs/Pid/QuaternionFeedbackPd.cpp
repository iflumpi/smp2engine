
#include "QuaternionFeedbackPd.h"

namespace Adcs
{
namespace Pid
{


// Execute PD control algorithm according current and target value
std::vector<double> QuaternionFeedbackPd::execute(std::vector<double> currentQuaternion, std::vector<double> currentOmega, std::vector<double> targetQuaternion)
{
    // Calculate axis error form quaternions
    auto q1Error = ( targetQuaternion.at(0)) * (currentQuaternion.at(0)) + ( targetQuaternion.at(1)) * (currentQuaternion.at(1)) +
                   (-targetQuaternion.at(2)) * (currentQuaternion.at(2)) + (-targetQuaternion.at(3)) * (currentQuaternion.at(3));
    auto q2Error = (-targetQuaternion.at(1)) * (currentQuaternion.at(0)) + ( targetQuaternion.at(0)) * (currentQuaternion.at(1)) +
                   ( targetQuaternion.at(3)) * (currentQuaternion.at(2)) + (-targetQuaternion.at(2)) * (currentQuaternion.at(3));
    auto q3Error = ( targetQuaternion.at(2)) * (currentQuaternion.at(0)) + (-targetQuaternion.at(3)) * (currentQuaternion.at(1)) +
                   ( targetQuaternion.at(0)) * (currentQuaternion.at(2)) + (-targetQuaternion.at(1)) * (currentQuaternion.at(3));
	auto q4Error = ( targetQuaternion.at(3)) * (currentQuaternion.at(0)) + ( targetQuaternion.at(2)) * (currentQuaternion.at(1)) +
                   ( targetQuaternion.at(1)) * (currentQuaternion.at(2)) + ( targetQuaternion.at(0)) * (currentQuaternion.at(3));

    // Calculate torque
    std::vector<double> torque;
    auto t1Torque = (this->kw * currentOmega.at(0)) + (this->kq * q2Error);
    auto t2Torque = (this->kw * currentOmega.at(1)) + (this->kq * q3Error);
    auto t3Torque = (this->kw * currentOmega.at(2)) + (this->kq * q4Error);
    torque.push_back(t1Torque);
    torque.push_back(t2Torque);
    torque.push_back(t3Torque);

    // Return torque
    return torque;
}

// Set proportional gain
void QuaternionFeedbackPd::setKw(double kw)
{
    this->kw = kw;
}

// Set derivative gain
void QuaternionFeedbackPd::setKq(double kq)
{
    this->kq = kq;
}

// Set delta
void QuaternionFeedbackPd::setDelta(double delta)
{
    this->delta = delta;
}


}
}
