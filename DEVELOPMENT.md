# Development

---

- **4/19/20** Created an outline of what files my app needs
    - Added Floor, Engine, and Block files
- **4/20/20** Created the block that the user will control
    - Drew the block that the user will control on the screen
- **4/21/20** Added the SQL interface that I will use as my external library
    - Added the SQL interface that will be used to view the scores of the player
    - Added Score class to add scores into the database
- **4/23/20** Added Animation to the floors
    - Floors now slowly move up the screen
    - Floors also regenerate after if there are less than a set number
    - Moved Block data out of engine and into its own class
- **4/25/20** Added Automatic Gravity to the game
    - The block now automatically falls whenever it is over an open spot in the floor
    - Fixed issue with gaps in the floor not generating to both ends
- **4/28/20** Ability to Change Game Mode
    - Added logic for changing game modes
    - Added a speed increase after a set amount of time