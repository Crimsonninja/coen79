#include "sequence.h"
#include <iostream>

using namespace std;
using namespace coen79_lab7;

int main(int argc, char const *argv[])
{
  coen79_lab7::sequence seq;
  seq.attach(5.0);
  seq.attach(3.4);
  seq.attach(1.3);
  seq.attach(2.5);
  seq.attach(0.9);
  seq.start();
  // cout << seq.size() << endl;
  // for (int i = 0; i < seq.size(); i++) {
    // std::cout << seq.current() << endl;
    // seq.advance();
  // }
  cout << seq.current() << endl;
  seq.advance();
  cout << seq.current() << endl;
  seq.remove_current();
  cout << seq.current() << endl;
  seq.advance();
  cout << seq.current() << endl;
  // seq.advance();
  // cout << seq.current() << endl;
  // seq.advance();
  // cout << seq.current() << endl;
  // seq.remove_current();
  // seq.end();
  // cout << seq.current() << endl;

  coen79_lab7::sequence seq2;
  seq2.insert(7.5);
  seq2.insert(1.6);
  seq2 = seq;
  seq2.start();
  cout << seq2.current() << endl;
  seq2.advance();
  cout << seq2.current() << endl;
  seq2.advance();
  cout << seq2.current() << endl;
  seq2.advance();
  cout << seq2.current() << endl;

  return 0;
}
