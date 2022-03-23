#include "gas_container.h"
#include <random>

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer(): handler_(kNumParticles,
                                       kRectTopLeft,
                                       kRectBottomRight,
                                       kHistColors) {
  for (size_t i = 0; i < kNumHistograms; i++) {
    Histogram hist(kHistCoords[i], vector<float>(1, 0), kHistColors[i]);
    histograms_.push_back(hist);
  }
}

void GasContainer::Display() {
  // draw gas particle box
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kRectTopLeft, kRectBottomRight));
  // draw gas particles
  for (const Particle &particle : handler_.particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  // draw histograms
  DrawHistograms();
}

void GasContainer::AdvanceOneFrame() {
  for (Particle &p : handler_.particles_) {
    p.SetPosition(p.GetPosition() + p.GetVelocity());
  }
  handler_.ProcessWallCollision();
  handler_.ProcessParticleCollision();
}

void GasContainer::DrawHistograms() {
  vector<vector<float>> vec_of_velocities(kNumHistograms);
  for (size_t hist_idx = 0; hist_idx < kNumHistograms; hist_idx++) {
    ci::Color this_color = kHistColors.at(hist_idx);
    for (const Particle &p : handler_.particles_) {
      if (p.GetColor() == this_color) {
        vec_of_velocities.at(hist_idx).push_back(glm::length(p.GetVelocity()));
      }
    }
    histograms_.at(hist_idx).Update(vec_of_velocities[hist_idx]);
    histograms_.at(hist_idx).Draw();
  }
}

}  // namespace idealgas
