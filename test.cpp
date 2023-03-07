#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string str = "12d34";
  std::stringstream ss(str);
  int num;
//   ss >> num;

  std::cout << "The integer value of the string is: " << num << std::endl;
  return 0;
}