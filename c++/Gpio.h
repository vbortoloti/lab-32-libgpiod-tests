#include <string>
#include <gpiod.hpp>

#ifndef RELOGIO_H
#define RELOGIO_H
class Gpio
{
private:
    std::string alias;
    ::gpiod::chip chip;
    string chipNumber;
    ::gpiod::line line;
    int pin;
    int mode; // Output; input; interrupt
    int status;

public:
    Gpio(int pin, int mode, std::string alias);
    void enable();
    void releaseAll();

    void write(int status);
    int read();
    void attachInterrupt();
};
#endif