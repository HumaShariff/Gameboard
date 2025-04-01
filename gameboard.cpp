/*
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

#include "gameboard.hh"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GameBoard::GameBoard()
{
    // Define the board using a 2D vector
    board = std::make_shared<BoardType>(ROWS, std::vector<std::string>(COLUMNS, " "));
}

GameBoard::~GameBoard()
{

}

void GameBoard::initialFill()
{
    *board = {
        {"G", "G", "G", "G"},
        {" ", "o", " ", " "},
        {" ", "o", "o", " "},
        {" ", "o", " ", " "},
        {"R", "R", "R", "R"}
    };
}

void GameBoard::print() const
{
    std::cout << toString();
}

std::string GameBoard::toString() const
{

    std::ostringstream boardStr;

    boardStr << "===============\n";
    addBoardHeader(boardStr);
    addBoardRows(boardStr);
    boardStr << "===============\n";

    return boardStr.str();
}

void GameBoard::addBoardHeader(std::ostringstream& boardStr) const
{
    boardStr << "|   | ";

    // Add column headers
    for (size_t c = 1; c <= COLUMNS; ++c) {
        boardStr << c << " ";
    }
    boardStr << "|\n";
    boardStr << "---------------\n";  // Separator after the header
}

void GameBoard::addBoardRows(std::ostringstream& boardStr) const
{
    for (size_t r = 0; r < ROWS; ++r) {
        boardStr << "| ";

        // Add row number
        boardStr << r + 1 << " | ";

        // Add each column's value in the row
        for (size_t c = 0; c < COLUMNS; ++c) {
            boardStr << (*board)[r][c] << " ";
        }
        boardStr << "|\n";
    }
}

void GameBoard::injectState(BoardType &b)
{

    for (size_t r = 0; r < ROWS; ++r) {
        for (size_t c = 0; c < COLUMNS; ++c) {
            (*board)[r][c] = b[r][c];
        }
    }
}

bool GameBoard::isOutsideBoard(const Location& loc) const {
    return (loc.y >= ROWS || loc.x >= COLUMNS);
}

bool GameBoard::isInvalidLocation(const Location& loc) const {
    return ((*board)[loc.y][loc.x] == " ");
}

bool GameBoard::isValidButton(const Location& loc) const {
    return ((*board)[loc.y][loc.x] != " " && (*board)[loc.y][loc.x] != "o");
}

bool GameBoard::isValidDestination(const Location& loc) const {
    return ((*board)[loc.y][loc.x] == "o");
}

bool GameBoard::isValidLocations(const Location &start, const Location &destination) const
{

    // if locations are same
    if(start == destination) return false;

    // Check if either location is outside the board
    if (isOutsideBoard(start) || isOutsideBoard(destination)) {
        return false;
    }

    // Check if either location is invalid
    if (isInvalidLocation(start) || isInvalidLocation(destination)) {
        return false;
    }

    // Ensure start is a valid button
    if (!isValidButton(start)) {
        return false;
    }

    // Ensure destination is an empty space
    if (!isValidDestination(destination)) {
        return false;
    }

    return true;

}

bool GameBoard::isGameOver() const
{
    BoardType gameOveState;
    gameOveState = BoardType(ROWS, std::vector<std::string>(COLUMNS, " "));
    gameOveState = {
        {"R", "R", "R", "R"},
        {" ", "o", " ", " "},
        {" ", "o", "o", " "},
        {" ", "o", " ", " "},
        {"G", "G", "G", "G"}
    };

    // can optimze to check only the first and last row to check
    // because there is no way we can make other moves
    for (size_t r = 0; r < ROWS; ++r) {
        for (size_t c = 0; c < COLUMNS; ++c) {
            if((*board)[r][c] != gameOveState[r][c]) {
                return false;
            }
        }
    }

    return true;
}

bool GameBoard::move(const Location &start, const Location &destination)
{
    const int CROSS_POINT_COLUMN = 1;

    // Step 1: Check if there is a horizontal path from start(x,y) to (x,2)
    if (!isPathClearHorizontal(start, {CROSS_POINT_COLUMN, start.y})) {
        return false;  // If the path is not clear, return false
    }

    // Step 2: Check if there is a horizontal path from destination(x,y) to (x,2)
    if (!isPathClearHorizontal(destination, {CROSS_POINT_COLUMN, destination.y})) {
        return false;  // If the path is not clear, return false
    }

    // Step 3: Check if there is a vertical path from the start row to the destination row at column 2
    if (!isPathClearVertical({CROSS_POINT_COLUMN, start.y}, {1, destination.y})) {
        return false;  // If the vertical path is not clear, return false
    }

    // If all checks pass, return true
    (*board)[destination.y][destination.x] = (*board)[start.y][start.x];
    (*board)[start.y][start.x] = "o";
    return true;
}

bool GameBoard::isPathClearHorizontal(const Location& start, const Location& end) {
    // No moment needed
    if (start == end) return true;

    // Ensure we always move from left to right
    if (start.x < end.x) {
        // Move from left to right
        for (unsigned int x = start.x + 1; x <= end.x; ++x) {
            if ((*board)[start.y][x] != "o") return false;
        }
    } else {
        // Move from right to left
        for (int x = start.x - 1; x >= (int)end.x; --x) {
            if ((*board)[start.y][x] != "o") return false;
        }
    }
    return true;

}

bool GameBoard::isPathClearVertical(const Location& start, const Location& end) {
    // No movement needed
    if (start == end) return true;

    // Ensure we always move from top to bottom
    if (start.y < end.y) {
        // Move from top to bottom
        for (unsigned int y = start.y + 1; y <= end.y; ++y) {
            if ((*board)[y][start.x] != "o") return false;
        }
    } else {
        // Move from bottom to top
        for (int y = start.y - 1; y >= (int)end.y; --y) {
            if ((*board)[y][start.x] != "o") return false;
        }
    }
    return true;
}
