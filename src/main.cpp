#include <iostream>

using namespace std;

class A {
  public:

	void display() { cout << "display class A" << endl; }
};

class B {
  public:

  void virtual print() { cout << "print class B" << endl; }
};

class C : public B, public A{
  public:

  void virtual print() { cout << "print class C" << endl; }
};

int main() {
	C* c = new C();
  c->print();
  c->display();
}