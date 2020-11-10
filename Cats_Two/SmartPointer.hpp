#pragma once

#include <memory>
#include "Test.hpp"

namespace smart_pointer {
// `exception` class definition
class exception : std::exception {
  using base_class = std::exception;
  using base_class::base_class;
};

// `SmartPointer` class declaration
template <typename T, typename Allocator>
class SmartPointer {
  // don't remove this macro
  ENABLE_CLASS_TESTS;

 public:
  using value_type = T;

  explicit SmartPointer(value_type* pointer = nullptr) {
    if (pointer != nullptr) {
      core = new Core(pointer);
    } else {
      core = nullptr;
    }
  }

  // copy constructor
  SmartPointer(const SmartPointer& other_pointer) {
    if (other_pointer.core != nullptr) {
      core = other_pointer.core;
      core->count += 1;
    } else {
      core = nullptr;
    }
  }

  // move constructor
  SmartPointer(SmartPointer&& other_pointer) {
    core = std::exchange(other_pointer.core, nullptr);
  }

  // copy assigment
  SmartPointer& operator=(const SmartPointer& other_pointer) {
    this->~SmartPointer();
    if (other_pointer.core != nullptr) {
      core = other_pointer.core;
      core->count += 1;
    } else {
      core = nullptr;
    }
    return *this;
  }

  // move assigment
  SmartPointer& operator=(SmartPointer&& other_pointer) {
    this->~SmartPointer();
    core = std::exchange(other_pointer.core, nullptr);
    return *this;
  }

  //
  SmartPointer& operator=(value_type* other_pointer) {
    this->~SmartPointer();
    if (other_pointer == nullptr) {
      core = nullptr;
    } else {
      core = new Core(other_pointer);
    }
    return *this;
  }

  ~SmartPointer() {
    if (core != nullptr) {
      core->count -= 1;
      if (core->count <= 0) {
        delete core;
      }
    }
  }

  // return reference to the object of class/type T
  // if SmartPointer contains nullptr throw `SmartPointer::exception`
  value_type& operator*() {
    if (core == nullptr) {
      throw smart_pointer::exception();
    } else {
      return *core->pointer;
    }
  }
  const value_type& operator*() const {
    if (core == nullptr) {
      throw smart_pointer::exception();
    } else {
      return *core->pointer;
    }
  }

  // return pointer to the object of class/type T
  value_type* operator->() const {
    if (core != nullptr) {
      return core->pointer;
    } else {
      return nullptr;
    }
  }

  value_type* get() const {
    if (core != nullptr) {
      return core->pointer;
    } else {
      return nullptr;
    }
  }

  // if pointer == nullptr => return false
  operator bool() const {
    if (core == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  // if pointers points to the same address or both null => true
  template <typename U, typename AnotherAllocator>
  bool operator==(
      const SmartPointer<U, AnotherAllocator>& other_pointer) const {
    if (this->get() == nullptr && other_pointer.get() == nullptr) {
      return true;
    }
    if (static_cast<void*>(this->get()) ==
        static_cast<void*>(other_pointer.get())) {
      return true;
    } else {
      return false;
    }
  }

  // if pointers points to the same address or both null => false
  template <typename U, typename AnotherAllocator>
  bool operator!=(
      const SmartPointer<U, AnotherAllocator>& other_pointer) const {
    if (this->get() == nullptr && other_pointer.get() == nullptr) {
      return false;
    }
    if (static_cast<void*>(this->get()) ==
        static_cast<void*>(other_pointer.get())) {
      return false;
    } else {
      return true;
    }
  }

  // if smart pointer contains non-nullptr => return count owners
  // if smart pointer contains nullptr => return 0
  std::size_t count_owners() const {
    if (core != nullptr) {
      return core->count;
    } else {
      return 0;
    }
  }

 private:
  class Core {
   public:
    explicit Core(value_type* pointer) {
      this->pointer = pointer;
      count = 1;
    }
    ~Core() { delete pointer; }
    value_type* pointer;
    int count;
  };
  Core* core;
};
}  // namespace smart_pointer
