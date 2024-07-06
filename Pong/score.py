from turtle import Turtle
ALIGNMENT = "center"
FONT = ("Arial", 24, "bold")

class Score(Turtle):
    def __init__(self):
        super().__init__()
        self.r_score = 0
        self.l_score = 0
        self.color("white")
        self.penup()
        self.goto(0,260)
        self.hideturtle()
        self.update_scoreboard()
    
    def update_scoreboard(self):
        self.write(f"{self.l_score} : {self.r_score}", align=ALIGNMENT, font=FONT)
    
    def l_increase_score(self):
        self.l_score += 1
        self.clear()
        self.update_scoreboard()
    
    def r_increase_score(self):
        self.r_score += 1
        self.clear()
        self.update_scoreboard()
    
