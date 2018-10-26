// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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

#include "naive_bayes.h"
#include "linear_regression.h"
#include "logistic_regression.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <streambuf>
#include <numeric>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

using namespace rapidjson;
using namespace mllib;

std::string loadFile(std::string filename) {
  std::ifstream t(filename);
  std::string data((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  return data;
}

Document loadJson(std::string filename) {
  auto json = loadFile(filename);

  Document d;
  d.Parse(json.c_str());

  return d;
}

TEST_CASE( "Test logistic regression", "[classifier]" ) {
  mllib::LogisticRegression cl;
  cl.LoadModel("{\"features\":[\"test1\", \"test2\", \"test3\"], \"weights\":[0.2, 0.4, 0.9], \"bias\": 0.5}");
  auto features = std::map<std::string, double>();
  features["test1"] = 0.1;
  features["test2"] = 0.3;
  REQUIRE(cl.Predict(features).at(0) ==  Approx( 0.65475 ));
}

TEST_CASE( "Test linear model", "[classifier]" ) {
  mllib::LinearRegression lr;

  auto svm_model_json = loadJson("test/data/linear_svm.json");
  const Value& svm_model_feature_names = svm_model_json["features"];
  auto feature_names = std::vector<std::string>();
  for (SizeType it = 0; it < svm_model_feature_names.Size(); it++) {
    feature_names.push_back(svm_model_feature_names[it].GetString());
  }

  lr.LoadModel(loadFile("test/data/linear_svm.json"));

  auto doc = loadJson("test/data/svm_scores.json");
  const Value& tests = doc["tests"];
  for (SizeType it = 0; it < tests.Size(); it++) {
    const Value& features = tests[it]["features"];
    auto feature_vector = std::map<std::string, double>();
    for (SizeType j = 0; j < features.Size(); j++) {      
      feature_vector[feature_names.at(j)] = features[j].GetDouble();
    }
    
    double expected = tests[it]["score"].GetDouble();
    double predicted = lr.Predict(feature_vector).at(0);
    
    REQUIRE( predicted == Approx(expected) );
  }
}