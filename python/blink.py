# sudo apt install python3-libgpiod


import gpiod
import sys

if __name__ == '__main__':
    if len(sys.argv) < 3:
        raise TypeError('usage: gpioset.py <gpiochip> <offset1>=<value1> ...')

    with gpiod.Chip(sys.argv[1]) as chip:
        offsets = []
        values = []
        for arg in sys.argv[2:]:
            arg = arg.split('=')
            offsets.append(int(arg[0]))
            values.append(int(arg[1]))

        lines = chip.get_lines(offsets)
        lines.request(consumer=sys.argv[0], type=gpiod.LINE_REQ_DIR_OUT)
        lines.set_values(values)
        input()