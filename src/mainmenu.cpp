#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), mainLay(new QVBoxLayout(this))
{
    buttonPlay = new QPushButton("Играть", this);
    buttonLevelMaker = new QPushButton("Создание уровня",this);
    buttonExit = new QPushButton("Выход",this);

    setFixedSize(400, 300);

    setStyleSheet(
        "QPushButton {"
        "    background-color: #5e503f;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 12px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #eae0d5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #eae0d5;"
        "}"
        );

    mainLay->addWidget(buttonPlay);
    mainLay->addWidget(buttonLevelMaker);
    mainLay->addWidget(buttonExit);

    connect(buttonPlay, &QPushButton::clicked, this, &MainMenu::PlayClick);
    connect(buttonLevelMaker, &QPushButton::clicked, this, &MainMenu::LevelMakerClick);
}

void MainMenu::PlayClick()
{
    emit PlayClicked();
}

void MainMenu::LevelMakerClick()
{
    emit LevelMakerClicked();
}

void MainMenu::ExitClick()
{
    emit ExitClicked();
}
