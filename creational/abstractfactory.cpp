/*
 * ABSTRACT FACTORY
 *  Provide an interface for creating families of related or dependent
 *  objects without specifying their concrete classes. 
 */

#include <iostream>
using namespace std;

// shape
class Shape {
  public:
    Shape() {
      id_ = total_++;
    }
    virtual void draw() = 0;
  protected:
    int id_;
    static int total_;
};
// :: is scope; initialize total_ to 0;
int Shape::total_ = 0;

// circle extends shape
class Circle : public Shape {
  public:
    void draw() {
      cout << "circle " << id_ << ": draw" << endl;
    }
};

// square extends shape
class Square : public Shape {
  public:
    void draw() {
      cout << "square " << id_ << ": draw" << endl;
    }
};

// ellipse extends shape
class Ellipse : public Shape {
  public:
    void draw() {
      cout << "ellipse " << id_ << ": draw" << endl;
    }
};

// rectangle extends shape
class Rectangle : public Shape {
  public:
    void draw() {
      cout << "rectangle " << id_ << ": draw" << endl;
    }
};

// factory
class Factory {
  // methods to be implemented by simple/robust factories
  public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

// simple shape factory.
class SimpleShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance() {
      return new Circle;
    }
    Shape* createStraightInstance() {
      return new Square;
    }
};
class RobustShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance()   {
      return new Ellipse;
    }
    Shape* createStraightInstance() {
      return new Rectangle;
    }
};

// define in command line -DSIMPLE or -DROBUST
int main() {
// Factory is it's own thing, implementation changes on setup
//  other examples could include ui based on version of windows.
//  or user specified themes.
#ifdef SIMPLE
  Factory* factory = new SimpleShapeFactory;
#elif ROBUST
  Factory* factory = new RobustShapeFactory;
#endif
  Shape* shapes[3];
  // dependent on factory initialization output is different
  // code doesn't know whether it's simple or robust; works all the same
  shapes[0] = factory->createCurvedInstance();   // shapes[0] = new Ellipse;
  shapes[1] = factory->createStraightInstance(); // shapes[1] = new Rectangle;
  shapes[2] = factory->createCurvedInstance();   // shapes[2] = new Ellipse;

  for (int i=0; i < 3; i++) {
    shapes[i]->draw();
  }
}
