#include "special.h"
#include "main.h"


using namespace std;

Special::Special(float x, float y, float bottom,int type) {
    this->position = glm::vec3(x, y, 0);
    float r =0.3;
    this->radius = r;
    this->type = type;
    this->speed.v_x = -0.04;
    this->speed.v_y = 0.1;
    this->speed.g = 0.001;
    this->speed.d_y =0;
    const double PI = 3.141592;
    this->bottom = bottom;
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
        -r,r,0.0f, // triangle 1 : begin
        r,r, 0.0f,
        -r, -r, 0.0f, // triangle 1 : end
        -r, -r,0.0f, // triangle 2 : begin
        r,-r,0.0f,
        r, r,0.0f, // triangle 2 : end
    };
    if(type == 0){
        this->object_circle = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_MAGENTA, GL_FILL);
        this->object_base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_CYAN, GL_FILL);
    }
    else{
        this->object_circle = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_LASER_YELLOW, GL_FILL);
        this->object_base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    }
    this->object_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
}

void Special::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_base);
    draw3DObject(this->object_circle);
}

float Special::ret_x(){
    return this->position.x;
}
float Special::ret_y(){
    return this->position.y;
}
int Special::move(){
    this->position.x += this->speed.v_x;
    this->position.y += this->speed.v_y;
    if(this->position.y > this->bottom){
        this->position.y -= this->speed.d_y;
        this->speed.d_y += this->speed.g;
        if(this->position.y < this->bottom){
            this->position.y = this->bottom;
            return 1;
        }
        return 0;
    }
    else{
        return 1;
    }
}