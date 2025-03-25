#include "startscreen.h"

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    // Create the start button
    startButton = new QPushButton("Start Game", this);

    // Define button size
    int buttonWidth = 2000;
    int buttonHeight = 500;


    // Does not work. Centering is off. The button works, albeit in the top left corner instead
    int x = (this->width() - buttonWidth) / 2;
    int y = (this->height() - buttonHeight) / 2;
    startButton->setGeometry(QRect(x, y, buttonWidth, buttonHeight));

    connect(startButton, &QPushButton::clicked, this, &StartScreen::startButtonClicked);
}
