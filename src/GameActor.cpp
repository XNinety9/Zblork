#include "include/GameActor.h"

GameActor::GameActor(float x, float y)
    : x_(x), y_(y), vx_(0.0f), vy_(0.0f)
{

}

float GameActor::getX() const{
    return x_;

}

void GameActor::setX(float x){
    x_ = x;
}

float GameActor::getY() const{
    return y_;
}

void GameActor::setY(float y){
    y_ = y;
}

float GameActor::getVelocityX() const{
    return vx_;
}

void GameActor::setVelocityX(float vx){
    vx_ = vx;
}

float GameActor::getVelocityY() const{
    return vy_;

}

void GameActor::setVelocityY(float vy){
    vy_ = vy;
}
