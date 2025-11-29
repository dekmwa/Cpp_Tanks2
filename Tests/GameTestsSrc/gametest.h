#ifndef GAMETEST_H
#define GAMETEST_H

#include <QObject>


class GameTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();

    void testGameStorageCreation();
    void testGameStorageAddTank();
    void testGameStorageAddWall();
    void testGameStorageObjectsExisting();
    void testGameStorageDeleteObject();

    void testJsonManagerEmptyFile();
    void testJsonManagerInvalidJson();
    void testJsonManagerMissingFields();
    void testJsonManagerNoTanks();
    void testJsonManagerDublicateCoordinates();
    void testJsonManagerValidFile();

    void testGameControllerCreation();
    void testGameControllerProcessAction();
    void testGameControllerMovement();
    void testGameControllerRotation();
    void testGameControllerShotDestroysWall();
    void testGameControllerTankSwitching();
    void testGameControllerBoundaryMovement();
    void testGameControllerCollision();

    void testLevelMakerControllerPlaceTank();
    void testLevelMakerControllerPlaceWall();
    void testLevelMakerControllerDeleteObject();
    void testLevelMakerControllerRotateTank();
    void testLevelMakerControllerOverrideTankWithWall();
    void testLevelMakerControllerMultipleObjects();

    void cleanupTestCase();
    void cleanup();
};

#endif // GAMETEST_H
