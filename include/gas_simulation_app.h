#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  // Play around with these variables so that you can see the entire UI on your screen.
  const int kWindowWidth = 1200;
  const int kWindowHeight = 800;

 private:
  GasContainer container_;
};

}  // namespace idealgas
