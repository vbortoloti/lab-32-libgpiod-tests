#ifndef GPIO
#define GPIO
#include <string>
#include <gpiod.hpp>

class Gpio
{
private:
    enum Pin
    {   
        A28 = 28,
        B0  = 32,
        B1  = 33,
        B2  = 34,
        B8  = 40,
        B10 = 42,
        B13 = 45,
        B15 = 47,
        B16 = 48,
        B18 = 50,
        B19 = 51, 
        C0  = 64, 
        C1  = 65, 
        C4  = 68,
        C5  = 69,
        C6  = 70,
        C23 = 87,
        C24 = 88,
        D30 = 126,
        E2  = 130,
        E3  = 131  
    };

    std::string alias;
    ::gpiod::chip chip;
    std::string chipNumber;
    ::gpiod::line line;
    Pin pin;
    int mode; // Output; input; interrupt
    int state;

public:
    Gpio(Pin pin, int mode, std::string alias);
    ~Gpio();
    void enable();
    void releaseAll();

    void write(int state);
    int read();
    void attachInterrupt();
    
    void error(int num);
};
#endif