#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

int SIZE;
int score = 0;
int highScore = 0;
vector<vector<int>> board;

// Helper Functions
void reverseRow(int row)
{
    for (int col = 0; col < SIZE / 2; col++)
    {
        swap(board[row][col], board[row][SIZE - 1 - col]);
    }
}

void transposeBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i + 1; j < SIZE; j++)
        {
            swap(board[i][j], board[j][i]);
        }
    }
}

void introduction()
{
    cout << "=============================" << endl;
    cout << "        2048 Game           " << endl;
    cout << "=============================" << endl;
    cout << "Use W (Up), A (Left), S (Down), D (Right) to move tiles." << endl;
    cout << "Combine tiles with the same number to reach 2048!" << endl;
    cout << "Press Q to quit the game." << endl;
    cout << "Press R to restart the game." << endl;
    cout << "=============================" << endl;
    cout << endl;
}

// Main Game Functions
void initializeBoard(int size)
{

    SIZE = size;
    board.assign(SIZE, vector<int>(SIZE, 0));
    // set everything to zero
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }

    int x1 = rand() % SIZE;
    int y1 = rand() % SIZE;
    board[x1][y1] = (rand() % 2 + 1) * 2; // place first tile (2 or 4)

    int x2, y2;
    do
    {
        x2 = rand() % SIZE;
        y2 = rand() % SIZE;
    } while (x1 == x2 && y1 == y2);

    board[x2][y2] = (rand() % 2 + 1) * 2; // place second tile (2 or 4)
}

void printBoard()
{
    system("clear");
    std::
            cout
        << "Score: " << score << "  High Score: " << highScore << endl;
    for (int i = 0; i < SIZE; i++)
        std::cout << "+-----";
    std::cout << "+" << std::endl;

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            std::cout << "|";
            if (board[row][col] == 0)
            {
                std::cout << "     ";
            }
            else
            {
                std::string val = std::to_string(board[row][col]);
                int padding = 5 - val.size();
                int leftPad = padding / 2;
                int rightPad = padding - leftPad;
                std::cout << std::string(leftPad, ' ')
                          << val
                          << std::string(rightPad, ' ');
            }
        }
        std::cout << "|" << std::endl;

        // print border again
        for (int i = 0; i < SIZE; i++)
            std::cout << "+-----";
        std::cout << "+" << std::endl;
    }
}

void addRandomTile()
{
    vector<pair<int, int>> emptyCells;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
                emptyCells.push_back({i, j});
        }
    }

    if (emptyCells.empty())
        return;

    int idx = rand() % emptyCells.size();
    int x = emptyCells[idx].first;
    int y = emptyCells[idx].second;
    board[x][y] = (rand() % 2 + 1) * 2; // place new tile (2 or 4)
}

bool moveLeft()
{
    bool moved = false;

    for (int row = 0; row < SIZE; row++)
    {
        // Slide non-zero tiles to the left
        vector<int> newRow;

        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] != 0)
                newRow.push_back(board[row][col]);
        }

        while (newRow.size() < SIZE)
            newRow.push_back(0);

        // Merge tiles
        for (int col = 0; col < SIZE - 1; col++)
        {
            if (newRow[col] != 0 && newRow[col] == newRow[col + 1])
            {
                newRow[col] *= 2;
                score += newRow[col];
                newRow[col + 1] = 0;
                moved = true;
            }
        }

        // Slide again after merging
        vector<int> finalRow;
        for (int col = 0; col < SIZE; col++)
        {
            if (newRow[col] != 0)
                finalRow.push_back(newRow[col]);
        }

        while (finalRow.size() < SIZE)
            finalRow.push_back(0);

        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] != finalRow[col])
            {
                moved = true;
                board[row][col] = finalRow[col];
            }
        }
    }

    return moved;
}
bool moveRight()
{
    for (int row = 0; row < SIZE; row++)
        reverseRow(row);

    bool moved = moveLeft();

    for (int row = 0; row < SIZE; row++)
        reverseRow(row);

    return moved;
}
bool moveUp()
{
    transposeBoard();
    bool moved = moveLeft();
    transposeBoard();
    return moved;
}
bool moveDown()
{
    transposeBoard();
    for (int row = 0; row < SIZE; row++)
        reverseRow(row);
    bool moved = moveLeft();
    for (int row = 0; row < SIZE; row++)
        reverseRow(row);
    transposeBoard();
    return moved;
}
bool canMove()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            // if there is an empty space
            if (board[row][col] == 0)
                return true;

            // check right
            if (col < SIZE - 1 && board[row][col] == board[row][col + 1])
                return true;
            // check down
            if (row < SIZE - 1 && board[row][col] == board[row + 1][col])
                return true;
        }
    }
    return false;
}

int main()
{
    srand(time(0));

    introduction();

    int chosenSize;
    cout << "Enter board size (e.g., 4 for 4x4): ";
    cin >> chosenSize;
    while (chosenSize < 2)
    {
        cout << "Invalid size! Please enter a size of 2 or greater: ";
        cin >> chosenSize;
    }

    initializeBoard(chosenSize);

    char move;
    while (true)
    {
        printBoard();

        // Game over check
        if (!canMove())
        {
            cout << "Game Over!" << endl;
            cout << "Final Score: " << score << endl;

            if (score > highScore)
            {
                highScore = score;
                cout << "New High Score: " << highScore << endl;
            }

            cout << "Press R to Restart or Q to Quit: ";
            cin >> move;

            if (toupper(move) == 'R')
            {
                score = 0;
                introduction();
                initializeBoard(chosenSize);
                continue;
            }
            else if (toupper(move) == 'Q')
            {
                cout << "Thanks for playing!" << endl;
                break;
            }
            else
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }

        // Normal move
        cout << "Move (W/A/S/D, Q=Quit, R=Restart): ";
        cin >> move;

        if (toupper(move) == 'Q')
        {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else if (toupper(move) == 'R')
        {
            score = 0;
            introduction();
            initializeBoard(chosenSize);
            continue;
        }

        bool moved = false;
        switch (toupper(move))
        {
        case 'W':
            moved = moveUp();
            break;
        case 'A':
            moved = moveLeft();
            break;
        case 'S':
            moved = moveDown();
            break;
        case 'D':
            moved = moveRight();
            break;
        default:
            cout << "Invalid move! Use W/A/S/D." << endl;
            continue;
        }

        if (moved)
            addRandomTile();
    }

    return 0;
}
