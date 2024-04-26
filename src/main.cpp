#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

#define FRAMERATE 144

// CIMER GPT
// Function to generate a random value between 0 and 1
float getRandomValue() {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define the range for the uniform distribution
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    // Generate a random value
    float randomValue = dist(gen);

    return randomValue;
}

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project", sf::Style::Default};
    window.setFramerateLimit(FRAMERATE);

    // Permission de changer ça lol, je faisais des tests c'est tout
    
    // Load the sound file
    sf::SoundBuffer buffer;
    char bufferD[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, bufferD);
    std::cout << "Current working directory: " << bufferD << std::endl;
    if (!buffer.loadFromFile("../../assets/sound-asset.wav")) {
        std::cerr << "Failed to load sound file!" << std::endl;
        return 1;
    }

    // Get the size of the window
    sf::Vector2u windowSize = window.getSize();
    float bigger = 0.0f;
    int counter = FRAMERATE;
    float colors[9];
    for(int i = 0; i < 9; i++)
    {
        colors[i] = getRandomValue();
    }
        
    // Calculate the center of the window
    float centerX = static_cast<float>(windowSize.x) / 2.f;
    float centerY = static_cast<float>(windowSize.y) / 2.f;
    float x1 = windowSize.x - centerX;
    float y1 = windowSize.y - centerY;
    float maxDistance = std::sqrt(x1 * x1 + y1 * y1);

    // Create a sound instance and set its buffer
    sf::Sound sound;
    sound.setBuffer(buffer);

    // Play the sound
    sound.play();

    while (window.isOpen())
    {
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
                    float x1 = event.mouseButton.x - centerX;
                    float y1 = event.mouseButton.y - centerY;
                    float distance = std::sqrt(x1 * x1 + y1 * y1);
                    float gradientValue = 1.5f - 1.5f * (distance / maxDistance);
                    sound.setPitch(gradientValue);
                    std::cout << "Pitch @(x=" << event.mouseButton.x << ", y=" << event.mouseButton.y << "): " << gradientValue << std::endl;
                    bigger += 25 * (1 + gradientValue);
                    sound.play();

                }
            }
        }
        window.clear();

        float scaling = bigger + 100.f;
        bigger *= 0.9;

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

        window.display();
    }

    sound.stop();

    return 0;
}
    
// 8====D