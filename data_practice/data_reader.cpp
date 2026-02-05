#include "data_reader.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace {
int to_int(const std::string &s, int fallback = -1) {
  try {
    return std::stoi(s);
  } catch (...) {
    return fallback;
  }
}

long long to_ll(const std::string &s, long long fallback = -1) {
  try {
    return std::stoll(s);
  } catch (...) {
    return fallback;
  }
}

double to_double(const std::string &s, double fallback = -1.0) {
  try {
    return std::stod(s);
  } catch (...) {
    return fallback;
  }
}
} // namespace

Dataset read_data(const std::string &path) {
  Dataset data;
  std::ifstream file(path);
  if (!file) {
    return data;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    std::vector<std::string> fields;
    fields.reserve(23);
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, '\t')) {
      fields.push_back(field);
    }

    if (fields.size() != 23) {
      continue;
    }

    data.sale.push_back(to_int(fields[0]));
    data.sales_amount_in_euro.push_back(to_double(fields[1]));
    data.time_delay_for_conversion.push_back(to_ll(fields[2]));
    data.click_timestamp.push_back(to_ll(fields[3]));
    data.nb_clicks_1week.push_back(to_int(fields[4]));
    data.product_price.push_back(to_double(fields[5]));
    data.product_age_group.push_back(fields[6]);
    data.device_type.push_back(fields[7]);
    data.audience_id.push_back(fields[8]);
    data.product_gender.push_back(fields[9]);
    data.product_brand.push_back(fields[10]);
    data.product_category1.push_back(fields[11]);
    data.product_category2.push_back(fields[12]);
    data.product_category3.push_back(fields[13]);
    data.product_category4.push_back(fields[14]);
    data.product_category5.push_back(fields[15]);
    data.product_category6.push_back(fields[16]);
    data.product_category7.push_back(fields[17]);
    data.product_country.push_back(fields[18]);
    data.product_id.push_back(fields[19]);
    data.product_title.push_back(fields[20]);
    data.partner_id.push_back(fields[21]);
    data.user_id.push_back(fields[22]);
  }

  return data;
}
