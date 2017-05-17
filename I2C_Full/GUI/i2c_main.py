from gui import *
from instructor import *

def main():

    instr = instructor()
    root = Tk()
    app = gui(root, instr)
    root.mainloop()


if __name__ == '__main__':
    main()
