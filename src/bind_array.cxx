#include "bind_array.hxx"

BindArray::BindArray() {
}

void BindArray::bind() {
  // Bind required buffers
  for (auto const &b: binds) {
    b->bind();
  }
}

void BindArray::unbind() {
  for (auto const &b: binds) {
    b->unbind();
  }
}

void BindArray::recordBind(Bindable &bind) {
  binds.push_back(std::shared_ptr<Bindable>(&bind));
}
