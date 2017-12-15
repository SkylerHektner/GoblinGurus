#include "effect.h"
#include <QDebug>
///
/// \brief effect::addSprite: add images to sprites vector.
/// \param image
///
void effect::addSprite(QVector<sf::Texture> images, QWidget *parent){
    int height = 0;
    int width = 0;
    for(int i = 0; i < images.length(); i++){
        // get the size of the image
        height = images[i].getSize().x;
        width = images[i].getSize().y;
        sf::Sprite s;
        //create sprite struct
        sprite_info sprite;
        sprite.transform = s;
        sprite.width = width;
        sprite.height = height;
        sprite.transform.setOrigin(width/2, height/2);
        sprite.transform.setPosition(width/2, height/2);
        sprite.texture = images[i];
        sprite.canvas = new QLabel(parent);
        //create a texture to draw to.
        sf::RenderTexture * t = new sf::RenderTexture();
        t->create(width, height);
        //hold the sprites and textures to render.
        renderTexture.append(t);
        sprites.append(sprite);
    }
}
///
/// \brief effect::moveEffect: move the effect sprite by sprite.
/// \param index
/// \param rotation
///
void effect::moveEffect(int index, float rotation, int x, int y){
    if(y < 5000){
        //qDebug() << rotation;
        renderTexture[index]->clear(sf::Color::Transparent);
        sprites[index].canvas->setGeometry(x, y, sprites[index].width * 1.5, sprites[index].height * 1.5);
        sprites[index].transform.setTexture(sprites[index].texture);
        sprites[index].transform.setRotation(rotation);
        renderTexture[index]->draw(sprites[index].transform);
        renderTexture[index]->display();

        sf::Image image = renderTexture[index]->getTexture().copyToImage();
        QImage sprite(image.getPixelsPtr(), sprites[index].width, sprites[index].height, QImage::Format_ARGB32);
        sprite = sprite.rgbSwapped();
        sprite = sprite.scaled(sprites[index].canvas->size(), Qt::IgnoreAspectRatio);
        sprites[index].canvas->setPixmap(QPixmap::fromImage(sprite));
        sprites[index].canvas->show();
    }
}
///
/// \brief effect::getImage
/// \param index
/// \return sf::Image
///
sf::Image effect::getImage(int index){
    return sprites[index].transform.getTexture()->copyToImage();
}
