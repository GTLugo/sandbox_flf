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

    //bool onAppEvent(const ff::AppEvent& e) override;
    bool onLogicEvent(const ff::LogicEvent& e) override;
    bool onRenderEvent(const ff::RenderEvent& e) override;
    //bool onWindowEvent(const ff::WindowEvent& e) override;
    bool onKeyboardEvent(const ff::KeyboardEvent& e) override;
    bool onMouseEvent(const ff::MouseEvent& e) override;
    //bool onCursorEvent(const ff::CursorEvent& e) override;
    bool onScrollEvent(const ff::ScrollEvent& e) override;
  private:
    ff::Shared<ff::VertexArray> vao_;
    ff::Shared<ff::VertexArray> background_;
    ff::Shared<ff::Shader> shader_;

    ff::Entity camera_{&ecs()};
  };
}

