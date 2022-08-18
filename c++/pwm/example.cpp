#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Pwm.h"

using namespace std;

int main(){
    Pwm* motor = new Pwm("C0",0.1,0.3);
    motor->start();
    for(;;)
    {
        std::this_thread::sleep_for(chrono::seconds(4));
    }
    
    return 0;
}