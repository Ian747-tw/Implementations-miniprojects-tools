#include "func.hpp"
using namespace std;

unordered_map<tuple<string, string, long long>, int, tuple_hash> make_M(const Dataset &data){
    unordered_map<tuple<string, string, long long>, int, tuple_hash> M;

    for(size_t i = 0; i < data.sale.size(); i++){
        tuple<string, string, long long> temp = make_tuple(data.user_id[i], data.product_id[i], data.click_timestamp[i]);
        M[temp] = data.sale[i];
    }

    return M;
}

unordered_map<string, vector<struct product_info>> make_purchased(const Dataset &data){
    unordered_map<string, vector<struct product_info>> purchased;
    unordered_map<string, bool> is_in_users;
    vector<string> users;

    for(size_t i = 0; i < data.sale.size(); i++){
        if(!is_in_users[data.user_id[i]]){
            is_in_users[data.user_id[i]] = true;
            users.push_back(data.user_id[i]);
        }

        struct product_info temp;
        temp.product_id = data.product_id[i];
        temp.click_timestamp = data.click_timestamp[i];
        temp.product_price = data.product_price[i];
        temp.product_age_group = data.product_age_group[i];
        temp.product_gender = data.product_gender[i];

        purchased[data.user_id[i]].push_back(temp);
    }

    for(size_t i = 0; i < users.size(); i++){
        sort(purchased[users[i]].begin(), purchased[users[i]].end(), [](const product_info &a, const product_info &b){
            if(a.product_id != b.product_id)
                return a.product_id < b.product_id;

            return a.click_timestamp < b.click_timestamp;
        });
    }

    return purchased;
}

unordered_map<string, vector<string>> make_clicked(const Dataset &data){
    unordered_map<string, vector<string>> clicked;
    unordered_map<string, unordered_map<string, bool>> is_in_clicked;
    
    for(size_t i = 0; i < data.sale.size(); i++){
        string pid = data.product_id[i];
        string uid = data.user_id[i];

        if(!is_in_clicked[pid][uid]){
            clicked[pid].push_back(uid);
            is_in_clicked[pid][uid] = true;
        }
    }

    for(auto &i : clicked)
        sort(i.second.begin(), i.second.end());

    return clicked;
    
}

unordered_map<string, unordered_map<string, bool>> make_check_user_of(const unordered_map<string, vector<string>> &clicked){
    unordered_map<string, unordered_map<string, bool>> check_user_of;
    
    for(const auto &i : clicked){
        const string &pid = i.first;
        const vector<string> &users = i.second;

        for(size_t j = 0; j < users.size(); j++){
            check_user_of[pid][users[j]] = true;
        }
    }

    return check_user_of;
}

map<long long, map<string, double>> make_users_avg_sales_after_t(const Dataset &data){
    map<long long, map<string, double>> users_avg_sales_after_t;

    map<long long, map<string, long long>> users_sales_at_t;
    map<string, long long> users_total_sales;
    map<long long, map<string, int>> users_clicks_at_t;
    map<string, int> users_total_clicks;

    vector<string> uids;
    unordered_map<string, bool> is_in_uids;
    
    for(size_t i = 0; i < data.sale.size(); i++){
        string uid = data.user_id[i];
        int sale = data.sale[i];
        long long ct = data.click_timestamp[i];
        
        users_total_sales[uid] += sale;
        users_total_clicks[uid]++;

        if(!users_sales_at_t[ct][uid])
            users_sales_at_t[ct][uid] = sale;
        else
            users_sales_at_t[ct][uid] += sale;
        
        if(!is_in_uids[uid]){
            is_in_uids[uid] = true;
            uids.push_back(uid);
        }

        if(!users_clicks_at_t[ct][uid])
            users_clicks_at_t[ct][uid] = 1;
        else
            users_clicks_at_t[ct][uid]++;
    }

    map<long long, map<string, long long>> users_sales_before_t;
    map<long long, map<string, int>> users_clicks_before_t;

    map<long long, map<string, long long>> users_sales_after_t;
    map<long long, map<string, int>> users_clicks_after_t;

    long long last_ct;
    int t = 0;

    for(const auto &ct_users : users_sales_at_t){
        if(t == 0){
            for(const auto &user : uids){
                users_sales_before_t[ct_users.first][user] = users_sales_at_t[ct_users.first][user];
                users_clicks_before_t[ct_users.first][user] = users_clicks_at_t[ct_users.first][user];

                users_sales_after_t[ct_users.first][user] = users_total_sales[user] - users_sales_before_t[ct_users.first][user] + users_sales_at_t[ct_users.first][user];
                users_clicks_after_t[ct_users.first][user] = users_total_clicks[user] - users_clicks_before_t[ct_users.first][user] + users_clicks_at_t[ct_users.first][user];

                if(users_clicks_after_t[ct_users.first][user] == 0){
                    users_avg_sales_after_t[ct_users.first][user] = 0.0;
                }else{
                    users_avg_sales_after_t[ct_users.first][user] =
                        static_cast<double>(users_sales_after_t[ct_users.first][user]) /
                        users_clicks_after_t[ct_users.first][user];
                }
            }
        }else{
            for(const auto &user : uids){
                users_sales_before_t[ct_users.first][user] = users_sales_at_t[ct_users.first][user] + users_sales_before_t[last_ct][user];
                users_clicks_before_t[ct_users.first][user] = users_clicks_at_t[ct_users.first][user] + users_clicks_before_t[last_ct][user];
                
                users_sales_after_t[ct_users.first][user] = users_total_sales[user] - users_sales_before_t[ct_users.first][user] + users_sales_at_t[ct_users.first][user];
                users_clicks_after_t[ct_users.first][user] = users_total_clicks[user] - users_clicks_before_t[ct_users.first][user] + users_clicks_at_t[ct_users.first][user];
 
                if(users_clicks_after_t[ct_users.first][user] == 0){
                    users_avg_sales_after_t[ct_users.first][user] = 0.0;
                }else{
                    users_avg_sales_after_t[ct_users.first][user] =
                        static_cast<double>(users_sales_after_t[ct_users.first][user]) /
                        users_clicks_after_t[ct_users.first][user];
                }
            }
        }

        last_ct = ct_users.first;
        t++;     
    }

    return users_avg_sales_after_t;    

}
