#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool check_winner(const string& board, char player) {
    // Rows
    if (board[0] == player && board[1] == player && board[2] == player) return true;
    if (board[3] == player && board[4] == player && board[5] == player) return true;
    if (board[6] == player && board[7] == player && board[8] == player) return true;
    // Columns
    if (board[0] == player && board[3] == player && board[6] == player) return true;
    if (board[1] == player && board[4] == player && board[7] == player) return true;
    if (board[2] == player && board[5] == player && board[8] == player) return true;
    // Diagonals
    if (board[0] == player && board[4] == player && board[8] == player) return true;
    if (board[2] == player && board[4] == player && board[6] == player) return true;
    return false;
}

bool is_board_full(string &board)
{
    for (int i = 0; i < 9; i++)
        if (board[i] == ' ' || board[i] == '.')
            return false;
    return true;
}

int negamax(string &board, char curr, int depth, int alpha, int beta)
{
    char prev = (curr == 'X') ? 'O' : 'X';
    if (check_winner(board, prev))
        return depth - 10;
    if (is_board_full(board))
        return 0;
    int score;
    int best_score = -10000;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ' || board[i] == '.')
        {
            char next = (curr == 'X') ? 'O' : 'X';
            board[i] = curr;
            score = -negamax(board, next, depth + 1, -beta, -alpha);
            board[i] = '.';
            best_score = max(best_score, score);
            alpha = max(alpha, score);
            if (alpha >= beta)
                return alpha;
        }
    }
    return best_score;
}

extern "C" {
    int get_best_move(const char* board_state, char ai_player)
    {
        cout << "the board : " << board_state << endl;
        int best_move = -10000;
        int ans = -1;
        int score = -10000;
    
        char opponent = (ai_player == 'X') ? 'O' : 'X'; 

        string board(board_state, 9);

        for (int i = 0; i < 9; i++)
        {
            if (board[i] == '.' || board[i] == ' ')
            {
                board[i] = ai_player;
                score = -negamax(board, opponent, 1, -10000, 10000);
                board[i] = '.';
                if (best_move < score)
                {
                    best_move = score;
                    ans = i;
                }
            }
        }
        return ans;
    }
}
