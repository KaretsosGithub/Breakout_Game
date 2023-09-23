//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Breakout Game - Header file for the ball object
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BALL_H
#define BALL_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <QImage>
#include <QRect>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
  --Y Coordinate of the ball
  --Width of the window
*/
static const int COORD_Y_BALL = 355;
static const int RIGHT_EDGE = 300;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Ball {
public:
    // Constructor+Destructor
    Ball();
    ~Ball();

public:
    /*
      --Ball manipulation
    */
    void reset_ball_State(int);
    void SetInitialDirection();
    void move_the_ball();
    /*
      --Setters and Getters for the
        x and y direction of the ball
    */
    void setDir_X(int);
    int getDir_X();

    void setDir_Y(int);
    int getDir_Y();
    /*
      --Ball dimensions stuff
    */
    void setRect();
    QRect getRect();
    /*
      --Load image
      --Getter for the image
    */
    void loadImage();
    QImage& getImage();

private:
    int xdir;
    int ydir;
    int startDirection;
    QImage image;
    QRect rect;
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
