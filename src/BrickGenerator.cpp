//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Breakout Game - Implementation of the BrickGenerator class
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "include/BrickGenerator.h"
#include <cmath>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<pair<int, int>> BrickGenerator::SimplePattern() {

    vector<pair<int, int>> positions;

    int startX = 30;
    int startY = 50;
    int brickWidth = 40;
    int brickHeight = 10;
    int numRows = 5;
    int numColumns = 6;

    // Simple Grid pattern
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numColumns; ++j) {
            int x = startX + j * brickWidth;
            int y = startY + i * brickHeight;
            positions.push_back(make_pair(x, y));
        }
    }
    return positions;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<pair<int, int>> BrickGenerator::ZigZagPattern() {

    vector<pair<int, int>> positions;

    int startX = 5;
    int startY = 20;
    int brickWidth = 50;
    int brickHeight = 20;
    int numRows = 5;
    int numCols_even = 6;
    int numCols_odd = 5;

    // Zig-Zag pattern
    for (int i = 0; i < numRows; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < numCols_even; j++) {
                int x = startX + (j * brickWidth);
                int y = startY + (i * brickHeight);
                positions.push_back(std::make_pair(x, y));
            }
        } else {
            for (int j = 0; j < numCols_odd; j++) {
                int x = (startX + 25) + (j * brickWidth);
                int y = startY + (i * brickHeight);
                positions.push_back(std::make_pair(x, y));
            }
        }
    }
    // Last 2 Bricks
    positions.push_back(make_pair(80, 120));
    positions.push_back(make_pair(180, 120));
    return positions;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<pair<int, int>> BrickGenerator::TwoPyramids() {

    vector<pair<int, int>> positions;

    // Inverted Pyramid
    int startX = 50;
    int startY = 30;
    int stepX = 40;
    int stepY = 10;
    int numRows = 5;
    int currentX = startX;
    int currentY = startY;

    for (int i = numRows; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            positions.push_back(make_pair(currentX, currentY));
            currentX += stepX;
        }

        currentX = startX + (numRows - i + 1) * stepX / 2;
        currentY += stepY;
    }

    // Normal Pyramid
    startX = 130;
    startY = 80;
    currentX = startX;
    currentY = startY;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j <= i; j++) {
            positions.push_back(make_pair(currentX, currentY));
            currentX += stepX;
        }

        currentX = startX - (i + 1) * stepX / 2;
        currentY += stepY;
    }
    return positions;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<pair<int, int>> BrickGenerator::Diagonals() {

    vector<pair<int, int>> positions;

    int startX = 30;
    int startY = 50;
    int stepX = 40;
    int stepY = 10;
    int numRows = 5;
    int currentX = startX;
    int currentY = startY;

    // First Diagonal pattern
    for (int i = 0; i < numRows; i++) {
        for (int j = i; j < numRows; j++) {
            positions.push_back(make_pair(currentX, currentY));
            currentX += stepX;
        }
        currentX = startX;
        currentY += stepY;
    }

    // Second diagonal pattern
    startX = 230;
    startY = 80;
    stepX = -40;
    stepY = 10;
    numRows = 5;
    currentX = startX;
    currentY = startY;

    for (int i = 0; i < numRows; i++) {
        for (int j = i; j >= 0; j--) {
            positions.push_back(make_pair(currentX, currentY));
            currentX += stepX;
        }

        currentX = startX;
        currentY += stepY;
    }
    return positions;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
