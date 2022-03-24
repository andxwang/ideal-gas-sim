#pragma once

#include "cinder/gl/gl.h"
#include "physics_handler.h"
#include "histogram.h"
#include <vector>

using glm::vec2;
using std::vector;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {

 public:
  /**
   * Constructor for a GasContainer object.
   * Initializes a PhysicsHandler with a passed in
   * number of particles and rectangle coordinates.
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  void DrawHistograms();

 private:

  const vec2 kRectTopLeft = vec2(500, 20);
  const vec2 kRectBottomRight = vec2(1180, 780);
  const int kNumParticles = 100;
  const int kNumHistograms = 3;
  const vector<std::pair<vec2, vec2>> kHistCoords =
      {{vec2(50, 20), vec2(400, 220)},
       {vec2(50, 270), vec2(400, 470)},
       {vec2(50, 520), vec2(400, 720)}};
  const vector<ci::Color> kHistColors = {ci::Color("cyan"),
                                         ci::Color("magenta"),
                                         ci::Color("yellow")};
  vector<Histogram> histograms_;
  PhysicsHandler handler_;
};

}  // namespace idealgas
