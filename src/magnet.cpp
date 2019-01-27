#include "magnet.h"
#include "main.h"


using namespace std;

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    float r =0.25;
    this->radius = r;
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
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
    GLfloat clear_vertex[] = {
        -r+r,-r,0.0f, // triangle 1 : begin
        r+r,r, 0.0f,
        -r+r, r, 0.0f, // triangle 1 : end
        r+r, -r,0.0f, // triangle 2 : begin
        r+r,r,0.0f,
        -r+r, -r,0.0f, // triangle 2 : end
    };
    GLfloat upper_vertex[] = {
        0.0f,r,0.0f, // triangle 1 : begin
        0.0f,r/2, 0.0f,
        r, r, 0.0f, // triangle 1 : end
        r, r/2,0.0f, // triangle 2 : begin
        r,r,0.0f,
        0, r/2, 0.0f, // triangle 2 : end
    };
    GLfloat lower_vertex[] = {
        0.0f,-r,0.0f, // triangle 1 : begin
        0.0f,-r/2, 0.0f,
        r, -r, 0.0f, // triangle 1 : end
        r, -r/2,0.0f, // triangle 2 : begin
        r,-r,0.0f,
        0, -r/2, 0.0f, // triangle 2 : end
    };
    GLfloat North_vertex[] = {
        3*r/4,r,0.0f, // triangle 1 : begin
        3*r/4,r/2, 0.0f,
        r, r, 0.0f, // triangle 1 : end
        r, r/2,0.0f, // triangle 2 : begin
        r,r,0.0f,
        3*r/4, r/2, 0.0f, // triangle 2 : end
    };
    GLfloat South_vertex[] = {
        3*r/4,-r,0.0f, // triangle 1 : begin
        3*r/4,-r/2, 0.0f,
        r, -r, 0.0f, // triangle 1 : end
        r, -r/2,0.0f, // triangle 2 : begin
        r,-r,0.0f,
        3*r/4, -r/2, 0.0f, // triangle 2 : end
    };
    GLfloat clean_vertex[] = {
        -r,-r,0.0f, // triangle 1 : begin
        r,r, 0.0f,
        -r, r, 0.0f, // triangle 1 : end
        r, -r,0.0f, // triangle 2 : begin
        r,r,0.0f,
        -r, -r,0.0f, // triangle 2 : end
    };
    this->object_base = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_FIRE, GL_FILL);
    this->object_cut = create3DObject(GL_TRIANGLES, 6, clear_vertex, COLOR_BACKGROUND, GL_FILL);
    this->object_upper = create3DObject(GL_TRIANGLES, 6, upper_vertex, COLOR_FIRE, GL_FILL);
    this->object_lower = create3DObject(GL_TRIANGLES, 6, lower_vertex, COLOR_FIRE, GL_FILL);
    this->object_North = create3DObject(GL_TRIANGLES, 6, North_vertex, COLOR_GREY, GL_FILL);
    this->object_South = create3DObject(GL_TRIANGLES, 6, South_vertex, COLOR_GREY, GL_FILL);
    this->object_clear = create3DObject(GL_TRIANGLES, 6, clean_vertex, COLOR_BACKGROUND, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_base);
    draw3DObject(this->object_cut);
    draw3DObject(this->object_upper);
    draw3DObject(this->object_lower);
    draw3DObject(this->object_North);
    draw3DObject(this->object_South);
    
}
void Magnet::clear(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_clear);
}
float Magnet::ret_x(){
    return this->position.x;
}
float Magnet::ret_y(){
    return this->position.y;
}
