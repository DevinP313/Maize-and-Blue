#include "startscreen.h"
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <stack>
#include <QTimer>

#include <QAudioOutput>

#include <QMediaPlayer>


// Create aliases for the stack data structure
typedef std::stack<int> IntStack;

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = nullptr);


private slots:
    void onTimerTimeout();
    void startGame();

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    // Audio
    QMediaPlayer *play;
    QAudioOutput *audio;
    void playVictorySound();
    void playDeathSound();

    // Maze
    static const int mazeCount = 4;
    int mazes[mazeCount][10][10];
    int maze[10][10];

    // Player
    int playerRow;
    int playerCol;
    IntStack rowHistory; // Stack for row history
    IntStack colHistory; // Stack for column history

    bool isTrapped;

    // Timer
    QTimer *timer;
    int duration;
    QTimer *gameTimer;
    int timeRemaining;
    void updateTimeRemaining();

    //start screen
    StartScreen *startScreen;
    bool gameStarted;


    // Player Movement
    void movePlayer(int newRow, int newCol);
    void undoMove();
};

#endif // WIDGET_H


