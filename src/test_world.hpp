//
// Created by galex on 4/2/2022.
//

#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestWorld : public ff::World {
    using Input = ff::Input;
    using Key = ff::Key;
    using Modifier = ff::Modifier;
  public:
    explicit TestWorld(const std::string& name) : ff::World{name} {}

    //bool onMainEvent(const ff::MainEvent& e) override;
    bool onGameEvent(const ff::GameEvent& e) override;
    //bool onWindowEvent(const ff::WindowEvent& e) override;
    bool onInputEvent(const ff::InputEvent& e) override;
  private:
    ff::Entity background_{&ecs()};
    ff::Entity testEntity_{&ecs()};
  };
}

