#This code makes the table dance using for loops


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

if __name__ == '__main__':

    colorArray1 = ["2ff0000","2ffaa00","2aaff00","200ff00","200aa50","2005412"]
    colorArray2 = ["20000ff","200aaff","21200aa","2ff00ff","200ffff","2000000"]

    writeNumber("1serial")
    time.sleep(1)

    writeNumber("1d10")
    time.sleep(1)

    writeNumber("2serial")
    time.sleep(1)

    for i in colorArray1:
        writeNumber(i)
        time.sleep(1)

    writeNumber("1u10")
    time.sleep(1)

    for i in colorArray2:
        writeNumber(i)
        time.sleep(1)

    writeNumber("1d5")
    time.sleep(1)

    for i in range(0, 3):
        writeNumber(colorArray1[i])
        time.sleep(1)

    writeNumber("1u5")
    time.sleep(1)

    for i in range(0, 3):
        writeNumber(colorArray2[i])
        time.sleep(1)

    writeNumber("2000000")
    time.sleep(1)
