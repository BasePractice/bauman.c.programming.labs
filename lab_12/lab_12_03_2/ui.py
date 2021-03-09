# LINK: https://docs.python.org/3/library/ctypes.html
# coding=utf-8
import os.path
from ctypes import *

from tkinter import *
from tkinter import messagebox

me = os.path.abspath(os.path.dirname(__file__))
# NOTICE:  путь для библиотеки. Указан относительный путь при сборке cmake в папку .build_w64
lb = cdll.LoadLibrary(os.path.join(me, "../../.build_w64/lab_12/lab_12_03_2", "liblab_12_03_2.dll"))

copy = lb.copy
copy.restype = c_longlong
copy.argtypes = [POINTER(c_longlong), c_longlong, POINTER(c_longlong), c_longlong]

elements = list()
window = Tk()
window.title("Лабораторная №12")
element = Label(window, text="Элемент: ")
element.grid(column=0, row=0)
element_text = Entry(window, width=10)
element_text.grid(column=1, row=0)
entered = Label(window, text="Всего элементов: 0")
entered.grid(column=0, row=1)


def append():
    elements.append(int(element_text.get()))
    entered.configure(text='Всего элементов: {}'.format(len(elements)))


enter = Button(window, text="Добавить элемент", command=append)
enter.grid(column=0, row=2)


def clicked():
    length = len(elements)
    src = (c_longlong * length)()
    for i in range(length):
        src[i] = elements[i]
    new = copy(None, 0, src, length)
    dst = (c_longlong * new)()
    ret = copy(dst, new, src, length)
    export = ""
    i = 0
    while i < ret:
        export += "Элемент {}: {}\n".format(i + 1, dst[i])
        i += 1
    messagebox.showinfo('Результат', export)


btn = Button(window, text="Рассчитать", command=clicked)
btn.grid(column=0, row=3)

window.mainloop()
