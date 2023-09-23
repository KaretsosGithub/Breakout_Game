//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Breakout Game - Header file for the game logic
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BREAKOUT_H
#define BREAKOUT_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "include/Ball.h"
#include "include/Brick.h"
#include "include/Paddle.h"
#include <QApplication>
#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QSet>
#include <QWidget>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
  --Total number of bricks
  --Delay of timer for the game cycle
  --Height of the game window
*/
static const int N_OF_BRICKS = 30;
static const int DELAY = 10;
static const int BOTTOM_EDGE = 400;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Breakout : public QWidget {
    Q_OBJECT
public:
    // Constructor+Destructor
    Breakout(QWidget* parent = nullptr);
    ~Breakout();

protected:
    /*
      --Paint stuff
      --Timer for game cycle
      --"Listen" for key press by the user
      --"Listen" for key release by the user
      --Draw objects
    */
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void drawObjects(QPainter*);

    /*
      --Self explanatory
    */
    void initializeGame();
    void initializeBricksToNullptr();
    void initializeBricks(const vector<pair<int, int>>& brickPositions);
    void deleteBricks();

    void startGame();
    void pauseGame();

    void checkDefeatState();
    void checkVictoryState();

    void victory();
    void defeat();

    void moveObjects();
    void gameplay();

    void drawGameStateMessage(QPainter*, QString, QString, QString);
    void drawInstructionsMessage(QPainter*, QString, QString, QString, QString);

    void check_ballWithPaddle_Collision();
    void check_ballWithBrick_Collision();

    void PatternSelection();

private:
    /*
      --Objects for the ball, paddle, brick(s)
    */
    Ball* ball;
    Paddle* paddle;
    Brick* bricks[N_OF_BRICKS];

    /* An integer, used for
       the movement of the paddle
    */
    int x;

    // Game states and timer
    int timerId;
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;

    // Show instructions message flag
    bool showMessage;

    // Rapidly update the paddle position!
    QSet<int> pressedKeys;

    /* Bricks pattern selection
       and instruction message
    */
    QPushButton* SimpleGridButton;
    void createSimpleGridButton();

    QPushButton* ZigZagButton;
    void createZigZagButton();

    QPushButton* TwoPyramidsButton;
    void createTwoPyramidsButton();

    QPushButton* DiagonalsButton;
    void createDiagonalsButton();

    QPushButton* InstructionFrame;
    void createInstructionFrame();

    void createButtons();
    void showButtons();
    void hideButtons();

private slots:
    /*
      Slots, connected to
      bricks pattern buttons
    */
    void startSimpleGridGame();
    void startZigZagGame();
    void startTwoPyramidsGame();
    void startDiagonalsGame();
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
