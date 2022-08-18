#ifndef PWM
#define PWM
#include <string>
//#include "Gpio.h"

class Pwm{
private:
    //Gpio gpio;
    bool state = false;
    double frequency;
    double dutyCicle;
    double period;
    static int pwmNumber;

    void run();
public:
    Pwm(std::string pin, double frequency, double dutyCicle);
    ~Pwm();
    void start();
    void stop();
};

#endif
