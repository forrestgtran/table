#This code lets you choose which Arduino to send i2c serial commands to.

import time
import smbus

bus = smbus.SMBus(1)

address = 0
address1 = 0x04
address2 = 0x06

def writeNumber(value):

        outString = str(value)

        if(outString[0] == '1'):
                address = address1
        elif(outString[0] == '2'):
                address = address2
        else:
                print("Error: incorrect Arduino address, choose 1 or 2.")

	if(len(outString)<10 and len(outString)>0):
		outString = str(len(outString)-1)+outString[1:]
	else:
		outString = '0'+outString[1:] #signals that command is wrong (deal with this in Arduino code)

        print(outString)



	for character in outString: # convert into a string and iterate over it
        	bus.write_byte(address, ord(character)) # send each char's ASCII encoding
	return -1

# while True:
#
# 	try:
# 		var = raw_input("Enter a string: ")
# 	except ValueError:
#
# 		print("Try again")
# 		continue
#
# 	writeNumber(var)
# 	print("Wrote: "+ var)
# time.sleep(1)

if __name__ == '__main__':
    writeNumber("1serial")
    time.sleep(1)
    
    writeNumber("1d10")
    time.sleep(1)
    
    writeNumber("2serial")
    time.sleep(1)
    
    writeNumber("2ff0000")
    time.sleep(1)
    
    writeNumber("2ffaa00")
    time.sleep(1)
    
    writeNumber("20000ff")
    time.sleep(1)
    
    writeNumber("200aaff")
    time.sleep(1)
    
    writeNumber("1u10")
    time.sleep(1)
    
    writeNumber("200ff00")
    time.sleep(1)
    
    writeNumber("20000ff")
    time.sleep(1)
    
    writeNumber("2000000")
    time.sleep(1)

    writeNumber("2ffaa00")
    time.sleep(1)
    
    writeNumber("20000ff")
    time.sleep(1)
    
    writeNumber("200aaff")
    time.sleep(1)

    writeNumber("2000000")
    time.sleep(1)
