#include "gametest.h"
#include "../../src/jsonmanager.h"
#include "../../src/gamescreencontroller.h"
#include "../../src/levelmakercontroller.h"

#include <QTest>
#include <QSignalSpy>
#include <QTemporaryFile>
#include <QJsonObject>
#include <QJsonArray>


void GameTest::initTestCase() {}
void GameTest::init() {}

void GameTest::testGameStorageCreation()
{
    GameStorage storage;

    QCOMPARE(storage.getTanksCount(), 0);
    QCOMPARE(storage.getWallsCount(), 0);
    QCOMPARE(storage.getWidthCellsCount(), 0);
    QCOMPARE(storage.getHeightCellsCount(), 0);
}

void GameTest::testGameStorageAddTank()
{
    GameStorage storage;

    Tank* tank = new Tank(2, 3, Direction::UP);
    storage.pushTank(tank);

    QCOMPARE(storage.getTanksCount(), 1);

    Tank* retrievedTank = storage.getTankByIndex(0);
    QVERIFY(retrievedTank != nullptr);
    QCOMPARE(retrievedTank->getCoordinateX(), 2);
    QCOMPARE(retrievedTank->getCoordinateY(), 3);
    QCOMPARE(retrievedTank->getDirection(), Direction::UP);
}

void GameTest::testGameStorageAddWall()
{
    GameStorage storage;

    Wall* wall = new Wall(5, 7);
    storage.pushWall(wall);

    QCOMPARE(storage.getWallsCount(), 1);

    Wall* retrievedWall = storage.getWallByIndex(0);
    QVERIFY(retrievedWall != nullptr);
    QCOMPARE(retrievedWall->getCoordinateX(), 5);
    QCOMPARE(retrievedWall->getCoordinateY(), 7);
}

void GameTest::testGameStorageObjectsExisting()
{
    GameStorage storage;

    storage.pushTank(new Tank(1, 1, Direction::UP));
    storage.pushWall(new Wall(2, 2));

    QVERIFY(storage.tankOnCoordinatesExist(1, 1));
    QVERIFY(!storage.tankOnCoordinatesExist(9, 9));

    QVERIFY(storage.wallOnCoordinatesExist(2, 2));
    QVERIFY(!storage.wallOnCoordinatesExist(9, 9));

    QVERIFY(storage.objectOnCoordinatesExist(1, 1));
    QVERIFY(storage.objectOnCoordinatesExist(2, 2));
    QVERIFY(!storage.objectOnCoordinatesExist(9, 9));
}

void GameTest::testGameStorageDeleteObject()
{
    GameStorage storage;

    storage.pushTank(new Tank(1, 1, Direction::UP));
    storage.pushWall(new Wall(2, 2));
    storage.pushTank(new Tank(3, 3, Direction::RIGHT));

    QCOMPARE(storage.getTanksCount(), 2);
    QCOMPARE(storage.getWallsCount(), 1);

    storage.deleteExistObjectOnCoordinates(1, 1);
    QCOMPARE(storage.getTanksCount(), 1);
    QVERIFY(!storage.tankOnCoordinatesExist(1, 1));

    storage.deleteExistObjectOnCoordinates(2, 2);
    QCOMPARE(storage.getWallsCount(), 0);
    QVERIFY(!storage.wallOnCoordinatesExist(2, 2));

    QVERIFY(storage.tankOnCoordinatesExist(3, 3));
}


void GameTest::testJsonManagerEmptyFile()
{
    JsonManager manager;

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.close();

    ValidationResult result = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(!result.isValid);
    QVERIFY(!result.errorMessage.isEmpty());
}

void GameTest::testJsonManagerInvalidJson()
{
    JsonManager manager;

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.write("{ неправильный json }");
    tempFile.close();

    ValidationResult result = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(!result.isValid);
}

void GameTest::testJsonManagerMissingFields()
{
    JsonManager manager;

    QJsonObject invalidJson;
    invalidJson["widthCellsCnt"] = 5;

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.write(QJsonDocument(invalidJson).toJson());
    tempFile.close();

    ValidationResult result = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(!result.isValid);
    QVERIFY(result.errorMessage.contains("Не валидные размеры уровня"));
}

