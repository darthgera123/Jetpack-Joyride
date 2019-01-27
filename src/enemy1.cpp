
#include "enemy1.h"
#include "main.h"

using namespace std;

Enemy_1::Enemy_1(float x, float y,float width, float height,float rotation=0.0) {
    double r=0.1;
    this->radius=r;
    this->position = glm::vec3(x, y, 0);
    this->height = height;
    this->width =width;
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    this->rotation = rotation; //collision detection flawed from 30 beyond
    const double PI = 3.141592;
	int n = 50;
	GLfloat circle_vertex_buffer_data[30*n];
    int i;
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data[9*i] =0.0f;
		circle_vertex_buffer_data[9*i+1] =0.0f;
		circle_vertex_buffer_data[9*i+2] =0.0f;
		
		circle_vertex_buffer_data[9*i+3] =r*cos(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+4] =r*sin(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+5] =0.0f;
		
		circle_vertex_buffer_data[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+8] =0.0f;
    }
    GLfloat circle_vertex_buffer_data_2[30*n];
    //int i;
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data_2[9*i] =width;
		circle_vertex_buffer_data_2[9*i+1] =0.0f;
		circle_vertex_buffer_data_2[9*i+2] =0.0f;
		
		circle_vertex_buffer_data_2[9*i+3] =r*cos(2*(PI/n)*i)+width;
		circle_vertex_buffer_data_2[9*i+4] =r*sin(2*(PI/n)*i);
		circle_vertex_buffer_data_2[9*i+5] =0.0f;
		
		circle_vertex_buffer_data_2[9*i+6] =r*cos(2*((i+1)%n)*(PI/n))+width;
		circle_vertex_buffer_data_2[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data_2[9*i+8] =0.0f;
    }
    // this->object_circle = create3DObject(GL_TRIANGLES, 3*n+9, circle_vertex_buffer_data, COLOR_LASER_YELLOW, GL_FILL);
    this->object_circle_2 = create3DObject(GL_TRIANGLES, 3*n+9, circle_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_circle = create3DObject(GL_TRIANGLES, 3*n+9, circle_vertex_buffer_data_2, COLOR_BLACK, GL_FILL);
    GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        1.0f*width,1.0f*height, 0.0f,
        1.0f*width, 0.0f, 0.0f, // triangle 1 : end
        0.0f, 1.0f*height,0.0f, // triangle 2 : begin
        1.0f*width,1.0f*height,0.0f,
        0.0f, 0.0f,0.0f, // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_FIRE, GL_FILL);
}

void Enemy_1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object_circle_2);
    draw3DObject(this->object_circle);
    
}
void Enemy_1::move_left() {
    this->position.x -= 0.04;
}
float Enemy_1::ret_radius(){
    return this->radius;
}
float Enemy_1::ret_x(){
    return this->position.x;
}
float Enemy_1::ret_y(){
    return this->position.y;
}