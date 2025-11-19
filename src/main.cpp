#include <QApplication>
#include "snake.hpp"

int main(int ARGC, char *ARGV[]) {
    QApplication app(ARGC, ARGV);
    Snake window;

    window.setWindowTitle("Snake Game");
    window.show();

    return app.exec();
}