void GameTest::testJsonManagerNoTanks()
{
    JsonManager manager;

    QJsonObject levelSettings;
    levelSettings["widthCellsCnt"] = 5;
    levelSettings["heightCellsCnt"] = 5;

    QJsonObject json;
    json["levelSettings"] = levelSettings;
    json["tanks"] = QJsonArray();
    json["walls"] = QJsonArray();

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.write(QJsonDocument(json).toJson());
    tempFile.close();

    ValidationResult result = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(!result.isValid);
    QVERIFY(result.errorMessage.contains("Для начала игры должен быть хотя бы 1 танк"));
}

void GameTest::testJsonManagerDublicateCoordinates()
{
    JsonManager manager;

    QJsonObject levelSettings;
    levelSettings["widthCellsCnt"] = 5;
    levelSettings["heightCellsCnt"] = 5;

    QJsonArray tanks;
    QJsonObject tank1;
    tank1["coordinateX"] = 1;
    tank1["coordinateY"] = 1;
    tank1["direction"] = 0;
    tanks.append(tank1);

    QJsonObject tank2;
    tank2["coordinateX"] = 1;
    tank2["coordinateY"] = 1;
    tank2["direction"] = 1;
    tanks.append(tank2);

    QJsonObject json;
    json["levelSettings"] = levelSettings;
    json["tanks"] = tanks;
    json["walls"] = QJsonArray();

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.write(QJsonDocument(json).toJson());
    tempFile.close();

    ValidationResult result = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(!result.isValid);
    QVERIFY(result.errorMessage.contains("Координаты X:1 Y:1 в json файле не уникальны"));
}

void GameTest::testJsonManagerValidFile()
{
    JsonManager manager;

    QJsonObject levelSettings;
    levelSettings["widthCellsCnt"] = 5;
    levelSettings["heightCellsCnt"] = 5;

    QJsonArray tanks;
    QJsonObject tank1;
    tank1["coordinateX"] = 1;
    tank1["coordinateY"] = 1;
    tank1["direction"] = 0;

    QJsonObject tank2;
    tank2["coordinateX"] = 3;
    tank2["coordinateY"] = 2;
    tank2["direction"] = 1;
    tanks.append(tank1);
    tanks.append(tank2);

    QJsonArray walls;
    QJsonObject wall1;
    wall1["coordinateX"] = 2;
    wall1["coordinateY"] = 2;

    QJsonObject wall2;
    wall2["coordinateX"] = 4;
    wall2["coordinateY"] = 4;
    walls.append(wall1);
    walls.append(wall2);

    QJsonObject json;
    json["levelSettings"] = levelSettings;
    json["tanks"] = tanks;
    json["walls"] = walls;

    QTemporaryFile tempFile;
    tempFile.open();
    tempFile.write(QJsonDocument(json).toJson());
    tempFile.close();

    ValidationResult validation = manager.jsonFileIsValid(tempFile.fileName());
    QVERIFY(validation.isValid);

    GameStorage* storage = manager.JsonToGameStorage(tempFile.fileName());

    QCOMPARE(storage->getWidthCellsCount(), 5);
    QCOMPARE(storage->getHeightCellsCount(), 5);
    QCOMPARE(storage->getTanksCount(), 2);
    QCOMPARE(storage->getWallsCount(), 2);

    // координаты из Json файла идут по счёту клеток, поэтому они на 1 больше чем координаты в gameStorage
    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getCoordinateX(), 1 - 1);
    QCOMPARE(tank->getCoordinateY(), 1 - 1);
    QCOMPARE(tank->getDirection(), Direction::UP);
    tank = storage->getTankByIndex(1);
    QCOMPARE(tank->getCoordinateX(), 3 - 1);
    QCOMPARE(tank->getCoordinateY(), 2 - 1);
    QCOMPARE(tank->getDirection(), Direction::RIGHT);

    Wall* wall = storage->getWallByIndex(0);
    QCOMPARE(wall->getCoordinateX(), 2 - 1);
    QCOMPARE(wall->getCoordinateY(), 2 - 1);
    wall = storage->getWallByIndex(1);
    QCOMPARE(wall->getCoordinateX(), 4 - 1);
    QCOMPARE(wall->getCoordinateY(), 4 - 1);

    delete storage;
}

