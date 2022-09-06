import gpiod
import sys

chip=gpiod.chip("/dev/gpiochip0")
lines = chip.get_lines([65])
lines.request(consumer="teste", type=gpiod.LINE_REQ_DIR_IN)
vals = lines.get_values()

for val in vals:
    print(val, end=' ')
print()