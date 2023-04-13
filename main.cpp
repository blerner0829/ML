// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

int main(int argc, char* argv[]) {
  if ((argc != 3) && (argc != 4) || ((argc == 4) && (argv[3] != "--debug"))) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  };

  ifstream trainFile(argv[1]);
  if (!trainFile.is_open()) {
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  ifstream testFile(argv[2]);
  if (!testFile.is_open()) {
    cout << "Error opening file: " << argv[2] << endl;
    return 1;
  }

  
}