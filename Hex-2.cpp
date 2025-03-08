#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


#define NR_OF_BOARDS 517
#define NEW_LINE 10
#define MAX_BOARD_SIZE 11
#define MAX_NR_OF_CONNECTIONS 6
#define GRAPH_WIDTH 8
class Board_basics {
public:
    int nr_of_rows = 1;
    int nr_of_pawns_r = 0;
    int nr_of_pawns_b = 0;
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int current_column = -1;
    int current_row = 0;
    bool wiedest_point = false;
    int correction = 0;
    int GetBoardSize() {
        return nr_of_rows / 2 + 1;
    }
    void neighbours(int neighbours[6], int i, int j, char player) {

        int posit = 0;
        if (j - 1 >= 0 && board[i][j - 1] == player) {
            // to the left
            neighbours[posit] = i * GetBoardSize() + j - 1;
            posit++;
        }
        if (j - 1 >= 0 && i - 1 >= 0 && board[i - 1][j - 1] == player) {
            // to the left and up
            neighbours[posit] = (i - 1) * GetBoardSize() + j - 1;
            posit++;
        }
        if (i - 1 >= 0 && board[i - 1][j] == player) {
            //  up
            neighbours[posit] = (i - 1) * GetBoardSize() + j;
            posit++;
        }
        if (j + 1 < GetBoardSize() && board[i][j + 1] == player) {
            // to the right
            neighbours[posit] = i * GetBoardSize() + j + 1;
            posit++;
        }
        if (j + 1 < GetBoardSize() && i + 1 < GetBoardSize() && board[i + 1][j + 1] == player) {
            // to the right And down
            neighbours[posit] = (i + 1) * GetBoardSize() + j + 1;
            posit++;
        }
        if (i + 1 < GetBoardSize() && board[i + 1][j] == player) {
            //  down
            neighbours[posit] = (i + 1) * GetBoardSize() + j;
            posit++;
        }
    }
};

void Reset(Board_basics& basics, int* i) {
    basics.nr_of_rows = 1;
    basics.nr_of_pawns_r = 0;
    basics.nr_of_pawns_b = 0;
    //cout << *i << endl;
    (*i)++;
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            basics.board[i][j] = ' ';
        }
    }
    basics.current_column = -1;
    basics.current_row = 0;
    basics.wiedest_point = false;
    basics.correction = 0;
}

void AddingToTheBoard(Board_basics& basics, string token) {
    if (!basics.wiedest_point)
        basics.board[basics.current_column - basics.current_row][basics.current_row] = token[0];
    else
        basics.board[basics.current_column - basics.current_row + basics.correction][basics.current_row] = token[0];
}

void PrintBoard(Board_basics& basics, int board_size) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            cout << basics.board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void DFS(Board_basics& basics, bool visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int board_size, int start_y, int start_x, char player) {
    visited[start_y][start_x] = true;
    int neighbours[8];
    for (int i = 0; i < 8; i++) {
        neighbours[i] = MAX_BOARD_SIZE * MAX_BOARD_SIZE + MAX_BOARD_SIZE;
    }
    basics.neighbours(neighbours, start_y, start_x, player);
    for (int neighbour : neighbours) {

        if (neighbour == MAX_BOARD_SIZE * MAX_BOARD_SIZE + MAX_BOARD_SIZE) {
            return;
        }
        else {
            int j = neighbour % basics.GetBoardSize();
            int i = (neighbour - j) / basics.GetBoardSize();
            if (!visited[i][j]) {
                DFS(basics, visited, board_size, i, j, player);
            }
        }
    }

}

int IsGameOver(Board_basics& basics, char player) {
    bool visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    for (int i = 0; i < basics.GetBoardSize(); i++) {
        for (int j = 0; j < basics.GetBoardSize(); j++) {
            visited[i][j] = false;
        }
    }

    //for red
    if (player == 0 || player == 'r') {
        for (int start_point = 0; start_point < basics.GetBoardSize(); start_point++) {
            if (basics.board[start_point][0] == 'r') {
                DFS(basics, visited, basics.GetBoardSize(), start_point, 0, 'r');
            }
            for (int ending_point = 0; ending_point < basics.GetBoardSize(); ending_point++) {
                if (visited[ending_point][basics.GetBoardSize() - 1] == true) {
                    //cout << "R" << endl;
                    return 1;
                }

            }
            for (int i = 0; i < basics.GetBoardSize(); i++) {
                for (int j = 0; j < basics.GetBoardSize(); j++) {
                    visited[i][j] = false;
                }
            }
        }
    }

    //for blue
    if (player == 0 || player == 'b') {
        for (int start_point = 0; start_point < basics.GetBoardSize(); start_point++) {
            if (basics.board[0][start_point] == 'b') {
                DFS(basics, visited, basics.GetBoardSize(), 0, start_point, 'b');
            }
            for (int ending_point = 0; ending_point < basics.GetBoardSize(); ending_point++) {
                if (visited[basics.GetBoardSize() - 1][ending_point] == true) {
                    //cout << "R" << endl;
                    return 2;
                }

            }
            for (int i = 0; i < basics.GetBoardSize(); i++) {
                for (int j = 0; j < basics.GetBoardSize(); j++) {
                    visited[i][j] = false;
                }
            }
        }
    }

    return 0;
}

