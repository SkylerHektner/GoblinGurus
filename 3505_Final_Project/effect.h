#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QWidget>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <QVector>
#include <QLabel>
#include <QTimer>
class effect : public QWidget
{
    Q_OBJECT

    struct Sprite{
        sf::Texture spriteTexture;
        sf::Sprite transform;
        QLabel* canvas;
        sf::RenderTexture texture;
        int width;
        int height;
    };

    struct Effect{
        int FPS;
        int typeOfEffect;
    };

public:
    explicit effect(QWidget *parent = nullptr);
    void addSprite(QImage image);
    void addSprite(QImage, int x, int y);
    void scaleSprites(int x, int y);
    void setTypeOfEffect(int FPS, int typeOfEffect);
    QWidget* _parent;
signals:

public slots:
    void updateEffect();
    void startEffect(QWidget*);
private:
    QVector<Sprite*> listOfSprites;
};

#endif // EFFECT_H
