//
// Created by Andy Wang on 3/7/22.
//

#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle()
    : position_(0, 0),
      velocity_(0, 0),
      radius_(1),
      color_(ci::Color("blue")) {}

Particle::Particle(const vec2& position, const vec2& velocity, float radius, const ci::Color& color)
    : position_(position),
      velocity_(velocity),
      radius_(radius),
      color_(color) {}

const vec2 &Particle::GetPosition() const {
  return position_;
}

const vec2 &Particle::GetVelocity() const {
  return velocity_;
}

float Particle::GetRadius() const {
  return radius_;
}

const cinder::Color &Particle::GetColor() const {
  return color_;
}

void Particle::SetPosition(const vec2 &position) {
  position_ = position;
}

void Particle::SetVelocity(const vec2 &velocity) {
  velocity_ = velocity;
}

void Particle::SetRadius(float radius) {
  radius_ = radius;
}

void Particle::SetColor(const cinder::Color &color) {
  color_ = color;
}

}