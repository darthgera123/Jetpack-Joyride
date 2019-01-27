#include "main.h"

#ifndef ENEMY2_H
#define ENEMY2_H

class Enemy_2{
    public:
        Enemy_2() {}
        Enemy_2(float x, float y,float width,float dir);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        void draw_midrib(glm::mat4 VP);
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        void move_y(float bottom,float up);
        float height;
        float width;
        float speed;
        float lethal;
        float side;
        float timer;
    private:
        VAO *object;
        VAO *object_rec_2;
        VAO *object_rec_1;
        VAO *object_clear;
        VAO *object_rec_2_clear;
        VAO *object_rec_1_clear;   
};

#endif