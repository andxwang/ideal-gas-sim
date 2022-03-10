#include "gas_container.h"
#include <random>

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer() : handler_(kNumParticles,
                                        kRectTopLeft,
                                        kRectBottomRight) {}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kRectTopLeft, kRectBottomRight));

  for (const Particle &particle : handler_.particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  for (Particle &p : handler_.particles_) {
    p.SetPosition(p.GetPosition() + p.GetVelocity());
    // I tried to make a Move() function in the Particle class and PhysicsHandler class,
    // but for some reason, even though the code is the exact same,
    // it doesn't properly move and results in a blank screen.
    // I tried almost everything and nothing worked.
    // So I had to manually set the position of the particle.
  }
  handler_.ProcessWallCollision();
  handler_.ProcessParticleCollision();
}

}  // namespace idealgas