void GameTest::testGameControllerCreation()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);

    GameController controller(storage, 5, 5);

    QCOMPARE(controller.getCurrentTankIndex(), 0);
    QVERIFY(controller.getGameStorage() == storage);

    delete storage;
}

void GameTest::testGameControllerProcessAction()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(2, 2, Direction::UP));

    GameController controller(storage, 5, 5);

    QSignalSpy changedSpy(&controller, &GameController::gameStorageChanged);
    QSignalSpy highlightSpy(&controller, &GameController::highlightCell);

    controller.processAction(Action::FORWARD);

    QCOMPARE(changedSpy.count(), 1);
    QCOMPARE(highlightSpy.count(), 1);

    delete storage;
}

void GameTest::testGameControllerMovement()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(2, 2, Direction::UP));

    GameController controller(storage, 5, 5);

    controller.processAction(Action::FORWARD);
    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getCoordinateY(), 1);

    controller.processAction(Action::BACKWARD);
    QCOMPARE(tank->getCoordinateY(), 2);

    delete storage;
}

void GameTest::testGameControllerRotation()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(2, 2, Direction::UP));

    GameController controller(storage, 5, 5);

    controller.processAction(Action::TURNRIGHT);
    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getDirection(), Direction::RIGHT);

    controller.processAction(Action::TURNLEFT);
    QCOMPARE(tank->getDirection(), Direction::UP);

    delete storage;
}

void GameTest::testGameControllerShotDestroysWall()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(1, 1, Direction::RIGHT));
    storage->pushWall(new Wall(2, 1));

    GameController controller(storage, 5, 5);

    QCOMPARE(storage->getWallsCount(), 1);
    controller.processAction(Action::SHOT);
    QCOMPARE(storage->getWallsCount(), 0);

    delete storage;
}

void GameTest::testGameControllerTankSwitching()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(1, 1, Direction::UP));
    storage->pushTank(new Tank(3, 3, Direction::RIGHT));

    GameController controller(storage, 5, 5);

    QCOMPARE(controller.getCurrentTankIndex(), 0);
    controller.processAction(Action::FORWARD);
    QCOMPARE(controller.getCurrentTankIndex(), 1);
    controller.processAction(Action::FORWARD);
    QCOMPARE(controller.getCurrentTankIndex(), 0);

    delete storage;
}

void GameTest::testGameControllerBoundaryMovement()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(3);
    storage->setHeightCellsCount(3);
    storage->pushTank(new Tank(0, 0, Direction::UP));

    GameController controller(storage, 3, 3);

    controller.processAction(Action::FORWARD);
    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getCoordinateY(), 0);

    tank->setDirection(Direction::LEFT);
    controller.processAction(Action::FORWARD);
    QCOMPARE(tank->getCoordinateX(), 0);

    delete storage;
}

void GameTest::testGameControllerCollision()
{
    GameStorage* storage = new GameStorage();
    storage->setWidthCellsCount(5);
    storage->setHeightCellsCount(5);
    storage->pushTank(new Tank(1, 1, Direction::RIGHT));
    storage->pushWall(new Wall(2, 1));
    storage->pushTank(new Tank(3, 3, Direction::LEFT));

    GameController controller(storage, 5, 5);

    controller.processAction(Action::FORWARD);
    Tank* tank1 = storage->getTankByIndex(0);
    QCOMPARE(tank1->getCoordinateX(), 1);

    controller.processAction(Action::FORWARD);
    Tank* tank2 = storage->getTankByIndex(1);
    QCOMPARE(tank2->getCoordinateX(), 2);

    delete storage;
}

void GameTest::testLevelMakerControllerPlaceTank()
{
    GameStorage* storage = new GameStorage();
    LevelMakerController controller(storage);

    QSignalSpy spy(&controller, &LevelMakerController::gameStorageChanged);

    controller.placeTank(2, 3);

    QCOMPARE(storage->getTanksCount(), 1);
    QCOMPARE(spy.count(), 1);

    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getCoordinateX(), 3);
    QCOMPARE(tank->getCoordinateY(), 2);
    QCOMPARE(tank->getDirection(), Direction::UP);

    delete storage;
}

