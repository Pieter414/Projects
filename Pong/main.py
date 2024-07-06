from turtle import Screen
from paddle import Paddle
from ball import Ball
from score import Score
import time

#setup screen
s = Screen()
s.setup(width=800, height=600)
s.bgcolor("black")
s.title("Pong game project")
s.tracer(0)

#import class
r_paddle = Paddle((350, 0))
l_paddle = Paddle((-350, 0))
ball = Ball()
score = Score()

#controller
s.listen()
s.onkeypress(r_paddle.right_up, "Up")
s.onkeypress(r_paddle.right_down, "Down")
s.onkeypress(l_paddle.right_up, "w")
s.onkeypress(l_paddle.right_down, "s")

#project of the game
game_is_on = True
while game_is_on:
    time.sleep(ball.move_speed)
    s.update()
    ball.move()

    #detect collision with upper and lower wall
    if ball.ycor() > 280 or ball.ycor() < -280:
        ball.bounce_y()
    
    #detect collision with paddle
    if ball.distance(r_paddle) < 50 and ball.xcor() > 320 or ball.distance(l_paddle) < 50 and ball.xcor() < -320:
        ball.bounce_x()
    
    #detect collision out of bound
    if ball.xcor() > 380:
        score.l_increase_score()
        ball.refresh() 
    elif ball.xcor() < -380:
        score.r_increase_score()
        ball.refresh()    

s.exitonclick()