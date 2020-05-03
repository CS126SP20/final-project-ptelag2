//
// Created by Praval Telagi on 4/21/20.
//

#include <mylibrary/scores.h>
#include <sqlite_modern_cpp.h>

#include <string>
using std::string;

namespace myapp {

void SQL_Leaderboard::InsertScoreToLeaderboard(const int score, const string mode) {
  /*string database_information = "insert into ";
  database_information.append(mode);
  database_information.append("_mode_leaderboard (score) values (?)");
  db_ << database_information
      << score;*/

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

void SQL_Leaderboard::InsertScoreToEasyLeaderboard(const int score) {
  db_ << "insert into easy_mode_leaderboard (score) values (?)"
      << score;
}

SQL_Leaderboard::SQL_Leaderboard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists easy_mode_leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

}