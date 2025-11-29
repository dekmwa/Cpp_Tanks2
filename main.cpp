#include "Game/game.h"

#include <QApplication>


#include <QDebug>
#include <QFile>
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game game;
    game.show();
    return app.exec();
}
