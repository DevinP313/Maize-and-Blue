#include "widget.h"
#include "StartScreen.h"

#include <QPainter>
#include <QMessageBox>
#include <QPainter>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <QMediaPlayer>
#include <QAudio>
#include <QUrl>
#include <QAudioOutput>




MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent)
{
    // Initialize random seed
    srand(time(NULL));

    // Define mazes
    int maze1[10][10] = {
        {0, 1, 0, 0, 2, 1, 1, 1, 0, 'E'},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 2, 0, 0},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 2, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


    int maze2[10][10] = {
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 'E'},
        {0, 0, 0, 2, 1, 0, 0, 0, 2, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 2, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };


    int maze3[10][10] = {
        {0, 1, 0, 2, 2, 1, 1, 1, 0, 'E'},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 2, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };


    int maze4[10][10] = {
        {0, 1, 1, 1, 0, 1, 0, 2, 0, 'E'},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 2, 0, 0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };



    //Copy Maize to Maize Array
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            mazes[0][i][j] = maze1[i][j];
            mazes[1][i][j] = maze2[i][j];
            mazes[2][i][j] = maze3[i][j];
            mazes[3][i][j] = maze4[i][j];
        }
    }

    // randomly select maize
    int selectedMaze = rand() % mazeCount;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            maze[i][j] = mazes[selectedMaze][i][j];
        }
    }


    setFixedSize(600, 600);
    playerRow = 0;
    playerCol = 0;

    // trap check
    isTrapped = false;

    //timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MazeWidget::onTimerTimeout);
    timer->start(15000); // 10 seconds

    timeRemaining = 15;
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MazeWidget::updateTimeRemaining);
    gameTimer->start(1000);

    //start screen
    startScreen = new StartScreen(this);
    connect(startScreen, &StartScreen::startButtonClicked, this, &MazeWidget::startGame);

    //audio
    play = new QMediaPlayer(this);
    audio = new QAudioOutput(this);

    play->setAudioOutput(audio);
    audio->setVolume(50);

    play -> setSource(QUrl::fromLocalFile("C:\\370\\C++\\ECE370_FINAL_PROJECT\\Rick.mp3"));


}

void MazeWidget::startGame() {
    gameStarted = true;
    startScreen->hide(); // Hide the start screen
    setFocus();
}

void MazeWidget::updateTimeRemaining()
{
    if (timeRemaining > 0) {
        timeRemaining--;

        qDebug() << "Time remaining:" << timeRemaining << "seconds";
    } else {
        gameTimer->stop();
        qDebug() << "Time's up!";
    }
}

void MazeWidget::onTimerTimeout()
{
    // Display message and stop the timer
    playDeathSound();
    QMessageBox::information(this, "Big L", "You've been beat by the Buckeyes!");
    timer->stop();
}

void MazeWidget::keyPressEvent(QKeyEvent *event)
{
    if (!gameStarted) return;

    if (!gameStarted || isTrapped) {
        if(event->key() == Qt::Key_U) {
            undoMove();
            isTrapped = false;
        }
        return;
    }

    int newRow = playerRow;
    int newCol = playerCol;

    if (event->key() == Qt::Key_Up) {
        newRow = qMax(0, playerRow - 1);
    } else if (event->key() == Qt::Key_Down) {
        newRow = qMin(9, playerRow + 1);
    } else if (event->key() == Qt::Key_Left) {
        newCol = qMax(0, playerCol - 1);
    } else if (event->key() == Qt::Key_Right) {
        newCol = qMin(9, playerCol + 1);
    } else if (event->key() == Qt::Key_U) { // Undo last move
        undoMove();
        return;
    }

    if (maze[newRow][newCol] == 2) {  // Assuming 2 represents a trap
        QMessageBox::information(this, "Trapped!", "Press 'U' to undo.");
        isTrapped = true;
        return;
    }

    // Code that Plays Depending on Where the User's Location
    if (maze[newRow][newCol] == 0) {
        movePlayer(newRow, newCol);
        update();
    } else if (maze[newRow][newCol] == 1) {
        playDeathSound();
        QMessageBox::information(this, "Oh, Buck!", "Oh no, you've been blocked by the Buckeyes!");


    } else if (maze[newRow][newCol] == 'E') {
        playVictorySound();
        QMessageBox::information(this, "Victory!", "Congratulations, you've reached the end! Go Blue!");

        close();
    }

}

void MazeWidget::playVictorySound()
{
    play->setSource(QUrl::fromLocalFile("C:\\370\\C++\\ECE370_FINAL_PROJECT\\HAIL_V.mp3"));
    play->play();
}

void MazeWidget::playDeathSound()
{
    play->setSource(QUrl::fromLocalFile("C:\\370\\C++\\ECE370_FINAL_PROJECT\\Rick.mp3"));
    play->play();
}

void MazeWidget::movePlayer(int newRow, int newCol)
{
    // Push current position onto stack before moving
    rowHistory.push(playerRow);
    colHistory.push(playerCol);

    // Update player's position
    playerRow = newRow;
    playerCol = newCol;
}

// Undo Function
void MazeWidget::undoMove()
{

    if (!rowHistory.empty() && !colHistory.empty()) {
        // Revert player's position to last saved state
        playerRow = rowHistory.top();
        playerCol = colHistory.top();
        rowHistory.pop();
        colHistory.pop();

        update();
        play -> play();

        isTrapped = false;
    }
}

//Paint Events
void MazeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Define colors
    QColor backgroundColor(200, 200, 200);
    QColor red(186, 12, 47); // Red color for walls
    QColor darkRed(139, 0, 0); // Dark red color for traps
    QColor blue(0, 39, 76); // Blue color for the player
    QColor maize(251, 236, 93); // Maize color for the end point
    QColor black(0,0,0);

    // Fill the background
    painter.fillRect(rect(), backgroundColor);

    // Drawing the maze
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QRect square(j * 60, i * 60, 60, 60);
            if (maze[i][j] == 1) {
                painter.fillRect(square, red);
            } else if (maze[i][j] == 2) { // Draw traps
                painter.fillRect(square, darkRed);
                painter.setPen(black); // Set pen color for text
                painter.drawText(square, Qt::AlignCenter, "O");
            } else if (maze[i][j] == 'E') {
                painter.fillRect(square, maize);
            }
        }
    }



    // Drawing the player
    QRect playerSquare(playerCol * 60, playerRow * 60, 60, 60);
    painter.fillRect(playerSquare, blue);

    // Setting up font for drawing the letter 'M'
    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(36);
    painter.setFont(font);
    painter.setPen(maize);

    // Draw the letter 'M'
    painter.drawText(playerSquare, Qt::AlignCenter, "M");
}

