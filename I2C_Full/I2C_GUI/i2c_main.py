from gui import *
from instructor import *

def main():

    instr = instructor()
    root = Tk()
    root.geometry("510x510+100+100")
    app = gui(root, instr)
    root.mainloop()


if __name__ == '__main__':
    main()
