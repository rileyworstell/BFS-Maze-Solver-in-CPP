#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

void buildPath(unordered_map<string, string> &prevs, vector<vector<int>> &board, vector<string> &path) {
    path.push_back(to_string(board.size()-1) + "," + to_string(board[0].size()-1));
    auto point = prevs[to_string(board.size()-1) + "," + to_string(board[0].size()-1)];
    while (point != "0,0") {
      path.push_back(point);
      point = prevs[point];
    }
    path.push_back(point);
    reverse(path.begin(), path.end());
}

vector<string> bfs(vector<vector<int>> &board) {
    unordered_map<string, string> prevs;
    set<vector<int>> visited;

    vector<string> path;
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<vector<int>> q;
    q.push({0, 0, -1, -1}); // (row, col, prevRow, prevCol)
    while (q.size() != 0) {
      int row, col, prevRow, prevCol;
      auto back = q.front();
      row = back[0];
      col = back[1];
      prevRow = back[2];
      prevCol = back[3];
      // set the value to look back at history
      prevs[to_string(row) + "," + to_string(col)] = to_string(prevRow) + "," + to_string(prevCol);
      q.pop();
      visited.insert({row, col});

      // board is solved
      if (board[back[0]][back[1]] == -2) {
        queue<vector<int>> empty;
        swap(q, empty);
      }
      else {
        // loop through directions
        for (int dir = 0; dir < (sizeof(dirs)/sizeof(dirs[0])); dir++) {
          int newR = row + dirs[dir][0];
          int newC = col + dirs[dir][1];
          if (newR > -1 && newR < board.size() && newC > -1 && newC < board[0].size()) {
            if (visited.find({newR, newC}) == visited.end() && board[newR][newC] != 1) {
              q.push({newR, newC, row, col});
            }
          }
        }
      }

    }
    buildPath(prevs, board, path);
    return path;
}

int main() {
  /*
  -1 is starting point
  -2 is ending point
  0's are free spaces
  1's are walls
  */
  vector<vector<int>> board = {
    {-1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, -2}
  };

  vector<string> answer = bfs(board);
  cout << "Your path is: " << endl;
  for (int i = 0; i < answer.size(); i++) {
    cout << answer[i][0] << " - " << answer[i][2] << endl;
  }
  return 0;
}
