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
    int total_unique_words = 0;
    double logPC = 0;
    double logPWC = 0;
    set<string> unique_word_set;
    map<string, int> word_occur;
    map<string, int> label_occur;
    map<string, map<string, int>> label_word_counts;
    map<string, map<string, string>> string_storage;
    
  public:
    Classifier (){}
    map<string, map<string, string>> storeString(csvstream &file) {
      map<string, string> row;
      while (file >> row){
        string_storage[row["n"]][row["tag"]] = row["content"];
      }
      return string_storage;
    }

    int countPosts(map<string, map<string, string>> string_storage) {
      string highest_n= "0";
      for (const auto& pair : string_storage) {
        const string& n_value = pair.first;
        if (n_value > highest_n) {
          highest_n = n_value;
        }
      }
      numPosts = stoi(highest_n);
      return stoi(highest_n);
    }

    int totalUniqueWords(map<string, map<string, string>> string_storage, set<string> &unique_word_set) {
      int total = 0;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
            total += unique_words(innerPair.second).size();
            unique_word_set.insert(unique_words(innerPair.second).begin(), unique_words(innerPair.second).end());
        }
      }
      return total;
    }

    void wordOccurances(map<string, map<string, string>> string_storage) {
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          istringstream stream(innerPair.second);
          string word;
          set<string> uniqueWordsInString;

          while (stream >> word) {
            uniqueWordsInString.insert(word);
          }

          for (const auto& uniqueWord : uniqueWordsInString) {
            if (uniqueWordsInString.count(uniqueWord)) {
                ++word_occur[uniqueWord];
            }
          }
        }
      }
    }

    void labelOccurances(map<string, map<string, string>> string_storage) {
      set<string> uniqueLabelsInString;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          string word = innerPair.first;
          uniqueLabelsInString.insert(word);
        }
      }

      for (const auto& uniqueLabel : unique_word_set) {
        if (uniqueLabelsInString.count(uniqueLabel)) {
          ++label_occur[uniqueLabel];
        }
      }
    }

    void wordAndLabel(map<string, map<string, string>> string_storage) {
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          string label = innerPair.first;
          string content = innerPair.second;
          for (const auto& word : unique_word_set) {
            if (content.find(word) != string::npos) {
              label_word_counts[label][word]++;
            }
          }
        }
      }
    }

    void logPC(string label, map<string, map<string, string>> string_storage) {
      logPC = log(label_occur[label] / numPosts);
    }

    void logPWC(string label, string word) {
      if (label_word_counts.count(label) && label_word_counts[label].count(word)) {
        logPWC = log(label_word_counts[label][word] / numPosts);
      }
      else if (word_occur.count(word)) {
        logPWC = log(word_occur[word] / numPosts);
      }
      else {
        logPWC = log(1 / numPosts);
      }
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
  set<string> unique_word_set;
  int total_posts = 0;
  int total_unique_words = 0;
  map<string, map<string, string>> string_storage;
  cout.precision(3);
  if ((argc != 3) && (argc != 4) || ((argc == 4) && (argv[3] != "--debug"))) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  };

  csvstream trainFile(argv[1]);
  csvstream testFile(argv[2]);
  Classifier train;

  string_storage = train.storeString(trainFile);
  total_posts = train.countPosts(string_storage);
  total_unique_words = train.totalUniqueWords(string_storage, unique_word_set);
  train.wordOccurances(string_storage);
  train.labelOccurances(string_storage);
  train.wordAndLabel(string_storage);



}