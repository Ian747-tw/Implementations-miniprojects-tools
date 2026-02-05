#include "data_reader.hpp"
#include "func.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " /path/to/data/file\n";
    return 1;
  }

  Dataset data = read_data(argv[1]);
  if (data.sale.empty()) {
    cerr << "No data loaded. Check the file path.\n";
    return 1;
  }

  unordered_map<tuple<string, string, long long>, int, tuple_hash> M = make_M(data);
  unordered_map<string, vector<product_info>> purchased = make_purchased(data);
  unordered_map<string, vector<string>> clicked = make_clicked(data);
  unordered_map<string, unordered_map<string, bool>> check_user_of = make_check_user_of(clicked);
  map<long long, map<string, double>> users_avg_sales_after_t = make_users_avg_sales_after_t(data);

  const string star_line(20, '*');
  string line;
  while (getline(cin, line)) {
    if (line.empty()) {
      continue;
    }

    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "quit") {
      break;
    }

    cout << star_line << "\n";

    if (cmd == "get") {
      string uid;
      string pid;
      long long ct = 0;
      ss >> uid >> pid >> ct;
      tuple<string, string, long long> key = make_tuple(uid, pid, ct);
      auto it = M.find(key);
      cout << (it == M.end() ? 0 : it->second) << "\n";
    } else if (cmd == "purchased") {
      string uid;
      ss >> uid;
      auto it = purchased.find(uid);
      if (it != purchased.end()) {
        cout << fixed << setprecision(6);
        for (const auto &info : it->second) {
          cout << info.product_id << "\t" << info.click_timestamp << "\t"
               << info.product_price << "\t" << info.product_age_group
               << "\t" << info.product_gender << "\n";
        }
      }
    } else if (cmd == "clicked") {
      string p1;
      string p2;
      ss >> p1 >> p2;
      auto it = clicked.find(p1);
      if (it != clicked.end()) {
        for (const auto &user : it->second) {
          if (check_user_of[p2][user]) {
            cout << user << "\n";
          }
        }
      }
    } else if (cmd == "profit") {
      long long t = 0;
      double theta = 0.0;
      ss >> t >> theta;
      auto it = users_avg_sales_after_t.lower_bound(t);
      if (it != users_avg_sales_after_t.end()) {
        size_t printed = 0;
        for (const auto &user_avg : it->second) {
          if (user_avg.second >= theta) {
            cout << user_avg.first << "\n";
            printed++;
            if (printed == 10) {
              break;
            }
          }
        }
      }
    }

    cout << star_line << "\n";
  }

  return 0;
}
