#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin{
    public:
        Coin() {}
        Coin(float x, float y,int type);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        void set_position(float x,float y);
        //float platform_y;
        //float ceiling_y;
        float radius;
        float ret_x();
        float ret_y();
        void move_left();
        int type;
        float ret_radius();
    private:
        VAO *object_circle;
        VAO *object_circle_2;
        VAO *object_clear;   
};

#endif