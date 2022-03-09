#include "gas_container.h"
#include <iostream>
#include <random>

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer() : handler_(2, rect_top_left, rect_bottom_right) {
//  particles_ = vector<Particle> (kNumParticles);
//  for (Particle& particle : particles_) {
//    std::cout << rand() % (int) (rect_bottom_right_.x - rect_top_left_.x) + rect_top_left_.x << std::endl;
//    particle.setPosition(vec2(rand() % (int) (rect_bottom_right_.x - rect_top_left_.x) + rect_top_left_.x,
//                              rand() % (int) (rect_bottom_right_.y - rect_top_left_.y) + rect_top_left_.y));
//    std::cout << particle.getPosition().x << ", " << particle.getPosition().y << std::endl;
//  }

}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidCircle(vec2(dummy_variable_, dummy_variable_), 10);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(rect_top_left, rect_bottom_right));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(1, 1), vec2(300, 50)));

  // TODO: for loop over a vector of Particles and drawSolidCircle for each particle
  ci::gl::color(ci::Color("blue"));
  for (const Particle &p : particles) {
    ci::gl::drawSolidCircle(p.getPosition(), 10);
  }

  ci::gl::color(ci::Color("red"));
  ci::gl::drawSolidCircle(vec2(300, 300), 20);
}

void GasContainer::AdvanceOneFrame() {
  ++dummy_variable_;
  // check to make sure no collisions with wall or other particles_
  // if particles_ are near each other, reverse direction/similar action
}

}  // namespace idealgas
