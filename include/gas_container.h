#pragma once

#include "cinder/gl/gl.h"
#include "physics_handler.h"
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
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:

  const vec2 kRectTopLeft = vec2(100, 100);
  const vec2 kRectBottomRight = vec2(800, 800);
  const int kNumParticles = 10;

  PhysicsHandler handler_;

};

}  // namespace idealgas
