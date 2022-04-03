//
// Created by galex on 4/3/2022.
//

#pragma once

#include "flugel.hpp"

namespace sbx {
  class CameraSystem : public ff::System<ff::Transform, ff::Camera> {
  public:
    void onUpdate() override {
      for (auto& [id, entity] : entities) {
        auto& transform{entity.component<ff::Transform>()};
        auto& camera{entity.component<ff::Camera>()};
        camera.viewMatrix = glm::inverse(transform.matrix());
      }
    }
  };
}
