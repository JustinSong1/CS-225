#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"

class SquareMaze {
public:
    SquareMaze();
    bool canTravel(int x, int y, int dir) const;
    cs225::PNG* drawMaze() const;
    cs225::PNG* drawMazeWithSolution();
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
private:
    int width_;
    int height_;
    std::vector<bool> down;
    std::vector<bool> right;
    DisjointSets set;
    int getIndex(int x, int y) const{
        return y*width_ + x;
    }
};

#endif /* MAZE_H */

