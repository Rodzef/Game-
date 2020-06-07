#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FiveWindow.hpp"

void clickChecker(int x, int y, std::vector<std::vector<int>>& grid) {
	Vector2i move_vector = Vector2i(0, 0);
	int fieldSize = grid.size() - 2;
	if (grid[x + 1][y] == fieldSize*fieldSize - 1) { move_vector.x = 1; move_vector.y = 0; }
	if (grid[x][y + 1] == fieldSize*fieldSize - 1) { move_vector.x = 0; move_vector.y = 1; }
	if (grid[x][y - 1] == fieldSize*fieldSize - 1) { move_vector.x = 0; move_vector.y = -1; }
	if (grid[x - 1][y] == fieldSize*fieldSize - 1) { move_vector.x = -1; move_vector.y = 0; }

	if (move_vector.x != 0 || move_vector.y != 0) {
		int temp = grid[x][y];
		grid[x][y] = fieldSize*fieldSize - 1;
		grid[x + move_vector.x][y + move_vector.y] = temp;
	}
}

bool gridsAreEqual(const std::vector<std::vector<int>>& grid1, const std::vector<std::vector<int>>& grid2) {
	if (grid1.size() != grid2.size()) {
		printf("size1\n");
		return false;
	}

	for (int i = 0; i < grid1.size(); i++) {
		if (grid1[i].size() != grid2[i].size()) {
			printf("size2");
			return false;
		}
	}

	for (int i = 0; i < grid1.size(); i++) {
		for (int j = 0; j < grid1[i].size(); j++) {
			printf("%d-%d ", grid1[i][j], grid2[i][j]);
			if (grid1[i][j] != grid2[i][j]) {
				return false;
			}
		}
		printf("\n");
	}
	

	return true;
}	
    
//Test
TEST_CASE("Grid test") {
  FiveWindow game(500 / 4, 4, "images/15!!!.jpg");

  int fieldSize = 4;
  int numOfCheckIterations = 100;

  std::vector<std::vector<int>> grid;
  std::pair<int, int> lastMove = std::make_pair(-1, -1);

  grid.resize(fieldSize + 2, std::vector<int>(fieldSize + 2));
  int n = 0;
  for (int i = 0; i < fieldSize; i++) {
    for (int j = 0; j < fieldSize; j++) {
      grid[i + 1][j + 1] = n;
      n++;
    }
  }

  for (int i = 0; i < numOfCheckIterations; i++) {
    lastMove = std::make_pair(std::rand() % fieldSize + 1, std::rand() % fieldSize + 1);

    clickChecker(lastMove.first, lastMove.second, grid);
    game.clickHandler(lastMove.first, lastMove.second);
    CHECK(gridsAreEqual(grid, game.grid));
  }
}