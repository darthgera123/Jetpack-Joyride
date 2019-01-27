#include "enemy2.h"
#include "main.h"
#include <unistd.h>

using namespace std;

Enemy_2::Enemy_2(float x, float y,float width, float dir) {
    this->position = glm::vec3(x, y, 0);
    this->width =width;
    float side = 0.5;
    this->side = side;
    this->speed = -0.02*dir;
    this->lethal =0;
    this->timer =0;
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        side,side, 0.0f,
        side, 0.0f, 0.0f, // triangle 1 : end
        0.0f, side,0.0f, // triangle 2 : begin
        side,side,0.0f,
        0.0f, 0.0f,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_2[] = {
        0.0f+width+0.5,0.0f,0.0f, // triangle 1 : begin
        side+width+0.5,side, 0.0f,
        side+width+0.5, 0.0f, 0.0f, // triangle 1 : end
        0.0f+width+0.5, side,0.0f, // triangle 2 : begin
        side+width+0.5,side,0.0f,
        0.0f+width+0.5, 0.0f,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_3[] = {
        side,0.25*side,0.0f, // triangle 1 : begin
        side+width,0.75*side, 0.0f,
        side+width, 0.25*side, 0.0f, // triangle 1 : end
        side, 0.75*side,0.0f, // triangle 2 : begin
        side+width,0.75*side, 0.0f,
        side, 0.25*side,0.0f, // triangle 2 : end
    };
    this->object_rec_1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_NAVY_BLUE, GL_FILL);
    this->object_rec_2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_2, COLOR_NAVY_BLUE, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_3, COLOR_FIRE, GL_FILL);
    this->object_rec_1_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
    this->object_rec_2_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_2, COLOR_BACKGROUND, GL_FILL);
    this->object_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_3, COLOR_BACKGROUND, GL_FILL);
}

void Enemy_2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_rec_1);
    draw3DObject(this->object_rec_2);
}
void Enemy_2::draw_midrib(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
}
void Enemy_2::clear(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_clear);
    draw3DObject(this->object_rec_1_clear);
    draw3DObject(this->object_rec_2_clear);
    
}
void Enemy_2::move_y(float bottom,float up) {
    if(this->position.y<bottom || this->position.y>up)
        this->speed *= -1;
    this->position.y += this->speed;

}
float Enemy_2::ret_x(){
    return this->position.x;
}
float Enemy_2::ret_y(){
    return this->position.y;
}