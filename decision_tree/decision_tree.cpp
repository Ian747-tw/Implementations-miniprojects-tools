#include "decision_tree.hpp"

tuple<int, double, double> best_split(const vector<Example> &data, int feature_size){
    if (data.empty() || feature_size <= 0) {
        return make_tuple(-1, 0.0, 1.0);
    }
    int best_feature = -1;
    double best_threshold = 0.0;
    double best_conf = 1e9;
    for(int i = 0; i < feature_size; i++){
        unordered_map<double, pair<int, int>> value_record;
        vector<double> distinct_vals;
        unordered_map<double, bool> in_vals;
    for(size_t j = 0; j < data.size(); j++){
            double val = data[j].features[i];
            if(!in_vals[val]){
                in_vals[val] = true;
                distinct_vals.push_back(val);
            }
            int label = data[j].label;
            if(label == 1)
                value_record[val].first++;
            
            if(label == -1)
                value_record[val].second++;
        }

        sort(distinct_vals.begin(), distinct_vals.end());
        int num1 = 0;
        int num0 = 0;
        for(size_t j = 0; j < distinct_vals.size(); j++){
            num1 += value_record[distinct_vals[j]].first;
            num0 += value_record[distinct_vals[j]].second;
        }

        if (distinct_vals.size() < 2) {
            continue;
        }

        double best_threshold_f = 0.0;
        double best_conf_f = 1e9;
        bool feature_found = false;
        int pf1 = 0;
        int pf0 = 0;
        for(size_t j = 0; j + 1 < distinct_vals.size(); j++){
            double thresh = (distinct_vals[j] + distinct_vals[j + 1]) / 2.0 ;
            pf1 += value_record[distinct_vals[j]].first;
            pf0 += value_record[distinct_vals[j]].second;
            double conf = min(pf1, pf0) + min(num1 - pf1, num0 - pf0);
            conf = conf * 2.0 / double(num1 + num0);
            if(!feature_found){
                best_threshold_f = thresh;
                best_conf_f = conf;
                feature_found = true;
            }else if(conf < best_conf_f){
                best_threshold_f = thresh;
                best_conf_f = conf;
            }
        }

        if(!feature_found){
            continue;
        }
        if(best_conf_f < best_conf){
            best_feature = i;
            best_conf = best_conf_f;
            best_threshold = best_threshold_f;
        }
    }

    return make_tuple(best_feature, best_threshold, best_conf);
    
}

static int majority_label(const vector<Example> &data) {
    int pos = 0;
    int neg = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].label == 1) {
            pos++;
        } else if (data[i].label == -1) {
            neg++;
        }
    }
    return (pos >= neg) ? 1 : -1;
}

void build_tree(struct node* head, int feature_size, double epsilon){
    const vector<Example> &data = head->data;
    head->left = nullptr;
    head->right = nullptr;
    head->is_leaf = false;

    if (data.empty()) {
        head->is_leaf = true;
        head->predict_label = 1;
        return;
    }
    tuple<int, double, double> split = best_split(data, feature_size);
    int feature = get<0>(split);
    double threshold = get<1>(split);
    double conf = get<2>(split);

    if(feature < 0 || conf < epsilon){
        head->is_leaf = true;
        head->predict_label = majority_label(data);
        return;
    }

    head->feature_index = feature;
    head->threshold = threshold;
    
    vector<Example> left_data;
    vector<Example> right_data;

    for(size_t i = 0; i < data.size(); i++){
        if(data[i].features[feature] > threshold)
            left_data.push_back(data[i]);
        else
            right_data.push_back(data[i]);
    }

    if (left_data.empty() || right_data.empty()) {
        head->is_leaf = true;
        head->predict_label = majority_label(data);
        return;
    }

    head->right = new struct node;
    head->right->data = right_data;
    build_tree(head->right, feature_size, epsilon);

    head->left = new struct node;
    head->left->data = left_data;
    build_tree(head->left, feature_size, epsilon);

    
      


}

void print_tab(int depth){
    while(depth--)
        cout<<"\t";
}

void print_tree(struct node* head, int depth){
    if(head->is_leaf){
        print_tab(depth);
        cout<<"return "<<head->predict_label<<";"<<endl;
        return;
    }else{
        print_tab(depth);
        cout<<"if(attr["<<head->feature_index<<"]"<<" > "<<head->threshold<<"){"<<endl;
        
        print_tree(head->left, depth + 1);
        
        print_tab(depth);
        cout<<"}"<<endl;

        print_tab(depth);
        cout<<"else{"<<endl;

        print_tree(head->right, depth + 1);
        
        print_tab(depth);
        cout<<"}"<<endl;

    }
}
