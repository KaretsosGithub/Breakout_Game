
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
    Main script for the Breakout game
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "include/Breakout.h"
#include <QApplication>
#include <QPalette>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    // Main window creation
    Breakout window;

    // Create a palette and set the background color
    QPalette palette;
    QColor backgroundColor(168, 128, 128);
    palette.setColor(QPalette::Background, backgroundColor);

    // Set the palette on the window
    window.setPalette(palette);
    window.setFixedSize(300, 400);

    // Set the title and display the window
    window.setWindowTitle("Breakout Game");
    window.show();

    return app.exec();
}
