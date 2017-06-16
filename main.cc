#include "decaying-ddos-detector.hpp"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
  DecayingDDoSDetector detector = DecayingDDoSDetector();
  for (int i = 0; i < 3000; ++i) {
    stringstream ss;
    ss << i;
    string s;
    ss >> s;
    string res = detector.addItem(s);
    if (res != "safe") {
      cout << res << endl;
      break;
    }
  }
  return 0;
}