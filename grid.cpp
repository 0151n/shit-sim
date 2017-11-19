#include"grid.hpp"

int init_grid(){
	int i,j;
	for(i = 0;i < 800;i++){
		for(j = 0;j < 450;j++){
			grid[i][j] = 0;
		}
	}
    //grid width
    int gwidth = GWIDTH;
    //grid width
    int gheight = GHEIGHT;
    //size of single particle
    int blk_size = 5;
    //middle point of ^ particle
    int half_blk = blk_size / 2;
    //main grid
    int grid[GWIDTH][GHEIGHT];
}
