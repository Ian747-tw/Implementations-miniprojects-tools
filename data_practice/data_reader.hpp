#pragma once

#include <string>
#include <vector>

using namespace std;

struct Dataset {
  std::vector<int> sale;
  std::vector<double> sales_amount_in_euro;
  std::vector<long long> time_delay_for_conversion;
  std::vector<long long> click_timestamp;
  std::vector<int> nb_clicks_1week;
  std::vector<double> product_price;
  std::vector<std::string> product_age_group;
  std::vector<std::string> device_type;
  std::vector<std::string> audience_id;
  std::vector<std::string> product_gender;
  std::vector<std::string> product_brand;
  std::vector<std::string> product_category1;
  std::vector<std::string> product_category2;
  std::vector<std::string> product_category3;
  std::vector<std::string> product_category4;
  std::vector<std::string> product_category5;
  std::vector<std::string> product_category6;
  std::vector<std::string> product_category7;
  std::vector<std::string> product_country;
  std::vector<std::string> product_id;
  std::vector<std::string> product_title;
  std::vector<std::string> partner_id;
  std::vector<std::string> user_id;
};

Dataset read_data(const std::string &path);
