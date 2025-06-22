#include "snake.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

Snake::Snake(int width, int height) 
    : gameWidth(width), gameHeight(height), dir(RIGHT), score(0) {
    // 初始化蛇身（3节）
    body.push_back({width/2, height/2});
    body.push_back({width/2-1, height/2});
    body.push_back({width/2-2, height/2});
    srand(time(nullptr));
    generateFood();
}

void Snake::changeDirection(Direction newDir) {
    if (!isOpposite(dir, newDir)) {
        dir = newDir;
    }
}

bool Snake::move() {
    auto head = body.front();
    switch(dir) {
        case UP:    head.second--; break;
        case DOWN:  head.second++; break;
        case LEFT:  head.first--; break;
        case RIGHT: head.first++; break;
    }

    // 检测碰撞
    if (head.first <= 0 || head.first >= gameWidth-1 ||
        head.second <= 0 || head.second >= gameHeight-1) {
        return false; // 撞墙
    }
    for (const auto& seg : body) {
        if (head == seg) return false; // 撞自己
    }

    body.push_front(head);
    
    // 吃食物检测
    if (head == food) {
        score += 10;
        generateFood();
    } else {
        body.pop_back();
    }
    return true;
}

void Snake::generateFood() {
    do {
        food.first = rand() % (gameWidth-2) + 1;
        food.second = rand() % (gameHeight-2) + 1;
    } while ([this](){
        for (const auto& seg : body) {
            if (seg == food) return true;
        }
        return false;
    }());
}

int Snake::getScore() const { return score; }

const std::deque<std::pair<int, int>>& Snake::getBody() const { return body; }

std::pair<int, int> Snake::getFood() const { return food; }

bool Snake::isOpposite(Direction dir1, Direction dir2) {
    return (dir1 == UP && dir2 == DOWN) || (dir1 == DOWN && dir2 == UP) ||
           (dir1 == LEFT && dir2 == RIGHT) || (dir1 == RIGHT && dir2 == LEFT);
}
