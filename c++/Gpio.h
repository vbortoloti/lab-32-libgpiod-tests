#include <string>
#include <gpiod.hpp>

#ifndef RELOGIO_H
#define RELOGIO_H
class Gpio
{
private:
    std::string alias;
    ::gpiod::chip chip;
    std::string chipNumber;
    ::gpiod::line line;
    int pin;
    int mode; // Output; input; interrupt
    int status;

public:
    Gpio(int pin, int mode, std::string alias);
    ~Gpio();
    void enable();
    void releaseAll();

    void write(int state);
    int read();
    void attachInterrupt();
    
    void error(int num);
};
#endif