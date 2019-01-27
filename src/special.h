#include "main.h"

#ifndef SPECIAL_H
#define SPECIAL_H

struct Veloc{
    float v_x;
    float v_y;
    float g;
    float d_y;
};

class Special{
    public:
        Special() {}
        Special(float x, float y, float bottom,int type);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        int type;
        Veloc speed;
        int move();
    private:
        VAO *object_base;
        VAO *object_circle;
        VAO *object_clear;
};

#endif