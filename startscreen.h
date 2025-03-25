#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPushButton>

class StartScreen : public QWidget {
    Q_OBJECT

public:
    StartScreen(QWidget *parent = nullptr);

signals:
    void startButtonClicked();

private:
    QPushButton *startButton;
};

#endif // STARTSCREEN_H


