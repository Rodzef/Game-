#include "FiveWindow.hpp"

FiveWindow::FiveWindow(const int blockWidht, const int fieldSize, const std::string texture_path) : RenderWindow(VideoMode(fieldSize*blockWidht, fieldSize*blockWidht), "Game") {
	this->blockWidht = blockWidht;
	this->fieldSize = fieldSize;
	texture.loadFromFile(texture_path);
	
	grid.resize(fieldSize + 2, std::vector<int>(fieldSize + 2));

	int n = 0;
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < fieldSize; j++) {
			sprite.push_back(Sprite());
			sprite[n].setTexture(texture);
			sprite[n].setTextureRect(IntRect(i*blockWidht, j*blockWidht, blockWidht, blockWidht));
			grid[i + 1][j + 1] = n;
			n++;
		}
	}

	setFramerateLimit(60);
};

void FiveWindow::clickHandler(int x, int y) {
	Vector2f mouse = mapPixelToCoords(Mouse::getPosition(*this));
	for (int i = 0; i < fieldSize*fieldSize; i++) {
		FloatRect bounds = sprite[i].getGlobalBounds();

		Vector2i move_vector;
		if (bounds.contains(mouse)) {
			if (grid[x + 1][y] == fieldSize*fieldSize - 1) { move_vector.x = 1; move_vector.y = 0; }
			if (grid[x][y + 1] == fieldSize*fieldSize - 1) { move_vector.x = 0; move_vector.y = 1; }
			if (grid[x][y - 1] == fieldSize*fieldSize - 1) { move_vector.x = 0; move_vector.y = -1; }
			if (grid[x - 1][y] == fieldSize*fieldSize - 1) { move_vector.x = -1; move_vector.y = 0; }
		}
		else {
			continue;
		}

		if (move_vector.x != 0 || move_vector.y != 0) {
			int temp = grid[x][y];
			grid[x][y] = fieldSize*fieldSize - 1;
			grid[x + move_vector.x][y + move_vector.y] = temp;
			break;
		}
	}
}


void FiveWindow::run() {
	while (isOpen()) {
		Event event;
		while (pollEvent(event)) {
			if (event.type == Event::Closed) {	
				close();
			}

			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				Vector2i position = Mouse::getPosition(*this);
				int x = position.x / blockWidht +1;
				int y = position.y / blockWidht +1;
				clickHandler(x, y);
			}
		}

		for (int i = 0; i < fieldSize; i++) {
			for (int j = 0; j < fieldSize; j++) {
				sprite[grid[i + 1][j + 1]].setPosition(i*blockWidht, j*blockWidht);
				draw(sprite[grid[i + 1][j + 1]]);
			}
		}

		display();
	}
}

void FiveWindow::shuffle() {
	int x, y;

	std::srand(std::time(nullptr));
	for (int k = 0; k < 5000; k++) {
		x = std::rand() % fieldSize + 1;
		y = std::rand() % fieldSize + 1;
		clickHandler(x, y);

		//clear(Color::White);
		for (int i = 0; i < fieldSize; i++) {
			for (int j = 0; j < fieldSize; j++) {
				sprite[grid[i + 1][j + 1]].setPosition(i*blockWidht, j*blockWidht);
			}
		}
	}

	//printf("Shuffle done\n");
}
