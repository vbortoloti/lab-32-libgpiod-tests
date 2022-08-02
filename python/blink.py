# sudo apt install python3-libgpiod


import gpiod
import sys

if __name__ == '__main__':
    line = gpiod.find_line(sys.argv[1])
    if line is None:
        sys.exit(1)

    print('{} {}'.format(line.owner().name(), line.offset()))
    line.owner().close()