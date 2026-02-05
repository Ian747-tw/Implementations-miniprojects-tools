#include<bits/stdc++.h>
#include "data_reader.hpp"
using namespace std;

struct product_info{
    string product_id;
    long long click_timestamp;
    double product_price;
    string product_age_group;
    string product_gender;
};

struct tuple_hash {
    size_t operator()(const tuple<string, string, long long> &key) const {
        const auto &user_id = get<0>(key);
        const auto &product_id = get<1>(key);
        long long click_timestamp = get<2>(key);
        size_t h1 = hash<string>{}(user_id);
        size_t h2 = hash<string>{}(product_id);
        size_t h3 = hash<long long>{}(click_timestamp);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

unordered_map<tuple<string, string, long long>, int, tuple_hash> make_M(const Dataset &data);

unordered_map<string, vector<struct product_info>> make_purchased(const Dataset &data);

unordered_map<string, vector<string>> make_clicked(const Dataset &data);

unordered_map<string, unordered_map<string, bool>> make_check_user_of(const unordered_map<string, vector<string>> &clicked);

map<long long, map<string, double>> make_users_avg_sales_after_t(const Dataset &data);
