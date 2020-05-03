//
// Created by Praval Telagi on 4/21/20.
//

#ifndef FINALPROJECT_SCORES_H
#define FINALPROJECT_SCORES_H

#include <sqlite_modern_cpp.h>

#include <string>
using std::string;
using std::vector;
namespace myapp {

class SQL_Leaderboard {

 public:
  //SQL_Leaderboard();
  SQL_Leaderboard(const std::string& db_path);
  void InsertScoreToLeaderboard(const int score, const string mode);
  void InsertScoreToEasyLeaderboard(const int score);
  vector<int> GetHighestScores(const int limit, const string mode);

 private:
  sqlite::database db_;
};

}



#endif  // FINALPROJECT_SCORES_H
