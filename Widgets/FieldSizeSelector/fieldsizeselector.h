#ifndef FIELDSIZESELECTOR_H
#define FIELDSIZESELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>


class FieldSizeSelector : public QWidget
{
    Q_OBJECT

public:
    FieldSizeSelector(QWidget *parent = nullptr);

private:
    QLabel *widthText;
    QLabel *heightText;
    //QLabel *infoText;
    QPushButton *confirmSizes;
    QLineEdit *widthInput;
    QLineEdit *heightInput;

    const int widthCellsLimit = 50;
    const int heightCellsLimit = 50;

    QVBoxLayout *layout;

signals:
    void confirmSizesClicked();
    void invalidSizes();
    void validSizes(int widthCount, int heightCount);

private slots:
    void checkSizes();
    void invalidSizesNotice();
};

#endif // FIELDSIZESELECTOR_H
