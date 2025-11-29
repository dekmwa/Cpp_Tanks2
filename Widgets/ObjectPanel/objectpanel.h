#ifndef OBJECTPANEL_H
#define OBJECTPANEL_H

#include "../../Utils/ImagesManager/imagesmanager.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


class ObjectPanel : public QWidget
{
    Q_OBJECT

public:
    ObjectPanel(QWidget *parent, ImagesManager &imgManager);
    ~ObjectPanel();

private:
    QVBoxLayout *mainLay;
    QHBoxLayout *objects;
    QHBoxLayout *otherActions;

    QPushButton *tank;
    QPushButton *wall;
    QPushButton *clearCell;
    QPushButton *rotateObj;
    QPushButton *savePresetButton;

    void buttonsBacklightRemove();
    void inactiveAllButtons();

    QLabel *topText;
    QLabel *otherActionsText;
    //QLabel *messagesText;

signals:
    void onTankObjectClicked();
    void onWallObjectClicked();
    void onClearCellClicked();
    void onRotateClicked();
    void onSavePresetClicked();

private slots:
    void tankButtonClicked();
    void wallButtonClicked();
    void clearCellClicked();
    void rotateObjClicked();
    void savePresetClicked();
};

#endif // OBJECTPANEL_H
