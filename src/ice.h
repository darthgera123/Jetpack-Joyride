#include "main.h"

#ifndef ICE_H
#define ICE_H


class Ice{
    public:
        Ice() {}
        Ice(float x, float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        float v_x;
        void move(float x);
    private:
        VAO *object_base;
};

#endif