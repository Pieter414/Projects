import time
from turtle import Screen
from player import Player
from car_manager import CarManager
from scoreboard import Scoreboard

screen = Screen()
screen.setup(width=600, height=600)
screen.bgcolor("white")
screen.tracer(0)

turtle = Player()
car_manager = CarManager()
score = Scoreboard()

screen.listen()
screen.onkeypress(turtle.move, "Up")

game_is_on = True
while game_is_on:
    time.sleep(0.1)
    screen.update()
    #car manuver
    car_manager.new_car()
    car_manager.move_car()
    #detect collision with a car
    for car in car_manager.all_cars:
        if car.distance(turtle) < 20:
            score.game_over()
            game_is_on = False
    #detect finish line
    if turtle.ycor() >= 290:
        turtle.go_to_start()
        car_manager.finish_line_dash()
        score.level_up()



screen.exitonclick()
