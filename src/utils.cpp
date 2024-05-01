#include <random>

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