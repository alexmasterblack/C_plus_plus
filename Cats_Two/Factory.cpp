#include <map>
#include <string>

class Object {
 public:
  virtual std::string ToString() const = 0;
  virtual ~Object() {}
};
class Smthg : public Object {
 public:
    explicit Smthg(const std::string& class_id) {
        this->class_id = class_id;
    }
    std::string ToString() const override {
        return class_id;
    }

 private:
    std::string class_id;
};
class Factory {
 public:
  std::map<std::string, std::function<Object*()>> elements;
  Factory() {
    elements["apple!"] = []() {
        return new Smthg("apple!");
    };
    elements["list"] = []() {
        return new Smthg("list");
    };
    elements["yet another identifier"] = []() {
      return new Smthg("yet another identifier");
    };
  }
  Object* Create(const std::string& class_id) {
      return elements[class_id]();
  }
  void Register(const std::string& class_id, Object* (*instance_creator)()) {
    elements[class_id] = instance_creator;
  }
};
