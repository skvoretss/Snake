#include <QPainter>
#include <QTime>
#include <QRandomGenerator>
#include "snake.hpp"

Snake::Snake(QWidget *parent): QWidget(parent) {
    setStyleSheet("background-color:black;");
    setFixedSize(B_WIDTH, B_HEIGHT);
    direction = Direction::Right;
    inGame = true;
    loadImages();
    initGame();
}

void Snake::initGame() {
    dots = INIT_SIZE;

    for (int z = 0; z < dots; ++z) {
        x[z] = 50 - z * DOT_SIZE;
        y[z] = 50;
    }

    locateFood();
    timer = startTimer(DELAY);
}

void Snake::loadImages() {
    body.load(BODY_PATH);
    head.load(HEAD_PATH);
    food.load(FOOD_PATH);
}

void Snake::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    draw();
}

void Snake::draw() {
    QPainter qp(this);

    if (inGame) {
        qp.drawImage(food_x, food_y, food);

        for (int z = 0; z < dots; z++) {
            if (z == 0) qp.drawImage(x[z], y[z], head);
            else qp.drawImage(x[z], y[z], body);
        }
    } 
    else finishGame(qp);
}

void Snake::finishGame(QPainter &qp) {
    setStyleSheet("background-color:white;");
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);
    qp.setFont(font);
    int h = height();
    int w = width();
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Snake::checkFood() {
    if ((x[0] == food_x) && (y[0] == food_y)) {
        ++dots;
        locateFood();
    }
}

void Snake::move() {
    for (int z = dots; z > 0; --z) {
        x[z] = x[z - 1];
        y[z] = y[z - 1];
    }

    if (direction == Direction::Left) {
        x[0] -= DOT_SIZE;
    }
    else if (direction == Direction::Right) {
        x[0] += DOT_SIZE;
    }
    else if (direction == Direction::Up) {
        y[0] -= DOT_SIZE;
    }
    else if (direction == Direction::Down) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {
    for (int z = dots; z > 4; z--) {
        if ((x[0] == x[z]) && (y[0] == y[z])) inGame = false;
    }

    if (y[0] < 0 || y[0] >= B_HEIGHT) inGame = false;
    else if (x[0] < 0 || x[0] >= B_WIDTH) inGame = false;

    if (!inGame) killTimer(timer);
}

void Snake::locateFood() {
    int r;
    r = QRandomGenerator::global()->generate() % RAND_POS;
    food_x = (r * DOT_SIZE);

    r = QRandomGenerator::global()->generate() % RAND_POS;
    food_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (inGame) {
        checkFood();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {
    int key = e->key();

    if ((key == Qt::Key_Left) && (direction != Direction::Right))
        direction = Direction::Left;
    else if ((key == Qt::Key_Right) && (direction != Direction::Left))
        direction = Direction::Right;
    else if ((key == Qt::Key_Up) && (direction != Direction::Down))
        direction = Direction::Up;
    else if ((key == Qt::Key_Down) && (direction != Direction::Up))
        direction = Direction::Down;

    QWidget::keyPressEvent(e);
}
