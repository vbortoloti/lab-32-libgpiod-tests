#include "Gpio.h"
#include <gpiod.hpp>
#include <stdlib.h>
#include <string>
#include <iostream>

Gpio::Gpio(int pin, int mode, std::string alias)
{
    this->pin = pin;
    this->mode = mode;
    this->alias = alias;
    chipNumber = "0";
    enable();
}
Gpio::~Gpio(){
    releaseAll();
}
void Gpio::enable()
{
    this->chip = gpiod::chip(chipNumber, gpiod::chip::OPEN_BY_NUMBER);
    if (!chip)
    {
        error(2);
        return;
    }
    this->line = chip.get_line(pin);
    if (!line)
    {
        error(3);
        return;
    }
    if (line.is_used())
    {
        error(4);
        return;
    }

    gpiod::line_request request;
    request.request_type = gpiod::line_request::DIRECTION_OUTPUT;
    request.consumer = "User Led";

    line.request(request);

    std::cout << "Enabling GPIO " << pin << " as " << mode << std::endl;
    std::cout << "Chip " << chip << " openned successfully" << std::endl;
    std::cout << "Line " << line << " setted as output successfully" << std::endl;
    std::cout << alias << " is ready to use" << std::endl;

    line.release();
}

void Gpio::releaseAll()
{
   
    line.set_value(0);
    line.release();
    std::cout << "GPIO released" << pin << std::endl;

}

void Gpio::write(int state)
{
    this->state = state;
    
    line.set_value(state);
    
    std::cout << "Writing " << state << std::endl;
}

int Gpio::read()
{
    // return val = gpiod_line_get_value(line);
    std::cout << "Reading pin " << pin << std::endl;
    return 0;
}

void Gpio::error(int num){
    switch (num)
    {
    case 2:
        std::cerr << "Could not find/ open gpio chip" << std::endl;
        break;
    case 3:
        std::cerr << "Could not find output line" << std::endl;
        break;
    case 4:
        std::cerr << "output line is already used!" << std::endl;
        break;
    default:
        break;
    }
}

