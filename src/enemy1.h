#include "main.h"

#ifndef ENEMY1_H
#define ENEMY1_H

class Enemy_1{
    public:
        Enemy_1() {}
        Enemy_1(float x, float y,float width,float height,float rotation);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        void set_position(float x,float y);
        float radius;
        float ret_x();
        float ret_y();
        void move_left();
        int type;
        float height;
        float width;
        float rotation;
        float ret_radius();
    private:
        VAO *object;
        VAO *object_circle_2;
        VAO *object_circle;   
};

#endif