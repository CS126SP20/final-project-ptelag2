//
// Created by Praval Telagi on 4/21/20.
//

#include <mylibrary/scores.h>
#include <sqlite_modern_cpp.h>

#include <string>
using std::string;

namespace myapp {

void SQL_Leaderboard::InsertScoreToLeaderboard(const int score, const string mode) {
  db_ << "insert into " + mode + "_mode_leaderboard (score) values (?)"
      << score;
}

vector<int> SQL_Leaderboard::GetHighestScores(const int limit, const string mode) {
  auto rows = db_ << "select score from " + mode + "_mode_leaderboard order by score"
                     " desc Limit ?"
                  << limit;

  vector<int> top_scores;
  for (auto& row : rows) {
    int score;
    row >> score;
    top_scores.push_back(score);
  }
  return top_scores;
}

SQL_Leaderboard::SQL_Leaderboard(const std::string& db_path) : db_{db_path} {
  //Creates Easy mode leaderboard
  db_ << "CREATE TABLE if not exists easy_mode_leaderboard (\n"
         "  score INTEGER NOT NULL\n"
         ");";

  //Creates Medium mode leaderboard
  db_ << "CREATE TABLE if not exists medium_mode_leaderboard (\n"
         "  score INTEGER NOT NULL\n"
         ");";

  //Creates Hard mode leaderboard
  db_ << "CREATE TABLE if not exists hard_mode_leaderboard (\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

}