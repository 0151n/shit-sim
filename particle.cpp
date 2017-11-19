#include"particle.hpp"
/*
 * Particle types
 * 0. static/non gravity affected
 * 1. gravity affected
 * 2. collider/ turns type zeros into type 1s. <-- todo
 * */



Particle::Particle(sf::Vector2f in_pos, sf::Vector2f in_vel, sf::Color in_col, int in_ty, int in_den){
	position = in_pos;
	velocity = in_vel;
	color = in_col;
	type = in_ty;
	density = in_den;
	active = false;	
	rest = false;
	   cur_grid_x = (int(position.x) / 5) * 5 + 3;
	   cur_grid_y = (int(position.y) / 5) * 5 + 3;
}
Particle::Particle(){
	type = 0;
	density = 0;	
	active = false;	
	rest = false;
}
int Particle::update(){
    //TODO: change edge values to allow for modfication
	//check that bottom border hasnt been passed
	if(position.y > 450){
		position.y = 445;
		velocity.y = 0;
		rest = true;
	}
	if(position.x > 800){
		position.x = 795;
		velocity.x = 0;
	}else if(position.x < 0){
		position.x = 0;
		velocity.x = 0;
	}
	if(rest)color = sf::Color(255,0,0);
    if(!rest)color = sf::Color(0,255,0);
	position += velocity;
	   lst_grid_x = cur_grid_x;
	   lst_grid_y = cur_grid_y;
	   cur_grid_x = (int(position.x) / BLK_SIZE);
	   cur_grid_y = (int(position.y) / BLK_SIZE);

    if(cur_grid_x == lst_grid_x && cur_grid_y == lst_grid_y){
		return 0;
	} else {
		return 1;
	}
}
