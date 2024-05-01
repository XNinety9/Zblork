
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

class GameActor{        

    public:
        GameActor(float x, float y);

        virtual ~GameActor() {}
        
        virtual void display(sf::RenderWindow& window) = 0;
        virtual void jump() = 0;

        virtual void update(sf::RenderWindow& window, sf::Sound& sound, float dt) = 0; 
        virtual void handle_events(sf::RenderWindow& window, sf::Sound& sound) = 0; 
        virtual void moveX(float dx) = 0; 
        virtual void moveY(float dy) = 0; 

        float getX() const;
        void setX(float x);

        float getY() const;
        void setY(float y);

        float getVelocityX() const;
        void setVelocityX(float vx);

        float getVelocityY() const;
        void setVelocityY(float vy);


    private:
        float x_;
        float y_;

        float vx_;
        float vy_;

};