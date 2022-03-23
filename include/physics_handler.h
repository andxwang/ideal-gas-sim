//
// Created by Andy Wang on 3/8/22.
//

#pragma once

#include "particle.h"
#include <vector>
#include <random>
#include <glm/glm.hpp>

using namespace glm;
using glm::vec2;
using std::vector;

#ifndef IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_
#define IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_

namespace idealgas {

class PhysicsHandler {

 public:

  PhysicsHandler(int num_particles, const vec2& top_left, const vec2& bottom_right);

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

 private:
  vec2 rect_top_left_;
  vec2 rect_bottom_right_;
//  const float kMinRadius = 1.0;
  const float kMaxRadius = 30.0;
  const float kMaxVelocity = 5.0;
//  const float kMinMass = 0.1;
//  const float kMaxMass = 10.0;
  const std::vector<float> masses = {1.0, 3.0, 5.0};
  const std::vector<float> radii = {10.0, 12.0, 15.0};
  std::random_device device;
  std::mt19937 generator;
  std::uniform_int_distribution<> random_x;
  std::uniform_int_distribution<> random_y;
//  std::uniform_real_distribution<> random_radius;
//  std::uniform_real_distribution<> random_mass;
  std::uniform_real_distribution<> random_vel;
  std::uniform_real_distribution<> color_picker;
//  std::uniform_real_distribution<> random_rgb;
  /**
   * Calculate the average of two RGB colors
   * by averaging each component.
   * @param color1 the first color
   * @param color2 the second color
   * @return the average color
   */
  ci::Color GetAvgColor(const ci::Color& color1, const ci::Color& color2);
};

} // namespace idealgas

#endif //IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_PHYSICS_HANDLER_H_
