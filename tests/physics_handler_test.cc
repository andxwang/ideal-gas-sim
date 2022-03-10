#include <catch2/catch.hpp>

#include <gas_container.h>

using namespace idealgas;

TEST_CASE("Invalid rectangle coordinates passed in") {
  REQUIRE_THROWS_AS(PhysicsHandler(2, vec2(100, 100), vec2(0, 0)),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(PhysicsHandler(2, vec2(100, 50), vec2(200, 50)),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(PhysicsHandler(2, vec2(200, 0), vec2(100, 100)),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(PhysicsHandler(2, vec2(50, 50), vec2(50, 50)),
                    std::invalid_argument);
}

TEST_CASE("No collision") {
  SECTION("No contact, moving away") {
    PhysicsHandler handler(2, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    Particle& p1 = handler.particles_[1];
    p0.SetPosition(vec2(4, 4));
    p0.SetVelocity(vec2(-1, 0));
    p0.SetRadius(1);
    p1.SetPosition(vec2(6, 6));
    p1.SetVelocity(vec2(1, 0));
    p1.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    p1.SetPosition(p1.GetPosition() + p1.GetVelocity());

    REQUIRE(p0.GetPosition() == vec2(3, 4));
    REQUIRE(p0.GetVelocity() == vec2(-1, 0));
    REQUIRE(p1.GetPosition() == vec2(7, 6));
    REQUIRE(p1.GetVelocity() == vec2(1, 0));
  }
  SECTION("Moving away from each other with overlap") {
    PhysicsHandler handler(2, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    Particle& p1 = handler.particles_[1];
    p0.SetPosition(vec2(4, 4));
    p0.SetVelocity(vec2(-0.1, 0));
    p0.SetRadius(2);
    p1.SetPosition(vec2(6, 4));
    p1.SetVelocity(vec2(0.1, 0));
    p1.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    p1.SetPosition(p1.GetPosition() + p1.GetVelocity());

    REQUIRE(p0.GetPosition() == vec2(3.9, 4));
    REQUIRE(p0.GetVelocity() == vec2(-0.1, 0));
    REQUIRE(p1.GetPosition() == vec2(6.1, 4));
    REQUIRE(p1.GetVelocity() == vec2(0.1, 0));
  }
}

TEST_CASE("Collision") {
  SECTION("Head on: velocities are exactly opposite") {
    PhysicsHandler handler(2, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    Particle& p1 = handler.particles_[1];
    p0.SetPosition(vec2(3.9, 5));
    p0.SetVelocity(vec2(1, 0));
    p0.SetRadius(1);
    p1.SetPosition(vec2(6.1, 5));
    p1.SetVelocity(vec2(-1, 0));
    p1.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    p1.SetPosition(p1.GetPosition() + p1.GetVelocity());
    handler.ProcessParticleCollision();

    REQUIRE(p0.GetVelocity() == vec2(-1, 0));
    REQUIRE(p1.GetVelocity() == vec2(1, 0));
  }

  SECTION("Offset collision 1") {
    PhysicsHandler handler(2, vec2(0, 0), vec2(100, 100));
    Particle& p0 = handler.particles_[0];
    Particle& p1 = handler.particles_[1];
    p0.SetPosition(vec2(9.6, 14.9));
    p0.SetVelocity(vec2(0.4, 0.1));
    p0.SetRadius(8);
    p1.SetPosition(vec2(22.3, 20.5));
    p1.SetVelocity(vec2(-0.3, -0.5));
    p1.SetRadius(5);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    p1.SetPosition(p1.GetPosition() + p1.GetVelocity());
    handler.ProcessParticleCollision();

    REQUIRE(abs(p0.GetVelocity().x - -0.40947) < 0.01);
    REQUIRE(abs(p0.GetVelocity().y - -0.23728) < 0.01);
    REQUIRE(abs(p1.GetVelocity().x -  0.50947) < 0.01);
    REQUIRE(abs(p1.GetVelocity().y - -0.16272) < 0.01);
  }

  SECTION("Offset collision 2") {
    PhysicsHandler handler(2, vec2(0, 0), vec2(100, 100));
    Particle& p0 = handler.particles_[0];
    Particle& p1 = handler.particles_[1];
    p0.SetPosition(vec2(10, 34.5));
    p0.SetVelocity(vec2(2, -0.5));
    p0.SetRadius(8);
    p1.SetPosition(vec2(21.5, 48.2));
    p1.SetVelocity(vec2(-1.5, 0.8));
    p1.SetRadius(9);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    p1.SetPosition(p1.GetPosition() + p1.GetVelocity());
    handler.ProcessParticleCollision();

    REQUIRE(abs(p0.GetVelocity().x -  1.76471) < 0.01);
    REQUIRE(abs(p0.GetVelocity().y - -0.94118) < 0.01);
    REQUIRE(abs(p1.GetVelocity().x - -1.26471) < 0.01);
    REQUIRE(abs(p1.GetVelocity().y -  1.24118) < 0.01);
  }
}

TEST_CASE("Wall collision") {
  SECTION("North wall") {
    PhysicsHandler handler(1, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    p0.SetPosition(vec2(5, 1));
    p0.SetVelocity(vec2(0, -0.1));
    p0.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    handler.ProcessWallCollision();

    REQUIRE(p0.GetVelocity() == vec2(0, 0.1));
  }
  SECTION("South wall") {
    PhysicsHandler handler(1, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    p0.SetPosition(vec2(5, 9));
    p0.SetVelocity(vec2(0, 0.1));
    p0.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    handler.ProcessWallCollision();

    REQUIRE(p0.GetVelocity() == vec2(0, -0.1));
  }
  SECTION("West wall") {
    PhysicsHandler handler(1, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    p0.SetPosition(vec2(1, 5));
    p0.SetVelocity(vec2(-0.1, 0));
    p0.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    handler.ProcessWallCollision();

    REQUIRE(p0.GetVelocity() == vec2(0.1, 0));
  }
  SECTION("East wall") {
    PhysicsHandler handler(1, vec2(0, 0), vec2(10, 10));
    Particle& p0 = handler.particles_[0];
    p0.SetPosition(vec2(9, 5));
    p0.SetVelocity(vec2(0.1, 0));
    p0.SetRadius(1);

    p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
    handler.ProcessWallCollision();

    REQUIRE(p0.GetVelocity() == vec2(-0.1, 0));
  }
}

TEST_CASE("Fun: test color change when collide") {
  ci::Color color1(0.2, 0.7, 0.4);
  ci::Color color2(0.8, 0.3, 0.6);
  PhysicsHandler handler(2, vec2(0, 0), vec2(100, 100));
  Particle& p0 = handler.particles_[0];
  Particle& p1 = handler.particles_[1];
  p0.SetPosition(vec2(9.6, 14.9));
  p0.SetVelocity(vec2(0.4, 0.1));
  p0.SetRadius(8);
  p0.SetColor(color1);
  p1.SetPosition(vec2(22.3, 20.5));
  p1.SetVelocity(vec2(-0.3, -0.5));
  p1.SetRadius(5);
  p1.SetColor(color2);

  p0.SetPosition(p0.GetPosition() + p0.GetVelocity());
  p1.SetPosition(p1.GetPosition() + p1.GetVelocity());
  handler.ProcessParticleCollision();

  REQUIRE(p0.GetColor() == ci::Color(0.5, 0.5, 0.5));
}