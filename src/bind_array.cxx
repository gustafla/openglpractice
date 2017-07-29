#include "bind_array.hxx"

void BindArray::bind() const {
  // Bind required buffers
  for (auto const &b: binds) {
    b->bind();
  }
}

void BindArray::unbind() const {
  for (auto const &b: binds) {
    b->unbind();
  }
}

void BindArray::recordBind(std::shared_ptr<Bindable const> bindable) {
  binds.push_back(bindable);
}
