#include<bits/stdc++.h>
#include "data_reader.hpp"

using namespace std;

struct node{
    struct node* right;
    struct node* left;
    vector<Example> data;
    int feature_index;
    double threshold;
    bool is_leaf;
    int predict_label;
};

tuple<int, double, double> best_split(const vector<Example> &data, int feature_size);

void build_tree(struct node* head, int feature_size, double epsilon);

void print_tab(int depth);

void print_tree(struct node* head, int depth);