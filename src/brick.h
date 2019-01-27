#include "main.h"

#ifndef BRICK_H
#define BRICK_H


class Brick {
public:
    Brick() {}
    Brick(float x, float y, color_t color, float factor);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif
