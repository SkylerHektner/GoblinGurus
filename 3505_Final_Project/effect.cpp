#include "effect.h"
#include <QDebug>
///
/// \brief effect::addSprite: add images to sprites vector.
/// \param image
///
void effect::addSprite(QVector<sf::Texture> images, int x, int y, QWidget *parent){
    for(int i = 0; i < images.length(); i++){
        sf::Sprite s;
        //create sprite struct
        sprite_info sprite;
        sprite.transform = s;
        sprite.xMovement = x;
        sprite.yMovement = y;
        sprite.transform.setOrigin(22.0f, 22.0f);
        sprite.transform.setPosition(22.0f, 22.0f);
        sprite.texture = images[i];
        sprite.canvas = new QLabel(parent);
        sprites.append(sprite);
    }
    renderTexture.create(44, 44);
}
///
/// \brief effect::moveEffect: move the effect sprite by sprite.
/// \param index
/// \param rotation
///
void effect::moveEffect(int index, float rotation, int x, int y){
    //qDebug() << rotation;
    sprites[index].canvas->setGeometry(x, y, 60, 60);
    sprites[index].transform.setTexture(sprites[index].texture);
    sprites[index].transform.setRotation(rotation);
    renderTexture.draw(sprites[index].transform);
    renderTexture.display();

    sf::Image image = renderTexture.getTexture().copyToImage();
    QImage sprite(image.getPixelsPtr(), 44, 44, QImage::Format_ARGB32);
    sprite = sprite.rgbSwapped();
    sprite = sprite.scaled(sprites[index].canvas->size(), Qt::IgnoreAspectRatio);
    sprites[index].canvas->setPixmap(QPixmap::fromImage(sprite));
    sprites[index].canvas->show();
}
///
/// \brief effect::getImage
/// \param index
/// \return sf::Image
///
sf::Image effect::getImage(int index){
    return sprites[index].transform.getTexture()->copyToImage();
}
