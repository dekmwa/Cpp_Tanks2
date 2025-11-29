#include "fieldsizeselector.h"

#include <QDebug>
#include <QStringLiteral>
#include <QMessageBox>


FieldSizeSelector::FieldSizeSelector(QWidget *parent) : QWidget(parent)
{
    widthText = new QLabel(QStringLiteral("Количество клеток в ширину (от 1 до %1)").arg(widthCellsLimit), this);
    heightText = new QLabel(QStringLiteral("Количество клеток в высоту (от 1 до %1)").arg(heightCellsLimit), this);
    //infoText = new QLabel("Введите размеры создаваемого уровня", this);
    widthInput = new QLineEdit(this);
    heightInput = new QLineEdit(this);
    confirmSizes = new QPushButton("Подтвердить размеры", this);

    QFont font;
    font.setPointSize(14);
    font.setBold(true);

    widthText->setFont(font);
    heightText->setFont(font);

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

    layout = new QVBoxLayout(this);

    //layout->addWidget(infoText);
    layout->addWidget(widthText);
    layout->addWidget(widthInput);
    layout->addWidget(heightText);
    layout->addWidget(heightInput);
    layout->addWidget(confirmSizes);

    connect(confirmSizes, &QPushButton::clicked, this, &FieldSizeSelector::checkSizes);
    connect(this, &FieldSizeSelector::invalidSizes, this, &FieldSizeSelector::invalidSizesNotice);
}

void FieldSizeSelector::checkSizes()
{
    if (widthInput->text().toInt() >= 1 && widthInput->text().toInt() <= widthCellsLimit
        && heightInput->text().toInt() >= 1 && heightInput->text().toInt() <= heightCellsLimit)
    {
        //qDebug() << "Размеры: " << "ширина" << widthInput->text().toInt() << " высота" << heightInput->text().toInt() << "приняты за валидные.";
        emit validSizes(widthInput->text().toInt(), heightInput->text().toInt());
    } else {
        emit invalidSizes();
    }
}

void FieldSizeSelector::invalidSizesNotice()
{
    QMessageBox::critical(this, "Размеры карты", "Размеры выходят за допустимые пределы");
    widthInput->clear();
    heightInput->clear();
}
