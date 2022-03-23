//
// Created by Andy Wang on 3/8/22.
//

#include "physics_handler.h"

namespace idealgas {

PhysicsHandler::PhysicsHandler(int num_particles,
                               const vec2& top_left,
                               const vec2& bottom_right,
                               const vector<ci::Color>& colors) {
  if (top_left.x >= bottom_right.x || top_left.y >= bottom_right.y)
    throw std::invalid_argument("Invalid top left and bottom right coordinates!");
  rect_top_left_ = vec2(top_left);
  rect_bottom_right_ = vec2(bottom_right);
  particles_ = vector<Particle> (num_particles);

  generator = std::mt19937(device());
  random_x = std::uniform_int_distribution<> (rect_top_left_.x + kMaxRadius,
                                              rect_bottom_right_.x - kMaxRadius);
  random_y = std::uniform_int_distribution<> (rect_top_left_.y + kMaxRadius,
                                              rect_bottom_right_.y - kMaxRadius);
  random_vel = std::uniform_real_distribution<> (-kMaxVelocity, kMaxVelocity);
  color_picker = std::uniform_real_distribution<> (0.0, 1.0);

  for (Particle& particle : particles_) {
    particle.SetPosition(vec2(random_x(generator), random_y(generator)));
    particle.SetVelocity(vec2(random_vel(generator), random_vel(generator)));
    double color_rand = color_picker(generator);
    if (color_rand < 0.333) {
      particle.SetColor(ci::Color(colors[0]));
      particle.SetMass(masses[0]);
      particle.SetRadius(radii[0]);
    } else if (color_rand < 0.667) {
      particle.SetColor(ci::Color(colors[1]));
      particle.SetMass(masses[1]);
      particle.SetRadius(radii[1]);
    } else {
      particle.SetColor(ci::Color(colors[2]));
      particle.SetMass(masses[2]);
      particle.SetRadius(radii[2]);
    }
  }
}

void PhysicsHandler::Collide(Particle &first, Particle &second) {
  vec2 vel1_old = first.GetVelocity();
  vec2 pos1_old = first.GetPosition();
  vec2 vel2_old = second.GetVelocity();
  vec2 pos2_old = second.GetPosition();

  vec2 v1_new = vel1_old -
      (2 * second.GetMass()) / (first.GetMass() + second.GetMass()) *
      (float) (glm::dot((vel1_old - vel2_old), (pos1_old - pos2_old)) /
      pow(glm::length(pos1_old - pos2_old), 2)) *
      (pos1_old - pos2_old);
  vec2 v2_new = vel2_old -
      (2 * first.GetMass()) / (first.GetMass() + second.GetMass()) *
      (float) (glm::dot((vel2_old - vel1_old), (pos2_old - pos1_old)) /
      pow(glm::length(pos2_old - pos1_old), 2)) *
      (pos2_old - pos1_old);

  first.SetVelocity(v1_new);
  second.SetVelocity(v2_new);
}

void PhysicsHandler::HitVerticalWall(Particle &particle) {
  vec2 velocity = particle.GetVelocity();
  velocity.x = -1 * velocity.x;
  particle.SetVelocity(velocity);
}

void PhysicsHandler::HitHorizontalWall(Particle &particle) {
  vec2 velocity = particle.GetVelocity();
  velocity.y = -1 * velocity.y;
  particle.SetVelocity(velocity);
}

void PhysicsHandler::ProcessParticleCollision() {
  for (size_t outer = 0; outer < particles_.size(); outer++) {
    for (size_t inner = outer + 1; inner < particles_.size(); inner++) {
      vec2 outer_pos = particles_[outer].GetPosition();
      vec2 outer_vel = particles_[outer].GetVelocity();
      int outer_radius = particles_[outer].GetRadius();
      vec2 inner_pos = particles_[inner].GetPosition();
      vec2 inner_vel = particles_[inner].GetVelocity();
      int inner_radius = particles_[inner].GetRadius();

      // collision only executed if two particles are moving towards each other
      if (dot((outer_vel - inner_vel), (outer_pos - inner_pos)) < 0) {
        if (distance(outer_pos, inner_pos) <= (outer_radius + inner_radius)) {
          Collide(particles_[outer], particles_[inner]);
        }
      }
    }
  }
}

void PhysicsHandler::ProcessWallCollision() {
  for (Particle& particle : particles_) {
    // if the distance to the wall is less than the Particle's radius,
    // and the particle is moving towards the wall, call HitWall.
    // Check top & bottom wall, then left & right wall
    vec2 pos = particle.GetPosition();
    vec2 vel = particle.GetVelocity();
    if ((distance(pos, vec2(pos.x, rect_top_left_.y)) < particle.GetRadius() &&
    vel.y < 0) ||
    (distance(pos, vec2(pos.x, rect_bottom_right_.y)) < particle.GetRadius() &&
    vel.y > 0)) {
      HitHorizontalWall(particle);
    } else if ((distance(pos, vec2(rect_top_left_.x, pos.y)) < particle.GetRadius() &&
    vel.x < 0) ||
    (distance(pos, vec2(rect_bottom_right_.x, pos.y)) < particle.GetRadius() &&
    vel.x > 0)) {
      HitVerticalWall(particle);
    }
  }
}

ci::Color PhysicsHandler::GetAvgColor(const ci::Color& color1, const ci::Color& color2) {
  ci::Color result;
  result.r = (color1.r + color2.r) / 2;
  result.g = (color1.g + color2.g) / 2;
  result.b = (color1.b + color2.b) / 2;
  return result;
}

}