#pragma once

#include "window.hxx"
#include "bindable.hxx"
#include <vector>
#include <memory>

class BindArray: public Bindable {
  public:
    void bind() const;
    void unbind() const;
    void recordBind(std::shared_ptr<Bindable const> bindable);

  private:
    std::vector<std::shared_ptr<Bindable const>> binds;
};
