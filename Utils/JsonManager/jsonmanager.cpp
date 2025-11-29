#include "jsonmanager.h"
#include "../../Objects/Tank/tank.h"
#include "../../Objects/Wall/wall.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QDebug>


JsonManager::JsonManager() {}

bool JsonManager::GameStorageToJson(GameStorage *gs, int widthCellsCnt, int heightCellsCnt)
{
    QJsonObject fullLevel;
    QJsonObject levelSettings;
    QJsonArray tanks;
    QJsonArray walls;

    levelSettings["widthCellsCnt"] = widthCellsCnt;
    levelSettings["heightCellsCnt"] = heightCellsCnt;

    for (int i = 0; i < gs->getTanksCount(); i++)
    {
        Tank *currentTank = gs->getTankByIndex(i);
        QJsonObject jsonTank;
        int direction;

        switch(currentTank->getDirection()) {
        case Direction::UP: direction = 0; break;
        case Direction::RIGHT: direction = 1; break;
        case Direction::DOWN: direction = 2; break;
        case Direction::LEFT: direction = 3; break;
        }

        jsonTank["coordinateX"] = currentTank->getCoordinateX() + 1;
        jsonTank["coordinateY"] = currentTank->getCoordinateY() + 1;
        jsonTank["direction"] = direction;

        tanks.append(jsonTank);
    }

    for (int i = 0; i < gs->getWallsCount(); i++)
    {
        Wall *currentWall = gs->getWallByIndex(i);
        QJsonObject jsonWall;
        jsonWall["coordinateX"] = currentWall->getCoordinateX() + 1;
        jsonWall["coordinateY"] = currentWall->getCoordinateY() + 1;
        walls.append(jsonWall);
    }

    fullLevel["levelSettings"] = levelSettings;
    fullLevel["tanks"] = tanks;
    fullLevel["walls"] = walls;

    QString filename = QFileDialog::getSaveFileName(
        nullptr,
        "Сохранить уровень",
        "",
        "JSON Files (*.json)"
    );
    qDebug() << "Имя файла: " << filename;

    QJsonDocument document(fullLevel);
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(document.toJson());
        file.close();
        return true;
    } else {
        return false;
    }
}

