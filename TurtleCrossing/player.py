from turtle import Turtle
STARTING_POSITION = (0, -280)
MOVE_DISTANCE = 10
FINISH_LINE_Y = 280

class Player(Turtle):
    def __init__(self, shape="turtle"):
        super().__init__(shape)
        self.penup()
        self.left(90)
        self.goto(STARTING_POSITION)
    
    def move(self):
        self.forward(MOVE_DISTANCE)
    
    def go_to_start(self):
        self.goto(STARTING_POSITION)
