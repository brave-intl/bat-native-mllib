/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef INCLUDE_NAIVE_BAYES_H_
#define INCLUDE_NAIVE_BAYES_H_

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <regex>
#include <iterator>
#include <cmath>

namespace mllib {
class NaiveBayes {
 public:
  NaiveBayes();
  ~NaiveBayes();
  bool LoadModel(const std::string& model);
  std::vector<double> Predict(std::map<std::string, double> features);
  std::vector<std::string> Classes();

 private:
  std::vector<std::string> classes_;
  std::vector<double> priors_;
  std::map<std::string, std::vector<double> > features_;
};
}  // namespace mllib

#endif  // INCLUDE_NAIVE_BAYES_H_
