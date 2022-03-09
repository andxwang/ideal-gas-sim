//
// Created by Andy Wang on 3/8/22.
//

#pragma once

#include "particle.h"
#include <vector>
#include <glm/glm.hpp>

using namespace glm;
using glm::vec2;
using std::vector;

#ifndef IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_
#define IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_

namespace idealgas {

class PhysicsHandler {

 public:

  PhysicsHandler(int num_particles, vec2 top_left, vec2 bottom_right);

  /**
   * Updates the velocity of two particles_ that Collide.
   * @param first the first Particle
   * @param second the second Particle
   */
  void Collide(Particle &first, Particle &second);

  /**
   * Changes velocity of particle that hits a vertical wall,
   * so that the x-component is negated.
   * @param particle the particle that hit the wall
   */
  void HitVerticalWall(Particle &particle);

  /**
   * Changes velocity of particle that hits a horizontal wall,
   * so that the y-component is negated.
   * @param particle the particle that hit the wall
   */
  void HitHorizontalWall(Particle &particle);

  /**
   * Check if there are particle collisions, and handle them by calling Collide.
   * Will run in O(n^2) time.
   */
  void ProcessParticleCollision();

  /**
   * Check if there are any particle collisions with walls,
   * and handle them by calling HitVerticalWall or HitHorizontalWall.
   */
  void ProcessWallCollision();

  vector<Particle> particles_;
  vec2 rect_top_left_;
  vec2 rect_bottom_right_;

};

} // namespace idealgas

#endif //IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_
