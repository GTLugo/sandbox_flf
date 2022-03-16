#include "flugel.hpp"
#include "entry_point.hpp"

#include "test_layer.hpp"

namespace sbx {
  class Sandbox final : public ff::App {
    public:
      Sandbox()
        : ff::App{{
          .title       = "SANDBOX", // title
          .width       = 800, // width
          .height      = 450, // height
          .renderApi   = ff::Renderer::API::OpenGL,
          .customDecor = false
        }} {
        ff::Log::trace("Constructing sandbox...");
        pushLayer(new TestLayer{});
      }

      ~Sandbox() final {
        ff::Log::trace("Destructing sandbox...");
      };
  };
}

namespace ff {
  Unique<App> createApp() {
    return std::move(makeUnique<sbx::Sandbox>());
  }
}