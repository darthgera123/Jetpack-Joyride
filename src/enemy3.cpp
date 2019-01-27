#include "enemy3.h"
#include "main.h"
#include <unistd.h>

using namespace std;

Enemy_3::Enemy_3(float x, float y,float top,float bottom) {
    this->position = glm::vec3(x, y, 0);
    float side =0.4;
    this->rotation = 1;
    this->speed_player.v_x = 0.155;
    this->speed_player.v_y = 0.022;
    this->speed_player.d_x = 0;
    this->speed_player.g_x = 0.0015;
    this->top = top;
    this->original = x;
    this->bottom = bottom;
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        -side,0.0f, 0.0f,
        0.0f, -side, 0.0f, // triangle 1 : end
    };
    GLfloat vertex_buffer_data_2[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        0.0f,side, 0.0f,
        side, 0.0f, 0.0f, // triangle 1 : end
    };
    this->object_upper = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->object_lower = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_2, COLOR_DARK_GREEN, GL_FILL);
}

void Enemy_3::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_upper);
    draw3DObject(this->object_lower);
    
    
}
void Enemy_3::move_y(float bottom,float up) {
    if(this->position.y<bottom || this->position.y>up)
        this->speed *= -1;
    this->position.y += this->speed;

}
void Enemy_3::move_down(){
    if(this->position.y > this->bottom)
        this->position.y -= this->speed_player.v_y;
}
void Enemy_3::move_left(){
    if(this->position.y > this->bottom)
        this->position.x -= this->speed_player.v_x;
}
void Enemy_3::gravity(){
    if(this->position.x < this->original){
        this->position.x += this->speed_player.d_x;
        this->speed_player.d_x += this->speed_player.g_x;
        if(this->position.x > this->original)
        {
            this->position.x = this->original;
        }
    }
    else{
        this->speed_player.d_x =0;
    }
}
float Enemy_3::ret_x(){
    return this->position.x;
}
float Enemy_3::ret_y(){
    return this->position.y;
}
void Enemy_3::rotate(){
    this->rotation += 100;
}