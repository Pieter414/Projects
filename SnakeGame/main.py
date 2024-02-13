from turtle import Screen
from snake import Snake
from food import Food
from scoreboard import ScoreBoard
import time

s = Screen()
s.setup(width=600, height=600)
s.bgcolor("black")
s.title("Snake game project - Pieter")
s.tracer(0)

snake = Snake()
food = Food()
score = ScoreBoard()
  
s.listen()
s.onkey(snake.up, "Up")
s.onkey(snake.down, "Down")
s.onkey(snake.left, "Left")
s.onkey(snake.right, "Right")

game_is_on = True
while game_is_on:
    s.update()
    time.sleep(0.1)
    snake.move()

    #collision with the food
    if snake.head.distance(food) < 15:
        food.refresh()
        snake.extend()
        score.increase_score()
    #detect collision in wall
    if snake.head.xcor() > 295 or snake.head.xcor() < -295 or snake.head.ycor() > 295 or snake.head.ycor() < -295:
        score.score_reset()
        score.game_over()
        game_is_on = False
    #detect collision with the body
    for segment in snake.segments[1:]:
        if snake.head.distance(segment) < 8:
            score.score_reset()
            score.game_over()
            game_is_on = False

s.exitonclick()