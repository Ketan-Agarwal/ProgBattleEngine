#ifndef GRID_H
#define GRID_H

#include <vector>


class Grid {
public:
    Grid (int width, int height);
    
    void initialize();
    void update();

    
private:
    int width;
    int height;



};


#endif