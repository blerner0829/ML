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

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

class Classifier {
  private:
    int numPosts = 0;
    double logPCvar = 0;
    double logPWCvar = 0;
    set<string> unique_word_set;
    map<string, int> word_occur;
    map<string, int> label_occur;
    map<string, map<string, int>> label_word_counts;
    map<string, map<string, string>> string_storage;
    
  public:
    Classifier () {}
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

    void logPC(string label) {
      logPCvar = log(label_occur[label] / numPosts);
    }

    void logPWC(string label, string word) {
      if (label_word_counts.count(label) && label_word_counts[label].count(word)) {
        logPWCvar = log(label_word_counts[label][word] / numPosts);
      }
      else if (word_occur.count(word)) {
        logPWCvar = log(word_occur[word] / numPosts);
      }
      else {
        logPWCvar = log(1 / numPosts);
      }
    }

    pair<string, double> predict(string content) {
      map<string, double> label_prob;
      for (const auto& label : unique_word_set) {
        double prob = 0;
        for (const auto& word : unique_words(content)) {
          logPWC(label, word);
          prob += logPWCvar;
        }
        logPC(label);
        prob += logPCvar;
        label_prob[label] = prob;
      }
      string highest_label = "";
      double highest_prob = 0;
      for (const auto& pair : label_prob) {
        if (pair.second > highest_prob) {
          highest_label = pair.first;
          highest_prob = pair.second;
        }
      }
      return pair<string, double>(highest_label, highest_prob);
    }

    // https://eecs280staff.github.io/p5-ml/#example
    // for each, prints out labal and content
    void printTrainingData(map<string, map<string, string>> string_storage) {
      cout << "training data:" << endl;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          cout << "  label = " << innerPair.first;
          cout << ",  content = " << innerPair.second << endl;
          }
      }
    }

    // https://eecs280staff.github.io/p5-ml/#example
    // print out each label, number of examples it was trained on, and the value for log-prior
    // print all of these using a for loop to iterate through the labels
    void printClasses() {
      cout << "classes:" << endl;
      for (const auto& label : unique_word_set) {
        cout << "  label = " << label;
        cout << ", " << label_occur[label] << " examples";
        logPC(label);
        cout << ",  log-prior = " << logPCvar << endl;
        }
    }
    // https://eecs280staff.github.io/p5-ml/#example
    //For each label, and for each word that occurs for that label: The number of posts with that label that contained the word, 
    // and the log-likelihood of the word given the label.
    // ex: 
    // classifier parameters:
    // calculator:assert, count = 1, log-likelihood = -1.1
    // calculator:big, count = 1, log-likelihood = -1.1
    // euchre:twice, count = 1, log-likelihood = -1.61
    // euchre:upcard, count = 2, log-likelihood = -0.916
    void printClassifierParamaters() {
      cout << "classifier parameters:" << endl;
      for (const auto& label : unique_word_set) {
        for (const auto& word : unique_word_set) {
          if (label_word_counts.count(label) && label_word_counts[label].count(word)) {
            cout << "  " << label << ":" << word << ", count = " << label_word_counts[label][word];
            logPWC(label, word);
            cout << ", log-likelihood = " << logPWCvar << endl;
          }
        }
      }
      cout << endl;
    }

    // https://eecs280staff.github.io/p5-ml/#example
    void printTestData(map<string, map<string, string>> test_string_storage) {
      cout << "test data:" << endl;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          cout << "  correct = " << innerPair.first;
          cout << ", predicted = " << predict(innerPair.second).first;
          cout << ", prob = " << predict(innerPair.second).second << endl;
          cout << "  content = " << innerPair.second << endl << endl;
          }
      }
    }
    
    // Print the number of correct predictions and total number of test posts.
    // ex:
    // performance: 2 / 3 posts predicted correctly
    void printPerformance(map<string, map<string, string>> test_string_storage) {
      int correct = 0;
      int total = 0;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          if (innerPair.first == predict(innerPair.second).first) {
            correct++;
          }
          total++;
          }
      }
      cout << "performance: " << correct << " / " << total << " posts predicted correctly" << endl;
    }
    
};

int main(int argc, char* argv[]) {
  set<string> unique_word_set;
  int total_posts = 0;
  int total_unique_words = 0;
  map<string, map<string, string>> string_storage;
  cout.precision(3);
  if (((argc != 3) && (argc != 4)) || ((argc == 4) && (strcmp(argv[3], "--debug") != 0))) {
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

  //take the words from the post in the test file
  //iterate through the labels from the training set
  //for each label calculate a log score by adding the log of all the words together
  //store the first one as the greatest value and subsequently compare all following against the first
  map<string, map<string, string>> test_string_storage = train.storeString(testFile);
  train.printTrainingData(string_storage); // if debug
  cout << "trained on" << total_posts << "examples" << endl;
  cout << "vocabulary size = " << total_unique_words << endl << endl; // if debug
  train.printClasses(); // if debug
  train.printClassifierParamaters(); // if debug


  train.printTestData(test_string_storage);
  train.printPerformance(test_string_storage);



}