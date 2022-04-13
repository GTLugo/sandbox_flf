//
// Created by galex on 4/2/2022.
//

#include "test_world.hpp"

namespace sbx {
  bool TestWorld::onGameEvent(const ff::GameEvent& e) {
    return std::visit(ff::EventVisitor{
        [=](const ff::GameAwakeEvent&) {
          simpleShader_ = ff::Shader::create("res/flugel/shaders/simple_shader.glsl");
          return false;
        },
        [=](const ff::GameStartEvent&) {

          // Set up entities
          ff::Log::debug("background: {}", background_.id());
          background_.add<ff::Name>("background")
              .add<ff::Transform>()
              .add<ff::Mesh>(
                  ff::VertexArray::create(
                      { // Vertices
                          -1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
                          1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
                          1.f,  1.f, .1f, /**/ .7, .6, .6, 1.,
                          -1.f,  1.f, .1f, /**/ .7, .6, .6, 1.
                      },
                      { // Layout
                          ff::VertexAttribute<ff::vec3>{"pos"},
                          ff::VertexAttribute<ff::vec4>{"color"},
                      },
                      {0, 1, 2, 2, 3, 0}), // Indices
                  simpleShader_
              );
          ff::Log::debug("test_entity: {}", testEntity_.id());
          testEntity_.add<ff::Name>("test_entity")
              .add<ff::Transform>()
              .add<ff::Mesh>(
                  ff::VertexArray::create(
                      { // Vertices
                          -.5f, -.5f,  0.f, /**/.7f, .1f, .1f, 1.f,
                          .5f, -.5f,  0.f, /**/.1f, .7f, .1f, 1.f,
                          0.f,  .5f,  0.f, /**/.1f, .1f, .7f, 1.f
                      },
                      { // Layout
                          ff::VertexAttribute<ff::vec3>{"pos"},
                          ff::VertexAttribute<ff::vec4>{"color"},
                      },
                      {0, 1, 2}), // Indices
                  simpleShader_
              );

          ff::Entity tempEntity{ecs()};
          tempEntity.add<ff::Name>("temp_entity")
              .add<ff::Transform>()
              .add<ff::Mesh>(
                  ff::VertexArray::create(
                      { // Vertices
                          -.5f, -.5f,  0.f, /**/.7f, .1f, .1f, 1.f,
                          .5f, -.5f,  0.f, /**/.1f, .7f, .1f, 1.f,
                          0.f,  .5f,  0.f, /**/.1f, .1f, .7f, 1.f
                      },
                      { // Layout
                          ff::VertexAttribute<ff::vec3>{"pos"},
                          ff::VertexAttribute<ff::vec4>{"color"},
                      },
                      {0, 1, 2}), // Indices
                  simpleShader_
              );
          tempEntity.kill();
          return false;
        },
        [=](const ff::GameStopEvent&) {
          testEntity_.kill();
          background_.kill();

          return false;
        },
        [](const auto& event) { return false; }
    }, e);
  }

  bool TestWorld::onInputEvent(const ff::InputEvent& e) {
    return std::visit(ff::EventVisitor{
      [](const ff::InputKeyEvent& event) {
        ff::Log::debug("{}", event);
        return false;
      },
      [](const ff::InputMouseEvent& event) {
        ff::Log::debug("{}", event);
        return false;
      },
      [](const ff::InputScrollEvent& event) {
        ff::Log::debug("{}", event);
        return false;
      },
      [](const auto& event) { return false; }
    }, e);
  }
}