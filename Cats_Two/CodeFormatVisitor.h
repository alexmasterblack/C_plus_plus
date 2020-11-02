#include <vector>
#include <string>

class FormatVisitor : public BaseVisitor {
 public:
  void Visit(const BaseNode* node) override { node->Visit(this); }
  void Visit(const ClassDeclarationNode* node) override {
    format_code.push_back(space + "class " + node->ClassName() + " {");
    if (!node->PublicFields().empty()) {
      format_code.push_back(space + "  public:");
      space += "    ";
      for (auto i : node->PublicFields()) {
        Visit(i);
        format_code[format_code.size() - 1] += ";";
      }
      space.resize(space.size() - 4);
    }
    if (!node->ProtectedFields().empty()) {
      format_code.push_back("");
      format_code.push_back(space + "  protected:");
      space += "    ";
      for (auto i : node->ProtectedFields()) {
        Visit(i);
        format_code[format_code.size() - 1] += ";";
      }
      space.resize(space.size() - 4);
    }
    if (!node->PrivateFields().empty()) {
      format_code.push_back("");
      format_code.push_back(space + "  private:");
      space += "    ";
      for (auto i : node->PrivateFields()) {
        Visit(i);
        format_code[format_code.size() - 1] += ";";
      }
      space.resize(space.size() - 4);
    }
    format_code.push_back(space + "}");
    if (space == "") {
      format_code[format_code.size() - 1] += ";";
    }
  }
  void Visit(const VarDeclarationNode* node) override {
    format_code.push_back(space + node->TypeName() + " " + node->VarName());
  }
  void Visit(const MethodDeclarationNode* node) override {
    format_code.push_back(space + node->ReturnTypeName() + " " +
                          node->MethodName() + "(");
    int size = static_cast<int>(node->Arguments().size());
    for (int i = 0; i < size; i++) {
      Visit(node->Arguments()[i]);
      std::string arg =
          format_code[format_code.size() - 1].substr(space.size());
      if (i != size - 1) {
        format_code[format_code.size() - 2] += arg + ", ";
      } else {
        format_code[format_code.size() - 2] += arg;
      }
      format_code.pop_back();
    }
    format_code[format_code.size() - 1] += ")";
  }
  const std::vector<std::string>& GetFormattedCode() const {
    return format_code;
  }

 private:
  std::vector<std::string> format_code;
  std::string space = "";
};
