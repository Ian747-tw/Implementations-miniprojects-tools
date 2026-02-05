#include "data_reader.hpp"

#include <fstream>
#include <sstream>

using namespace std;

bool parse_libsvm_line(const string &line, int max_feature, Example &out) {
  istringstream iss(line);
  int label = 0;
  if (!(iss >> label)) {
    return false;
  }

  vector<double> dense(max_feature + 1, 0.0);
  string token;
  while (iss >> token) {
    size_t colon = token.find(':');
    if (colon == string::npos) {
      continue;
    }
    int idx = stoi(token.substr(0, colon));
    if (idx < 0 || idx > max_feature) {
      continue;
    }
    double val = stod(token.substr(colon + 1));
    dense[idx] = val;
  }

  out.label = label;
  out.features = move(dense);
  return true;
}

vector<Example> read_libsvm_file(const string &path,
                                 int max_feature,
                                 int *max_feature_seen) {
  vector<Example> data;
  if (max_feature_seen) {
    *max_feature_seen = 0;
  }
  ifstream fin(path);
  string line;
  while (getline(fin, line)) {
    Example ex;
    if (!parse_libsvm_line(line, max_feature, ex)) {
      continue;
    }
    if (max_feature_seen) {
      for (int i = max_feature; i >= 0; --i) {
        if (ex.features[i] != 0.0) {
          if (i + 1 > *max_feature_seen) {
            *max_feature_seen = i + 1;
          }
          break;
        }
      }
    }
    data.push_back(move(ex));
  }
  return data;
}
