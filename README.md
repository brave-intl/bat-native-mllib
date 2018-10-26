[![Build Status](https://travis-ci.org/brave-intl/bat-native-mllib.svg?branch=master)](https://travis-ci.org/brave-intl/bat-native-mllib)

# BAT Native ML Lib

This library implements the inference part of the following models:
- Naive Bayes
- Logistic Regression
- Linear Regression

## Installation

- Run `gn gen out\default` to generate ninja files
- Run `ninja -C out\default test` to compile
- Run `out\default\test.exe` for the tests
- Run `python scripts\cpplint.py` for linting