#include "GameActor.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

class Doritos : public GameActor{
public:
    Doritos( float x, float y);

    void display(sf::RenderWindow& window);
    void jump(void);

    void update(sf::RenderWindow& window, sf::Sound& sound, float dt);
    void handle_events(sf::RenderWindow& window, sf::Sound& sound); 
    void moveX(float dx);
    void moveY(float dy); 
    float get_bigger();
    void set_bigger(float val);
private:
    float bigger_;
};