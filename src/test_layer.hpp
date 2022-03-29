#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer final : public ff::Layer {
    using Input = ff::Input;
    using Key = ff::Key;
    using Modifier = ff::Modifier;
  public:
    TestLayer() : Layer{"test_layer"} {}

    bool onRenderEvent(const ff::RenderEvent& e) final;
    bool onLogicEvent(const ff::LogicEvent& e) final;
    bool onKeyboardEvent(const ff::KeyboardEvent& e) final;
    bool onMouseEvent(const ff::MouseEvent& e) final;
    bool onScrollEvent(const ff::ScrollEvent& e) final;

  private:
    ff::Shared<ff::VertexArray> vao_;
    ff::Shared<ff::VertexArray> background_;
    ff::Shared<ff::Shader> shader_;

    ff::Camera camera_{-1.f, 1.f, -1.f, 1.f, -1.f, 1.f};

    bool left_{false};
    ff::vec3 pos_{0, 0, 0};
  };
}