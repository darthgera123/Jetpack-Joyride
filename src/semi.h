#include "main.h"

#ifndef SEMI_H
#define SEMI_H

class Semi{
    public:
        Semi() {}
        Semi(float x, float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        float v_x;
        int type;
        int move();
    private:
        VAO *object_circle;
        VAO *object_clear;
        VAO *object_clear_upper;
};

#endif