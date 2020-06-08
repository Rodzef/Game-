#include "FiveWindow.hpp"
/*Создаем блоки со стороной  blockWidht = 500/4. Pазмер поля fieldSize =
4*sprite. Создаем и загружаем текстуры texture. Создаем игровое поля grid [6][6]
(размер игрового части поля [4][4] и обертка из 0). Создаем и задаем значение
спрайтов sprite. Задаем частоту смены кадров 60. Задаем координаты "последнему
шагу".
*/

FiveWindow::FiveWindow(const int blockWidht, const int fieldSize,
  const std::string texture_path)
  : RenderWindow(VideoMode(fieldSize * blockWidht, fieldSize * blockWidht),
  "Game") {
  this->blockWidht = blockWidht;
  this->fieldSize = fieldSize;
  texture.loadFromFile(texture_path);

  grid.resize(fieldSize + 2, std::vector<int>(fieldSize + 2));

  int n = 0;
  for (int i = 0; i < fieldSize; i++) {
    for (int j = 0; j < fieldSize; j++) {
      sprite.push_back(Sprite());
      sprite[n].setTexture(texture);
      sprite[n].setTextureRect(
        IntRect(i * blockWidht, j * blockWidht, blockWidht, blockWidht));
      grid[i + 1][j + 1] = n;
      n++;
    }
  }

  setFramerateLimit(60);
  lastMove = std::make_pair(-1, -1);
};

/* Проверяем возможно ли передвинуть спрайт. Если такая возможность есть -
// двигаем спрайт. Иначе продолжаем игру.
*/
void FiveWindow::clickHandler(int x, int y) {
  Vector2i move_vector;
  if (grid[x + 1][y] == fieldSize * fieldSize - 1) {
      move_vector.x = 1;
      move_vector.y = 0;
  }
  if (grid[x][y + 1] == fieldSize * fieldSize - 1) {
      move_vector.x = 0;
      move_vector.y = 1;
  }
  if (grid[x][y - 1] == fieldSize * fieldSize - 1) {
      move_vector.x = 0;
      move_vector.y = -1;
  }
  if (grid[x - 1][y] == fieldSize * fieldSize - 1) {
      move_vector.x = -1;
      move_vector.y = 0;
  }


  if (move_vector.x != 0 || move_vector.y != 0) {
      int temp = grid[x][y];
      grid[x][y] = fieldSize * fieldSize - 1;
      grid[x + move_vector.x][y + move_vector.y] = temp;
      lastMove = std::make_pair(x + move_vector.x, y + move_vector.y);
  }
}

/* Делаем "шаг назад". При повторном вызове функции - возвращаемся в исходное
положение.
*/
void FiveWindow::stepBack() {
  if (lastMove.first == -1)
    return;
  clickHandler(lastMove.first, lastMove.second);
}

/* Создаем окно, и пока оно открыто выполняем действия.
Если нажали на крестик - окно закрывается.
Если нажали правую кнопку мыши - вызываем функцию stepBack.
Если нажали правую кнопку мыши - отслеживаем положение мыши и вызываем функцию
clickHandler. Выполняем отрисовку спрайтов.
*/
void FiveWindow::run() {
  while (isOpen()) {
    Event event;
    while (pollEvent(event)) {
      if (event.type == Event::Closed) {
        close();
      }

      if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Right) {
        stepBack();
      }

      if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left) {
        Vector2i position = Mouse::getPosition(*this);
        int x = position.x / blockWidht + 1;
        int y = position.y / blockWidht + 1;
        clickHandler(x, y);
      }
    }

    for (int i = 0; i < fieldSize; i++) {
      for (int j = 0; j < fieldSize; j++) {
        sprite[grid[i + 1][j + 1]].setPosition(i * blockWidht, j * blockWidht);
        draw(sprite[grid[i + 1][j + 1]]);
      }
    }

    display();
  }
}

/*Делаем 5000 рандомных кликов по полю, и соответственно, меняем спрайты
местами. Тем самым перемешиваем спрайты между собой.
*/
void FiveWindow::shuffle() {
  int x, y;

  std::srand(std::time(nullptr));
  for (int k = 0; k < 5000; k++) {
    x = std::rand() % fieldSize + 1;
    y = std::rand() % fieldSize + 1;
    clickHandler(x, y);

    // clear(Color::White);
    for (int i = 0; i < fieldSize; i++) {
      for (int j = 0; j < fieldSize; j++) {
        sprite[grid[i + 1][j + 1]].setPosition(i * blockWidht, j * blockWidht);
      }
    }
  }
}