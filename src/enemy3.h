#include "main.h"

#ifndef ENEMY3_H
#define ENEMY3_H
struct VELOCITY{
    float v_x;
    float v_y;
    float d_x;
    float g_x;
};
class Enemy_3{
    public:
        Enemy_3() {}
        Enemy_3(float x, float y,float top,float bottom);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        void move_y(float bottom,float up);
        float rotation;
        float height;
        float width;
        float speed;
        float side;
        float top;
        float original;
        float bottom;
        void move_down();
        void move_left();
        VELOCITY speed_player;
        void rotate();
        void gravity();
    private:
        VAO *object_upper;
        VAO *object_lower;
};

#endif