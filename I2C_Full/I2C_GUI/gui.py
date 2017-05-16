
from Tkinter import *
from ttk import Frame, Button, Style, Radiobutton

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

    def initUI(self):

        var = IntVar()

        self.parent.title("Adress Bus Manager")
        self.style = Style()
        self.style.theme_use("default")

        self.pack(fill=BOTH, expand=1)

        quitButton = Button(self, text="Quit",
            command=self.quit)
        quitButton.place(x=50, y=450)

        ledRadio = Radiobutton(self, text="LED Strip",variable=var,value=1,
            command = self.instructor.setAddress(0x04))
        vertRadio = Radiobutton(self, text = "Vertical Motion", variable=var,value=2,
            command = self.instructor.setAddress(0x06))
        ledRadio.place(x = 50, y = 200)
        vertRadio.place(x = 50, y = 230)

        sendLabel = Label(self, text="Enter command:")
        sendLabel.place(x = 240, y = 200)

        textBox = Entry(self, bd=5)
        textBox.place(x=240, y = 240)

        sendButton = Button(self, text = "Send")
        sendButton.place(x=240, y = 280, command=self.assignCommand(textBox.get()))



    def centerWindow(self):

        w = 500
        h = 500

        sw = self.parent.winfo_screenwidth()
        sh = self.parent.winfo_screenheight()

        x = (sw - w)/2
        y = (sh - h)/2
        self.parent.geometry('%dx%d+%d+%d' % (w, h, x, y))
