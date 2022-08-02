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

#define OUTPUT_PIN 64
#define S_IN_US 1000000
#define LARGEST_FREQUENCY 100000
#define RPI_MAX_FREQUENCY 3000

static bool run = true;

void signalHandler(int signum);

int main(int argc, char* argv[]) {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGILL, signalHandler);
    std::signal(SIGABRT, signalHandler);

    /* // Parse frequency
    if (argc != 2) {
        std::cerr << "Unsupported command." << std::endl << "Usage: pwm <frequency (hz)>" << std::endl;
        return 2;
    }
    long frequency = -1;

    try {
        frequency = std::stol(argv[1]);
    } catch (const std::invalid_argument &ex) {
        std::cerr << "Could not parse '" << argv[1] << "' to a number" << std::endl;
        return 3;
    }

    if (frequency < 0) {
        std::cerr << "Frequency can not be negative" << std::endl;
        return 2;
    }
    if (frequency > LARGEST_FREQUENCY) {
        std::cerr << "Frequencies larger than " << LARGEST_FREQUENCY << " are not supported" << std::endl;
        return 2;
    }
    if (frequency == 0) {
        std::cerr << "A frequency of 0 doesn't make sense" << std::endl;
        return 2;
    }
    if (frequency > RPI_MAX_FREQUENCY) {
        std::cerr << "Warning: frequency is larger than " << RPI_MAX_FREQUENCY << " (it is " << frequency << "), from "
        << "testing it is shown that the max frequency for the raspberry pi 3 is around " << RPI_MAX_FREQUENCY/1000
        << "Khz. Going to try and run with this frequency anyways, expect unusual frequencies on your output."
        << std::endl;
    }
    std::cout << "Going to use " << frequency << " for the frequency" << std::endl;
 */
    long frequency = 50;

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
    request.consumer = "User PWM";

    line.request(request);

    bool state = false;
    float dutyCicle = 40; // 40% do meu tempo em alta => 0,4*
    auto duration_Hight = std::chrono::microseconds(   (dutyCicle/100) *(S_IN_US/frequency));
    auto duration_Low   = std::chrono::microseconds((1-(dutyCicle/100))*(S_IN_US/frequency));

    while (run) {
        auto start = std::chrono::system_clock::now();
        line.set_value(state);
        state = !state;

        if(state == true) std::this_thread::sleep_until(start + duration_Hight);
        else std::this_thread::sleep_until(start + duration_Low);

    }
    line.set_value(0);
    line.release();

    return 0;
}

void signalHandler(int signum) {
    run = false;
}