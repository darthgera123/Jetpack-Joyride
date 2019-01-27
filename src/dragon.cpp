#include "dragon.h"
#include "main.h"


using namespace std;

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    float r =0.3;
    this->radius = r;
    this->type = type;
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
    GLfloat vertex_buffer_data[] = {
        -1.5*r,r*sin(M_PI/4),0.0f, // triangle 1 : begin
        -r*cos(M_PI/4),r*sin(M_PI/4), 0.0f,
        -r*cos(M_PI/4), 0.0f, 0.0f, // triangle 1 : end
        -r*cos(M_PI/4), -r*sin(M_PI/4),0.0f, // triangle 2 : begin
        -r*cos(M_PI/4),0.0f,0.0f,
        -1.5*r, -r*sin(M_PI/4),0.0f, // triangle 2 : end
    };
        this->object_circle = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_MAGENTA, GL_LINE);
        //this->object_clear = create3DObject(GL_TRIANGLES, 3*n, clear_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
        this->object_beak = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);  
    draw3DObject(this->object_beak);
    draw3DObject(this->object_circle);
    //draw3DObject(this->object_clear_upper);
}

float Dragon::ret_x(){
    return this->position.x;
}
float Dragon::ret_y(){
    return this->position.y;
}
void Dragon::move(float y){
    this->position.y = y;
}
