#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include "include/Doritos.h"
#include <unistd.h>
#include <iostream>
#include "include/Constants.h"
#include "include/utils.h"
#include <cmath>



Doritos::Doritos( float x, float y)
    : GameActor(x, y), bigger_(0.f)
{

}

void Doritos::moveX(float dx){
    setX(getX()+ dx);
}

void Doritos::moveY(float dy){
    setY(getY()+ dy);
}

float Doritos::get_bigger(){
    return bigger_;
}

void Doritos::set_bigger(float val){
    bigger_ = val;
}

void Doritos::update(sf::RenderWindow& window, sf::Sound& sound, float dt){

        sf::Vector2u windowSize = window.getSize();
        float window_size_x = static_cast<float>(windowSize.x);
        float window_size_y = static_cast<float>(windowSize.y);

        float velocity_treshold = dt * GRAVITY;

        // TBH, idc
        float triangle_height = 100;

        // stop condition
        if (getVelocityY() <= velocity_treshold && getY() >= window_size_y - triangle_height -1 )
            return;

        if (getY() >= window_size_y - triangle_height ) {
            setY(window_size_y - triangle_height);

            // Bounces
            if(getVelocityY() > 1 ){
                setVelocityY(-getVelocityY() * 0.70 );
                sound.play();
            }
            
            // Stop condition
            else if (abs(getVelocityY()) <= velocity_treshold){ 
                if (getVelocityY() != 0.f){
                    setVelocityY(0.f);
                    sound.play();
                    return;
                }
            }
        }
        
        setVelocityY( getVelocityY() + dt * GRAVITY);

        float dy = getVelocityY() * dt;
        float dx = getVelocityX() * dt;

        moveX(dx);
        moveY(dy);
}

void Doritos::handle_events(sf::RenderWindow& window, sf::Sound& proutSound){

    float x1 = window.getSize().x - getX();
    float y1 = window.getSize().y - getY();
    float maxDistance = std::sqrt(x1 * x1 + y1 * y1);
    float yPosition = getY();

    for (auto event = sf::Event{}; window.pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                float x1 = event.mouseButton.x - getX();
                float y1 = event.mouseButton.y - getY();
                float distance = std::sqrt(x1 * x1 + y1 * y1);
                float gradientValue = 1.5f - 1.5f * (distance / maxDistance);
                proutSound.setPitch(gradientValue);
                std::cout << "Pitch @(x=" << event.mouseButton.x << ", y=" << event.mouseButton.y << "): " << gradientValue << std::endl;
                set_bigger(get_bigger() + 25 * (1 + gradientValue));
                proutSound.play();
            }
        }
    }
}

void Doritos::display(sf::RenderWindow& window){

        // Get the size of the window
        sf::Vector2u windowSize = window.getSize();
        int counter = FRAMERATE;
        float colors[9];
        for(int i = 0; i < 9; i++)
        {
            colors[i] = getRandomValue();
        }
            
        // Calculate the center of the window
        float centerX = getX();
        float centerY = getY();
        float x1 = windowSize.x - centerX;
        float y1 = windowSize.y - centerY;
        float maxDistance = std::sqrt(x1 * x1 + y1 * y1);

        float scaling = get_bigger() + 100.f;
        set_bigger(get_bigger()*0.9);

        counter++;
        if (counter >= FRAMERATE / 6)
        {
            counter = 0;
            for(int i = 0; i < 9; i++)
            {
                colors[i] = (colors[i] + getRandomValue())/2.0f;
            }
        }
        
        // Save the OpenGL states
        window.pushGLStates();

        // Draw with OpenGL
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, windowSize.x, windowSize.y, 0, -1, 1);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set polygon mode to filled

        glBegin(GL_TRIANGLES);
        glColor3f(colors[0], colors[1], colors[2]);
        glVertex2f(centerX, centerY - scaling);
        glColor3f(colors[3], colors[4], colors[5]);
        glVertex2f(centerX - scaling, centerY + scaling);
        glColor3f(colors[6], colors[7], colors[8]);
        glVertex2f(centerX + scaling, centerY + scaling);
        glEnd();

        // Restore the OpenGL states
        window.popGLStates();
}


void Doritos::jump(){
    setVelocityY(40.f);
}

