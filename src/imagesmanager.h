#ifndef IMAGESMANAGER_H
#define IMAGESMANAGER_H

#include <QPixmap>
#include <QColor>


class ImagesManager
{
public:
    ImagesManager();

    void loadImages();
    QPixmap getTankScaledImage(int size);
    QPixmap getWallScaledImage(int size);
    QPixmap getDeleteScaledImage(int size);
    QPixmap getRotateScaledImage(int size);
    QPixmap getBulletScaledImage(int size);

private:
    QPixmap tankOriginalImage;
    QPixmap wallOriginalImage;
    QPixmap deleteOriginalImage;
    QPixmap rotateOriginalImage;
    QPixmap bulletOriginalImage;
    QPixmap rescaleImage(QPixmap &image, int size);
};

#endif // IMAGESMANAGER_H
