#include "data_reader.hpp"
#include "decision_tree.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {
const int kMaxFeature = 1024;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <data-file> <epsilon>\n";
    return 1;
  }

  const string data_path = argv[1];
  const double epsilon = atof(argv[2]);
  (void)epsilon;

  int feature_count = 0;
  vector<Example> data = read_libsvm_file(data_path, kMaxFeature, &feature_count);
  if (data.empty()) {
    cerr << "No examples loaded from " << data_path << "\n";
    return 1;
  }

  // TODO: Build decision tree using data and feature_count.
  struct node* head = new struct node;
  head->data = data;

  build_tree(head, feature_count, epsilon);

  // TODO: Print C/C++ code for tree_predict to stdout.
  cout<<"int tree_predict(double *attr){"<<endl;
  print_tree(head, 1);
  cout<<"}"<<endl;

  return 0;
}
