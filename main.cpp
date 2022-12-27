#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>

void buildPath(std::unordered_map<std::string, std::string> &prevs, std::vector<std::vector<int>> &board, std::vector<std::string> &path) {
    path.push_back(std::to_string(board.size()-1) + "," + std::to_string(board[0].size()-1));
    auto point = prevs[std::to_string(board.size()-1) + "," + std::to_string(board[0].size()-1)];
    while (point != "0,0") {
      path.push_back(point);
      point = prevs[point];
    }
    path.push_back(point);
    std::reverse(path.begin(), path.end());
}

std::vector<std::string> bfs(std::vector<std::vector<int>> &board) {
    std::unordered_map<std::string, std::string> prevs;
    std::set<std::vector<int>> visited;

    std::vector<std::string> path;
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::queue<std::vector<int>> q;
    q.push({0, 0, -1, -1}); // (row, col, prevRow, prevCol)
    while (q.size() != 0) {
      int row, col, prevRow, prevCol;
      auto back = q.front();
      row = back[0];
      col = back[1];
      prevRow = back[2];
      prevCol = back[3];
      // set the value to look back at history
      prevs[std::to_string(row) + "," + std::to_string(col)] = std::to_string(prevRow) + "," + std::to_string(prevCol);
      q.pop();
      visited.insert({row, col});

      // board is solved
      if (board[back[0]][back[1]] == -2) {
        std::queue<std::vector<int>> empty;
        std::swap(q, empty);
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
  std::vector<std::vector<int>> board = {
    {-1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, -2}
  };

  std::vector<std::string> answer = bfs(board);
  std::cout << "Your path is: " << std::endl;
  for (int i = 0; i < answer.size(); i++) {
    std::cout << answer[i][0] << " - " << answer[i][2] << std::endl;
  }
  return 0;
}
