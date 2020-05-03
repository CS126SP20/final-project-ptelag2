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
  /**
   * Constructor for the SQL_Leaderboard
   * Creates the necessary tables if not already created
   * @param db_path Path the the database file
   */
  SQL_Leaderboard(const std::string& db_path);

  /**
   * Inputs a score into the correct leaderboard
   * @param score Score to be inputted
   * @param mode Game Mode to know which leaderboard to input to
   */
  void InsertScoreToLeaderboard(const int score, const string mode);

  /**
   * Gets the Highest scores from the leader board
   * @param limit Amount of scores wanted
   * @param mode Game Mode to get scores from
   * @return A vector with the score in descending order
   */
  vector<int> GetHighestScores(const int limit, const string mode);

 private:
  sqlite::database db_;
};

}



#endif  // FINALPROJECT_SCORES_H
