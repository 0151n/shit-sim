#include"particle.hpp"
/*
 * Particle types
 * 0. static/non gravity affected
 * 1. gravity affected
 * 2. collider/ turns type zeros into type 1s.
 *
 * density
 * 1 = solid
 * < 1 and > 0.5 = liquid
 * < 0.5 = gas
 */



Particle::Particle ( sf::Vector2f in_pos, sf::Vector2f in_vel, sf::Color in_col, int in_ty, int in_den )
{
    position = in_pos;
    velocity = in_vel;
    color = in_col;
    type = in_ty;
    density = in_den;
    active = false;
    rest = false;
    cur_grid_x = ( int ( position.x ) / BLK_SIZE );
    cur_grid_y = ( int ( position.y ) / BLK_SIZE );
}
Particle::Particle()
{
    type = 0;
    density = 0;
    active = false;
    rest = false;
}
int Particle::update()
{
    if ( position.y > GHEIGHT) {
        position.y = GHEIGHT - BLK_SIZE;
        velocity.y = 0;
        rest = true;
    }
    if ( position.x > GWIDTH ) {
        position.x = GWIDTH - BLK_SIZE;
        velocity.x = 0;
    } else if ( position.x < 0 ) {
        position.x = 0;
        velocity.x = 0;
    }
    if ( rest ) color = sf::Color ( 255,0,0 );
    if ( !rest ) color = sf::Color ( 0,255,0 );
    position += velocity;
    lst_grid_x = cur_grid_x;
    lst_grid_y = cur_grid_y;
    cur_grid_x = ( int ( position.x ) / BLK_SIZE );
    cur_grid_y = ( int ( position.y ) / BLK_SIZE );

    if ( cur_grid_x == lst_grid_x && cur_grid_y == lst_grid_y ) {
        return 0;
    } else {
        return 1;
    }
}

