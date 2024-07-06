from turtle import Turtle
import random

class Ball(Turtle):
    def __init__(self):
        super().__init__()
        self.color("white")
        self.shape("circle")
        self.penup()
        self.move_x = 10
        self.move_y = 10
        self.move_speed = 0.06
                
    def move(self):
        new_x = self.xcor() + self.move_x
        new_y = self.ycor() + self.move_y
        self.goto(new_x, new_y)

    def bounce_x(self):
        self.move_x *= -1
        self.move_speed *= 0.9

    def bounce_y(self):
        self.move_y *= -1
    
    def refresh(self):
        self.home()
        self.move_speed = 0.1
        self.move_x *= -1
        
        
