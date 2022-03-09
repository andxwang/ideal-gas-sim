//
// Created by Andy Wang on 3/8/22.
//

#include "physics_handler.h"

namespace idealgas {

PhysicsHandler::PhysicsHandler(int num_particles, vec2 top_left, vec2 bottom_right) {
  particles_ = vector<Particle> (num_particles);
}

void PhysicsHandler::Collide(Particle &first, Particle &second) {
  vec2 vel1_old = first.getVelocity();
  vec2 pos1_old = first.getPosition();
  vec2 vel2_old = second.getVelocity();
  vec2 pos2_old = second.getPosition();
  vec2 v1_new = vel1_old - (float) (glm::dot((vel1_old - vel2_old), (pos1_old - pos2_old)) /
      pow(glm::length(pos1_old - pos2_old), 2)) *
          (pos1_old - pos2_old);
  vec2 v2_new = vel2_old - (float) (glm::dot((vel2_old - vel1_old), (pos2_old - pos1_old)) /
      pow(glm::length(pos2_old - pos1_old), 2)) *
          (pos2_old - pos1_old);
  first.setVelocity(v1_new);
  second.setVelocity(v2_new);
}

void PhysicsHandler::HitVerticalWall(Particle &particle) {
  vec2 velocity = particle.getVelocity();
  velocity.x = -1 * velocity.x;
  particle.setVelocity(velocity);
}

void PhysicsHandler::HitHorizontalWall(Particle &particle) {
  vec2 velocity = particle.getVelocity();
  velocity.y = -1 * velocity.y;
  particle.setVelocity(velocity);
}

void PhysicsHandler::ProcessParticleCollision() {
  for (size_t outer = 0; outer < particles_.size(); outer++) {
    for (size_t inner = 0; inner < particles_.size(); inner++) {
      if (outer == inner) continue; // particle can't collide with itself
      vec2 outer_pos = particles_[outer].getPosition();
      vec2 outer_vel = particles_[outer].getVelocity();
      int outer_radius = particles_[outer].getRadius();
      vec2 inner_pos = particles_[inner].getPosition();
      vec2 inner_vel = particles_[inner].getVelocity();
      int inner_radius = particles_[inner].getRadius();

      // collision only executed if two particles are moving towards each other
      if (dot((outer_vel - inner_vel), (outer_pos - inner_pos)) < 0) {
        if (distance(outer_pos, inner_pos) < (outer_radius + inner_radius)) {
          Collide(particles_[outer], particles_[inner]);
        }
      }
    }
  }
}

void PhysicsHandler::ProcessWallCollision() {
  for (Particle& particle : particles_) {
    // if the distance to the wall is less than the Particle's radius, call HitWall
    // check top & bottom wall, then left & right wall
    vec2 pos = particle.getPosition();
    if (distance(pos, vec2(pos.x, rect_top_left_.y)) < particle.getRadius() ||
    distance(pos, vec2(pos.x, rect_bottom_right_.y)) < particle.getRadius()) {
      HitHorizontalWall(particle);
    } else if (distance(pos, vec2(rect_top_left_.x, pos.y)) < particle.getRadius() ||
    distance(pos, vec2(rect_bottom_right_.x, pos.y)) < particle.getRadius()) {
      HitVerticalWall(particle);
    }
  }
}

}