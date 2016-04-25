/*
 * DECORATOR
 *  The decorator can be used to extend(decorate) the functionality of an object. The
 *    decorator wraps the original class. 
 *  1. Subclass the original "Component" class into a Decorator class
 *  2. In the Decorator class, add a component pointer as a field
 *  3. Pass a Component to the Decorator constructor to initialize the Component pointer
 *  4. In the Decorator class, forward all "Component" methods to the "Component" pointer
 *  5. In the ConcreteDecoratorClass, override any Component method(s) whose behavior needs
 *     to be modified.
 *  Since the decorator is itself subclass component, decorator's can stack. Essentially wrapping
 *    each decorator around the preceding decorator. Useful when subclassing is impractical(of 
 *    concrete component classes). Instead each decorator add's a piece of functionality that
 *    can be added to any componenet and stacked. A transparent enclosure.
 *  Con; lots of little objects
 *    a decorator and it's component aren't identical from an object identity point of view.
 */

 #include <iostream>
using namespace std;

// Component
class Widget {
public:
  virtual void draw() = 0;
};

// Concrete Component
class TextField: public Widget {
  int width, height;
public:
  TextField(int w, int h) {
    width = w;
    height = h;
  }

  /* virtual */
  void draw() {
    cout << "TextField: " << width << ", " << height << '\n';
  }
};

// Decorator
class Decorator: public Widget {
  Widget *wid;
public:
  Decorator(Widget *w) {
    wid = w;
  }

  /* virtual */
  void draw() {
    wid->draw();
  }
};

// Concrete Decorator
class BorderDecorator: public Decorator {
public:
  BorderDecorator(Widget *w): Decorator(w) {}

  /* virtual */
  void draw() {
    // call to super draw method
    Decorator::draw();
    cout << " BorderDecorator" << '\n';
  }
};

class ScrollDecorator: public Decorator {
public:
  ScrollDecorator(Widget *w): Decorator(w) {}

  /* virtual */
  void draw() {
    Decorator::draw();
    cout << " ScrollDecorator" << '\n';
  }
};

int main() {
  Widget *aWidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(80,24))));

  aWidget->draw();
}