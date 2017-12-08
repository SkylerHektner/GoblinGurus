#include "effect.h"

effect::effect(QWidget *parent) : QWidget(parent)
{
    _parent = parent;
}
///
/// \brief effect::addSprite: turnes image into a textured sprite and adds it to the sprites vector, original demensions are preserved.
/// \param image
///
void effect::addSprite(QImage image)
{
    const uchar* imageData = image.bits();
    Sprite *sprite;
    sprite->spriteTexture.loadFromMemory(imageData, image.byteCount());
    sprite->transform.setTexture(sprite->spriteTexture);
    sprite->texture.create(image.size().width(), image.size().height());
    sprite->height = image.size().height();
    sprite->width = image.size().width();
    sprite->canvas = new QLabel(_parent);//set up the QLabel that will be painted.
    listOfSprites.append(sprite);
}
///
/// \brief effect::addSprite: Overloaded addSprtie with height and width scaling.
/// \param image
/// \param x
/// \param y
///
void effect::addSprite(QImage image, int x, int y)
{
    const uchar* imageData = image.bits();
    Sprite sprite;
    sprite.spriteTexture.loadFromMemory(imageData, image.byteCount());
    sprite.transform.setTexture(sprite.spriteTexture);
    sprite.texture.create(image.size().width(), image.size().height());
    sprite.height = y;
    sprite.width = x;
    sprite.canvas = new QLabel(_parent);
    listOfSprites.append(&sprite);
}
///
/// \brief effect::scaleSprites: Change the size of the sprite by x width and y height.
/// \param x
/// \param y
///
void effect::scaleSprites(int x, int y)
{
    for(int i = 0; listOfSprites.length(); i++){
        listOfSprites[i]->width = x;
        listOfSprites[i]->height = y;
    }
}
///
/// \brief effect::setEffect: set the desired predefined effect and FPS.
/// \param FPS
/// \param effectType
///
void effect::setTypeOfEffect(int FPS, int effectType){
    Effect thisEffect;
    thisEffect.FPS = FPS;
    thisEffect.typeOfEffect = effectType;
}

void effect::updateEffect()
{

}
