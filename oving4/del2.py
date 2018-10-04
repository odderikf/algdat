#!/usr/bin/python3
class Node:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.value = ""
        self.left = None
        self.right = None


    def depth(self, i=0):
        left = self.left
        right = self.right
        if not left and not right:
            return i
        elif not left:
            return right.depth(i+1)
        elif not right:
            return left.depth(i+1)
        else:
            return max(left.depth(i+1), right.depth(i+1))

    def insert(self, value):
        LABELWIDTH = 7*len(self.value)
        textX = self.x+self.width/2
        textY = self.y+LABELHEIGHT
        childnodewidth = self.width/2 - LABELWIDTH
        childnodeheight = self.height - textY
        if not self.value:
            self.value = value
            text = rootC.create_text(textX, textY, text=self.value, font= ('Consolas', '8') )
        elif value <= self.value:
            if not self.right:
                self.right = Node(self.x, self.y+2*LABELHEIGHT, childnodewidth, childnodeheight)
                rootC.drawLine(textX, textY+0.7*LABELHEIGHT, self.x+childnodewidth/2 - 2, self.y+2.5*LABELHEIGHT)
            self.right.insert(value)
        else:
            if not self.left:
                self.left = Node(textX + LABELWIDTH, self.y+2.*LABELHEIGHT, childnodewidth, childnodeheight)
                rootC.drawLine(textX, textY+0.7*LABELHEIGHT, textX + LABELWIDTH+childnodewidth/2 + 2, self.y+2.5*LABELHEIGHT)
            self.left.insert(value)

from tkinter import *

class NodeCanvas(Canvas):
    def drawLine(self, oldx, oldy, newx,newy):
        self.create_line(oldx, oldy, newx, newy)

           
def addHandler():
    print(entry.get())
    root.insert(entry.get())
    entry.delete(0, END)


window = Tk()
window.title("tre")

entry = Entry(window)
entry.pack()
Button(window, text="add", command=addHandler).pack()
    

WIDTH = 1600
HEIGHT = 1500
window.geometry( str(1600)+"x"+str(900) )
LABELHEIGHT = 30
rootC = NodeCanvas(window)
root = Node(150,0, WIDTH, HEIGHT)
rootC.pack(side="top", fill="both",expand=True)
rootC.configure(xscrollincrement='1')
rootC.configure(scrollregion=(-100,0,WIDTH+200,HEIGHT))

horiScroll = Scrollbar(rootC, orient=HORIZONTAL)
horiScroll.pack(side="bottom", fill="both")
vertScroll = Scrollbar(rootC, orient=VERTICAL)
vertScroll.pack(side="right", fill="both")
rootC.xview_moveto(0.33)

rootC.config(xscrollcommand=horiScroll.set)
horiScroll.config(command=rootC.xview)
rootC.config(yscrollcommand=vertScroll.set)
vertScroll.config(command=rootC.yview)

window.mainloop()
