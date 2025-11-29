#include "levelselector.h"

#include <QFileDialog>


LevelSelector::LevelSelector(QWidget *parent) : QWidget(parent), mainLay(new QVBoxLayout(this))
{
    textInfo = new QLabel("Укажите путь к пресету уровня", this);

    textExplorer = new QLabel("Указать в проводнике", this);
    openExplorer = new QPushButton("Открыть проводник", this);

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

    QFont font;
    font.setPointSize(14);
    font.setBold(true);

    textInfo->setFont(font);
    textExplorer->setFont(font);

    mainLay->addWidget(textInfo);
    mainLay->addWidget(textExplorer);
    mainLay->addWidget(openExplorer);

    connect(openExplorer, &QPushButton::clicked, this, &LevelSelector::openExplorerClicked);
}

void LevelSelector::openExplorerClicked()
{
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        "Выбрать уровень",
        "",
        "JSON Files (*.json)"
        );

    emit filepath(filename);
}
