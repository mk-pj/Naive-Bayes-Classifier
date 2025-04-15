#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::string, std::unordered_set, std::vector, std::unordered_map;

class NaiveBayesClassifier {
public:
    int total_count;
    vector<string> headers;
    unordered_map<string, int> classes;
    unordered_map<string, unordered_set<string>> attribute_variations;
    unordered_map<string, unordered_map<string, int>> attribute_counts;
    explicit NaiveBayesClassifier(const string&);
    void train(const string&);
    string predict(const string&);
    void printStatistics() const;
};

#endif //NAIVEBAYESCLASSIFIER_H
