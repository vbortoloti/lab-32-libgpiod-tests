#include <string>
#ifndef RELOGIO_H
#define RELOGIO_H
class Gpio
{
private:
    std::string alias;
    int chip;
    int line;
    int pin;
    int mode; // Output; input; interrupt
    int status;

public:
    Gpio(int pin, int mode, std::string alias);
    void enable();
    void release();

    void write(int status);
    int read();
    void attachInterrupt();
};
#endif