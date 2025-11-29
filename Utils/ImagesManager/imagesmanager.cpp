#include "imagesmanager.h"

#include <QDebug>


ImagesManager::ImagesManager()
{
    loadImages();
}

void ImagesManager::loadImages()
{
    tankOriginalImage = QPixmap(":/Resources/Images/tank.png");
    if (tankOriginalImage.isNull())
    {
        qWarning() << "loadImages: Не удалось загрузить изображение танка";
    }

    wallOriginalImage = QPixmap(":/Resources/Images/wall.png");
    if (wallOriginalImage.isNull())
    {
        qWarning() << "loadImages: Не удалось загрузить изображение стены";
    }

    deleteOriginalImage = QPixmap(":/Resources/Images/delete.png");
    if (deleteOriginalImage.isNull())
    {
        qWarning() << "loadImages: Не удалось загрузить изображение delete.png";
    }

    rotateOriginalImage = QPixmap(":/Resources/Images/rotate.png");
    if (rotateOriginalImage.isNull())
    {
        qWarning() << "loadImages: Не удалось загрузить изображение rotate.png";
    }

    bulletOriginalImage = QPixmap(":/Resources/Images/bullet_sprite.png");
    if (bulletOriginalImage.isNull())
    {
        qWarning() << "loadImages: Не удалось загрузить изображение bullet_sprite.png";
    }
}

QPixmap ImagesManager::rescaleImage(QPixmap &image, int size)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap ImagesManager::getTankScaledImage(int size)
{
    return rescaleImage(tankOriginalImage, size);
}

QPixmap ImagesManager::getWallScaledImage(int size)
{
    return rescaleImage(wallOriginalImage, size);
}

QPixmap ImagesManager::getDeleteScaledImage(int size)
{
    return rescaleImage(deleteOriginalImage, size);
}

QPixmap ImagesManager::getRotateScaledImage(int size)
{
    return rescaleImage(rotateOriginalImage, size);
}

QPixmap ImagesManager::getBulletScaledImage(int size)
{
    return rescaleImage(bulletOriginalImage, size);
}
