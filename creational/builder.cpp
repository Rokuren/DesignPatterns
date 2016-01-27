/*
 * builder.cpp
 * Builder: separate the construction of a complex object from its
 *  representation so that the same construction process can create 
 *  different representations.
 */
#include <iostream>
#include <stdio.h>
#include <string.h>

enum PersistenceType {
 File, Queue, Pathway
};

// Only difference between struct and class is default accessibility?
struct PersistenceAttribute {
 PersistenceType type;
 char value[30];
};

// Product - Complex object to be built
class DistrWorkPackage {
 public:
  DistrWorkPackage(char *type) {
   sprintf(_desc, "Distributed Work Package for: %s", type);
  }

  void setFile(char *f, char *v) {
   sprintf(_temp, "\n File(%s): %s", f, v);
   strcat(_desc, _temp);
  }

  void setQueue(char *q, char *v) {
   sprintf(_temp, "\n Queue(%s): %s", q, v);
   strcat(_desc, _temp);
  }
 
  void setPathway(char *p, char *v) {
   sprintf(_temp, "\n Pathway(%s): %s", p, v);
   strcat(_desc, _temp);
  }

  const char *getState() {
   return _desc;
  }

 private:
  char _desc[200], _temp[80];
};

// Builder - abstract interface
class Builder {
 public:
  // virtual is what indicates it can be overridden by a sub-class
  // Go4 book suggests methods shouldn't be pure virtual, but empty methods.
  //  this lets clients override only the operations they're interested in.
  // = 0; signifies pure virtual method. sourcemaking original
  //  used pure virtual methods.
  virtual void configureFile(char*) {};
  virtual void configureQueue(char*) {};
  virtual void configurePathway(char*) {};

  DistrWorkPackage *getResult() {
   return _result;
  }
 protected:
  DistrWorkPackage *_result;
};

// ConcreteBuilder - constructs and assembles parts of the product
class UnixBuilder: public Builder {
 public:
  UnixBuilder() {
   _result = new DistrWorkPackage((char *)"Unix");
  }
  // overwrite superclass methods
  void configureFile(char *name) {
   _result->setFile((char *)"flatFile", name);
  }

  void configureQueue(char *queue) {
   _result->setQueue((char *)"FIFO", queue);
  }

  void configurePathway(char *type) {
   _result->setPathway((char *)"thread", type);
  }
};

// ConcreteBuilder - constructs and assembles parts of the product
class VmsBuilder : public Builder {
 public:
  VmsBuilder() {
   _result = new DistrWorkPackage((char *)"vms");
  }
  // overwrite superclass methods
  void configureFile(char * name) {
   _result->setFile((char *)"ISAM", name);
  }

  void configureQueue(char *queue) {
   _result->setQueue((char *)"priority", queue);
  }

  void configurePathway(char *type) {
   // cast string to char* to avoid deprecated conversion warning
   _result->setPathway((char *)"LWP", type);
  }
};

// Director - constructs an object using the Builder interface
class Reader {
 public:
  void setBuilder(Builder *b) {
   _builder = b;
  }

  void construct(PersistenceAttribute[], int);

 private:
  Builder *_builder;
};
// std::allocator::construct
void Reader::construct(PersistenceAttribute list[], int num) {
 for(int i = 0; i < num; i++) {
  if(list[i].type == File) {
   _builder->configureFile(list[i].value);
  } else if(list[i].type == Queue) {
   _builder->configureQueue(list[i].value);
  } else if(list[i].type == Pathway) {
   _builder->configurePathway(list[i].value);
  }
 }
};

const int NUM_ENTRIES = 6;
// PersistenceAttribute = the struct of ENUM TYPE & char array
PersistenceAttribute input[NUM_ENTRIES] = {
 { File, "state.dat" },
 { File, "config.sys" },
 { Queue, "compute" },
 { Queue, "log" },
 { Pathway, "authentication" },
 { Pathway, "error processing" }
};

int main() {
 UnixBuilder unixBuilder;
 VmsBuilder vmsBuilder;
 Reader reader;
 // Reader: director
 reader.setBuilder(&unixBuilder);
 reader.construct(input, NUM_ENTRIES);
 std::cout << unixBuilder.getResult()->getState() << std::endl;
 
 reader.setBuilder(&vmsBuilder);
 reader.construct(input, NUM_ENTRIES);
 std::cout << vmsBuilder.getResult()->getState() << std::endl;
}
