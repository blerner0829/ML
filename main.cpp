// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include "csvstream.h"

using namespace std;

class Classifier {
  private:
    int numPosts = 0;
    set<string> unique_words;
    map<string, int> word_occur;
    map<string, int> label_occur;
    map<string, map<string, int>> label_word_counts;
    map<string, map<string, string>> string_storage;

  public:
    map<string, map<string, string>> storeString(csvstream file) {
      map<string, string> row;
      while (file >> row){
        string_storage[row["n"]][row["tag"]] = row["content"];
      }
      return string_storage;
    }
    

};

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
  cout.precision(3);
  if ((argc != 3) && (argc != 4) || ((argc == 4) && (argv[3] != "--debug"))) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  };

  csvstream trainFile(argv[1]);
  csvstream testFile(argv[2]);


}