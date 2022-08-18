#ifndef GPIO
#define GPIO
#include <string>
#include <gpiod.hpp>

class Gpio
{
private:
    std::string alias;
    ::gpiod::chip chip;
    std::string chipNumber;
    ::gpiod::line line;

    int pin;
    int mode; // Output; input; interrupt
    int state;

    void enable();
    void releaseAll();
    void error(int num);
    int getPin(std::string pinName);
public:
    Gpio(std::string pin, int mode, std::string alias);
    ~Gpio();

    void write(int state);
    int read();
    void attachInterrupt();
};
#endif