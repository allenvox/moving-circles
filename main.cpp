#include <iostream>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

float getRandomSpeed()
{
    return (rand() % 70) / 100.0;
}

int getMultiplier()
{
    int multiplier = rand() % 2;
    if (multiplier == 0)
    {
        multiplier = -1;
    }
    return multiplier;
}

class tPoint
{
public:
    float x() const { return _x; };
    void setX(const float &x) { _x = x; }

    float y() const { return _y; };
    void setY(const float &y) { _y = y; }

    float Vx() const { return _Vx; };
    void setVx(const float &Vx) { _Vx = Vx; }

    float Vy() const { return _Vy; }
    void setVy(const float &Vy) { _Vy = Vy; }

    void moveLinear();
    void moveRandomly();

private:
    float _x, _y, _Vx, _Vy;
};

void tPoint::moveLinear()
{
    int direction = rand() % 2;
    if (direction == 0)
    {
        setVx(0.f);
        setVy(getRandomSpeed());
    }
    else
    {
        setVx(getRandomSpeed());
        setVy(0.f);
    }
}

void tPoint::moveRandomly()
{
    int x_multiplier = getMultiplier(), y_multiplier = getMultiplier();
    setVx(x_multiplier * getRandomSpeed());
    setVy(y_multiplier * getRandomSpeed());
}

int main()
{
    const int flag = 1;

    srand(time(NULL));
    const int wWidth = 1280, wHeight = 720;
    const int quantity = 100;
    const int radius = 7.f;
    tPoint points[quantity];
    sf::CircleShape shapes[quantity];
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "oop-lab3");

    for (int i = 0; i < quantity; i++)
    {
        shapes[i].setRadius(radius);
        shapes[i].setFillColor(sf::Color(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100));
        shapes[i].setOrigin(radius / 2.0, radius / 2.0);
        points[i].setX(rand() % (wWidth - radius - 1) + radius);
        points[i].setY(rand() % (wHeight - radius - 1) + radius);
        if (flag == 0)
        {
            points[i].moveLinear();
        }
        else
        {
            points[i].moveRandomly();
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (int i = 0; i < quantity; i++)
        {
            points[i].setX(points[i].x() + points[i].Vx());
            points[i].setY(points[i].y() + points[i].Vy());
            if (points[i].x() < radius || wWidth - radius < points[i].x())
            {
                points[i].setVx(points[i].Vx() * -1);
            }
            if (points[i].y() < radius || wHeight - radius < points[i].y())
            {
                points[i].setVy(points[i].Vy() * -1);
            }
            shapes[i].setPosition(points[i].x(), points[i].y());
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < quantity; i++)
        {
            window.draw(shapes[i]);
        }
        window.display();
    }
    return 0;
}