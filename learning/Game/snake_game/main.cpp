#include "snake.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

// 非阻塞输入函数
bool keyPressed() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) == 1;
}

// 初始化终端设置
void initTermios(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// 清屏函数
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// 游戏绘制函数
void draw(const Snake& snake, int width, int height) {
    clearScreen();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool isBody = false;
            for (const auto& seg : snake.getBody()) {
                if (x == seg.first && y == seg.second) {
                    std::cout << (seg == snake.getBody().front() ? "@" : "O");
                    isBody = true;
                    break;
                }
            }
            if (isBody) continue;
            
            if (x == snake.getFood().first && y == snake.getFood().second) {
                std::cout << "*";
            } else if (x == 0 || x == width-1 || y == 0 || y == height-1) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "Score: " << snake.getScore() << "\n";
}

int main() {
    const int WIDTH = 30, HEIGHT = 20;
    Snake snake(WIDTH, HEIGHT);
    initTermios(true);

    while (true) {
        draw(snake, WIDTH, HEIGHT);
        usleep(100000); // 控制游戏速度（100ms）

        if (keyPressed()) {
            char c = getchar();
            switch(c) {
                case 'w': snake.changeDirection(Snake::UP); break;
                case 's': snake.changeDirection(Snake::DOWN); break;
                case 'a': snake.changeDirection(Snake::LEFT); break;
                case 'd': snake.changeDirection(Snake::RIGHT); break;
                case 'q': initTermios(false); return 0;
            }
        }

        if (!snake.move()) {
            initTermios(false);
            std::cout << "Game Over! Final Score: " << snake.getScore() << "\n";
            return 0;
        }
    }
}