void GameTest::testLevelMakerControllerPlaceWall()
{
    GameStorage* storage = new GameStorage();
    LevelMakerController controller(storage);

    QSignalSpy spy(&controller, &LevelMakerController::gameStorageChanged);

    controller.placeWall(4, 5);

    QCOMPARE(storage->getWallsCount(), 1);
    QCOMPARE(spy.count(), 1);

    Wall* wall = storage->getWallByIndex(0);
    QCOMPARE(wall->getCoordinateX(), 5);
    QCOMPARE(wall->getCoordinateY(), 4);

    delete storage;
}

void GameTest::testLevelMakerControllerDeleteObject()
{
    GameStorage* storage = new GameStorage();
    storage->pushTank(new Tank(1, 1, Direction::UP));
    storage->pushWall(new Wall(2, 2));

    LevelMakerController controller(storage);
    QSignalSpy spy(&controller, &LevelMakerController::gameStorageChanged);

    controller.deleteObject(1, 1);
    QCOMPARE(storage->getTanksCount(), 0);
    QCOMPARE(spy.count(), 1);

    controller.deleteObject(2, 2);
    QCOMPARE(storage->getWallsCount(), 0);
    QCOMPARE(spy.count(), 2);

    delete storage;
}

void GameTest::testLevelMakerControllerRotateTank()
{
    GameStorage* storage = new GameStorage();
    storage->pushTank(new Tank(3, 3, Direction::UP));

    LevelMakerController controller(storage);
    QSignalSpy spy(&controller, &LevelMakerController::gameStorageChanged);

    controller.rotateTank(3, 3);

    Tank* tank = storage->getTankByIndex(0);
    QCOMPARE(tank->getDirection(), Direction::RIGHT);
    QCOMPARE(spy.count(), 1);

    controller.rotateTank(3, 3);
    QCOMPARE(tank->getDirection(), Direction::DOWN);
    QCOMPARE(spy.count(), 2);

    delete storage;
}

void GameTest::testLevelMakerControllerOverrideTankWithWall()
{
    GameStorage* storage = new GameStorage();
    storage->pushTank(new Tank(2, 2, Direction::UP));

    LevelMakerController controller(storage);

    controller.placeWall(2, 2);

    QCOMPARE(storage->getTanksCount(), 0);
    QCOMPARE(storage->getWallsCount(), 1);

    Wall* wall = storage->getWallByIndex(0);
    QCOMPARE(wall->getCoordinateX(), 2);
    QCOMPARE(wall->getCoordinateY(), 2);

    delete storage;
}

void GameTest::testLevelMakerControllerMultipleObjects()
{
    GameStorage* storage = new GameStorage();
    LevelMakerController controller(storage);

    controller.placeTank(0, 0);
    controller.placeTank(1, 1);
    controller.placeWall(2, 2);
    controller.placeWall(3, 3);

    QCOMPARE(storage->getTanksCount(), 2);
    QCOMPARE(storage->getWallsCount(), 2);

    Tank* tank1 = storage->getTankByIndex(0);
    Tank* tank2 = storage->getTankByIndex(1);
    Wall* wall1 = storage->getWallByIndex(0);
    Wall* wall2 = storage->getWallByIndex(1);

    QCOMPARE(tank1->getCoordinateX(), 0);
    QCOMPARE(tank1->getCoordinateY(), 0);
    QCOMPARE(tank2->getCoordinateX(), 1);
    QCOMPARE(tank2->getCoordinateY(), 1);
    QCOMPARE(wall1->getCoordinateX(), 2);
    QCOMPARE(wall1->getCoordinateY(), 2);
    QCOMPARE(wall2->getCoordinateX(), 3);
    QCOMPARE(wall2->getCoordinateY(), 3);

    delete storage;
}

void GameTest::cleanupTestCase() {}
void GameTest::cleanup() {}
