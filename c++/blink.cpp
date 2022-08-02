/**
 * Simple LED blink using libgpiod c++ binding
 * Add -lgpiodcxx
 * Close the program by a simple CTRL + C.
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <gpiod.hpp>

#define OUTPUT_PIN 65
#define WAIT_MS 1000

int main(int argc, char* argv[]) {

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
    
    while (1) {
        line.set_value(state);
        state = !state;

		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
    }

    line.set_value(0);
    line.release();

    return 0;
}
