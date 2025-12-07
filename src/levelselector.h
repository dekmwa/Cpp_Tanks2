#ifndef LEVELSELECTOR_H
#define LEVELSELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>

class LevelSelector : public QWidget
{
    Q_OBJECT

public:
    LevelSelector(QWidget *parent);

private:
    QVBoxLayout *mainLay;

    QLabel *textInfo;
    QLabel *textExplorer;

    QPushButton *openExplorer;

private:
    void openExplorerClicked();

signals:
    void filepath(QString filepath);
};

#endif // LEVELSELECTOR_H
