from textblob import TextBlob
from tkinter import *
import gtts
import playsound

def correct_spelling():
    input_data = enter1.get()
    improve = TextBlob(input_data)
    data = improve.correct()
    enter2.delete(0, END)
    enter2.insert(0, data)

    
    original_text = input_data.split()
    corrected_text = data.split()
    total_words = len(original_text)
    
    wrong_words = 0
    for i in range(len(original_text)):
        original = original_text[i]
        corrected = corrected_text[i]
        if original != corrected:
            wrong_words += 1
    
    accuracy = ((total_words - wrong_words) / total_words) * 100
    enter3.delete(0,END);
    enter3.insert(0,accuracy);

def pronounce():
    input_data=enter2.get()
    pronounciation=gtts.gTTS(input_data,lang="en")
    pronounciation.save("pro.mp3")
    playsound.playsound("pro.mp3")

    

def check_window():
    global enter1, enter2,enter3
    win = Tk()
    win.geometry("500x550")
    win.resizable(False,False)
    win.config(bg="black")
    win.title("Spell Checker-by THE CODE CRUSADERS")
    label1 = Label(win, text="Capstone Project", font=("Calibri", 35, "bold", "italic"), bg="black", fg="blue")
    label1.place(x=70, y=20, height=50, width=400)
    label2 = Label(win, text="Enter The Sentence", font=("Optima", 18, "bold"), bg="black", fg=("white"))
    label2.place(x=40, y=110, height=50, width=250)
    enter1 = Entry(win, font=("Times New Roman", 18))
    enter1.place(x=50, y=160, height=30, width=400)
    label3 = Label(win, text="Corrected Sentence", font=("Optima", 18, "bold"), bg="black", fg=("white"))
    label3.place(x=35, y=280, height=50, width=250)
    enter2 = Entry(win, font=("Times New Roman", 18))
    enter2.place(x=50, y=330, height=30, width=400)
    label4 = Label(win, text="Accuracy", font=("Optima", 18, "bold"), bg="black", fg=("white"))
    label4.place(x=30, y=400, height=50, width=150)
    enter3 = Entry(win, font=("Times New Roman", 18))
    enter3.place(x=50, y=450, height=30, width=125)

    button = Button(win, text="Let's Check", font=("Optima", 25, "bold", "italic"), bg="white", fg="black", command=correct_spelling)
    button.place(x=150, y=210, height=40, width=200)
    button = Button(win, text="Pronounce", font=("Optima", 25, "bold"), bg="white", fg="black", command=pronounce)
    button.place(x=150, y=500, height=40, width=200)





    

def main_widow():  
    win = Tk()
    win.geometry("500x550")
    win.resizable(False,True)
    win.config(bg="#f58742")
    win.title("Spell Checker- by THE CODE CRUSADERS")
    label1 = Label(win, text="WELCOME TO THE SPELL CHECKER",font=("Arial",12,"bold","italic"),bg="#b0f542",fg="green")
    label1.place(x=50,y=20,height=50,width=400)
    label2 = Label(win, text="-by THE CODE CRUSADERS",font=("Arial",12,"bold","italic"),bg="#b0f542",fg="green")
    label2.place(x=50,y=72,height=50,width=400)
    button=Button(win,text="Spell Check",font=("Times New Roman",18,"bold","italic"),bg="#b0f542",fg="green",command=check_window)
    button.place(x=150,y=130,height=50,width=200)


   

    win.mainloop()

    

main_widow()

