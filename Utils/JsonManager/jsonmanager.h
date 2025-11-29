#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include "../GameStorage/gamestorage.h"

#include <QString>


struct ValidationResult {
    bool isValid;
    QString errorMessage;
};

class JsonManager
{
public:
    JsonManager();

public:
    bool GameStorageToJson(GameStorage *gs, int widthCellsCnt, int heightCellsCnt);
    GameStorage* JsonToGameStorage(QString filepath);
    ValidationResult jsonFileIsValid(QString filepath);

private:
    const int heightCellsCntMax = 50;
    const int widthCellsCntMax = 50;
};

#endif // JSONMANAGER_H
