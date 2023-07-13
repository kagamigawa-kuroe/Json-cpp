#include "json/json.h"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace hongzhe;

int main() {
  //  Json j1 = 10;
  //  std::cout << j1.m_type << " " << j1.m_value.m_int << endl;
  //  Json j2 = "hello json";
  //  std::cout << j2.m_type << " " << *j2.m_value.m_string << endl;
  //
  //  int a = j1;
  //  string s = j2;
  //  std::cout << a << " " << s << std::endl;
  //  std::cout << j1.str() << std::endl;

  //  Json j3;
  //  j3.append(10);
  //  j3.append("hello");
  //
  //  Json j4;
  //  j4.append(30);
  //  j4.append(j3);
  //  j4.append("test");
  //  std::cout << j4.str() << std::endl;

  Json j1;
  j1["test"] = 1;
  cout << j1.str() << endl;

  Json j2;
  j2["hehhe"] = 2;
  string s2 = "t2d";
  j2[s2] = j1;
  cout << j2.str() << endl;
}
