//
// Created by Andy Wang on 3/7/22.
//

#include <glm/vec2.hpp>
#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle() : position_(0, 0), velocity_(0, 0), radius_(1) {}

Particle::Particle(const vec2& position, const vec2& velocity, int radius)
    : position_(position), velocity_(velocity), radius_(radius) {
}

vec2 Particle::getPosition() const {
  return position_;
}

void Particle::setPosition(const vec2 &position) {
  position_ = position;
}

const vec2 &Particle::getVelocity() const {
  return velocity_;
}

void Particle::setVelocity(const vec2 &velocity) {
  velocity_ = velocity;
}

int Particle::getRadius() const {
  return radius_;
}

void Particle::setRadius(int radius) {
  radius_ = radius;
}

}