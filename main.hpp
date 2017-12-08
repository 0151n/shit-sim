#ifndef MAIN_HPP
#define MAIN_HPP

#include<SFML/Graphics.hpp>
#include"particle.hpp"
#include<iostream>

//create window
sf::RenderWindow window(sf::VideoMode(GWIDTH,GHEIGHT),"shit_simulater");
sf::RectangleShape dot(sf::Vector2f(BLK_SIZE,BLK_SIZE));
sf::Clock timer;
sf::Time elapsed;
int draw();
int init();
int init_grid();
int spawn_particle(sf::Vector2f in_position, sf::Color col,int type,float den);
int dump_grid();
//mouse position
sf::Vector2i mouse_pos;
sf::Vector2f mouse_pos_vec;
//main grid
int gx = GWIDTH / BLK_SIZE;
int gy = GHEIGHT / BLK_SIZE;
int grid[GWIDTH][GHEIGHT];

#endif
