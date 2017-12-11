#include"main.hpp"
#include <assert.h>
#define MSPERFRAME 1000/60

using namespace std;

int main() {
    //max milliseconds - milliseconds used in a given frame
    int msfree = 0;
    //run intilization function
    init();
    //initialise random function
    srand (time(NULL));

    while(window.isOpen()) {
        
        /////////////////
        // User Input //
        ////////////////
        
        //mouse position transformations
        mouse_pos = sf::Mouse::getPosition(window);
        mouse_pos_vec.x = mouse_pos.x;
        mouse_pos_vec.y = mouse_pos.y;
        timer.restart();
        
        //mouse input capture
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            //spawn particle in a 5 x 5 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 5) * BLK_SIZE,mouse_pos_vec.y  + (rand() % 5) * BLK_SIZE),sf::Color(100,100,30),1,0.6f);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            //spawn particle in a 5 x 5 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 5) * BLK_SIZE,mouse_pos_vec.y  + (rand() % 5) * BLK_SIZE),sf::Color(100,100,30),1,0.25f);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //spawn particle in a 5 x 5 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 5) * BLK_SIZE,mouse_pos_vec.y  + (rand() % 5) * BLK_SIZE),sf::Color(100,100,30),1,1.0f);
            //	dump_grid();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            //spawn particle in a 3 x 3 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 3) * BLK_SIZE,mouse_pos_vec.y + (rand() % 3) * BLK_SIZE),sf::Color(100,100,30),0,1);
            //	dump_grid();
        }
        
        
        //integrate particles
        //cout << grid[int(mouse_pos_vec.x / 5)][int(mouse_pos_vec.y / 5)] << endl;
        ////////////////////////
        // Collision Handling //
        ////////////////////////
        for(i = 0; i < part_ind; i++) {
            if(parts[i].update()) {
                //collision
                if(grid[parts[i].cur_grid_x][parts[i].cur_grid_y] != -1) {
                    //handle collision for different particle types
                    int cur_index = grid[parts[i].cur_grid_x][parts[i].cur_grid_y];
                    switch(parts[i].type){
                        case 0: 
                            parts[i].cur_grid_x = parts[i].lst_grid_x;
                            parts[i].cur_grid_y = parts[i].lst_grid_y;
                            parts[i].position -= parts[i].velocity;
                            parts[i].rest = true;
                            break;
                        case 1:
                            parts[i].cur_grid_x = parts[i].lst_grid_x;
                            parts[i].cur_grid_y = parts[i].lst_grid_y;
                            parts[i].position -= parts[i].velocity;
                            parts[i].rest = true;
                            break;
                        case 2:
                            parts[i].type = 2;
                            parts[i].velocity = sf::Vector2f(0,1);
                            parts[i].cur_grid_x = parts[i].lst_grid_x;
                            parts[i].cur_grid_y = parts[i].lst_grid_y;
                            parts[i].position -= parts[i].velocity;
                            break;
                    }
                //no collision
                } else {
                    grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = i;
                    grid[parts[i].lst_grid_x][parts[i].lst_grid_y] = -1;
                    parts[i].rest = false;
                }
            }
            //////////////////////
            // Fluid Operations //
            //////////////////////
            //semi-liquid
            if(parts[i].density < 1.0f && grid[parts[i].cur_grid_x][parts[i].cur_grid_y + 1] != -1 && parts[i].rest){
                //change color to indicate fluid
                //set semi-liquid color, just for testing
                parts[i].color = sf::Color(150,100,50);
                //make sure rarest particle is on top
                if(parts[i].density < parts[grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1]].density && grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1] != -1)
                    swap_particles(i,grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1]);
                //check for free space below and to the left or right
                //check bottom right
                if(grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y + 1] == -1){
                    
                        grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y + 1] = grid[parts[i].cur_grid_x][parts[i].cur_grid_y];
                        grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = -1;
                        parts[i].cur_grid_x++;
                        parts[i].cur_grid_y++;
                        parts[i].position = sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,
                                                            (parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK); 
                //check bottom left
                } else if(grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y + 1] == -1){
                        grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y + 1] = grid[parts[i].cur_grid_x][parts[i].cur_grid_y];
                        grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = -1;
                        parts[i].cur_grid_x--;
                        parts[i].cur_grid_y++;
                        parts[i].position = sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,
                                                            (parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK);                                       
                }
                //full-liquid
                if(parts[i].density <= 0.5f){
                    //set liquid color, just for testing
                    parts[i].color = sf::Color(0,85,225);
                    //check for free space to the left or right
                    //check right
                    if(grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y] == -1){
                        
                            grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y] = grid[parts[i].cur_grid_x][parts[i].cur_grid_y];
                            grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = -1;
                            parts[i].cur_grid_x++;
                            parts[i].position = sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,
                                                                (parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK); 
                    //check bottom left
                    } else if(grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y] == -1){
                            grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y] = grid[parts[i].cur_grid_x][parts[i].cur_grid_y];
                            grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = -1;
                            parts[i].cur_grid_x--;
                            parts[i].position = sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,
                                                                (parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK);                                       
                    }
                }
            }
        }
        //////////////////////////////////////
        // Updating shit, Drawing to Screen //
        //////////////////////////////////////
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)window.close();
        }
        window.clear();
        draw();
        window.display();
        //calculate msfree
        msfree = MSPERFRAME - timer.getElapsedTime().asMilliseconds();
        //sleep until msfree is met
        if(msfree > 0)sf::sleep(sf::milliseconds(msfree));
    }
}

