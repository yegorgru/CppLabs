#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;
/// <summary>
///  The base Component class. Declares main operations for either simple or complex objects of class.
/// </summary>

class Component {

 protected:
  Component *parent_;
private:

 public:


  virtual ~Component() {}
  void SetParent(Component *parent) {
    this->parent_ = parent;
  }
  Component *GetParent() const {
    return this->parent_;
  }
    /// <summary>
    /// Method for adding the component;
    /// </summary
  virtual void Add(Component *component) {}
  /// <summary>
  /// Method for removing the component;
  /// </summary>
  virtual void Remove(Component *component) {}
  /// <summary>
  /// Method for checking if a structure is able to have components;
  /// </summary>
  /// <returns>
  /// False if can't have components. True if can have components
  /// </returns>
  virtual bool IsComposite() const {
    return false;
  }

  virtual std::string Operation() const = 0;
};
/// <summary>
/// The derived class of the Component class. It contains the structures, which can't have components.
/// </summary>
/// <remark>
/// Just like leaves in the tree structure.
/// </remark>
class Leaf : public Component {


 public:

    /// <summary>
    /// Method for performing an operation;
    /// </summary>
    /// <returns>
    /// Value of an argument
    /// </returns>
  std::string Operation() const override {
    return "Argument";
  }
};
/// <summary>
/// The derived class of the Component class. It contains complex structures, which can have nested components.
/// </summary>
class Composite : public Component {

 protected:
  std::list<Component *> children_;

 public:
  /// <summary>
  /// Object of container can add components to its structures.
  /// </summary>
  void Add(Component *component) override {
    this->children_.push_back(component);
    component->SetParent(this);
  }
  /// <summary>
  /// Object of container can remove components from its structures.
  /// </summary>
  void Remove(Component *component) override {
    children_.remove(component);
    component->SetParent(nullptr);
  }
  /// <summary>
  /// Method that checks if out structure can contain components.
  /// </summary>
  /// <returns>
  /// True if can have components. False if not.
  /// </returns>
  bool IsComposite() const override {
    return true;
  }
///<summary>
/// Method which recursively traverse through the tree. It collects and sums up the results of all the children.
/// </summary>
/// <returns>
/// The result of our recursive traverse.
/// </returns>
  std::string Operation() const override {
    std::string result;
    for (const Component *c : children_) {
      if (c == children_.back()) {
        result += c->Operation();
      } else {
        result += c->Operation() + "+";
      }
    }
    return "Loop(" + result + ")";
  }
};
///<summary>
/// Method which works with simple structures
/// </summary>
/// <remark>
/// For example: Argument or Loop(Loop(Argument+Argument) + Loop(Argument)).
/// </remark>
/// <returns>
/// The result string.
/// </returns>
string Simple_tree(Component *component) {
    string result;
 // std::cout << "RESULT: " << component->Operation();
return  result = component->Operation();
}

/// <summary>
/// Method which works with complex structures
/// </summary>
/// <remark>
/// For example:Complex_tree(tree,leaf) =  Argument + Loop(Loop(Argument+Argument) + Loop(Argument)) =Loop(Loop(Argument+Argument) + Loop(Argument)+ Argument)  .
/// </remark>
/// <returns>
/// The result string of a complex structure
/// </returns>
string Complex_tree(Component *component1, Component *component2) {
string result;
  if (component1->IsComposite()) {
    component1->Add(component2);
  }
  //std::cout << "RESULT: " << component1->Operation();
    return result = component1->Operation();
}

#endif // PARSER_H
