#include "main.h"

#ifndef WATER_H
#define WATER_H

struct Vel{
    float v_x;
    float v_y;
    float g;
    float d_y;
};

class Water{
    public:
        Water() {}
        Water(float x, float y, float bottom);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        Vel speed;
        int move();
    private:
        VAO *object_base;
};

#endif