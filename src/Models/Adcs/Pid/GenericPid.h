

namespace Adcs
{
namespace Pid
{

class GenericPid
{

public:
    // Constructor
    GenericPid(double kp, double ki, double kd, double delta, double max, double min)
    {
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;
        this->delta = delta;
        this->max = max;
        this->min = min;
        this->integralError = 0;
        this->lastError = 0;
    }

    // Methods
    double execute(double currentValue, double target);
    void setKp(double kp);
    void setKi(double ki);
    void setKd(double kp);
    void setDelta(double delta);


protected:
    // Attributes
    double kp;
    double ki;
    double kd;
    double delta;
    double max;
    double min;
    double integralError;
    double lastError;

};

}
};
