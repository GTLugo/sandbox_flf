//
// Created by galex on 2/17/2022.
//
#include "test_layer.hpp"

namespace sbx {
  bool TestLayer::onRenderEvent(fge::RenderEvent& e) {
    switch (e.action()) {
      case fge::RenderEvent::Start: {
        vao_ = fge::VertexArray::create(
          // Vertices
          {
            -.5f, -.5f,  0.f, /**/.7f, .1f, .1f, 1.f,
             .5f, -.5f,  0.f, /**/.1f, .7f, .1f, 1.f,
             0.f,  .5f,  0.f, /**/.1f, .1f, .7f, 1.f
          },
          // Layout
          {
            fge::BufferElement::create<fge::vec3>("pos"),
            fge::BufferElement::create<fge::vec4>("color"),
          },
          // Indices
          {0, 1, 2}
        );

        background_ = fge::VertexArray::create(
          // Vertices
          {
            -1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
             1.f, -1.f, .1f, /**/ .1, .1, .1, 1.,
             1.f,  1.f, .1f, /**/ .7, .6, .6, 1.,
            -1.f,  1.f, .1f, /**/ .7, .6, .6, 1.
          },
          // Layout
          {
            fge::BufferElement::create<fge::vec3>("pos"),
            fge::BufferElement::create<fge::vec4>("color"),
          },
          // Indices
          {0, 1, 2, 2, 3, 0}
        );

        shader_ = fge::Shader::create("res/flugel/shaders/simple_shader.glsl");

        return false;
      }
      case fge::RenderEvent::AppStep: {
        shader_->bind();
        fge::Renderer::submit(background_);
        fge::Renderer::submit(vao_);
        shader_->unbind();

        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool TestLayer::onLogicEvent(fge::LogicEvent& e) {
//      switch (e.type()) {
//        case fge::LogicEventType::Tick: {
//          if (Input::isPressed(Key::Space)) {
//            FGE_TRACE("{}", (Input::isPressed(Modifier::Shift|Modifier::Control)) ? "OwO" : "UwU");
//          }
//        }
//        default: break;
//      }
    return false;
  }

  bool TestLayer::onKeyboardEvent(fge::KeyboardEvent& e) {
    FGE_DEBUG("{}: {}", name_, e);
    return false;
  }

  bool TestLayer::onMouseEvent(fge::MouseEvent& e) {
    FGE_DEBUG("{}: {}", name_, e);
    return false;
  }

  bool TestLayer::onScrollEvent(fge::ScrollEvent& e) {
    FGE_DEBUG("{}: {}", name_, e);
    return false;
  }
}
