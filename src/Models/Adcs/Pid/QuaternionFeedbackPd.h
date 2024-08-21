
#include <vector>


namespace Adcs
{
namespace Pid
{

class QuaternionFeedbackPd
{

public:
    // Constructor
    QuaternionFeedbackPd(double kw, double kq, double delta)
    {
        this->kw = kw;
        this->kq = kq;
        this->delta = delta;
    }

    // Methods
    std::vector<double> execute(std::vector<double> currentQuaternion, std::vector<double> currentOmega, std::vector<double> targetQuaternion);
    void setKw(double kw);
    void setKq(double kq);
    void setDelta(double delta);


protected:
    // Attributes
    double kw;
    double kq;
    double delta;

};

}
};
