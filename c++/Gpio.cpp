#include "Gpio.h"
#include <gpiod.hpp>
#include <stdlib.h>
#include <string>
#include <iostream>

std::map<std::string,int> mapping = {
{"A28", 28 },
{"B0" , 32 },
{"B1" , 33 },
{"B2" , 34 },
{"B8" , 40 },
{"B10", 42 },
{"B13", 45 },
{"B15", 47 },
{"B16", 48 },
{"B18", 50 },
{"B19", 51 },
{"C0" , 64 },
{"C1" , 65 },
{"C4" , 68 },
{"C5" , 69 },
{"C6" , 70 },
{"C23", 87 },
{"C24", 88 },
{"D30", 126 },
{"E2" , 130 },
{"E3" , 131 }
};

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
        //throw error
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

int Gpio::getPin(std::string pinName){
    std::map<std::string, int>::const_iterator iter = mapping.find(pinName);
    if (iter != mapping.end()) return iter->second;
    else return -1;
}   
