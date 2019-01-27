#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon{
    public:
        Dragon() {}
        Dragon(float x, float y);
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
        void move(float y);
    private:
        VAO *object_circle;
        VAO *object_clear;
        VAO *object_beak;
        VAO *object_tail;
};

#endif