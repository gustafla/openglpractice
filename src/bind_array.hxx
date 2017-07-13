#pragma once

#include "window.hxx"
#include "bindable.hxx"
#include <vector>
#include <memory>

class BindArray: public Bindable {
  public:
    BindArray();
    void bind();
    void unbind();
    void recordBind(Bindable &bind);

  private:
    std::vector<std::shared_ptr<Bindable>> binds;
};
