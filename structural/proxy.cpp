/*
 * PROXY
 *  Provide a surrogate or placeholder for another object to control access to it.
 *    Can be used to activate resource heavy objects later when they're actually needed.
 *    Can be used to control access to the original object.
 */

 class Person {
  String nameString;
  static string list[];
  static int next;

public:
  Person() {
    nameString = list[next++];
  }

  string name() {
    return nameString;
  }
 };

 string Person::list[] = { "Tom", "Dick", "Harry", "Bubba" };

 int Person::next = 0;

class PettyCashProtected {
  int balance;

public:
  PettyCashProtected() {
    balance = 500;
  }
  bool withdraw(int amount) {
    if(amount > balance) { return false; }
    balance -= amount;

    return true;
  }

  int getBalance() {
    return balance;
  }
};

class PettyCash {
  PettyCashProtected realThing;

public:
  bool withdraw(Person &p, int amount) {
    if(p.name() == "Tom" || p.name() == "Harry" || p.name() == "Bubba") {
      return realThing.withdraw(amount);
    } else {
      return false;
    }
  }
  int getBalance() {
    return realThing.getBalance();
  }
};

int main() {
  PettyCash pc;
  Person workers[4];
  // How come I've never seen this before?
  for(int i = 0, amount = 100; i < 4; i++, amount += 100) {
    if(!pc.withdraw(workers[i], amount)) {
      cout << "No money for " << workers[i].name() << '\n';
    } else {
      cout << amount << " dollars for " << workers[i].name() << '\n';
    }

    cout << "Remaining balance is " << pc.getBalance() << '\n';
  }
}