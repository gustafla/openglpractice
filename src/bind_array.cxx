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

void BindArray::recordBind(std::shared_ptr<Bindable> bindable) {
  binds.push_back(bindable);
}
