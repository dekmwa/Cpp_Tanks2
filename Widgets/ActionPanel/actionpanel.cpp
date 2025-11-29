#include "actionpanel.h"

ActionPanel::ActionPanel(QWidget *parent) : QWidget(parent), mainLay(new QVBoxLayout(this))
{
    forward = new QPushButton("Вперед", this);
    forward->setFixedSize(140, 50);

    backward = new QPushButton("Назад", this);
    backward->setFixedSize(140, 50);

    left = new QPushButton("Влево", this);
    left->setFixedSize(140, 50);

    right = new QPushButton("Вправо", this);
    right->setFixedSize(140, 50);

    shot = new QPushButton("Выстрелить", this);
    shot->setFixedSize(140, 50);

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

    forward->setFont(font);
    backward->setFont(font);
    left->setFont(font);
    right->setFont(font);

    mainLay->addWidget(forward);
    mainLay->addWidget(backward);
    mainLay->addWidget(left);
    mainLay->addWidget(right);
    mainLay->addWidget(shot);

    connect(forward, &QPushButton::clicked, this, [this]() {
        emit actionClicked(Action::FORWARD);
    });
    connect(backward, &QPushButton::clicked, this, [this]() {
        emit actionClicked(Action::BACKWARD);
    });
    connect(left, &QPushButton::clicked, this, [this]() {
        emit actionClicked(Action::TURNLEFT);
    });
    connect(right, &QPushButton::clicked, this, [this]() {
        emit actionClicked(Action::TURNRIGHT);
    });
    connect(shot, &QPushButton::clicked, this, [this]() {
        emit actionClicked(Action::SHOT);
    });
}

ActionPanel::~ActionPanel()
{

    if (forward) {
        mainLay->removeWidget(forward);
        delete forward;
        forward = nullptr;
    }

    if (backward) {
        mainLay->removeWidget(backward);
        delete backward;
        backward = nullptr;
    }

    if (left) {
        mainLay->removeWidget(left);
        delete left;
        left = nullptr;
    }

    if (right) {
        mainLay->removeWidget(right);
        delete right;
        right = nullptr;
    }

    if (shot) {
        mainLay->removeWidget(shot);
        delete shot;
        shot = nullptr;
    }

    //qDebug() << "=== Destructor called: " << this->metaObject()->className() << "===";
}

void ActionPanel::inactiveAllButtons()
{
    forward->setEnabled(false);
    backward->setEnabled(false);
    left->setEnabled(false);
    right->setEnabled(false);
    shot->setEnabled(false);

    //qDebug() << "ActionPanel кнопки не активны";
}

void ActionPanel::activeAllButtons()
{
    forward->setEnabled(true);
    backward->setEnabled(true);
    left->setEnabled(true);
    right->setEnabled(true);
    shot->setEnabled(true);

    //qDebug() << "ActionPanel кнопки активны";
}