bool IsBoardCorrect(Board_basics basics) {
    //cout << "RED :" << basics.nr_of_pawns_r << endl;
    //cout << "BLUE :" << basics.nr_of_pawns_b << endl;
    if (basics.nr_of_pawns_r - basics.nr_of_pawns_b == 0 || basics.nr_of_pawns_r - basics.nr_of_pawns_b == 1)
        return true;
    return false;
}

bool IsBoardPossible(Board_basics basics) {
    int tmp = IsGameOver(basics, 0);
    char player;
    //checking who won for optimalization and checking if there is correct relation in terams of pawns
    if (tmp != 0) {
        if (tmp == 1) {
            if (!(basics.nr_of_pawns_r - basics.nr_of_pawns_b == 1))
                return false;
            player = 'r';
        }
        else if (tmp == 2) {
            if (!(basics.nr_of_pawns_r - basics.nr_of_pawns_b == 0))
                return false;
            player = 'b';
        }
        //check only for winning player
//if you remove all vertesis and dfs for all cases return true 
        for (int i = 0; i < basics.GetBoardSize(); i++) {
            for (int j = 0; j < basics.GetBoardSize(); j++) {
                if (basics.board[i][j] == player) {
                    basics.board[i][j] = ' ';
                    int won = IsGameOver(basics, player);
                    if (!won) {
                        return true;
                    }
                    basics.board[i][j] = player;
                }
            }
        }
        return false;
    }
    else
        return true;
}

bool AddPawnAndCheckIfWon(Board_basics basics, char player, bool move_twice, bool have_to_win) {
    for (int i = 0; i < basics.GetBoardSize(); i++) {
        for (int j = 0; j < basics.GetBoardSize(); j++) {
            if (basics.board[i][j] == ' ') {
                basics.board[i][j] = player;
                bool won = IsGameOver(basics, player);
                if (won && have_to_win) {
                    if (!move_twice)
                        return true;
                }
                else if (move_twice && have_to_win) {
                    bool won2;
                    won2 = AddPawnAndCheckIfWon(basics, player, false, true);
                    if (won2)
                        return true;
                }
                else if (!have_to_win && !won) {
                    if (move_twice) {
                        bool won2;
                        won2 = AddPawnAndCheckIfWon(basics, player, false, false);
                        if (!won2)
                            return true;
                    }
                    return true; //there exist the spot where you can place it and do not win
                }
                basics.board[i][j] = ' ';
            }
        }
    }
    return false;
}

bool CAN_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT(Board_basics basics, char player) {
    if (!IsBoardCorrect(basics) || IsGameOver(basics, 0)) {
        return false;
    }
    int free_spaces = 0;
    for (int i = 0; i < basics.GetBoardSize(); i++) {
        for (int j = 0; j < basics.GetBoardSize(); j++) {
            if (basics.board[i][j] == ' ')
                free_spaces++;
        }
    }

    char whose_turn;
    if (basics.nr_of_pawns_r - basics.nr_of_pawns_b == 0)
        whose_turn = 'r';
    else
        whose_turn = 'b';
    if (whose_turn == 'r' && player == 'r') {
        if (free_spaces < 3)
            return false;
        // add pawn
        if (AddPawnAndCheckIfWon(basics, 'b', false, false))
            return AddPawnAndCheckIfWon(basics, player, true, true);
        return false;
    }
    else if (whose_turn == 'b' && player == 'r') {
        if (free_spaces < 4)
            return false;
        // add pawn
        if (AddPawnAndCheckIfWon(basics, 'b', true, false))
            return AddPawnAndCheckIfWon(basics, player, true, true);
        return false;
    }
    else if (whose_turn == 'b' && player == 'b') {
        if (free_spaces < 3)
            return false;
        // add pawn
        if (AddPawnAndCheckIfWon(basics, 'r', false, false))
            return AddPawnAndCheckIfWon(basics, player, true, true);
        return false;
    }
    else if (whose_turn == 'r' && player == 'b') {
        if (free_spaces < 4)
            return false;
        // add pawn
        if (AddPawnAndCheckIfWon(basics, 'r ', true, false))
            return AddPawnAndCheckIfWon(basics, player, true, true);
        return false;
    }
    return false;
}

