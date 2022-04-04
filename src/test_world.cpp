//
// Created by galex on 4/2/2022.
//

#include "test_world.hpp"

namespace sbx {
  bool TestWorld::onLogicEvent(const ff::LogicEvent& e) {
    switch (e.action()) {
      case ff::LogicEvent::Start: {
        // Set up entities
        ff::Log::debug("background: {}", background_.id());
        background_.add<ff::Name>("background")
            .add<ff::Transform>()
            .add<ff::Mesh>();
        ff::Log::debug("test_entity: {}", testEntity_.id());
        testEntity_.add<ff::Name>("test_entity")
            .add<ff::Transform>()
            .add<ff::Mesh>();

        break;
      }
      case ff::LogicEvent::Stop: {
        testEntity_.kill();
        background_.kill();

        break;
      }
      default: break;
    }
    return false;
  }

  bool TestWorld::onRenderEvent(const ff::RenderEvent& e) {
    switch (e.action()) {
      case ff::RenderEvent::Start: {
//        std::vector<ff::Vertex> v{
//            {.pos = {0.f, 0.f, 0.f}, .color = {0.f, 0.f, 0.f, 1.f}},
//            {.pos = {0.f, 0.f, 0.f}, .color = {0.f, 0.f, 0.f, 1.f}},
//            {.pos = {0.f, 0.f, 0.f}, .color = {0.f, 0.f, 0.f, 1.f}},
//        };

        testEntity_.set<ff::Mesh>(
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

        background_.set<ff::Mesh>(
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

        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool TestWorld::onKeyboardEvent(const ff::KeyboardEvent& e) {
    ff::Log::debug("{}", e);
    return false;
  }

  bool TestWorld::onMouseEvent(const ff::MouseEvent& e) {
    ff::Log::debug("{}", e);
    return false;
  }

  bool TestWorld::onScrollEvent(const ff::ScrollEvent& e) {
    ff::Log::debug("{}", e);
    return false;
  }
}