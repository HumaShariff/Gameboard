/* Path
 *
 * Desc:
 *  This program generates a Path puzzle. The board is ROWS x COLUMNS (5x4),
 * and every round the player chooses a source point and a target point
 * (totally four numbers), making the given button to be moved to the target
 * position (if possible). The game checks if the user-given move can be made.
 *  At start all green buttons are on the top row, and all red buttons are on
 * the bottom row. Game will end when all green buttons have been moved to the
 * bottom row, and all red buttons to the top row. It is not allowed to move a
 * button over another button.
 *  When printing the game board, green button is represented by 'G', red
 * button by 'R', empty hole by 'o', and unused position by empty space.
 *
 * Program author ( Fill with your own info )
 * Name: Muneeb Ulla Shariff
 * Student number: 153418882
 * UserID: drv565@tuni.fi ( Necessary due to gitlab folder naming. )
 * E-Mail: muneeb.shariff@tuni.fi
 * Feedback language (fi/en): en
 *
 * Program author ( Fill with your own info )
 * Name: Huma Fatima Azmi Shaikh
 * Student number: 152757243
 * UserID: nsv323 ( Necessary due to gitlab folder naming. )
 * E-Mail: humafatimaazmi.shaikh@tuni.fi
 * Feedback language (fi/en): en
 *
 * Notes about the program and it's implementation:
 *
 * */


#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <set>

// Gameboard size
const unsigned int ROWS = 5;
const unsigned int COLUMNS = 4;

struct Location
{
    unsigned int x;
    unsigned int y;
    bool operator==(const Location& rhs) const
    {
        return x == rhs.x and y == rhs.y;
    }
    bool operator<(const Location& rhs) const
    {
        return (x < rhs.x) or (x == rhs.x and y < rhs.y);
    }
};

enum ValidationResult : bool
{
    INVALID = false,
    VALID = true
};

using BoardType = std::vector<std::vector<std::string>>;

class GameBoard
{
public:
    // Constructor
    GameBoard();

    // Destructor
    virtual ~GameBoard();

    // Fill the gameboard initially: all green buttons are put on the top row
    // and all red buttons on the bottom rows, other locations are nullptrs.
    void initialFill();

    // Print the gameboard.
    void print() const;

    // Return true, if the game is over, i.e. if all red buttons are on the
    // top row and all green buttons are on the bottom row.
    bool isGameOver() const;

    // Check the validity of given locations. To be valid, a location must be
    // inside the gameboard,
    // it must not be an unused location, and
    // the start must have a button, and
    // the destination must not have a button.
    // (Implicitly also check that p1 and p2 are not the same points.)
    // Returns true, if both the given locations are valid.
    bool isValidLocations(const Location& start,
                          const Location& destination) const;

    // If possible, move a button from the start location to the destination
    // one. A move may consists of horizontal and vertical steps.
    // Return true, if move is possible, i.e. if there is a path between
    // the given locations.
    bool move(const Location& start, const Location& destination);

    // This function will convert the current state of the game board into
    // a human-readable string. It can be used to visualize the current state
    // of the board, and is typically useful for debugging, testing, or displaying
    // the board's state to the user.
    std::string toString() const;

    // This function takes a reference to a BoardType
    // (which is the type of the game board, typically a 2D vector) and
    // updates the current board state with the provided one.
    // This is useful for testing purposes or for setting up the board
    // with a specific configuration. This function modifies the current state
    // of the game board (*board), and that's why it doesn't return anything.
    void injectState(BoardType& b);

private:
    // Shared pointer to the game board, a 2D vector of strings
    // The board holds the current state of the game. It is a
    // 2D grid where each cell can represent different game pieces.
    std::shared_ptr<BoardType> board;

    // Adds the column headers to the board string.
    // This includes numbering for better readability.
    void addBoardHeader(std::ostringstream& boardStr) const;

    // Adds the board rows with row numbers and content.
    // Iterates through the board and formats each row.
    void addBoardRows(std::ostringstream& boardStr) const;

    // Checks if a horizontal path from start to end is clear
    // This function checks if there are no obstacles (game pieces)
    // between the start and end points along the same row.
    bool isPathClearHorizontal(const Location& start, const Location& end);

    // Checks if a vertical path from start to end is clear
    // This function ensures there are no obstacles (game pieces)
    // between the start and end points along the same column.
    bool isPathClearVertical(const Location& start, const Location& end);

    // Checks if the given location is outside the board
    // boundaries. If the row or column exceeds limits,
    // it returns false, preventing out-of-bounds access.
    bool isOutsideBoard(const Location& loc) const;

    // Determines if the given location is invalid.
    // A location is invalid if it contains an empty
    // space, ensuring only valid moves are considered.
    bool isInvalidLocation(const Location& loc) const;

    // Checks if the given location contains a valid button.
    // A valid button must not be empty or marked as "o".
    // Ensures that only playable buttons are selected.
    bool isValidButton(const Location& loc) const;

    // Checks if the destination is valid for movement.
    // The destination must be an empty space "o".
    // Ensures moves are only made to open positions.
    bool isValidDestination(const Location& loc) const;

};


#endif // GAMEBOARD_HH
