#include "objectpanel.h"

ObjectPanel::ObjectPanel(QWidget *parent, ImagesManager &imgManager) : mainLay(new QVBoxLayout(this)),
    objects(new QHBoxLayout(this)), otherActions(new QHBoxLayout(this))
{
    topText = new QLabel("Выберите объект", this);

    tank = new QPushButton(this);
    tank->setFixedSize(50, 50);
    tank->setIconSize(QSize(50, 50));
    tank->setIcon(QIcon(imgManager.getTankScaledImage(50)));
    connect(tank, &QPushButton::clicked, this, &ObjectPanel::tankButtonClicked);

    wall = new QPushButton(this);
    wall->setFixedSize(50, 50);
    wall->setIconSize(QSize(50, 50));
    wall->setIcon(QIcon(imgManager.getWallScaledImage(50)));
    connect(wall, &QPushButton::clicked, this, &ObjectPanel::wallButtonClicked);

    objects->addWidget(tank);
    objects->addWidget(wall);

    otherActionsText = new QLabel("Другие действия", this);

    clearCell = new QPushButton(this);
    clearCell->setFixedSize(50, 50);
    clearCell->setIconSize(QSize(50, 50));
    clearCell->setIcon(QIcon(imgManager.getDeleteScaledImage(50)));
    connect(clearCell, &QPushButton::clicked, this, &ObjectPanel::clearCellClicked);

    rotateObj = new QPushButton(this);
    rotateObj->setFixedSize(50, 50);
    rotateObj->setIconSize(QSize(50, 50));
    rotateObj->setIcon(QIcon(imgManager.getRotateScaledImage(50)));
    connect(rotateObj, &QPushButton::clicked, this, &ObjectPanel::rotateObjClicked);

    otherActions->addWidget(clearCell);
    otherActions->addWidget(rotateObj);

    //messagesText = new QLabel("", this);

    savePresetButton = new QPushButton("Сохранить пресет", this);
    savePresetButton->setFixedSize(130, 50);
    connect(savePresetButton, &QPushButton::clicked, this, &ObjectPanel::savePresetClicked);

    setStyleSheet(
        "QPushButton {"
        "    background-color: #5e503f;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    font-size: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #eae0d5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #eae0d5;"
        "}"
    );

    QFont font;
    font.setPointSize(14);
    font.setBold(true);

    topText->setFont(font);
    tank->setFont(font);
    wall->setFont(font);
    otherActionsText->setFont(font);
    savePresetButton->setFont(font);

    mainLay->addWidget(topText);
    mainLay->addLayout(objects);
    mainLay->addWidget(otherActionsText);
    mainLay->addLayout(otherActions);
    mainLay->addWidget(savePresetButton);
}

ObjectPanel::~ObjectPanel()
{
    if (topText) {
        delete topText;
        topText = nullptr;
    }

    if (otherActionsText) {
        delete otherActionsText;
        otherActionsText = nullptr;
    }

    if (tank) {
        delete tank;
        tank = nullptr;
    }

    if (wall) {
        delete wall;
        wall = nullptr;
    }

    if (clearCell) {
        delete clearCell;
        clearCell = nullptr;
    }

    if (rotateObj) {
        delete rotateObj;
        rotateObj = nullptr;
    }

    if (savePresetButton) {
        delete savePresetButton;
        savePresetButton = nullptr;
    }

    //qDebug() << "=== Destructor called: " << this->metaObject()->className() << "===";
}

void ObjectPanel::savePresetClicked()
{
    //inactiveAllButtons();
    emit onSavePresetClicked();
}

void ObjectPanel::buttonsBacklightRemove()
{
    tank->setStyleSheet("");
    wall->setStyleSheet("");
    clearCell->setStyleSheet("");
    rotateObj->setStyleSheet("");
}

void ObjectPanel::inactiveAllButtons()
{
    tank->setEnabled(false);
    wall->setEnabled(false);
    clearCell->setEnabled(false);
    rotateObj->setEnabled(false);
    savePresetButton->setEnabled(false);
}

void ObjectPanel::tankButtonClicked()
{
    buttonsBacklightRemove();
    tank->setStyleSheet("background-color: red;");
    emit onTankObjectClicked();
}

void ObjectPanel::wallButtonClicked()
{
    buttonsBacklightRemove();
    wall->setStyleSheet("background-color: red;");
    emit onWallObjectClicked();
}

void ObjectPanel::clearCellClicked()
{
    buttonsBacklightRemove();
    clearCell->setStyleSheet("background-color: red;");
    emit onClearCellClicked();
}

void ObjectPanel::rotateObjClicked()
{
    buttonsBacklightRemove();
    rotateObj->setStyleSheet("background-color: red;");
    emit onRotateClicked();
}
