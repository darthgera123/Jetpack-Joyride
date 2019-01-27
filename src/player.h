#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H
struct Velocity_Player{
    float v_x;
    float v_y;
    float g;
    float d_y;
    float m_x;
    float m_y;
    float m_g;
};
class Player{
    public:
        Player() {}
        Player(float x, float y, float platform_y,float ceiling_y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void draw_shield(glm::mat4 VP);
        void remove_shield(glm::mat4 VP);
        void move_left(float left);
        void move_right(float right);
        void jump();
        void gravity();
        void set_position(float x,float y);
        float platform_y;
        float ceiling_y;
        float radius;
        bool inair();
        float ret_x();
        float ret_y();
        int shield;
        int circle;
        float circle_center_x;
        float circle_radius;
        float circle_center_y;
        float ret_radius();
        void magnet(float x,float y,float m_radius);
        long long int score;
        int life;
        int set_score(int score);
        Velocity_Player speed_t;
    private:
        VAO *object_circle;
        VAO *object_lower_triangle;
        VAO *object_upper_triangle;
        VAO *object_shield;
        VAO *object_remove;
};

#endif