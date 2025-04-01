# Game Program Overview

This program simulates a board game where players move pieces on a 2D grid. The user provides start and destination points for a move, and the game ensures that only valid moves are made. The game ends when the predefined "game over" state is reached, or the user opts to quit.

## Program Author Information

**Author 1:**
- **Name:** Muneeb Ulla Shariff
- **Email:** muneeb.shariff@tuni.fi

**Author 2:**
- **Name:** Huma Fatima Azmi Shaikh
- **Email:** humafatimaazmi.shaikh@tuni.fi

## Acknowledgments

The base structure and template of this program were provided as part of the course. The additional functionalities, such as move validation, game logic, and input handling, are my own contributions.

## Key Features

- **Initial Board Setup:** The game starts with a predefined board configuration.
- **User Input:** Users input start and destination points, or quit with 'q'.
- **Move Validation:** The program checks for valid moves and updates the board accordingly.
- **Game Over Detection:** The game ends when a specific condition is met or the user quits.
- **Move Count:** Tracks and displays the number of moves made.

## Constants

- **`INPUT_TEXT`**: Prompts for user input.
- **`INVALID_POINT`**: Displays when an invalid move is entered.
- **`CANNOT_MOVE`**: Informs when a move isn't possible.
- **`GAME_OVER`**: Displayed when the game finishes.
- **`MOVES_MADE`**: Shows the number of moves.

## Main Logic

1. **Initialization:** The game board is filled with an initial setup.
2. **Game Loop:** The program continuously accepts user input, processes valid moves, and updates the board. Invalid moves prompt an error message.
3. **Game Over or Quit:** The game ends when the winning condition is met or when the user decides to quit.

## Unit Testing

The project includes a comprehensive suite of unit tests written using the **Qt Test** framework. These tests verify the correctness of the game's behavior under different scenarios.

### Test Coverage

The unit tests cover several important areas:

#### 1. **Initial Board Setup**
- Ensures that the game board is initialized correctly.
- Tests that the initial state of the board matches the expected configuration.

#### 2. **Game Over Detection**
- Verifies that the game correctly identifies when a game-over condition is met.
- Tests various end-game scenarios.

#### 3. **Valid and Invalid Moves**
- Tests for valid and invalid moves based on game rules.
- Includes tests for horizontal, vertical, and special movement patterns.
- Checks edge cases like jumping over obstacles or moving outside allowed boundaries.

#### 4. **Start and Destination Validity**
- Validates that the starting and destination points are correct.
- Ensures that the start location has a button and the destination is empty.
- Prevents invalid moves like moving from or to blocked spaces.

#### 5. **Edge Case Testing**
- Includes tests for boundary conditions and other edge cases to make sure the game handles unexpected scenarios correctly.



Compile and run the program:

 ```sh
g++ -o game gameboard.cpp main.cpp
./game




