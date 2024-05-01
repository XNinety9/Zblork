#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <limits.h>
#include <unistd.h>
#include <chrono>

#ifdef _WIN32
#include "include/WindowsFileSystem.h"
#else
#include "include/LinuxFileSystem.h"
#endif
#include <GL/gl.h>

#include "include/Doritos.h"
#include "include/utils.h"

#define FRAMERATE 144
#define GRAVITY 9.98

IFileSystem* createFileSystem() {
#ifdef _WIN32
    return new WindowsFileSystem();
#else
    return new LinuxFileSystem();
#endif
}

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project", sf::Style::Default};
    window.setFramerateLimit(FRAMERATE);

    IFileSystem* fs = createFileSystem();
    std::string currentDir = fs->getCurrentDirectory();

    // Load the sound file
    sf::SoundBuffer buffer;
    std::cout << "Current working directory: " << currentDir << std::endl;
    if (!buffer.loadFromFile("../assets/sound-asset.wav")) {
        std::cerr << "Failed to load sound file!" << std::endl;
        return 1;
    }

    // Get the size of the window
    sf::Vector2u windowSize = window.getSize();

    // Calculate the center of the window
    float centerX = static_cast<float>(windowSize.x) / 2.f;
    float centerY = static_cast<float>(windowSize.y) / 2.f;

    // Create a sound instance and set its buffer
    sf::Sound proutSound;
    proutSound.setBuffer(buffer);

    // Play the sound
    proutSound.play();

    Doritos doritos = Doritos(centerX, centerY);

    float dt = 1.f / FRAMERATE;


    while (window.isOpen())
    {
        // Todo: Faire une singleton de l'etat global du jeu plutot que de bourrer les parametres
        // Todo: Faire methode unique qui call les 3 methodes (handle_events, update et display)
        doritos.handle_events(window, proutSound);
        doritos.update(window, proutSound, dt);
        doritos.display(window);

        window.display();
        window.clear();
    }

    proutSound.stop();

    return 0;
}
    
// 8====D