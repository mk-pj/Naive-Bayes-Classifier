#include <sstream>
#include <iostream>
#include "NaiveBayesUtils.h"

NaiveBayesClassifier init(std::stringstream &lines, const unsigned lines_to_read) {
    string line;
    std::getline(lines, line);
    NaiveBayesClassifier classifier(line);
    unsigned line_counter = 1;
    while(std::getline(lines, line) && line_counter < lines_to_read) {
        classifier.train(line);
        line_counter++;
    }
    classifier.train(line);
    return classifier;
}
