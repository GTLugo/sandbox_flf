#include "flugel.hpp"
#include "entry_point.hpp"

#include "test_world.hpp"

namespace sbx {
  class Sandbox final : public ff::App {
    public:
      Sandbox()
        : ff::App{{
          .title       = "SANDBOX", // title
          .width       = 800,       // width
          .height      = 450,       // height
          .renderApi   = ff::Renderer::API::OpenGL,
        }} {
        ff::Log::trace("Constructing sandbox...");
        insertWorld(masterWorld_);
        setActiveWorld(masterWorld_);
      }

      ~Sandbox() final {
        ff::Log::trace("Destructing sandbox...");
      };

  private:
    ff::Shared<ff::World> masterWorld_{ff::makeShared<TestWorld>("master")};
  };
}

namespace ff {
  Unique<App> createApp() {
    return std::move(makeUnique<sbx::Sandbox>());
  }
}