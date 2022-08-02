/**
 * Toggle GPIO using libgpiod C++ binding
 * Add -lgpiodcxx
 * Close the program by a simple CTRL + C.
 */

#include <iostream>
#include <gpiod.hpp>
#include <unistd.h>
 
int main(void)
{ 
   ::gpiod::chip chip("gpiochip0");
   
   auto line = chip.get_line(65);  // GPIO17
   line.request({"example", gpiod::line_request::DIRECTION_OUTPUT, 0},1);  
   
   sleep(0.1);
   
   line.set_value(0);
   line.release();
}
