#include "main.h"

#ifndef PROP_H
#define PROP_H

struct Velo{
    float v_x;
    float v_y;
    float g;
    float d_y;
};

class Prop{
    public:
        Prop() {}
        Prop(float x, float y, float bottom);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        Velo speed;
        int move();
    private:
        VAO *object_base;
};

#endif