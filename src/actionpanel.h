#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


enum class Action {
    FORWARD,
    BACKWARD,
    TURNLEFT,
    TURNRIGHT,
    SHOT
};

class ActionPanel : public QWidget
{
    Q_OBJECT

public:
    ActionPanel(QWidget *parent);
    ~ActionPanel();

private:
    QVBoxLayout *mainLay;

    QPushButton *forward;
    QPushButton *backward;
    QPushButton *left;
    QPushButton *right;
    QPushButton *shot;

public slots:
    void inactiveAllButtons();
    void activeAllButtons();

signals:
    void actionClicked(Action action);
};

#endif // ACTIONPANEL_H
