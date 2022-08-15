#include "Gpio.h"
#include <gpiod.hpp>
#include <stdlib.h>
#include <string>
#include <iostream>

Gpio::Gpio(std::string pin, int mode, std::string alias)
{
    this->pin = getPin(pin);
    if(this->pin!=-1){
        this->mode = mode;
        this->alias = alias;
        chipNumber = "0";
        enable();
    }else{
        error(1);
    }
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
    case 1:
        std::cerr << "Invalid GPIO" << std::endl;
        break;
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

int getPin(std::string pinName){
    switch (str2int(pinName))
    {
    case str2int("A28"):
        return 28;
        break;
    case str2int("B0"):
        return 32;
        break;
    case str2int("B1"):
        return 33;
        break;
    case str2int("B2"):
        return 34;
        break;
    case str2int("B8"):
        return 40;
        break;
    case str2int("B10"):
        return 42;
        break;
    case str2int("B13"):
        return 45;
        break;
    case str2int("B15"):
        return 47;
        break;
    case str2int("B16"):
        return 48;
        break;
    case str2int("B18"):
        return 50;
        break;
    case str2int("B19"):
        return 51;
        break;
    case str2int("C0"):
        return 64;
        break;
    case str2int("C1"):
        return 65;
        break;
    case str2int("C4"):
        return 67;
        break;
    case str2int("C5"):
        return 69;
        break;
    case str2int("C6"):
        return 70;
        break;
    case str2int("C23"):
        return 87;
        break;
    case str2int("C24"):
        return 88;
        break;
    case str2int("D30"):
        return 126;
        break;
    case str2int("E2"):
        return 130;
        break;
    case str2int("E3"):
        return 131;
        break;
        
        
    default:
        return -1;
        break;
    }
}
