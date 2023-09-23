//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Breakout Game - Header file for the paddle
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef PADDLE_H
#define PADDLE_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Y coordinate of the paddle
static const int COORD_Y_PADDLE = 360;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <QImage>
#include <QRect>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Paddle {

public:
    // Constructor+Destructor
    Paddle();
    ~Paddle();

public:
    /*
      --Set paddle's initial dx
      --Reset paddle's state
      --Move the paddle!
    */
    void setInitialDx();
    void reset_paddle_State();
    void move_the_paddle();

    /*
      --Setters and Getters for
        paddle's movement and dimensions
    */
    void setDx(int);
    int getDx();

    void setRect();
    QRect getRect();

    /*
      --Load image
      --Getter for the image
    */
    void loadImage();
    QImage& getImage();

    /*
      --Setter for the paddle's
        initial x coordinate
    */
    void setPaddleInitialPosition_X(int);
    int getPaddleInitialPosition_X();

private:
    QImage image;
    QRect rect;
    int dx;
    int startPos_X;
    int paddleCoord_X;
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
