//
// Created by galex on 4/2/2022.
//

#include "test_world.hpp"

namespace sbx {
  bool TestWorld::onGameEvent(const ff::GameEvent& e) {
    return FF_EVENT_HANDLERS(e,
        [=](const ff::GameAwakeEvent&) {
          simpleShader_ = ff::Shader::create("res/flugel/shaders/simple_shader");
          return false;
        },
        [=](const ff::GameStartEvent&) {
          // Set up entities
          ff::Log::debug("background: {}", background_.id());
          background_.add<ff::Name>("background")
              .add<ff::Transform>()
              .add<ff::Mesh>(ff::MeshData{
                    .vertices = {{-1.f, -1.f, .1f}, {1.f, -1.f, .1f}, {1.f, 1.f, .1f}, {-1.f, 1.f, .1f}},
                    .indices = {0, 1, 2, 2, 3, 0},
                  }, ff::Material{simpleShader_, ff::vec4{.6, .6, .7, 1.}});
          ff::Log::debug("test_entity: {}", testEntity_.id());
          testEntity_.add<ff::Name>("test_entity")
              .add<ff::Transform>()
              .add<ff::Mesh>(ff::MeshData{
                  .vertices = {{-.5f, -.5f, 0.f}, {.5f, -.5f, 0.f}, {0.f, .5f, 0.f}},
                  .indices = {0, 1, 2},
                  .colors = {{{.7f, .1f, .1f, 1.f}, {.1f, .7f, .1f, 1.f}, {.1f, .1f, .7f, 1.f}}},
              }, ff::Material{simpleShader_});

          ff::Entity tempEntity{ecs()};
          tempEntity.add<ff::Name>("temp_entity")
              .add<ff::Transform>()
              .add<ff::Mesh>(ff::MeshData{
                  .vertices = {{-.5f, -.5f, 0.f}, {.5f, -.5f, 0.f}, {0.f, .5f, 0.f}},
                  .indices = {0, 1, 2},
              }, ff::Material{simpleShader_});
          tempEntity.kill();
          return false;
        },
        [=](const ff::GameStopEvent&) {
          testEntity_.kill();
          background_.kill();

          return false;
        },
        [](const auto&) { return false; }
    );
  }

  bool TestWorld::onInputEvent(const ff::InputEvent& e) {
    return FF_EVENT_HANDLERS(e,
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
      [](const auto&) { return false; }
    );
  }
}