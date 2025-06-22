#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <utility> // for pair

class Snake {
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Snake(int width, int height);
    void changeDirection(Direction newDir);
    bool move();
    void generateFood();
    int getScore() const;
    const std::deque<std::pair<int, int>>& getBody() const;
    std::pair<int, int> getFood() const;

private:
    int gameWidth, gameHeight;
    Direction dir;
    std::deque<std::pair<int, int>> body;
    std::pair<int, int> food;
    int score;
    bool isOpposite(Direction dir1, Direction dir2);
};

#endif
