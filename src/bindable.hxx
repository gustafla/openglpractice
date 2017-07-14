#pragma once

class Bindable {
  public:
    virtual void bind() const = 0;
    virtual void unbind() const {};
};
