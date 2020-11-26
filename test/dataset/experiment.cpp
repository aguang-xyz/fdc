#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

auto out = ofstream("../../dataset.experiment.csv", fstream::out);

vector<string> parse_csv_line(string line) {
  vector<string> ret;
  string acc = "";

  for (int i = 0; i < line.size(); i++) {
    if (line[i] == ',') {
      ret.push_back(acc);
      acc = "";
    } else {
      acc += line[i];
    }
  }

  if (acc.size() > 0) {
    ret.push_back(acc);
  }

  return ret;
}

vector<vector<string>> parse_csv_file(ifstream csv) {
  vector<vector<string>> ret;
  string line;

  for (string line; getline(csv, line);) {
    ret.push_back(parse_csv_line(line));
  }

  return ret;
}

int verify(fds cover, vector<vector<string>> records) {

  for (auto f : cover) {
    
    bool violated = false;

    for (int i = 0; !violated && i < records.size(); i++) {
      for (int j = i + 1; !violated && j < records.size(); j++) {
        
        bool left_same = true;
        for (auto x : f.first) {
          if (records[i][x] != records[j][x]) {
            left_same = false;
          }
        }

        bool right_same = true;
        for (auto x : f.second) {
          if (records[i][x] != records[j][x]) {
            left_same = false;
          }
        }

        if (left_same && !right_same) {
          violated = false;
        }
      }
    }

    if (violated) {
      return violated;
    }
  }

  return false;
}

int verify_1000(fds cover, vector<vector<string>> records) {

  for (int i = 0; i < 999; i++) {
    verify(cover, records);
  }

  return verify(cover, records);
}

int n_attrs(fds cover) {
  int ret = 0;

  for (auto f : cover) {
    ret += f.first.size() + f.second.size();
  }

  return ret;
}

#define record(dataset, name, algo, N, F, G)                                   \
  {                                                                            \
    double t0 = clock();                                                       \
    auto result = algo(N, F);                                                  \
    out << dataset << ","                                                      \
        << name << ","                                                         \
        << (clock() - t0) / CLOCKS_PER_SEC << ","                              \
        << result.size() << ","                                                \
        << n_attrs(result) << ",";                                             \
    double t1 = clock();                                                       \
    auto violated = verify_1000(result, G);                                    \
    out << (clock() - t1) / CLOCKS_PER_SEC << "," << violated << endl;         \
  }

void do_experiment(const string dataset) {

  int N;
  fds F = fds();

  ifstream json = ifstream(dataset + ".json");

  from_json(json, N, F);
  sort(F.begin(), F.end());

  vector<vector<string>> G = parse_csv_file(ifstream(dataset + ".csv"));

  record(dataset, "Non-Redundant", non_redundant, N, F, G);
  record(dataset, "Canonical", canonical, N, F, G);
  record(dataset, "Minimum", minimum, N, F, G);
  record(dataset, "L-Minimum", lminimum, N, F, G);
  record(dataset, "LR-Minimum", lrminimum, N, F, G);
  record(dataset, "Mini", mini, N, F, G);
  record(dataset, "Optimal", optimal, N, F, G);
}

TEST(dataset, experiment) {
  do_experiment("../../dataset/Complete Data/abalone");
}
