#pragma once

#include <QWidget>
#include <QKeyEvent>
#include "macros.hpp"

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

class Snake: public QWidget {
  public:
    Snake(QWidget *parent = nullptr);

  protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

  private:
    QImage body;
    QImage head;
    QImage food;

    int timer;
    int dots;
    int food_x;
    int food_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    Direction direction;
    bool inGame;

    void initGame();
    void loadImages();
    void locateFood();
    void checkFood();
    void checkCollision();
    void move();
    void draw();
    void finishGame(QPainter &);
};
