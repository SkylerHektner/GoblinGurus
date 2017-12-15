#ifndef EFFECT_H
#define EFFECT_H

#include <QVector>
#include <QLabel>
#include <QImage>
#include <QString>
#include "SFML/Graphics.hpp"
class effect
{
public:
    typedef struct{
        sf::Sprite transform;
        sf::Texture texture;
        QLabel* canvas;
        float height;
        float width;
    }sprite_info;

    void addSprite(QVector<sf::Texture> images, QWidget* parent);
    void moveEffect(int index, float rotation, int x, int y);
    sf::Image getImage(int index);
    void setEffect(int type);
private:
    QVector<sprite_info> sprites;
    QVector<sf::RenderTexture *> renderTexture;
};

#endif // EFFECT_H
