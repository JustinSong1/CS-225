#include "maze.h"
#include <stack>
#include <map>

SquareMaze::SquareMaze() {
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    switch (dir) {
        case 0:
            if(x >= width_-1) {
                return false;
            }
            return !right[getIndex(x, y)];
        case 1:
            if(y >= height_-1) {
                return false;
            }
            return !down[getIndex(x, y)];
        case 2:
            if(x <= 0) {
                return false;
            }
            return !right[getIndex(x-1, y)];
        case 3:
            if(y <= 0) {
                return false;
            }
            return !down[getIndex(x, y-1)];
        default:
            return false;
    }
}

cs225::PNG *SquareMaze::drawMaze() const {
    cs225::PNG* maze = new cs225::PNG(width_*10+1, height_*10+1);
    cs225::HSLAPixel black(0, 0, 0);
    for(int i = 10; i < width_*10+1; i++) {
        maze->getPixel(i,0) = black;
    }
    for(int i = 0; i < height_*10+1; i++) {
        maze->getPixel(0, i) = black;
    }
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            if(right[getIndex(x, y)]) {
                for(int k = 0; k <= 10; k++) {
                    maze->getPixel((x+1)*10, y*10+k) = black;
                }
            }
            if(down[getIndex(x, y)]) {
                for(int k = 0; k <= 10; k++) {
                    maze->getPixel(x*10+k, (y+1)*10) = black;
                }
            }
        }
    }
    return maze;
}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    set.addelements(width*height);
    down = std::vector<bool>(width*height, true);
    right = std::vector<bool>(width*height, true);
    int deleted = 0;
    while(deleted != (width*height)-1) {
        int wallX = rand() % width;
        int wallY = rand() % height;
        int side = rand() % 2;
        if(side == 0 && wallX != width-1) {
            if(set.find(getIndex(wallX, wallY)) != set.find(getIndex(wallX+1, wallY)) && right[getIndex(wallX, wallY)]) {
                setWall(wallX, wallY, 0, false);
                set.setunion(getIndex(wallX, wallY), getIndex(wallX+1, wallY));
                deleted++;
            }
        }
        if(side == 1 && wallY != height-1) {
            if(set.find(getIndex(wallX, wallY)) != set.find(getIndex(wallX, wallY+1))  && right[getIndex(wallX, wallY)]) {
                setWall(wallX, wallY, 1, false);
                set.setunion(getIndex(wallX, wallY), getIndex(wallX, wallY+1));
                deleted++;
            }
        }
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir == 0) {
        right[getIndex(x, y)] = exists;
    }
    if(dir == 1) {
        down[getIndex(x, y)] = exists;
    }
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<bool> visited(width_*height_, false);
    std::stack<int> s;
    std::map<int, int> map;
    visited[0] = true;
    s.push(0);
    while(!s.empty()) {
        int curr = s.top();
        int currX = curr%width_;
        int currY = curr/width_;
        s.pop();
        if(canTravel(currX, currY, 0) && !visited[getIndex(currX+1, currY)]) {
            visited[getIndex(currX+1, currY)] = true;
            s.push(getIndex(currX+1, currY));
            map[getIndex(currX+1, currY)] = curr;
        }
        if(canTravel(currX, currY, 1) && !visited[getIndex(currX, currY+1)]) {
            visited[getIndex(currX, currY+1)] = true;
            s.push(getIndex(currX, currY+1));
            map[getIndex(currX, currY+1)] = curr;
        }
        if(canTravel(currX, currY, 2) && !visited[getIndex(currX-1, currY)]) {
            visited[getIndex(currX-1, currY)] = true;
            s.push(getIndex(currX-1, currY));
            map[getIndex(currX-1, currY)] = curr;
        }
        if(canTravel(currX, currY, 3) && !visited[getIndex(currX, currY-1)]) {
            visited[getIndex(currX, currY-1)] = true;
            s.push(getIndex(currX, currY-1));
            map[getIndex(currX, currY-1)] = curr;
        }
    }
    std::vector<int> longestPath;
    std::vector<int> temp;
    int longest = 0;
    for(int i = 0; i < width_; i++) {
        temp.clear();
        int length = 0;
        int next = getIndex(i,height_-1);
        while(next != 0) {
            if(next-map[next] == 1) {
                temp.push_back(0);
            } else if(next-map[next] == width_) {
                temp.push_back(1);
            } else if(next-map[next] == -1) {
                temp.push_back(2);
            } else if(next-map[next] == -width_) {
                temp.push_back(3);
            }
            length++;
            next = map[next];
        }
        if(length > longest) {
            longest = length;
            longestPath = temp;
        }
    }
    std::reverse(longestPath.begin(), longestPath.end());
    return longestPath;
}

cs225::PNG *SquareMaze::drawMazeWithSolution() {
    cs225::PNG* maze = drawMaze();
    cs225::HSLAPixel red(0, 1, 0.5, 1);
    std::vector<int> path = solveMaze();
    int x = 5;
    int y = 5;
    for(size_t i = 0; i < path.size(); i++) {
        if(path[i] == 0) {
            for(int j = 0; j <= 10; j++) {
                maze->getPixel(x+j, y) = red;
            }
            x += 10;
        } else if(path[i] == 1) {
            for(int j = 0; j <= 10; j++) {
                maze->getPixel(x, y+j) = red;
            }
            y += 10;
        } else if(path[i] == 2) {
            for(int j = 0; j <= 10; j++) {
                maze->getPixel(x-j, y) = red;
            }
            x -= 10;
        } else if(path[i] == 3) {
            for(int j = 0; j <= 10; j++) {
                maze->getPixel(x, y-j) = red;
            }
            y -= 10;
        }
    }
    x -= 5;
    y += 5;
    for(int i = 0; i <= 10; i++) {
        maze->getPixel(x+i, y) = cs225::HSLAPixel(0, 1, 1);
    }
    return maze;
}