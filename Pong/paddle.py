from turtle import Turtle
MOVE = 20

class Paddle(Turtle):
    def __init__(self, position):
        super().__init__()
        self.penup()
        self.goto(position)
        self.paddle = self.shape("square")
        self.color("White")
        self.shapesize(stretch_wid=5, stretch_len=1)
    
    def right_up(self):
        y = self.ycor()
        self.goto(self.xcor(), y + MOVE)

    def right_down(self):
        y = self.ycor()
        self.goto(self.xcor(), y - MOVE)
