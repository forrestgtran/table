import time

class instructor:

    def __init__(self):
        self.address = 0x04
        #self.address1 = 0x04
        #self.address2 = 0x06


    def setAddress(self, ad):
        self.address = ad
        print("New address: "+ str(self.address))

    def writeNumber(self,value):

        outString = str(value)

        if(len(outString)<10 and len(outString)>0):
            outString = str(len(outString))+outString
        else:
            outString = '0'+outString #signals that command is wrong (deal with this in Arduino code)
        print("Wrote: "+ outString)
