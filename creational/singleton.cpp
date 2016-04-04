/**
 *	SINGLETON
 *	 Application needs one, and only one, instance of an object. Additionally, lazy initialization
 *    and global access are necessary.
 *   Ensures a class has onl one instance.
 *
 *  Friendship:
 *    asymmentric - if number is a friend of octal, octal is not a friend of number
 *    intransitive - if there was a third class who was friends with a class that is friends with another.
 *      it is not shared.
 *    not inherited - frienship isn't passed along to the child.
 *    access due to friendship is inherited - can access friend superclass
 */
 #include <iostream>
 #include <string>
 #include <stdlib.h>
using namespace std;

class Number {
  public:
    // 2. Define a public static accessor function
    static Number *instance();
    static void setType(string t) {
      type = t;
      delete inst;
      inst = 0;
    }
    virtual void setValue(int in) {
      value = in;
    }
    virtual int getValue() {
      return value;
    }
  protected:
    int value;
    // 4. Define all ctors to be protected
    Number() {
      cout << ":ctor: ";
    }
  // 1. Define a private static attribute
  private:
    static string type;
    static Number *inst;
};

string Number::type = "decimal";
// inst initialized
Number *Number::inst = 0;

class Octal: public Number {
  // 6. Inheritance can be supported
  public:
    // a non-member function can access the private and protected members of a class if 
    //  it is declared a friend of that class.
    friend class Number;  // number can access Octal methods
    void setValue(int in) {
      char buf[10];
      sprintf(buf,"%o",in);
      sscanf(buf,"%d",&value);
    }
  protected:
    Octal(){}
};

Number *Number::instance() {
  if(!inst) {
    // 3. Do "lazy initialization" in the accessor function
    if(type == "octal") {
      inst = new Octal();
    } else {
      inst = new Number();
    }
  }
  return inst;
}

int main() {
  // Number myInstance; - error: cannot access protected constructor
  // 5. Clients may only use the accessor function to manipulate the Singleton
  Number::instance()->setValue(42);
  cout << "value is " << Number::instance()->getValue() << endl;
  Number::setType("octal");
  Number::instance()->setValue(64);
  cout << "value is " << Number::instance()->getValue() << endl;
}