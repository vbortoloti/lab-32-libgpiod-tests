#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  const char *chipname = "gpiochip0";
  struct gpiod_chip *chip;
  struct gpiod_line *led;    // Red LED

  int i, val;

  // Open GPIO chip
  chip = gpiod_chip_open_by_name(chipname);

  // Open GPIO lines
  led = gpiod_chip_get_line(chip, 24);

  // Open LED  for output
  gpiod_line_request_output(led, "example1", 0);

  // Blink LEDs in a binary pattern
  i = 0;
  while (true) {
  
    usleep(100000);
    i++;
  }

  // Release lines and chip
  gpiod_line_release(led);

  gpiod_chip_close(chip);
  return 0;
}