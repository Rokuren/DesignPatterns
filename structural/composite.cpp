/*
 * COMPOSITE
 *  1. Identify the scalar/primitive classes and vector/container classes
 *  2. Create an "interface" (lowest common denomiator) that can make all 
 *     concrete classes "interchangeable"
 *  3. All Concrete classes declare an "is a" relationship to the interface
 *  4. All "container" classes couple themselves to the interface (recursive
 *     composition, Composite "has a" set of children up the "is a " hierarchy)
 *  5. "Container" classes user polymorphism as they delegate to their children
 * PART-WHOLE
 *  Any object in a collection is a part of the whole composition. 
 *  IE, a directory. A directory is a composite of directories and files within
 *    and each object (dir/file) is a part of the whole (dir). 
 *  Directory is an example of a tree structure that represents part-whole hierarchies.
 *  (Leaf/Node); doesn't have to be uniform like dir->file
 */

#include <iostream>
#include <vector>

using namespace std;

// 2. Create an "interface" lowest common denominator
class Component {
public:
  virtual void traverse() = 0;
};

class Leaf: public Component {
  // 1. Scalar class    3. "is a" relationship
  int value;
public:
  Leaf(int val){
    value = val;
  }

  void traverse() {
    cout << value << ' ';
  }
};

class Composite: public Component {
  // 1. Vector class    3. "is a" relationship
  vector < Component *> children; // 4. "container" coupled to the interface
public:
  // 4. "container" class coupled to the interface
  voice add(Component *ele) {
    children.push_back(ele);
  }
  void traverse() {
    for(int i = 0; i < children.size(); i++) {
      // 5. Use polymorphism to delegate to children
      children[i]->traverse(); 
    }
  }
};

int main() {
  Composite containers[4];

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      containers[i].add(new Leaf(i * 3 + j));
    }
  }

  for(i = 1; i < 4; i++) {
    containers[0].add(&(containers[i]));
  }

  for(i = 0; i < 4; i++) {
    containers[i].traverse();
    cout << endl;
  }
}