ValidationResult JsonManager::jsonFileIsValid(QString filepath)
{
    ValidationResult result;
    result.isValid = false;
    result.errorMessage = "";

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        result.errorMessage = "Не удалось открыть файл: " + filepath;
        return result;
    }

    QByteArray levelData = file.readAll();
    file.close();
    QJsonDocument levelJsonDoc = QJsonDocument::fromJson(levelData);
    QJsonObject levelJsonFile = levelJsonDoc.object();

    QJsonObject levelSettings = levelJsonFile["levelSettings"].toObject();
    if (! (levelSettings.contains("heightCellsCnt") && levelSettings.contains("widthCellsCnt")
        && levelSettings["heightCellsCnt"].toInt() > 0 && levelSettings["heightCellsCnt"].toInt() < heightCellsCntMax
        && levelSettings["widthCellsCnt"].toInt() > 0 && levelSettings["widthCellsCnt"].toInt() < widthCellsCntMax)) {
        result.errorMessage = QString("Не валидные размеры уровня\nразмеры: %1 %2")
                                  .arg(levelSettings["heightCellsCnt"].toInt())
                                  .arg(levelSettings["widthCellsCnt"].toInt());
        return result;
    }

    QVector<QVector<bool>> existCoordinates(levelSettings["heightCellsCnt"].toInt(), QVector<bool>(levelSettings["widthCellsCnt"].toInt(), false));

    QJsonArray tanksArray = levelJsonFile["tanks"].toArray();
    if (tanksArray.size() < 1) {
        result.errorMessage = "Для начала игры должен быть хотя бы 1 танк";
        return result;
    }

    for (int i = 0; i < tanksArray.size(); i++) {
        QJsonObject currentTank = tanksArray[i].toObject();

        if (! (currentTank.contains("coordinateX") && currentTank["coordinateX"].toInt() > 0
              && currentTank["coordinateX"].toInt() <= levelSettings["widthCellsCnt"].toInt()
            && currentTank.contains("coordinateY") && currentTank["coordinateY"].toInt() > 0
              && currentTank["coordinateY"].toInt() <= levelSettings["heightCellsCnt"].toInt()
            && currentTank.contains("direction") && currentTank["direction"].toInt() >= 0 && currentTank["direction"].toInt() <= 3))
        {
            result.errorMessage = QString("Невалидный json объект танка под номером: %1").arg(i + 1);
            return result;
        }

        if (existCoordinates[currentTank["coordinateY"].toInt() - 1][currentTank["coordinateX"].toInt() - 1]) {
            result.errorMessage = QString("Координаты X:%1 Y:%2 в json файле не уникальны")
                                      .arg(currentTank["coordinateX"].toInt()).arg(currentTank["coordinateY"].toInt());
            return result;
        }

        existCoordinates[currentTank["coordinateY"].toInt() - 1][currentTank["coordinateX"].toInt() - 1] = true;
    }


    QJsonArray wallsArray = levelJsonFile["walls"].toArray();
    for (int i = 0; i < wallsArray.size(); i++) {
        QJsonObject currentWall = wallsArray[i].toObject();

        if (! (currentWall.contains("coordinateX") && currentWall["coordinateX"].toInt() > 0
              && currentWall["coordinateX"].toInt() <= levelSettings["widthCellsCnt"].toInt()
            && currentWall.contains("coordinateY") && currentWall["coordinateY"].toInt() > 0
              && currentWall["coordinateY"].toInt() <= levelSettings["heightCellsCnt"].toInt()))
        {
            result.errorMessage = QString("Невалидный json объект стены под номером: %1").arg(i + 1);
            return result;
        }

        if (existCoordinates[currentWall["coordinateY"].toInt() - 1][currentWall["coordinateX"].toInt() - 1]) {
            result.errorMessage = QString("Координаты X:%1 Y:%2 в json файле не уникальны")
                                      .arg(currentWall["coordinateX"].toInt()).arg(currentWall["coordinateY"].toInt());
            return result;
        }

        existCoordinates[currentWall["coordinateY"].toInt() - 1][currentWall["coordinateX"].toInt() - 1] = true;
    }

    result.isValid = true;
    return result;
}

GameStorage* JsonManager::JsonToGameStorage(QString filepath)
{
    GameStorage* gameStorage = new GameStorage();

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        return gameStorage;
    }

    QByteArray levelData = file.readAll();
    file.close();
    QJsonDocument levelJsonDoc = QJsonDocument::fromJson(levelData);
    QJsonObject levelJsonFile = levelJsonDoc.object();

    QJsonObject levelSettings = levelJsonFile["levelSettings"].toObject();
    gameStorage->setWidthCellsCount(levelSettings["widthCellsCnt"].toInt());
    gameStorage->setHeightCellsCount(levelSettings["heightCellsCnt"].toInt());

    QJsonArray tanksArray = levelJsonFile["tanks"].toArray();
    for (int i = 0; i < tanksArray.size(); i++) {
        QJsonObject currentTank = tanksArray[i].toObject();
        Direction direction = Direction::UP;

        switch (currentTank["direction"].toInt()){
        case 0: direction = Direction::UP; break;
        case 1: direction = Direction::RIGHT; break;
        case 2: direction = Direction::DOWN; break;
        case 3: direction = Direction::LEFT; break;
        }

        gameStorage->pushTank(new Tank(currentTank["coordinateX"].toInt() - 1, currentTank["coordinateY"].toInt() - 1, direction));
    }

    QJsonArray wallsArray = levelJsonFile["walls"].toArray();
    for (int i = 0; i < wallsArray.size(); i++) {
        QJsonObject currentWall = wallsArray[i].toObject();
        gameStorage->pushWall(new Wall(currentWall["coordinateX"].toInt() - 1, currentWall["coordinateY"].toInt() - 1));
    }

    return gameStorage;
}
