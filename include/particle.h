//
// Created by Andy Wang on 3/7/22.
//

#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace idealgas {

class Particle {

 public:
  Particle();
  Particle(const vec2& position, const vec2& velocity, int radius);

  vec2 getPosition() const;

  void setPosition(const vec2 &position);

  const vec2 &getVelocity() const;

  void setVelocity(const vec2 &velocity);

  int getRadius() const;

  void setRadius(int radius);

 private:
  vec2 position_;
  vec2 velocity_;
  int radius_;
};

} // namespace idealgas