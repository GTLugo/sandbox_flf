//
// Created by galex on 4/2/2022.
//

#include "test_world.hpp"

namespace sbx {
  bool TestWorld::onGameEvent(const ff::GameEvent& e) {
    switch (e.action()) {
      case ff::GameEvent::Start: {
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
                        ff::BufferElement::create<ff::vec3>("pos"),
                        ff::BufferElement::create<ff::vec4>("color"),
                    },
                    {0, 1, 2, 2, 3, 0}), // Indices
                ff::Shader::create("res/flugel/shaders/simple_shader.glsl")
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
                        ff::BufferElement::create<ff::vec3>("pos"),
                        ff::BufferElement::create<ff::vec4>("color"),
                    },
                    {0, 1, 2}), // Indices
                ff::Shader::create("res/flugel/shaders/simple_shader.glsl")
            );

        break;
      }
      case ff::GameEvent::Stop: {
        testEntity_.kill();
        background_.kill();

        break;
      }
      default: break;
    }
    return false;
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