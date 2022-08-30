from labrador_sdk.gpio import GPIO
from labrador_sdk.main import Labrador
import time
import sys

def getGpio(pin):
    if(pin == 3):
        labrador.gpio3.enable_io(GPIO.Direction.OUTPUT, alias="led_out")
    elif(pin == 7):
        labrador.gpio7.enable_io(GPIO.Direction.OUTPUT, alias="led_out")
    else:
        labrador.gpio11.enable_io(GPIO.Direction.OUTPUT, alias="led_out") 
    

pin = int(sys.argv[1])
labrador = Labrador()   
getGpio(pin)
print("runnin")
while True:
    labrador.led_status.high()
    time.sleep(0.5)
    labrador.led_status.low()
    time.sleep(0.5)

# while True:
#         try:
#             data = raw_input()
#             if 'close' in data:
#                 sys.exit(0)
#             data = int(data)
#         except (EOFError, SystemExit):        # hopefully always caused by us sigint'ing the program
#             GPIO.cleanup(pin)
#             sys.exit(0)
#         except:
#             if len(sys.argv) == 4:
#                 data = int(sys.argv[3])
#             else:
#                 data = 0
#         if data != 0:
#             data = 1
#         GPIO.output(pin,data)