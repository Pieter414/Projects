BACKGROUND_COLOR = "#B1DDC6"

from tkinter import *
import pandas
import random

#FUNCTION AREA

#reading csv.file
try :
    csv_data = pandas.read_csv("./word_to_learn.csv")
except FileNotFoundError:
    original_data = pandas.read_csv("./data/french_words.csv")
    to_learn = original_data.to_dict(orient="records")
else:
    to_learn = csv_data.to_dict(orient="records")

current_card = {}

def is_known():
    to_learn.remove(current_card)
    new_df = pandas.DataFrame(to_learn)
    new_df.to_csv("word_to_learn.csv", index=False)
    next_card()

def next_card():
    global current_card, flip_timer
    window.after_cancel(flip_timer)

    current_card = random.choice(to_learn)
    canvas.itemconfig(title, text="French", fill="black")
    canvas.itemconfig(word, text=current_card["French"], fill="black")
    canvas.itemconfig(canvas_image, image=front_img)
    flip_timer = window.after(3000, func=flip_card)

def flip_card():
    canvas.itemconfig(canvas_image, image=back_img)
    canvas.itemconfig(title, fill="white", text="English")
    canvas.itemconfig(word, fill="white", text=current_card["English"])

window = Tk()
window.title("Flashy")
window.config(padx=50, pady=50, bg=BACKGROUND_COLOR)

flip_timer = window.after(3000, func=flip_card)    

#canvas for the flaschcards
canvas = Canvas(width=800, height=526, highlightthickness=0, bg=BACKGROUND_COLOR)
front_img = PhotoImage(file="./images/card_front.png")
back_img = PhotoImage(file="./images/card_back.png")
canvas_image = canvas.create_image(400, 263, image = front_img)
title = canvas.create_text(400, 150, text="", font=("Ariel", 40, "italic"))
word = canvas.create_text(400, 263, text="", font=("Ariel", 60, "bold"))
canvas.grid(column=0, row=0, columnspan=2)

#two button of the images
check_img = PhotoImage(file="./images/right.png")
y_button = Button(image=check_img, highlightthickness=0, command=is_known)
y_button.grid(column=1, row=1)

cross_img = PhotoImage(file="./images/wrong.png")
n_button = Button(image=cross_img, highlightthickness=0, command=next_card)
n_button.grid(column=0, row=1)

next_card()

#changing the image
changer = False
def data():
    global changer
    changer =  True



window.mainloop()

