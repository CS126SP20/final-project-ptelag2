//
// Created by Praval Telagi on 4/21/20.
//

#include <sqlite_modern_cpp.h>
#include <mylibrary/scores.h>

namespace myapp {

void SQL_Leaderboard::InsertScoreToLeaderboard(const int score) {
  db_ << "insert into leaderboard (name, score) values (?,?)"
      << "TEST NAME"
      << score;
}

SQL_Leaderboard::SQL_Leaderboard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

}