/* tst_pathtest
 * Desc:
 *  This is used for writing unit tests for Path project
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

#include <QtTest>
#include "../gameboard.hh"
#include <iostream>
#include <memory>

// add necessary includes here


class pathtest : public QObject
{
    Q_OBJECT

public:
    pathtest();
    ~pathtest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void test_initialBoardPrint();
    void test_isValidInputAtInitial();
    void test_isValidInputAtInitial_data();
    void test_injectState();
    void test_gameOverTrue();
    void test_gameOverFalse();
    void test_invalidMoves_data();
    void test_invalidMoves();
    void test_validMoves_data();
    void test_validMoves();
    void test_allMoves();
    void test_oneErrorScenario();

private:
    std::shared_ptr<GameBoard> puzzle_;

};

pathtest::pathtest()
{

}

pathtest::~pathtest()
{

}

void pathtest::initTestCase()
{

}

void pathtest::cleanupTestCase()
{

}

void pathtest::init()
{
    puzzle_.reset();
    puzzle_ = std::make_shared<GameBoard>();
}

void pathtest::test_initialBoardPrint()
{
    std::string expectedStr, actualStr;

    expectedStr =R"(===============
|   | 1 2 3 4 |
---------------
| 1 | G G G G |
| 2 |   o     |
| 3 |   o o   |
| 4 |   o     |
| 5 | R R R R |
===============
)";
    puzzle_->initialFill();
    actualStr = puzzle_->toString();

    QCOMPARE(QString::fromStdString(actualStr), QString::fromStdString(expectedStr));

}

void pathtest::test_injectState()
{
    // Inject state
    BoardType b;
    b = BoardType(ROWS, std::vector<std::string>(COLUMNS, " "));
    b = {
        {"G", "R", "G", "G"},
        {" ", "o", " ", " "},
        {" ", "o", "o", " "},
        {" ", "o", " ", " "},
        {"R", "G", "R", "R"}
    };
    puzzle_->injectState(b);

    //std::cout << puzzle_->toString();
    QCOMPARE(1, 1);
}

void pathtest::test_gameOverTrue()
{
    // Inject state
    BoardType b;
    b = BoardType(ROWS, std::vector<std::string>(COLUMNS, " "));
    b = {
        {"R", "R", "R", "R"},
        {" ", "o", " ", " "},
        {" ", "o", "o", " "},
        {" ", "o", " ", " "},
        {"G", "G", "G", "G"}
    };
    puzzle_->injectState(b);

    bool expected, actual;
    expected = true;

    actual = puzzle_->isGameOver();

    QCOMPARE(actual, expected);
}

void pathtest::test_gameOverFalse()
{
    // Inject state
    BoardType b;
    b = BoardType(ROWS, std::vector<std::string>(COLUMNS, " "));
    b = {
        {"R", "R", "R", "R"},
        {" ", "o", " ", " "},
        {" ", "o", "G", " "},
        {" ", "o", " ", " "},
        {"G", "o", "G", "G"}
    };
    puzzle_->injectState(b);

    bool actual;
    actual = puzzle_->isGameOver();

    QCOMPARE(actual, false);
}

void pathtest::test_invalidMoves()
{

    QFETCH(BoardType, board);
    QFETCH(Location, p1);
    QFETCH(Location, p2);
    QFETCH(bool, expected);
    QFETCH(QString, message);

    puzzle_->injectState(board);
    bool actual = puzzle_->move(p1, p2);
    QVERIFY2(actual == expected, message.toUtf8().constData());

}

void pathtest::test_invalidMoves_data() {
    QTest::addColumn<BoardType>("board");
    QTest::addColumn<Location>("p1");
    QTest::addColumn<Location>("p2");
    QTest::addColumn<bool>("expected");
    QTest::addColumn<QString>("message");

    QTest::newRow("HorizontalRightFalse")
        << BoardType({
            {"G", "G", "G", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "o", " "},
            {" ", "o", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{1 - 1, 1 - 1}
        << Location{3 - 1, 3 - 1}
        << false
        << "HorizontalRightFalse2";

    QTest::newRow("HorizontalRightFalse2")
        << BoardType({
            {"G", "o", "G", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "o", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{4 - 1, 1 - 1}
        << Location{2 - 1, 1 - 1}
        << false
        << "HorizontalRightFalse2";

    QTest::newRow("VerticalUpFalse")
        << BoardType({
            {"G", "G", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{2 - 1, 4 - 1}
        << Location{2 - 1, 1 - 1}
        << false
        << "VerticalUpFalse";

    QTest::newRow("VerticalDownFalse")
        << BoardType({
            {"G", "G", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{2 - 1, 1 - 1}
        << Location{2 - 1, 4 - 1}
        << false
        << "VerticalDownFalse";
}

void pathtest::test_validMoves_data() {
    QTest::addColumn<BoardType>("board");
    QTest::addColumn<Location>("p1");
    QTest::addColumn<Location>("p2");
    QTest::addColumn<bool>("expected");
    QTest::addColumn<QString>("message");

    QTest::newRow("HorizontalRightTrue")
        << BoardType({
            {"G", "o", "G", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "o", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{1 - 1, 1 - 1}
        << Location{2 - 1, 1 - 1}
        << true
        << "HorizontalRightTrue";

    QTest::newRow("HorizontalLeftTrue")
        << BoardType({
            {"G", "o", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "o", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{4 - 1, 1 - 1}
        << Location{2 - 1, 1 - 1}
        << true
        << "HorizontalLeftTrue";

    QTest::newRow("VerticalUpTrue")
        << BoardType({
            {"G", "o", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{2 - 1, 4 - 1}
        << Location{2 - 1, 1 - 1}
        << true
        << "VerticalUpTrue";

    QTest::newRow("VerticalDownTrue")
        << BoardType({
            {"G", "G", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{2 - 1, 1 - 1}
        << Location{2 - 1, 3 - 1}
        << true
        << "VerticalDownTrue";

    QTest::newRow("LMovementLeftDownTrue")
        << BoardType({
            {"G", "o", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{4 - 1, 1 - 1}
        << Location{2 - 1, 3 - 1}
        << true
        << "LMovementLeftDownTrue";

    QTest::newRow("LMovementUpRightTrue")
        << BoardType({
            {"G", "o", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "G", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{2 - 1, 4 - 1}
        << Location{3 - 1, 1 - 1}
        << true
        << "LMovementUpRightTrue";

    QTest::newRow("ZMovementDownTrue")
        << BoardType({
            {"G", "o", "o", "G"},
            {" ", "o", " ", " "},
            {" ", "o", "o", " "},
            {" ", "G", " ", " "},
            {"R", "R", "R", "R"}
        })
        << Location{1 - 1, 1 - 1}
        << Location{3 - 1, 3 - 1}
        << true
        << "ZMovementDownTrue";

    QTest::newRow("ZMovementReplicateTrue")
        << BoardType({
            {"R", "R", "G", "G"},
            {" ", "R", " ", " "},
            {" ", "o", "G", " "},
            {" ", "o", " ", " "},
            {"R", "o", "o", "G"}
        })
        << Location{3 - 1, 3 - 1}
        << Location{3 - 1, 5 - 1}
        << true
        << "ZMovementReplicateTrue";
}

void pathtest::test_validMoves() {
    QFETCH(BoardType, board);
    QFETCH(Location, p1);
    QFETCH(Location, p2);
    QFETCH(bool, expected);
    QFETCH(QString, message);

    puzzle_->injectState(board);
    bool actual = puzzle_->move(p1, p2);
    QVERIFY2(actual == expected, message.toUtf8().constData());
}

void pathtest::test_allMoves()
{
    puzzle_->initialFill();
    Location p1, p2;

    const std::vector<Location> seriesOfMoves = {
        {2, 1}, {3, 3},
        {2, 5}, {2, 1},
        {1, 5}, {2, 2},
        {3, 3}, {1, 5},
        {2, 2}, {2, 5},
        {2, 1}, {3, 3},
        {1, 1}, {2, 4},
        {3, 3}, {1, 1},
        {2, 4}, {3, 3},
        {2, 5}, {2, 1},

        {3, 5}, {2, 2},
        {4, 5}, {2, 3},
        {1, 5}, {4, 5},
        {2, 3}, {1, 5},
        {3, 3}, {3, 5},
        {2, 2}, {2, 5},
        {2, 1}, {2, 4},
        {3, 1}, {3, 3},
        {4, 1}, {2, 3},
        {1, 1}, {4, 1},

        {2, 3}, {1, 1},
        {2, 4}, {3, 1},
        {2, 5}, {2, 1},
        {1, 5}, {2, 2},
        {3, 3}, {1, 5},
        {2, 2}, {2, 5},
        {2, 1}, {2, 4},
        {1, 1}, {3, 3},
        {2, 4}, {1, 1},
        {2, 5}, {2, 1},

        {3, 3}, {2, 5}
    };

    bool actual;
    for (size_t i = 0; i < seriesOfMoves.size(); i += 2) {
        if (i + 1 < seriesOfMoves.size()) {
            p1 = seriesOfMoves[i];     // Assign first cross point
            p2 = seriesOfMoves[i + 1]; // Assign second cross point

            p1.x -= 1; p1.y -= 1;
            p2.x -= 1; p2.y -= 1;

            actual = puzzle_->move(p1,p2);

        }
    }

    actual = puzzle_->isGameOver();
    QCOMPARE(actual, true);

}

void pathtest::test_oneErrorScenario()
{
    Location p1, p2;
    bool expected, actual;
    BoardType b;
    b = BoardType(ROWS, std::vector<std::string>(COLUMNS, " "));

    b = {
        {"G", "o", "G", "G"},
        {" ", "o", " ", " "},
        {" ", "o", "o", " "},
        {" ", "G", " ", " "},
        {"R", "R", "R", "R"}
    };
    puzzle_->injectState(b);

    p1 = {2-1, 5-1};
    p2 = {2-1, 1-1};
    expected = false;
    actual = puzzle_->move(p1,p2);
    QVERIFY2(actual==expected, "ErrorPathJumpingOver");

}

void pathtest::test_isValidInputAtInitial_data()
{
    QTest::addColumn<unsigned int>("sX");
    QTest::addColumn<unsigned int>("sY");
    QTest::addColumn<unsigned int>("dX");
    QTest::addColumn<unsigned int>("dY");
    QTest::addColumn<ValidationResult>("expectedStatus");

    QTest::newRow("invalid points")<< 1u << 2u << 3u << 2u << INVALID;
    QTest::newRow("invalid points2")<< 1u << 3u << 3u << 4u << INVALID;
    QTest::newRow("invalid points3")<< 4u << 2u << 3u << 3u << INVALID;
    QTest::newRow("invalid points4")<< 2u << 1u << 4u << 2u << INVALID;
    QTest::newRow("invalid points5")<< 1u << 2u << 1u << 2u << INVALID;

    QTest::newRow("one valid and other invalid")<< 3u << 1u << 4u << 4u << INVALID;

    QTest::newRow("valid points")<< 2u << 1u << 2u << 4u << VALID;
    QTest::newRow("valid points2")<< 4u << 5u << 3u << 3u << VALID;

    QTest::newRow("Start and destination should not be same")<< 2u << 1u << 2u << 1u << INVALID;
    QTest::newRow("Outside of game board")<< 6u << 6u << 7u << 7u << INVALID;
    QTest::newRow("Start should be a button")<< 2u << 4u << 2u << 2u << INVALID;
    QTest::newRow("Destination must be empty")<< 2u << 1u << 2u << 5u << INVALID;

}

void pathtest::test_isValidInputAtInitial()
{

    // Check the validity of given locations. To be valid, a location must be
    // inside the gameboard,
    // it must not be an unused location, and
    // the start must have a button, and
    // the destination must not have a button.
    // (Implicitly also check that p1 and p2 are not the same points.)
    // Returns true, if both the given locations are valid.

    // ASSUMPTION: the main.cpp already checks for co-ordinates to be numbers
    bool actualIsValid;
    Location p1, p2;

    QFETCH(unsigned int, sX);
    QFETCH(unsigned int, sY);
    QFETCH(unsigned int, dX);
    QFETCH(unsigned int, dY);
    QFETCH(ValidationResult, expectedStatus);

    p1 = {sX-1, sY-1};
    p2 = {dX-1, dY-1};

    puzzle_->initialFill();
    actualIsValid = puzzle_->isValidLocations(p1, p2);
    QCOMPARE(actualIsValid, expectedStatus);

}

QTEST_APPLESS_MAIN(pathtest)

#include "tst_pathtest.moc"
