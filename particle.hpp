#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include"defs.hpp"
#include<SFML/Graphics.hpp>

class Particle{
	public:
		sf::Vector2f position;
		sf::Vector2f velocity;
		int cur_grid_x;
		int cur_grid_y;
		int lst_grid_x;
		int lst_grid_y;
		sf::Color color;
		bool active;
		bool rest;
		int type;
		int density;
		Particle();
		Particle(sf::Vector2f in_pos, sf::Vector2f in_vel, sf::Color in_col, int in_ty, int in_den);
		int update();
};
		
#endif
