from labrador_sdk.gpio import GPIO
from labrador_sdk.main import Labrador
from cgi import test
import time
import sys

try:
    raw_input          # Python 2
except NameError:
    raw_input = input  # Python 3

def getGpio(pin):
    if(pin == 3):
        labrador.gpio3.enable_io(GPIO.Direction.OUTPUT, alias="led_out")
    elif(pin == 7):
        labrador.gpio7.enable_io(GPIO.Direction.OUTPUT, alias="led_out")
    else:
        labrador.gpio11.enable_io(GPIO.Direction.OUTPUT, alias="led_out") 
    

pin = int(sys.argv[1])
print("led "+str(pin)+" high")

labrador = Labrador()   
getGpio(pin)
print("runnin")

while True:
        try:
            data = raw_input()
            if 'close' in data:
                sys.exit(0)
            data = int(data)
        except (EOFError, SystemExit):        # hopefully always caused by us sigint'ing the program
            print("erro")
            sys.exit(0)
        except:
            if len(sys.argv) == 4:
                data = int(sys.argv[3])
            else:
                data = 0
        if data != 0:
            data = 1
        
        if(data == 1):
            labrador.led_out.high()
        elif(data ==0):
            labrador.led_out.low()
        else:
            print('invalid input')


        print("saida: "+str(data))
