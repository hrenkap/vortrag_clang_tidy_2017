#include <cstddef>  // for NULL
#include <memory>   // for auto_ptr

class Base {
public:
  Base() = default;
  Base(int) {}
  virtual int method(int* val_ptr) const {
    return (val_ptr != nullptr ? *val_ptr : 0);
  }
};

class Derived : public Base {
public:
  int method(int* val_ptr) const override {
    return (val_ptr != nullptr ? *val_ptr : 1);
  }
};

int func()
{
  int iVal = 42;
  std::unique_ptr<Base>  base_hold(new Derived());

  return base_hold->method(&iVal);
}
