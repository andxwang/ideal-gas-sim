#include "gas_container.h"
#include <random>

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer() : handler_(kNumParticles,
                                        kRectTopLeft,
                                        kRectBottomRight) {}

void GasContainer::Display() const {
  // draw gas particle box
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kRectTopLeft, kRectBottomRight));

  // draw gas particles
  for (const Particle &particle : handler_.particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  // draw three histograms
  DrawHistograms();
  ci::gl::drawStringCentered("TEST", vec2(100, 50),
                             ci::Color("white"), ci::Font("arial", 20));
}

void GasContainer::AdvanceOneFrame() {
  for (Particle &p : handler_.particles_) {
    p.SetPosition(p.GetPosition() + p.GetVelocity());
  }
  handler_.ProcessWallCollision();
  handler_.ProcessParticleCollision();
}

void GasContainer::DrawHistograms() const {
  vector<float> red_velocities, green_velocities, blue_velocities;
  for (const Particle &p : handler_.particles_) {
    if (p.GetColor() == ci::Color("red")) {
      red_velocities.push_back(glm::length(p.GetVelocity()));
    } else if (p.GetColor() == ci::Color("green")) {
      green_velocities.push_back(glm::length(p.GetVelocity()));
    } else if (p.GetColor() == ci::Color("blue")) {
      blue_velocities.push_back(glm::length(p.GetVelocity()));
    }
  }
  Histogram hist_red(kHistCoords[0], red_velocities, ci::Color("red"));
  Histogram hist_green(kHistCoords[1], green_velocities, ci::Color("green"));
  Histogram hist_blue(kHistCoords[2], blue_velocities, ci::Color("blue"));
  hist_red.Draw();
  hist_green.Draw();
  hist_blue.Draw();
}

}  // namespace idealgas
