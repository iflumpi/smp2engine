
#include "GenericPid.h"

namespace Adcs
{
namespace Pid
{


// Execute PID control algorithm according current and target value
double GenericPid::execute(double currentValue, double target)
{
    // Calculate error
    double error = target - currentValue;

    // Calculate proportional value
    double proportionalValue = this->kp * error;

    // Calculate integral value
    this->integralError += error * this->delta;
    double integralValue = this->ki * this->integralError;

    // Calculate derivative value
    double derivativeError = (error - this->lastError) / this->delta;
    double derivativeValue = this->kd * derivativeError;

    // Calculate total value
    double totalValue = proportionalValue + integralValue + derivativeValue;
    if (totalValue > this->max)
        totalValue = this->max;
    if (totalValue < this->min)
        totalValue = this->min;

    // Store last error
    this->lastError = error;

    // Return total value
    return totalValue;
}

// Set proportional gain
void GenericPid::setKp(double kp)
{
    this->kp = kp;
}

// Set integral gain
void GenericPid::setKi(double ki)
{
    this->ki = ki;
}

// Set derivative gain
void GenericPid::setKd(double kd)
{
    this->kd = kd;
}

// Set delta
void GenericPid::setDelta(double delta)
{
    this->delta = delta;
}


}
}
