#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include <string>
#include <vector>

using namespace std;

struct Example {
  int label;
  vector<double> features;
  int feature_size;
};

// Parse a LIBSVM-format line into a dense feature vector of size max_feature + 1.
// Returns true if the line was parsed successfully.
bool parse_libsvm_line(const string &line, int max_feature, Example &out);

// Read a LIBSVM-format file into dense examples.
vector<Example> read_libsvm_file(const string &path,
                                 int max_feature,
                                 int *max_feature_seen);

#endif
