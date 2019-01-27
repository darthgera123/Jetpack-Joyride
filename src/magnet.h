#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet{
    public:
        Magnet() {}
        Magnet(float x, float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
    private:
        VAO *object_base;
        VAO *object_cut;
        VAO *object_upper;
        VAO *object_lower;
        VAO *object_North;
        VAO *object_South;
        VAO *object_clear;
};

#endif