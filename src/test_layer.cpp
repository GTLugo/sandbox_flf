//
// Created by galex on 2/17/2022.
//
#include "test_layer.hpp"

namespace sbx {
  bool TestLayer::onRenderEvent(ff::RenderEvent& e) {
    switch (e.action()) {
      case ff::RenderEvent::Start: {
        vao_ = ff::VertexArray::create(
          // Vertices
          {
            -.5f, -.5f,  0.f, /**/.7f, .1f, .1f, 1.f,
             .5f, -.5f,  0.f, /**/.1f, .7f, .1f, 1.f,
             0.f,  .5f,  0.f, /**/.1f, .1f, .7f, 1.f
          },
          // Layout
          {
            ff::BufferElement::create<ff::vec3>("pos"),
            ff::BufferElement::create<ff::vec4>("color"),
          },
          // Indices
            {0, 1, 2}
        );

        background_ = ff::VertexArray::create(
          // Vertices
          {
            -1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
             1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
             1.f,  1.f, .1f, /**/ .7, .6, .6, 1.,
            -1.f,  1.f, .1f, /**/ .7, .6, .6, 1.
          },
          // Layout
          {
            ff::BufferElement::create<ff::vec3>("pos"),
            ff::BufferElement::create<ff::vec4>("color"),
          },
          // Indices
            {0, 1, 2, 2, 3, 0}
        );

        shader_ = ff::Shader::create("res/flugel/shaders/simple_shader.glsl");

        return false;
      }
      case ff::RenderEvent::AppStep: {
        shader_->bind();
        ff::Renderer::submit(background_);
        ff::Renderer::submit(vao_);
        shader_->unbind();

        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool TestLayer::onLogicEvent(ff::LogicEvent& e) {
//      switch (e.type()) {
//        case ff::LogicEventType::Tick: {
//          if (Input::isPressed(Key::Space)) {
//            FGE_TRACE("{}", (Input::isPressed(Modifier::Shift|Modifier::Control)) ? "OwO" : "UwU");
//          }
//        }
//        default: break;
//      }
    return false;
  }

  bool TestLayer::onKeyboardEvent(ff::KeyboardEvent& e) {
    ff::Log::debug("{}: {}", name_, e);
    return false;
  }

  bool TestLayer::onMouseEvent(ff::MouseEvent& e) {
    ff::Log::debug("{}: {}", name_, e);
    return false;
  }

  bool TestLayer::onScrollEvent(ff::ScrollEvent& e) {
    ff::Log::debug("{}: {}", name_, e);
    return false;
  }
}
