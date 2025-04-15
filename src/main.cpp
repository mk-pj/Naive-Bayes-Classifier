#include <iostream>
#include <sstream>
#include <fstream>
#include <fmt/ranges.h>
#include "NaiveBayesUtils.h"

int main() {
    const auto file_name = "../weather_data.csv";
    std::ifstream input(file_name);
    if (!input.is_open())
        std::cerr << "Error opening file: " << file_name << '\n';
    std::stringstream input_stream;
    input_stream << input.rdbuf();
    NaiveBayesClassifier classifier = init(input_stream, 12);
    string to_classify;
    std::getline(input_stream, to_classify);
    classifier.predict(to_classify);
    fmt::println("ROWS USED FOR TRAINING: {}", classifier.total_count);
    fmt::println("CLASS COUNTS: {}", classifier.classes);
    fmt::println("ATTRIBUTE VARIATIONS: {}", classifier.attribute_variations);
    fmt::print("ATTRIBUTE COUNTS PER CLASS: \n{}\n", fmt::join(classifier.attribute_counts, "\n"));
    input.close();
    return 0;
}