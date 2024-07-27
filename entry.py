import sys
import tty
import termios

def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch


r = """char tmp[9][9] =  {"""
for i in range(9):
    l = """{"""
    for j in range(9):
        t = getch()
        print(t)

        if(j==8) :
            l+=f"""{t}"""
        else:
            l+= f"""{t},"""
    l += """},"""
    r+= l

r += """}"""

print(r)
