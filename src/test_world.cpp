//
// Created by galex on 4/2/2022.
//

#include "test_world.hpp"

#include "camera_system.hpp"

namespace sbx {
  bool TestWorld::onLogicEvent(const ff::LogicEvent& e) {
    switch (e.action()) {
      case ff::LogicEvent::Start: {
        ff::Log::debug("camera_: \"{}\"", camera_.id());
        ecs().registerSystem<CameraSystem>();
        camera_.addComponent<ff::Transform>({})
            .addComponent<ff::Camera>({-1.f, 1.f, -1.f, 1.f, -1.f, 1.f});

        ff::Entity testEntity{&ecs()};
        ff::Log::debug("testEntity: \"{}\"", testEntity.id());
        testEntity.addComponent<ff::Transform>({});
        auto& transform{testEntity.component<ff::Transform>()};

        // TODO: automate somehow. reference counting?
        ecs().removeEntity(testEntity);
        break;
      }
      case ff::LogicEvent::Tick: {
        if (Input::isPressed(Key::Space)) {
          ff::Log::debug("{}", (Input::isPressed(Modifier::Shift|Modifier::Control)) ? "OwO" : "UwU");
        }
        break;
      }
      case ff::LogicEvent::Stop: {
        // TODO: automate somehow. reference counting?
        ecs().removeEntity(camera_);
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
        shader_->pushMat4(camera_.component<ff::Camera>().viewProjMatrix(), "vpMatrix");
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