bool CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(Board_basics basics, char player) {

    if (!IsBoardCorrect(basics) || IsGameOver(basics, 0)) {
        return false;
    }
    int free_spaces = 0;
    for (int i = 0; i < basics.GetBoardSize(); i++) {
        for (int j = 0; j < basics.GetBoardSize(); j++) {
            if (basics.board[i][j] == ' ')
                free_spaces++;
        }
    }

    char whose_turn;
    if (basics.nr_of_pawns_r - basics.nr_of_pawns_b == 0)
        whose_turn = 'r';
    else
        whose_turn = 'b';

    if (whose_turn == 'r' && player == 'r') {
        if (free_spaces < 1)
            return false;
        // add pawn
        return AddPawnAndCheckIfWon(basics, player, false, true);
    }
    else if (whose_turn == 'b' && player == 'r') {
        if (free_spaces < 2)
            return false;
        //chceck if there is a place where blu can place pawn and not win
        if (AddPawnAndCheckIfWon(basics, 'b', true, false))
            //add pawn
            return AddPawnAndCheckIfWon(basics, player, false, true);
        return false;
    }
    else if (whose_turn == 'b' && player == 'b') {
        if (free_spaces < 1)
            return false;
        // add pawn
        return AddPawnAndCheckIfWon(basics, player, false, true);
    }
    else if (whose_turn == 'r' && player == 'b') {
        if (free_spaces < 2)
            return false;
        // add pawn
        if (AddPawnAndCheckIfWon(basics, 'r', true, false))
            //add pawn
            return AddPawnAndCheckIfWon(basics, player, false, true);
        return false;
    }
    return false;
}

int main() {
    string token;
    Board_basics basics;

    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            basics.board[i][j] = ' ';
        }
    }
    char current_token;
    int  i = 0;
    int reset = 0;
    while ((current_token = getchar()) != EOF) {

        if (current_token != ' ' && current_token != NEW_LINE) {
            token += current_token;
        }
        else if (current_token == ' ' || current_token == NEW_LINE) {
            if (token == "--<") {
                basics.nr_of_rows++;
                if (!basics.wiedest_point)
                    basics.current_column++;
                else {
                    basics.current_row = basics.nr_of_rows - 1 - basics.current_column;
                    basics.correction = basics.current_row;
                }
            }
            else if (token == "---") {
                if (reset == 2) {
                    Reset(basics, &i);
                    reset = 0;
                }
                reset++;

            }
            else if (token == "<") {
                basics.wiedest_point = true;
                basics.current_column++;
            }
            else if (token == ">-<") {
                basics.current_row++;
            }
            else if (token == "r") {
                AddingToTheBoard(basics, token);
                basics.nr_of_pawns_r++;
            }
            else if (token == "b") {
                AddingToTheBoard(basics, token);
                basics.nr_of_pawns_b++;
            }
            if (token == "BOARD_SIZE") {
                cout << basics.GetBoardSize() << endl << endl;
                //Reset(basics, &i);
            }
            else if (token == "PAWNS_NUMBER") {
                cout << basics.nr_of_pawns_r + basics.nr_of_pawns_b << endl << endl;
                //Reset(basics, &i);
            }
            else if (token == "IS_BOARD_CORRECT") {
                if (IsBoardCorrect(basics))
                    cout << "YES" << endl << endl;
                else
                    cout << "NO" << endl << endl;
                //Reset(basics, &i);
            }
            else if (token == "IS_GAME_OVER") {
                //PrintBoard(basics, basics.GetBoardSize());


                if (IsBoardCorrect(basics)) {
                    int tmp = IsGameOver(basics, 0);
                    if (tmp == 1)
                        cout << "YES RED" << endl << endl;
                    else if (tmp == 2)
                        cout << "YES BLUE" << endl << endl;
                    else
                        cout << "NO" << endl << endl;
                }
                else
                    cout << "NO" << endl << endl;

                //Reset(basics, &i);
            }
            else if (token == "IS_BOARD_POSSIBLE") {
                //PrintBoard(basics, basics.GetBoardSize());
                if (IsBoardCorrect(basics)) {
                    //PrintGraph(basics, graph);
                    int tmp = IsBoardPossible(basics);
                    if (tmp == 1)
                        cout << "YES" << endl << endl;
                    else if (tmp == 2)
                        cout << "YES BLUE" << endl << endl;
                    else
                        cout << "NO" << endl << endl;
                }
                else
                    cout << "NO" << endl << endl;
            }
            else if (token == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
                if (CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(basics, 'r')) {
                    cout << "YES" << endl << endl;
                }
                else
                    cout << "NO" << endl << endl;
            }
            else if (token == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
                if (CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(basics, 'b')) {
                    cout << "YES" << endl << endl;
                }
                else
                    cout << "NO" << endl << endl;
            }
            else if (token == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                if (CAN_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT(basics, 'r')) {
                    cout << "YES" << endl << endl;
                }
                else
                    cout << "NO" << endl << endl;
            }
            else if (token == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                if (CAN_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT(basics, 'b')) {
                    cout << "YES" << endl;
                }
                else
                    cout << "NO" << endl << endl;
            }

            if (current_token == NEW_LINE) {
                basics.current_row = 0;
            }
            token.clear();
        }
    }
    return 0;
}
