
from Tkinter import *
from ttk import Frame, Button, Style, Radiobutton, Style
from constants import *

class gui(Frame):
    def __init__(self, parent, instructor):
        Frame.__init__(self, parent)

        self.instructor = instructor
        self.parent = parent
        self.centerWindow()
        self.initUI()
        self.command = "hi"

    def assignCommand(self, c):
        self.command = c
        self.instructor.writeNumber(self.command)
        print("Command: " + self.command)

    def initUI(self):

        var = IntVar()

        #General stuff
        self.parent.title("Adress Bus Manager")
        self.style = Style()
        self.style.theme_use("default")
        #self.pack(fill=BOTH, expand=1)
        self.parent.configure(background = Constants.BG_COL)

        s = Style()
        s.configure('C.TRadiobutton', background = Constants.BG_COL)

        #Quit button
        quitButton = Button(self.parent, text="Quit",
            command=self.quit)
        quitButton.place(x = Constants.QUIT_X, y = Constants.QUIT_Y)

        #Radiobuttons
        ledRadio = Radiobutton(self.parent, text="LED Strip",variable=var,value=1,
            command = lambda: self.instructor.setAddress(0x04), style = 'C.TRadiobutton')
        vertRadio = Radiobutton(self.parent, text = "Vertical Motion", variable=var,value=2,
            command = lambda: self.instructor.setAddress(0x06), style = 'C.TRadiobutton')
        ledRadio.place(x = Constants.LED_X, y = Constants.LED_Y)
        vertRadio.place(x = Constants.VERT_X, y = Constants.VERT_Y)
        #ledRadio.configure(background = Constants.BG_COL)

        #Label
        sendLabel = Label(self.parent, text="Enter command:", background = Constants.BG_COL)
        sendLabel.place(x = Constants.SENDL_X, y = Constants.SENDL_Y)

        #Address label
        adLabel = Label(self.parent, text="Select address:", background = Constants.BG_COL)
        adLabel.place(x = Constants.ADL_X, y = Constants.ADL_Y)

        #Text entry box
        textBox = Entry(self.parent, bd=2, width = Constants.TEXT_W)
        textBox.place(x = Constants.TEXT_X, y = Constants.TEXT_Y)

        #Send command button
        sendButton = Button(self.parent, text = "Send", command= lambda: self.assignCommand(textBox.get()))
        sendButton.place(x = Constants.SENDB_X, y = Constants.SENDB_Y)

    def centerWindow(self):

        w = Constants.WINDOW_WIDTH
        h = Constants.WINDOW_HEIGHT

        sw = self.parent.winfo_screenwidth()
        sh = self.parent.winfo_screenheight()

        x = (sw - w)/2
        y = (sh - h)/2
        self.parent.geometry('%dx%d+%d+%d' % (w, h, x, y))
