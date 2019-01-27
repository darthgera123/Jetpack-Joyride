#include "player.h"
#include "main.h"

using namespace std;

Player::Player(float x, float y, float platform_y,float ceiling_y) {
    double r=0.30;
    this->radius =r;
    this->score =0;
    this->shield =0;
    this->life=3;
    this->position = glm::vec3(x, y, 0);
    this->platform_y = platform_y+0.45*r;
    this->ceiling_y = ceiling_y-0.45*this->radius;
    this->speed_t.v_x = 0.1;
    this->speed_t.v_y = 0.1;
    this->speed_t.g = 0.0009;
    this->speed_t.m_g = 0.0009;
    this->speed_t.d_y = 0;
    this->speed_t.m_x = 0;
    this->speed_t.m_y = 0;
    this->circle=0;
    this->circle_center_x=0;
    this->circle_radius = 0;
    this->circle_center_y = 0;
    const double PI = 3.141592;
	int n = 50;
	GLfloat circle_vertex_buffer_data[30*n];
    GLfloat lower_triangle_vertex_buffer_data[30*n];
    GLfloat upper_triangle_vertex_buffer_data[30*n];
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

       lower_triangle_vertex_buffer_data[0] = -r/2;
       lower_triangle_vertex_buffer_data[1] = -r;
       lower_triangle_vertex_buffer_data[2] = 0.0f;
       lower_triangle_vertex_buffer_data[3] = r/2;
       lower_triangle_vertex_buffer_data[4] = -r;
       lower_triangle_vertex_buffer_data[5] = 0.0f;
       lower_triangle_vertex_buffer_data[6] = 0.0f;
       lower_triangle_vertex_buffer_data[7] = -2*r;
       lower_triangle_vertex_buffer_data[8] = 0.0f;

       upper_triangle_vertex_buffer_data[0] = -r/2;
       upper_triangle_vertex_buffer_data[1] = r;
       upper_triangle_vertex_buffer_data[2] = 0.0f;
       upper_triangle_vertex_buffer_data[3] = r/2;
       upper_triangle_vertex_buffer_data[4] = r;
       upper_triangle_vertex_buffer_data[5] = 0.0f;
       upper_triangle_vertex_buffer_data[6] = 0.0f;
       upper_triangle_vertex_buffer_data[7] = 2*r;
       upper_triangle_vertex_buffer_data[8] = 0.0f;

       GLfloat vertex_buffer_data[] = {
        -r,2*r,0.0f, // triangle 1 : begin
        r,2*r, 0.0f,
        -r, -2*r, 0.0f, // triangle 1 : end
        -r, -2*r,0.0f, // triangle 2 : begin
        r,-2*r,0.0f,
        r, 2*r,0.0f, // triangle 2 : end
    };
           
    this->object_circle = create3DObject(GL_TRIANGLES, 3*n+9, circle_vertex_buffer_data, COLOR_MILD_PURPLE, GL_LINE);
    this->object_lower_triangle = create3DObject(GL_TRIANGLES, 3, lower_triangle_vertex_buffer_data, COLOR_ORANGE, GL_FILL);
    this->object_upper_triangle = create3DObject(GL_TRIANGLES, 3, upper_triangle_vertex_buffer_data, COLOR_ORANGE, GL_FILL);
    this->object_shield = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->object_remove = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_circle);
    draw3DObject(this->object_lower_triangle);
    draw3DObject(this->object_upper_triangle);
}

void Player::draw_shield(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_circle);
    draw3DObject(this->object_shield);
}
void Player::remove_shield(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_circle);
    draw3DObject(this->object_remove);
}
void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::move_left(float left) {
    if(this->position.x > left+this->radius)
    {
        float circle_pos = this->circle_radius;
        float py =this->position.y -2*radius-this->circle_center_y;
        float px = this->position.x-this->circle_center_x;
        float distance = sqrt(pow(py,2)+pow(px,2));
        float angle = 25*M_PI/180.0;
        if(distance > circle_pos -0.05 && distance < circle_pos + 0.05 && py < this->circle_center_y && this->circle)
        {
            float t1 = this->position.x-this->circle_center_x;
            float t2 = this->position.y-this->circle_center_y;

            this->position.x = t1*cos(this->speed_t.v_x*angle) +t2*sin(this->speed_t.v_y*angle)+this->circle_center_x;
            this->position.y = -t1*sin(this->speed_t.v_x*angle) +t2*cos(this->speed_t.v_y*angle)+this->circle_center_y;
        }
        else{
            this->position.x -= this->speed_t.v_x;
        }
    }
}
void Player::move_right(float right) {
    if(this->position.x < right - this->radius){
        float circle_pos = this->circle_radius;
        float py =this->position.y -2*radius-this->circle_center_y;
        float px = this->position.x-this->circle_center_x;
        float distance = sqrt(pow(py,2)+pow(px,2));
        float angle = -25*M_PI/180.0;
        if(distance > circle_pos -0.05 && distance < circle_pos + 0.05 && py < this->circle_center_y && this->circle)
        {
            float t1 = this->position.x-this->circle_center_x;
            float t2 = this->position.y-this->circle_center_y;

            this->position.x = t1*cos(this->speed_t.v_x*angle) +t2*sin(this->speed_t.v_y*angle)+this->circle_center_x;
            this->position.y = -t1*sin(this->speed_t.v_x*angle) +t2*cos(this->speed_t.v_y*angle)+this->circle_center_y;
        }
        else{
            this->position.x += this->speed_t.v_x;
        }
    }
}
void Player::jump() {
    if(this->position.y < this->ceiling_y){
        this->position.y += this->speed_t.v_y;
        this->speed_t.d_y -= this->speed_t.g;
    }
}
void Player::gravity() {
    this->speed_t.g = 0.0009;
    if(this->inair()){
        this->position.y -= this->speed_t.d_y;
        this->speed_t.d_y += this->speed_t.g;
        if(this->position.y < this->platform_y)
        {
            this->position.y = this->platform_y;
        }
    }
    else{
        this->speed_t.d_y =0;
    }
}
bool Player::inair() {
    if(this->position.y > this->platform_y){
        float circle_pos = this->circle_radius;
        float py =this->position.y -2*radius-this->circle_center_y;
        float px = this->position.x-this->circle_center_x;
        float distance = sqrt(pow(py,2)+pow(px,2));
        if(distance > circle_pos -0.05 && distance < circle_pos + 0.05 && py < this->circle_center_y &&this->circle)
        {
            return false;   
        }
        return true;
    }
    return false;
}
float Player::ret_x() {
    return this->position.x;
}
float Player::ret_y() {
    return this->position.y;
}
float Player::ret_radius() {
    return this->radius;
}
int Player::set_score(int score) {
    this->score += score;
}
void Player::magnet(float x,float y,float m_radius) {
    if(this->position.x  > x)
    {
        this->speed_t.g = 0;
        this->position.x -= this->speed_t.m_x;
        this->speed_t.m_x += this->speed_t.m_g;
        if(this->position.x  < x)
        {
            this->position.x = x;
        }
        if(!(this->position.y > y && this->position.y < y))
        {
            if(this->position.y < y - m_radius)
            {
                this->position.y += this->speed_t.m_y;
                this->speed_t.m_y += this->speed_t.m_g/2;
            }
            if(this->position.y  > y + m_radius)
            {
                this->position.y -= this->speed_t.m_y;
                this->speed_t.m_y += this->speed_t.m_g/2;
            }
        }
    }
    else{
        this->speed_t.m_x =0;
        this->speed_t.g = 0.0009;
        this->speed_t.m_y =0;
    }
}