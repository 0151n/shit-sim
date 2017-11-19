#include"main.hpp"
#define MSPERFRAME 1000/60

using namespace std;

Particle parts[10000];
int x = 0;
int i = 0;
int part_ind = 0;

int main() {
    //run intilization function
    init();
    //initialise random function
    srand (time(NULL));

    int msfree = 0;

    //mouse position transformations
    while(window.isOpen()) {
        mouse_pos = sf::Mouse::getPosition(window);
        mouse_pos_vec.x = mouse_pos.x;
        mouse_pos_vec.y = mouse_pos.y;
        timer.restart();
        
        //mouse input capture
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //spawn particle in a 5 x 5 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 5) * BLK_SIZE,mouse_pos_vec.y  + (rand() % 5) * BLK_SIZE),sf::Color(100,100,30),1);
            //	dump_grid();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            //spawn particle in a 3 x 3 box around mouse
            spawn_particle(sf::Vector2f(mouse_pos_vec.x + (rand() % 3) * BLK_SIZE,mouse_pos_vec.y + (rand() % 3) * BLK_SIZE),sf::Color(100,100,30),0);
            //	dump_grid();
        }
        
        //integrate particles
        //cout << grid[int(mouse_pos_vec.x / 5)][int(mouse_pos_vec.y / 5)] << endl;
        for(i = 0; i < part_ind; i++) {
            if(parts[i].update()) {
                if(grid[parts[i].cur_grid_x][parts[i].cur_grid_y] != -1) {
                    parts[i].cur_grid_x = parts[i].lst_grid_x;
                    parts[i].cur_grid_y = parts[i].lst_grid_y;
                    parts[i].position -= parts[i].velocity;
                    //if(parts[grid[parts[i].cur_grid_x][parts[i].cur_grid_y] + 5].rest) {
                        parts[i].rest = true;
                    //}
                } else {
                    grid[parts[i].cur_grid_x][parts[i].cur_grid_y] = i;
                    grid[parts[i].lst_grid_x][parts[i].lst_grid_y] = -1;
                }
            }
        }
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)window.close();
        }
        window.clear();
        draw();
        window.display();
        msfree = MSPERFRAME - timer.getElapsedTime().asMilliseconds();
        //cout << msfree << endl;
        if(msfree > 0)sf::sleep(sf::milliseconds(msfree));
    }
}

int draw() {
    int i = 0;
    for(i = 0; i < part_ind; i++) {
        if(parts[i].active) {
            dot.setPosition(sf::Vector2f((parts[i].cur_grid_x * BLK_SIZE) + HALF_BLK,(parts[i].cur_grid_y * BLK_SIZE) + HALF_BLK));
            dot.setFillColor(parts[i].color);
            window.draw(dot);
        }
    }
}
int init() {
    std::srand(std::time(0));
    dot.setOrigin(3,3);
    init_grid();
}
int update() {

}
/**
 * @param in_position x,y position of the particle
 * @param col color of the particle
 * @param type type of the particle
 */
int spawn_particle(sf::Vector2f in_position, sf::Color col,int type) {
    if(grid[int(in_position.x / BLK_SIZE)][int(in_position.y / BLK_SIZE)] == -1) {
        parts[part_ind].position = in_position;
        parts[part_ind].color = col;
        parts[part_ind].active = true;
        parts[part_ind].type = type;
        //gravity
        //only set gravity for particle type 1
        (type == 1 ? parts[part_ind].velocity = sf::Vector2f(0,1) : parts[part_ind].velocity = sf::Vector2f(0,0));
        //for type 0 set rest to true on creation
        (type == 0 ? parts[part_ind].rest = true : false);
        //grid[int(in_position.x / 5)][int(in_position.y / 5)] = part_ind;
        //output particle data on creation
        //cout << "created particle:" << part_ind << " type:" << parts[part_ind].type << endl; 
        part_ind++;
        
    }
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
    for(i = 0; i < 160; i++) {
        for(j = 0; j < 90; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}