int draw() {
    int i = 0;
    for(i = 0; i < part_ind; i++) {
        if(parts[i].active) {
            if(grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y] != -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y + 1] != -1 &&
                grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y] == -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1] == -1  && SMOOTH){
                cornerl.setPosition(sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,(parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK));
                cornerl.setFillColor(parts[i].color);
                window.draw(cornerl);
            } else if(grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y] != -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y + 1] != -1 &&
                grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y] == -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1] == -1 && SMOOTH){
                cornerr.setPosition(sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,(parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK));
                cornerr.setFillColor(parts[i].color);
                window.draw(cornerr);
            } else if(grid[parts[i].cur_grid_x - 1][parts[i].cur_grid_y] == -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y + 1] != -1 &&
                grid[parts[i].cur_grid_x + 1][parts[i].cur_grid_y] == -1 && grid[parts[i].cur_grid_x][parts[i].cur_grid_y - 1] == -1 && SMOOTH){
                pointy.setPosition(sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,(parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK));
                pointy.setFillColor(parts[i].color);
                window.draw(pointy);
            } else {
                dot.setPosition(sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,(parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK));
                dot.setFillColor(parts[i].color);
                window.draw(dot);
            }
        }
    }
}
int init() {
    std::srand(std::time(0));
    //dot.setOrigin(3,3);
    //set up graphics shapes
    cornerl.setPointCount(3);
    cornerl.setPoint(0,sf::Vector2f(BLK_SIZE,0));
    cornerl.setPoint(1,sf::Vector2f(BLK_SIZE,BLK_SIZE));
    cornerl.setPoint(2,sf::Vector2f(0,BLK_SIZE));
    //cornerl.setOrigin(3,3);
    cornerr.setPointCount(3);
    cornerr.setPoint(0,sf::Vector2f(0,0));
    cornerr.setPoint(1,sf::Vector2f(BLK_SIZE,BLK_SIZE));
    cornerr.setPoint(2,sf::Vector2f(0,BLK_SIZE));
    //cornerr.setOrigin(3,3);
    pointy.setPointCount(3);
    pointy.setPoint(0,sf::Vector2f(0,BLK_SIZE));
    pointy.setPoint(1,sf::Vector2f(BLK_SIZE / 2,0));
    pointy.setPoint(2,sf::Vector2f(BLK_SIZE,BLK_SIZE));
    //initialise grid to -1
    init_grid();
}
int update() {

}
/**
 * @param in_position x,y position of the particle
 * @param col color of the particle
 * @param type type of the particle
 * @param den density of the particle
 */
int spawn_particle(sf::Vector2f in_position, sf::Color col,int type,float den) {
    if(grid[int(in_position.x / BLK_SIZE)][int(in_position.y / BLK_SIZE)] == -1) {
        parts[part_ind].position = in_position;
        parts[part_ind].color = col;
        parts[part_ind].active = true;
        parts[part_ind].type = type;
        parts[part_ind].density = den;

        //gravity
        //only set gravity for particle type 1
        (type >= 1 ? parts[part_ind].velocity = sf::Vector2f(0,1) : parts[part_ind].velocity = sf::Vector2f(0,0));
        //for type 0 set rest to true on creation
        (type == 0 ? parts[part_ind].rest = true : false);
        //grid[int(in_position.x / 5)][int(in_position.y / 5)] = part_ind;
        //output particle data on creation
        //cout << "created particle:" << part_ind << " type:" << parts[part_ind].type << endl; 
        part_ind++;
        
    }
}
//swap two particles give their indexs
int swap_particles(int i,int j){
    int tmp_x,tmp_y;
    tmp_x = parts[i].cur_grid_x;
    tmp_y = parts[i].cur_grid_y;
    parts[i].cur_grid_x = parts[j].cur_grid_x;
    parts[i].cur_grid_y = parts[j].cur_grid_y;
    parts[j].cur_grid_x = tmp_x;
    parts[j].cur_grid_y = tmp_y;
    grid[tmp_x][tmp_y] = j;
    grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = i;
}
int init_grid() {
    int i,j;
    for(i = 0; i < GWIDTH / BLK_SIZE; i++) {
        for(j = 0; j < GHEIGHT / BLK_SIZE; j++) {
            grid[i][j] = -1;
        }
    }
}
int dump_grid() {
    int i,j;
    for(i = 0; i < GWIDTH / BLK_SIZE; i++) {
        for(j = 0; j < GHEIGHT / BLK_SIZE; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}





