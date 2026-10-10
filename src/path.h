#ifndef SQLP_PATH_H
#define SQLP_PATH_H

#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

class Path {
  // ex. command might be w.paper.title
  std::string root_;
  std::vector<std::string> features_;

public:
  Path(std::string root, std::vector<std::string> features)
    : root_(std::move(root)), features_(std::move(features)) {
      if (root_.empty() || features_.empty()) {
        throw std::invalid_argument{
          "A path needs an alias and a feature"
        };
      }

      for (const auto &feature : features) {
        if (feature.empty()) {
          throw std::invalid_argument{
            "A feature name cannot be empty"
          };
        }
      }
    }

    const std::string &root() const {
      return root_;
    }

    const std::vector<std::string> features() const {
      return features_;
    }
};

#endif