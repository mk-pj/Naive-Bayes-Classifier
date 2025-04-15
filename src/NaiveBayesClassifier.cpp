#include <fmt/core.h>
#include "util.h"
#include "NaiveBayesClassifier.h"

using util::split;

NaiveBayesClassifier::NaiveBayesClassifier(const string &header_row) : total_count(0) {
    this->headers = split(header_row, ",");
    for (auto i = 0; i < this->headers.size() - 1; ++i) {
        auto &header = this->headers[i];
        this->attribute_variations[header] = unordered_set<string>();
    }
}

void NaiveBayesClassifier::train(const string &line) {
    ++this->total_count;
    const auto attributes = split(line, ",");
    auto &class_name = attributes.back();
    this->classes[class_name] += 1;
    auto &counts = this->attribute_counts[class_name];

    for (auto i = 0; i < attributes.size() - 1; ++i) {
        auto &attribute = attributes[i];
        auto &header = this->headers[i];
        auto key = header;
        key.append("=").append(attribute);
        counts[key] += 1;
        this->attribute_variations[header].insert(attribute);
    }
}

string NaiveBayesClassifier::predict(const string &x) {
    string prediction;
    double curr_max_prob { -1.0 };
    const auto attributes = split(x, ",");
    fmt::println("\n== PREDICTION FOR: {} ==", x);

    for (const auto &[class_name, count] : this->classes) {
        double class_prob = static_cast<double>(count) / this->total_count;
        fmt::println("P({}) = {}", class_name, class_prob);

        auto &counts = this->attribute_counts[class_name];
        for (auto i = 0; i < attributes.size() - 1; ++i) {
            auto &header = this->headers[i];
            auto &attribute = attributes[i];
            auto key = header;
            key.append("=").append(attribute);

            const int attr_count = counts.contains(key) ? counts[key] : 0;
            const auto denominator = static_cast<double>(count + this->attribute_variations[header].size());
            const double attr_prob = attr_count == 0 ? 1.0 / denominator : attr_count / static_cast<double>(count);

            fmt::println("  P({}|{}) = {} ({}/{})", key, class_name, attr_prob, attr_count, count);

            class_prob *= attr_prob;
        }

        fmt::println("  => P({}|x) = {}", class_name, class_prob);

        if (class_prob > curr_max_prob) {
            prediction = class_name;
            curr_max_prob = class_prob;
        }
    }
    fmt::println("PREDICTED CLASS: {} ==", prediction);
    return prediction;
}

void NaiveBayesClassifier::printStatistics() const {
    fmt::println("\n=== STATISTICS FROM TRAINING ===\n");
    for (const auto& [class_name, count] : this->classes) {
        fmt::println("Class: {} (count: {})", class_name, count);
        const auto& counts = this->attribute_counts.at(class_name);
        for (const auto& [key, val] : counts)
            fmt::println(" {}: {}", key, val);
    }
}