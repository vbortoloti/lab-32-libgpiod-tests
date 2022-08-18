#include "Pwm.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#define S_IN_US 1000000

Pwm::Pwm(std::string pin, double frequency, double dutyCicle){
    //gpio = new Gpio(pin,outuput,"pwm");
    this->frequency = frequency;

    this->dutyCicle = dutyCicle;
    this->period = S_IN_US/frequency;
    std::cout << "Pwm is ready to use\n"<< std::endl;
    std::cout << "Period: "<< period/S_IN_US << std::endl;
}

Pwm::~Pwm(){
    //delete gpio;
}

void Pwm::start(){
    this->state = true;
    std::thread t1(&Pwm::run,this);
    t1.detach();
}

void Pwm::stop(){
    this->state = false;
}

void Pwm::run(){
    while (state)
    {
        std::cout << "Pin High" << std::endl;
        //gpio.write(HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds((long)(period*dutyCicle)));
        
        std::cout << "Pin Low" << std::endl;
        //gpio.write(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds((long)(period*(1-dutyCicle))));
    }
    
}
