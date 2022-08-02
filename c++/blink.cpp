/**
 * Program for creating a simple 50% duty cycle pwm signal on a pin.
 * Change the `OUTPUT_PIN` define to change the output pin.
 * Add the desired frequency as a command line argument.
 *
 * Close the program by a simple CTRL + C.
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <gpiod.hpp>
#define S_IN_US 1000000
#define OUTPUT_PIN 65
static bool run = true;

int main(int argc, char* argv[]) {

    
    long frequency = 1;
    
    auto chip = gpiod::chip("0", gpiod::chip::OPEN_BY_NUMBER);
    if (!chip) {
        std::cerr << "Could not find/ open gpio chip" << std::endl;
        return 2;
    }
    auto line = chip.get_line(OUTPUT_PIN);
    if (!line) {
        std::cerr << "Could not find output line" << std::endl;
        return 3;
    }
    if (line.is_used()) {
        std::cerr << "output line is already used!" << std::endl;
        return 4;
    }

    gpiod::line_request request;
    request.request_type = gpiod::line_request::DIRECTION_OUTPUT;
    request.consumer = "User Led";

    line.request(request);

    bool state = false;

    auto duration = std::chrono::microseconds((S_IN_US / frequency));
    
    while (1) {
        auto start = std::chrono::system_clock::now();
        line.set_value(state);
        state = !state;

        std::this_thread::sleep_until(start + duration);
    }

    line.set_value(0);
    line.release();

    return 0;
}
