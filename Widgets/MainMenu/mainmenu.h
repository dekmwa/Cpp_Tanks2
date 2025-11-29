#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

private:
    QPushButton *buttonPlay;
    QPushButton *buttonLevelMaker;
    QPushButton *buttonExit;

    QVBoxLayout *mainLay;

signals:
    void PlayClicked();
    void LevelMakerClicked();
    void ExitClicked();

private slots:
    void PlayClick();
    void LevelMakerClick();
    void ExitClick();
};

#endif // MAINMENU_H
