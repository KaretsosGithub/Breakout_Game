//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Breakout Game - Implementation file for the "Breakout" class
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "include/Breakout.h"
#include "include/BrickGenerator.h"
#include <QApplication>
#include <QMessageBox>
#include <QPainter>
#include <QVBoxLayout>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Constructor
Breakout::Breakout(QWidget* parent)
    : QWidget(parent) {

    // Initialize stuff
    createButtons();
    initializeGame();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Destructor
Breakout::~Breakout() {
    deleteBricks();
    delete paddle;
    delete ball;
    delete SimpleGridButton;
    delete ZigZagButton;
    delete TwoPyramidsButton;
    delete DiagonalsButton;
    delete InstructionFrame;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createButtons() {
    createSimpleGridButton();
    createZigZagButton();
    createTwoPyramidsButton();
    createDiagonalsButton();
    createInstructionFrame();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::initializeGame() {
    x = 0;
    gameOver = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    showMessage = true;
    paddle = new Paddle();
    ball = new Ball();
    initializeBricksToNullptr();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::initializeBricksToNullptr() {
    // Initialize bricks to nullptr
    for (int i = 0; i < N_OF_BRICKS; i++) {
        bricks[i] = nullptr;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::initializeBricks(const vector<pair<int, int>>& brickPositions) {
    for (int i = 0; i < N_OF_BRICKS; i++) {
        int x = brickPositions[i].first;
        int y = brickPositions[i].second;
        bricks[i] = new Brick(x, y);
        bricks[i]->setDestroyed(false);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::deleteBricks() {
    for (int i = 0; i < N_OF_BRICKS; i++) {
        if (bricks[i] != nullptr) {
            delete bricks[i];
            bricks[i] = nullptr;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    QPainter painter(this);
    // Print game state messages
    if (gameOver && showMessage) {
        drawGameStateMessage(&painter, "Defeat!", "Press Space to replay", "Press Esc to quit");
    } else if (gameWon && showMessage) {
        drawGameStateMessage(&painter, "Victory!", "Press Space to replay", "Press Esc to quit");
    } else if (gameStarted) {
        drawObjects(&painter);
        if (paused) {
            drawGameStateMessage(&painter, "Paused", "Press P to unpause", "Press Esc to quit");
        }
    } else {
        // Game has not started
        if (showMessage) {
            drawInstructionsMessage(&painter, "Instructions", "Press space to begin", "Press P to pause the game",
                                    "Press Esc to quit");
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Game state message method
void Breakout::drawGameStateMessage(QPainter* painter, QString message_1, QString message_2, QString message_3) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);

    int textHeight = fm.height();
    int combinedHeight = textHeight * 3;

    painter->setFont(font);
    painter->translate(QPoint(width() / 2, height() / 2 - combinedHeight / 2 + textHeight));

    // Display the text, centered
    painter->drawText(-fm.horizontalAdvance(message_1) / 2, -textHeight, message_1);
    painter->drawText(-fm.horizontalAdvance(message_2) / 2, 0, message_2);
    painter->drawText(-fm.horizontalAdvance(message_3) / 2, textHeight, message_3);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Game's intruction method
void Breakout::drawInstructionsMessage(QPainter* painter, QString line1, QString line2, QString line3, QString line4) {
    QFont font("Courier", 13, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth1 = fm.width(line1);
    int textWidth2 = fm.width(line2);
    int textWidth3 = fm.width(line3);
    int textWidth4 = fm.width(line4);

    painter->setFont(font);
    int h = height();
    int w = width();

    // Horizontal line
    int lineHeight = 30;
    int startY = h / 2 - (lineHeight * 2);

    painter->setPen(Qt::black);
    painter->drawText(QRect(w / 2 - textWidth1 / 2, startY, textWidth1, lineHeight), Qt::AlignCenter, line1);
    painter->drawText(QRect(w / 2 - textWidth2 / 2, startY + lineHeight, textWidth2, lineHeight), Qt::AlignCenter, line2);
    painter->drawText(QRect(w / 2 - textWidth3 / 2, startY + 2 * lineHeight, textWidth3, lineHeight), Qt::AlignCenter, line3);
    painter->drawText(QRect(w / 2 - textWidth4 / 2, startY + 3 * lineHeight, textWidth4, lineHeight), Qt::AlignCenter, line4);

    // Draw a line below the first string
    int lineY = startY + lineHeight - 3;
    painter->drawLine(w / 2 - textWidth1 / 2, lineY, w / 2 + textWidth1 / 2, lineY);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Draw objects(ball, paddle, bricks)
void Breakout::drawObjects(QPainter* painter) {
    painter->drawImage(ball->getRect(), ball->getImage());
    painter->drawImage(paddle->getRect(), paddle->getImage());

    for (int i = 0; i < N_OF_BRICKS; i++) {
        if (!bricks[i]->isDestroyed()) {
            painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);
    // Rapidly update the paddle position!
    int dx = 0;
    if (pressedKeys.contains(Qt::Key_Left)) {
        dx = -1;
    }
    if (pressedKeys.contains(Qt::Key_Right)) {
        dx = 1;
    }
    paddle->setDx(dx);

    // Refresh stuff
    moveObjects();
    gameplay();
    repaint();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Move the ball and paddle
void Breakout::moveObjects() {
    ball->move_the_ball();
    paddle->move_the_paddle();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Key release method
void Breakout::keyReleaseEvent(QKeyEvent* e) {
    pressedKeys.remove(e->key());
    int dx = 0;

    switch (e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        dx = 0;
        paddle->setDx(dx);
        break;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Key press method
void Breakout::keyPressEvent(QKeyEvent* e) {

    pressedKeys.insert(e->key());
    int dx = 0;

    switch (e->key()) {
    case Qt::Key_Left:
        dx = -1;
        paddle->setDx(dx);
        break;
    case Qt::Key_Right:
        dx = 1;
        paddle->setDx(dx);
        break;
    case Qt::Key_P:
        /*
          --Prevent the user from trying to
            pause when the game has not started yet.
        */
        if (!gameStarted) {
            return;
        }
        pauseGame();
        break;
    case Qt::Key_Space:
        // startGame();
        if (!gameStarted) {
            PatternSelection();
            showMessage = false;
            repaint();
        }
        break;
    case Qt::Key_Escape:
        /*
          --The user can quit only
            when:
            1) - The game has not started
            2) - The game is over (Victory or Defeat)
            3) - The game is paused
        */
        if ((!gameStarted) || (paused)) {
            QApplication::quit();
        }
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::startGame() {
    hideButtons();
    if (!gameStarted) {
        /*
          --Game has not started yet,
            place objects in the right
            position (ball, paddle, bricks)
          --Set random initial ball direction
        */
        paddle->reset_paddle_State();
        int position = paddle->getPaddleInitialPosition_X();

        ball->reset_ball_State(position);
        ball->SetInitialDirection();

        // Set the game state flags
        gameOver = false;
        gameWon = false;
        gameStarted = true;

        // Start the game cycle
        timerId = startTimer(DELAY);
        setFocus();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Pause the game method
void Breakout::pauseGame() {
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
    } else {
        paused = true;
        killTimer(timerId);
        update();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Gameplay!
void Breakout::gameplay() {
    checkDefeatState();
    checkVictoryState();
    check_ballWithPaddle_Collision();
    check_ballWithBrick_Collision();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::checkDefeatState() {
    /*
      --Check if the ball has
        reached the bottom of
        the window, AKA, Defeat
    */
    if (ball->getRect().bottom() > BOTTOM_EDGE) {
        defeat();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::defeat() {
    // Kill the timer, stop the game
    killTimer(timerId);
    gameOver = true;
    gameStarted = false;
    showMessage = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::checkVictoryState() {
    /*
      --Check if all the bricks
        have been destroyed, AKA, Victory!
    */
    for (int i = 0, j = 0; i < N_OF_BRICKS; i++) {
        if (bricks[i]->isDestroyed()) {
            j++;
        }
        if (j == N_OF_BRICKS) {
            victory();
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::victory() {
    // Kill the timer, stop the game
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
    showMessage = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
  --Method to detect the collision of
    the ball with the paddle and declare
    the direction the ball moves after that.
*/
void Breakout::check_ballWithPaddle_Collision() {
    if ((ball->getRect()).intersects(paddle->getRect())) {
        int paddleLPos = paddle->getRect().left();
        int ballLPos = ball->getRect().left();

        /*
          --The paddle is divided in 4 section.
            The direction of the ball after the
            impact, is determined by the section
            of the paddle that the ball hit
        */
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        if (ballLPos < first) {
            ball->setDir_X(-1);
            ball->setDir_Y(-1);
        }

        if (ballLPos >= first && ballLPos < second) {
            ball->setDir_X(-1);
            ball->setDir_Y(-1 * ball->getDir_Y());
        }

        if (ballLPos >= second && ballLPos < third) {
            ball->setDir_X(0);
            ball->setDir_Y(-1);
        }

        if (ballLPos >= third && ballLPos < fourth) {
            ball->setDir_X(1);
            ball->setDir_Y(-1 * ball->getDir_Y());
        }

        if (ballLPos > fourth) {
            ball->setDir_X(1);
            ball->setDir_Y(-1);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
  --Method to detect the collision of
    the ball with the brick(s) and declare
    the direction the ball moves after that.
*/
void Breakout::check_ballWithBrick_Collision() {

    for (int i = 0; i < N_OF_BRICKS; i++) {
        if ((ball->getRect()).intersects(bricks[i]->getRect())) {
            /*
              --The ball is divided in 4 section.
                The direction of the ball after the
                impact, is determined by the section
                of the ball that hits a brick
            */
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop - 1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!bricks[i]->isDestroyed()) {
                if (bricks[i]->getRect().contains(pointRight)) {
                    ball->setDir_X(-1);
                } else if (bricks[i]->getRect().contains(pointLeft)) {
                    ball->setDir_X(1);
                }
                if (bricks[i]->getRect().contains(pointTop)) {
                    ball->setDir_Y(1);
                }

                else if (bricks[i]->getRect().contains(pointBottom)) {
                    ball->setDir_Y(-1);
                }
                bricks[i]->setDestroyed(true);
            }
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createSimpleGridButton() {
    /*
      Create an interactive button. When pressed
      the game starts and the pattern of the Bricks
      is a simple Grid.
    */
    SimpleGridButton = new QPushButton("Grid", this);
    /*
      --Move the button into position
      --Various style options
      --Set fixed button size
      --Initially hide the button
      --Connect it to a private slot
    */
    SimpleGridButton->move(30, 150);
    QString buttonStyle = "QPushButton {"
                          "    background-color: #3e8c41;"
                          "    color: white;"
                          "    font: bold 16px;"
                          "    padding: 10px;"
                          "    border: 2px solid #4d0808;"
                          "    border-radius: 10px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #245726;"
                          "}";
    SimpleGridButton->setStyleSheet(buttonStyle);
    SimpleGridButton->setFixedSize(100, 40);
    SimpleGridButton->setVisible(false);

    connect(SimpleGridButton, &QPushButton::clicked, this, &Breakout::startSimpleGridGame);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::startSimpleGridGame() {
    // Simple Grid button private slot
    initializeBricks(BrickGenerator::SimplePattern());
    startGame();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createZigZagButton() {
    /*
      Create an interactive button. When pressed
      the game starts and the pattern of the Bricks
      is a Zig Zag Grid.
    */
    ZigZagButton = new QPushButton("Zig Zag", this);
    /*
      --Move the button into position
      --Various style options
      --Set fixed button size
      --Initially hide the button
      --Connect it to a private slot
    */
    ZigZagButton->move(170, 150);
    QString buttonStyle = "QPushButton {"
                          "    background-color: #3e8c41;"
                          "    color: white;"
                          "    font: bold 16px;"
                          "    padding: 10px;"
                          "    border: 2px solid #4d0808;"
                          "    border-radius: 10px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #245726;"
                          "}";
    ZigZagButton->setStyleSheet(buttonStyle);
    ZigZagButton->setFixedSize(100, 40);
    ZigZagButton->setVisible(false);

    connect(ZigZagButton, &QPushButton::clicked, this, &Breakout::startZigZagGame);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::startZigZagGame() {
    // Zig Zag button private slot
    initializeBricks(BrickGenerator::ZigZagPattern());
    startGame();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createTwoPyramidsButton() {
    /*
      Create an interactive button. When pressed
      the game starts and the pattern of the Bricks
      is a two pyramids.
    */
    TwoPyramidsButton = new QPushButton("Pyramids", this);
    /*
      --Move the button into position
      --Various style options
      --Set fixed button size
      --Initially hide the button
      --Connect it to a private slot
    */
    TwoPyramidsButton->move(30, 200);
    QString buttonStyle = "QPushButton {"
                          "    background-color: #3e8c41;"
                          "    color: white;"
                          "    font: bold 16px;"
                          "    padding: 10px;"
                          "    border: 2px solid #4d0808;"
                          "    border-radius: 10px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #245726;"
                          "}";
    TwoPyramidsButton->setStyleSheet(buttonStyle);
    TwoPyramidsButton->setFixedSize(100, 40);
    TwoPyramidsButton->setVisible(false);

    connect(TwoPyramidsButton, &QPushButton::clicked, this, &Breakout::startTwoPyramidsGame);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::startTwoPyramidsGame() {
    // Two pyramids button private slot
    initializeBricks(BrickGenerator::TwoPyramids());
    startGame();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createDiagonalsButton() {
    /*
      Create an interactive button. When pressed
      the game starts and the pattern of the Bricks
      is a two diagonal patterns.
    */
    DiagonalsButton = new QPushButton("Diagonals", this);
    /*
      --Move the button into position
      --Various style options
      --Set fixed button size
      --Initially hide the button
      --Connect it to a private slot
    */
    DiagonalsButton->move(170, 200);
    QString buttonStyle = "QPushButton {"
                          "    background-color: #3e8c41;"
                          "    color: white;"
                          "    font: bold 16px;"
                          "    padding: 10px;"
                          "    border: 2px solid #4d0808;"
                          "    border-radius: 10px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #245726;"
                          "}";
    DiagonalsButton->setStyleSheet(buttonStyle);
    DiagonalsButton->setFixedSize(100, 40);
    DiagonalsButton->setVisible(false);

    connect(DiagonalsButton, &QPushButton::clicked, this, &Breakout::startDiagonalsGame);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::startDiagonalsGame() {
    // Diagonals button private slot
    initializeBricks(BrickGenerator::Diagonals());
    startGame();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::createInstructionFrame() {
    /*
      This is not an interactive button.
      Its sole purspose is to display a message.
    */
    InstructionFrame = new QPushButton("Select Brick Pattern", this);

    /*
      --Move the button into position
      --Various style options
      --Set fixed button size
      --Initially hide the button
      --Disable button interaction
    */
    InstructionFrame->move(20, 60);
    QString instructionsFrameStyle = "QPushButton {"
                                     "    background-color: #3e8c41;"
                                     "    color: white;"
                                     "    font: bold 16px;"
                                     "    padding: 10px;"
                                     "    border: 2px solid #4d0808;"
                                     "}"
                                     "QPushButton:hover {"
                                     "    background-color: #245726;"
                                     "}";
    InstructionFrame->setStyleSheet(instructionsFrameStyle);
    InstructionFrame->setFixedSize(260, 40);
    InstructionFrame->setVisible(false);
    InstructionFrame->setEnabled(false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::PatternSelection() {
    showButtons();
    update();
    setFocus();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::showButtons() {
    SimpleGridButton->setVisible(true);
    ZigZagButton->setVisible(true);
    TwoPyramidsButton->setVisible(true);
    DiagonalsButton->setVisible(true);
    InstructionFrame->setVisible(true);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Breakout::hideButtons() {
    SimpleGridButton->setVisible(false);
    ZigZagButton->setVisible(false);
    TwoPyramidsButton->setVisible(false);
    DiagonalsButton->setVisible(false);
    InstructionFrame->setVisible(false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
