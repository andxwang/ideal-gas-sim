//
// Created by Andy Wang on 3/7/22.
//

#pragma once

#include <glm/glm.hpp>
#include "cinder/Color.h"

using namespace glm;

namespace idealgas {

class Particle {

 public:
  Particle();
  Particle(const vec2& position, const vec2& velocity, float radius, const ci::Color& color);

  const vec2 &GetPosition() const;

  const vec2 &GetVelocity() const;

  float GetRadius() const;

  float GetMass() const;

  const cinder::Color &GetColor() const;

  void SetPosition(const vec2 &position);

  void SetVelocity(const vec2 &velocity);

  void SetRadius(float radius);

  void SetMass(float mass);

  void SetColor(const cinder::Color &color);

 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
  float mass_;
  ci::Color color_;
};

} // namespace idealgas