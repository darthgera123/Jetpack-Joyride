#include "main.h"
#include "timer.h"
#include "brick.h"
#include "player.h"
#include "coin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "magnet.h"
#include "water.h"
#include "propulsion.h"
#include "special.h"
#include "segment.h"
#include "semi.h"
#include "dragon.h"
#include "ice.h"
#include <vector>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Brick brick[200];
Brick ceiling[20];
Player p;
int coin_count = 10;
vector<Coin> v_coin;
bounding_box_t player_collison;
vector<bounding_box_t>coin_collision;
vector<Enemy_1> v_e1;
vector<bounding_box_t> e1_collision;
Enemy_2 e1,e2;
vector<Enemy_2> v_e2;
vector<Enemy_3> v_boomer;
bounding_box_t boomer_t;
vector<Magnet> m;
vector<Water> w;
vector<bounding_box_t> w_t;
vector<Prop> jp;
vector<Special> sp;
Segment seg_ones,seg_tens,seg_hs,seg_st,seg_life;
vector<Semi> semi;
vector<Dragon>dragon;
vector<Ice> v_ice;

long long int boomer_counter =0;
long long int magnet_counter =1;
long long int stage=1;
long long int ice_counter =0;
long long int stage_counter =0;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float top    = screen_center_y + 4 / screen_zoom;
float bottom = screen_center_y - 4 / screen_zoom;
float LEFT   = screen_center_x - 4 / screen_zoom;
float RIGHT  = screen_center_x + 4 / screen_zoom;
Timer t60(1.0 / 60);
void screen_draw(glm::mat4 VP){
    for(int i=0;i<20;i++){
        brick[i].draw(VP);
    }
    for(int i=0;i<10;i++){
        ceiling[i].draw(VP);
    }
}
// Collision of line segments
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
  // calculate the distance to intersection point
     bool I;
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
     if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
         return true;
     }return false;

}
bounding_box_t rotation(bounding_box_t a, float rotation)
{
    float angle = -(rotation *M_PI)/180;
    float tempy1 = a.X1-a.x;
    float tempy2 = a.X2-a.x;
    float tempy3 = a.Y1-a.y;
    float tempy4 = a.Y2-a.y;
    a.X1 = tempy1*cos(angle) + tempy3*sin(angle);
    a.X2 = tempy2*cos(angle) + tempy4*sin(angle);
    a.Y1 = -tempy1*sin(angle) + tempy3*cos(angle);
    a.Y2 = -tempy2*sin(angle) + tempy4*cos(angle);
    a.X1 += a.x;
    a.X2 += a.x;
    a.Y1 += a.y;
    a.Y2 += a.y;
    return a;

}
void screen_init(){
    for(int i=0;i<10;i++){
        if(i%2)
            brick[i] = Brick(-5+i,-2.5,COLOR_RED,1);
        else
            brick[i] = Brick(-5+i,-2.5,COLOR_GREEN,1);
    }
    for(int i=0;i<10;i++){
        if(i%2)
        brick[i+10] = Brick(-5+i,-3.5,COLOR_GREEN,1);
        else
        brick[i+10] = Brick(-5+i,-3.5,COLOR_RED,1);

    }
    for(int i=0;i<10;i++){
        ceiling[i] = Brick(-5+i,4.3,COLOR_BLACK,1);
    }
}
double GenerateRandom(double min, double max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    if (min > max)
    {
        std::swap(min, max);
    }
    return min + (double)rand() * (max - min) / (double)RAND_MAX;
}
bounding_box_t player_bounding_box(Player p)
{   
    player_collison.x = p.ret_x();
    player_collison.y = p.ret_y();
    player_collison.x1 = p.ret_x()-p.radius;
    player_collison.x2 = p.ret_x()+p.radius;
    player_collison.x3 = p.ret_x()+p.radius;
    player_collison.x4 = p.ret_x()-p.radius;
    player_collison.y1 = p.ret_y()+2*p.radius;
    player_collison.y2 = p.ret_y()+2*p.radius;
    player_collison.y3 = p.ret_y()-2*p.radius;
    player_collison.y4 = p.ret_y()-2*p.radius;
    return player_collison;
}
//coin_generation 
void coin_generation(bounding_box_t player_collison,glm::mat4 VP){
    vector<bounding_box_t>::iterator itb;
    vector<Coin>::iterator it;
    itb = coin_collision.begin();
    for(it = v_coin.begin();it!=v_coin.end();it++)
    {
        itb->x = it->ret_x();
        itb->y = it->ret_y();
        if(detect_collision(player_collison,*itb))
        {
            system("aplay sound/coin.wav &");
            p.set_score(it->type*10);
            it->clear(VP);
            v_coin.erase(it);
            coin_collision.erase(itb);
            it--;
            itb--;
            cout<<p.score<<endl;
        }
        else if(it->ret_x()< LEFT){
            v_coin.erase(it);
            it--;
            
        }
        else{
            it->move_left();
            it->draw(VP);
        }
        itb++;
    }
    if(v_coin.size()<10)
    {
        for(int i=0;i<2;i++)
        {
            double u = GenerateRandom(4,10);
            double v = GenerateRandom(-1.5,3);
            int p = rand()%2+1;
            v_coin.push_back(Coin(u,v,p));
            bounding_box_t coin;
            coin.height = 2*v_coin.back().radius;
            coin.width = 2*v_coin.back().radius;
            coin_collision.push_back(coin);
        }
    }
}
//enemy_1 generation
void enemy1_generation(bounding_box_t player_collison, glm::mat4 VP){
    vector<bounding_box_t>::iterator ite1;
    vector<Enemy_1>::iterator ite;
    ite1 = e1_collision.begin();
    int flag =0;
    for(ite = v_e1.begin();ite!=v_e1.end();ite++){
        ite1->x = ite->ret_x();
        ite1->y = ite->ret_y();
        ite1->X1 = ite->ret_x()-ite->radius;
        ite1->X2 = ite->ret_x()+3*ite->radius+ite->width;
        ite1->Y1 = ite->ret_y();
        ite1->Y2 = ite->ret_y();
        *ite1 = rotation(*ite1,ite->rotation);
        bool i1 = lineLine(player_collison.x2,player_collison.y2,player_collison.x3,player_collison.y3,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
        bool i2 = lineLine(player_collison.x1,player_collison.y1,player_collison.x4,player_collison.y4,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
        bool i3 = lineLine(player_collison.x2,player_collison.y2,player_collison.x1,player_collison.y1,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
        bool i4 = lineLine(player_collison.x4,player_collison.y4,player_collison.x3,player_collison.y3,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
        if(i1||i2||i3||i4){
            system("aplay sound/jump.wav &");
            p.life -= 1;
            cout<<p.life<<endl;
            if(p.life< 0)
            {
                cout<<"Collide"<<endl;
                quit(window);
            }
            else{
                p.set_position(-2,-1.9);
                p.draw(VP);
            }
            
        }
        vector<Water>::iterator w_it;
        for(w_it = w.begin();w_it!=w.end();w_it++)
        {
            bounding_box_t w_temp;
            w_temp.x = w_it->ret_x();
            w_temp.y = w_it->ret_y();
            w_temp.x1 = w_temp.x-w_it->radius;
            w_temp.x2 = w_temp.x+w_it->radius;
            w_temp.y1 = w_temp.y+w_it->radius;
            w_temp.y2 = w_temp.y+w_it->radius;
            w_temp.x3 = w_temp.x+w_it->radius;
            w_temp.x4 = w_temp.x-w_it->radius;
            w_temp.y3 = w_temp.x-w_it->radius;
            w_temp.y4 = w_temp.x-w_it->radius;
            bool i1 = lineLine(w_temp.x2,w_temp.y2,w_temp.x3,w_temp.y3,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
            bool i2 = lineLine(w_temp.x1,w_temp.y1,w_temp.x4,w_temp.y4,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
            bool i3 = lineLine(w_temp.x2,w_temp.y2,w_temp.x1,w_temp.y1,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
            bool i4 = lineLine(w_temp.x4,w_temp.y4,w_temp.x3,w_temp.y3,
                        ite1->X1,ite1->Y1,ite1->X2,ite1->Y2);
            if(i1||i2||i3||i4)
            {
                flag=1;
                system("aplay sound/kill.wav &");
                cout<<"Kill"<<endl;
                p.score += 50;
                break;
            }
        }
        if(ite1->X2< LEFT || flag)
        {
            v_e1.erase(ite);
            ite--;
        }else{
            ite->move_left();
            ite->draw(VP);
        }
    }
}
void create_enemy1(){
        double u = GenerateRandom(RIGHT,10);
        double v = GenerateRandom(-1.5,2);
        double h = GenerateRandom(0.01,0.05);
        double w = GenerateRandom(1.0,2.5);
        double r = GenerateRandom(-15,90);
        v_e1.push_back(Enemy_1(u,v,w,h,r));
        bounding_box_t e1;
        e1.height = 0.1;
        e1.width = w;
        e1_collision.push_back(e1);
}
void create_boomer(){
    v_boomer.push_back(Enemy_3(RIGHT,2.5,LEFT,-2));
    boomer_t.height = 2*v_boomer[0].side;
    boomer_t.width = 2*v_boomer[0].side;
    
}
int enemy3_generation(bounding_box_t player_collison, glm::mat4 VP) {
    
    int flag=0;
    vector<Enemy_3>::iterator it;
    for(it=v_boomer.begin();it!=v_boomer.end();it++){
        int flag =0;
        it->gravity();
        it->rotate();
        it->move_down();
        it->move_left();
        boomer_t.x = it->ret_x();
        boomer_t.y = it->ret_y();
        vector<Water>::iterator w_it;
        for(w_it = w.begin();w_it!=w.end();w_it++)
        {
            bounding_box_t w_temp;
            w_temp.x = w_it->ret_x();
            w_temp.y = w_it->ret_y();
            w_temp.height = 2* w_it->radius;
            w_temp.width = 2* w_it->radius;
            if(detect_collision(w_temp,boomer_t))
            {
                system("aplay sound/kill.wav &");
                flag=1;
                cout<<"Kill"<<endl;
                p.score += 50;
                break;
            }
        }
        if(detect_collision(player_collison,boomer_t))
        {
            system("aplay sound/jump.wav &");
            p.life -= 1;
            if(p.life < 0){
                cout<<"Collision"<<endl;
                quit(window);
            }else{
                p.set_position(-2,-1.9);
                p.draw(VP);
            }
        }
        if(it->ret_x() == it->original){
           v_boomer.erase(it);
           it--; 
        }else if(flag){
            v_boomer.erase(it);
            it--;
        }
        else{
            it->draw(VP);
        }
    }
    return flag;
}
void magnet_draw(glm::mat4 VP){
    if(magnet_counter%100 == 0){
        if(m.size())
        {
            m[0].clear(VP);
            m.clear();
        }
        else{
            double u = GenerateRandom(-3,-1.5);
            double v = GenerateRandom(-1,2);
            m.push_back(Magnet(u,v));
        }
    }
    if(m.size())
        m[0].draw(VP);
}
void create_enemy2(){
    v_e2.push_back(Enemy_2(LEFT,-1.2,7,1));
    v_e2.push_back(Enemy_2(LEFT,-1,7,-1));
}
void enemy2_lifetime(bounding_box_t player_collison, glm::mat4 VP){
    for(int i=0;i<v_e2.size();i++)
    {
        v_e2[i].timer++;
        if(v_e2[i].timer > 150)
        {
            v_e2[i].lethal =1;
            v_e2[i].draw_midrib(VP);
        }
        v_e2[i].move_y(-2.5,2.8);
        v_e2[i].draw(VP);
    }
    
    vector<Enemy_2>:: iterator e2_it;
    bounding_box_t eb;
    for(e2_it = v_e2.begin();e2_it!= v_e2.end();e2_it++)
    {
        eb.x = e2_it->ret_x()+e2_it->side+e2_it->width/2;
        eb.y = e2_it->ret_y()+e2_it->side/2;
        eb.height = 0.5*e2_it->side;
        eb.width = e2_it->width-0.75;
        vector<Water>::iterator w_it;
        for(w_it = w.begin();w_it!=w.end();w_it++)
        {
            bounding_box_t w_temp;
            w_temp.x = w_it->ret_x();
            w_temp.y = w_it->ret_y();
            w_temp.height = 2* w_it->radius;
            w_temp.width = 2* w_it->radius;
            if(detect_collision(w_temp,eb) && e2_it->lethal)
            {
                system("aplay sound/kill.wav &");
                e2_it->clear(VP);
                v_e2.erase(e2_it);
                e2_it--;
                p.score += 50;
                break;
            }
        }
        if(detect_collision(player_collison,eb) && e2_it->lethal){
            system("aplay sound/jump.wav &");
            p.life -= 1;
            if(p.life< 0)
            {
                cout<<"Collide"<<endl;
                quit(window);
            }
            else{
                p.position.x = -2;
                p.position.y = -1.9;
                p.draw(VP);
            }
        }
    }
}
Player special_lifetime(bounding_box_t player_collison, glm::mat4 VP, Player p){
    vector<Special>::iterator s_it;
    for(s_it = sp.begin();s_it != sp.end(); s_it ++)
    {
        bounding_box_t s;
        s.x = s_it->ret_x();
        s.y = s_it->ret_y();
        s.height = 2*s_it->radius;
        s.width = 2*s_it->radius;
        if(detect_collision(player_collison,s))
        {
            cout<<"Powerup"<<endl;
            if(s_it->type==0){
                cout<<"Higher"<<endl;
                p.speed_t.v_y *= 1.5;
            }
            else{
                cout<<"Life"<<endl;
                p.life += 1;
            }
            sp.erase(s_it);
            s_it--;
        }
        
        else{
            if(s_it->ret_x()+s_it->radius < LEFT)
            {
                sp.erase(s_it);
                s_it--;   
            }
            else    {
                s_it->move();
                s_it->draw(VP);
                }
        }
    }
    return p;
}
void display_score(glm::mat4 VP){
    int tStage = stage;
    long long int tScore = p.score;
    int tScore_h = tScore/1000;
    tScore %= 1000;
    int tScore_t = tScore/100;
    tScore %= 100;
    int tScore_o = tScore/10;
    tScore %= 10;
    if(tScore_o==0)
        seg_ones.draw_0(VP);
    if(tScore_o==1)
        seg_ones.draw_1(VP);
    if(tScore_o==2)
        seg_ones.draw_2(VP);
    if(tScore_o==3)
        seg_ones.draw_3(VP);
    if(tScore_o==4)
        seg_ones.draw_4(VP);
    if(tScore_o==5)
        seg_ones.draw_5(VP);
    if(tScore_o==6)
        seg_ones.draw_6(VP);
    if(tScore_o==7)
        seg_ones.draw_7(VP);
    if(tScore_o==8)
        seg_ones.draw_8(VP);
    if(tScore_o==9)
        seg_ones.draw_9(VP);
    
    if(tScore_t==0)
        seg_tens.draw_0(VP);
    if(tScore_t==1)
        seg_tens.draw_1(VP);
    if(tScore_t==2)
        seg_tens.draw_2(VP);
    if(tScore_t==3)
        seg_tens.draw_3(VP);
    if(tScore_t==4)
        seg_tens.draw_4(VP);
    if(tScore_t==5)
        seg_tens.draw_5(VP);
    if(tScore_t==6)
        seg_tens.draw_6(VP);
    if(tScore_t==7)
        seg_tens.draw_7(VP);
    if(tScore_t==8)
        seg_tens.draw_8(VP);
    if(tScore_t==9)
        seg_tens.draw_9(VP);
    
    if(tScore_h==0)
        seg_hs.draw_0(VP);
    if(tScore_h==1)
        seg_hs.draw_1(VP);
    if(tScore_h==2)
        seg_hs.draw_2(VP);
    if(tScore_h==3)
        seg_hs.draw_3(VP);
    if(tScore_h==4)
        seg_hs.draw_4(VP);
    if(tScore_h==5)
        seg_hs.draw_5(VP);
    if(tScore_h==6)
        seg_hs.draw_6(VP);
    if(tScore_h==7)
        seg_hs.draw_7(VP);
    if(tScore_h==8)
        seg_hs.draw_8(VP);
    if(tScore_h==9)
        seg_hs.draw_9(VP);
    
    if(tStage==0)
        seg_st.draw_0(VP);
    if(tStage==1)
        seg_st.draw_1(VP);
    if(tStage==2)
        seg_st.draw_2(VP);
    if(tStage==3)
        seg_st.draw_3(VP);
    if(tStage==4)
        seg_st.draw_4(VP);
    if(tStage==5)
        seg_st.draw_5(VP);
    if(tStage==6)
        seg_st.draw_6(VP);
    if(tStage==7)
        seg_st.draw_7(VP);
    if(tStage==8)
        seg_st.draw_8(VP);
    if(tStage==9)
        seg_st.draw_9(VP);
    
    if(p.life==0)
        seg_life.draw_0(VP);
    if(p.life==1)
        seg_life.draw_1(VP);
    if(p.life==2)
        seg_life.draw_2(VP);
    if(p.life==3)
        seg_life.draw_3(VP);
    if(p.life==4)
        seg_life.draw_4(VP);
    if(p.life==5)
        seg_life.draw_5(VP);
    if(p.life==6)
        seg_life.draw_6(VP);
    if(p.life==7)
        seg_life.draw_7(VP);
    if(p.life==8)
        seg_life.draw_8(VP);
    if(p.life==9)
        seg_life.draw_9(VP);
}
void create_semi(){
    if(semi.size()==0)
    {
        semi.push_back(Semi(6,0));
    }
}
void move_on_semi(glm::mat4 VP){
    if(semi.size())
    {
        semi[0].move();
        p.circle_radius = semi[0].radius;
        p.circle_center_y = semi[0].ret_y();
        p.circle_center_x = semi[0].ret_x();
        if(p.circle_center_x + p.circle_radius < LEFT-1)
        {
            semi.clear();
        }
        else{
            semi[0].draw(VP);
        }

    }
}
void dragon_slayer(bounding_box_t player_collison, glm::mat4 VP){
    if(dragon.size()){
        ice_counter++;
        if(ice_counter >100)
        {
            v_ice.push_back(Ice(dragon[0].ret_x()-0.5*dragon[0].radius,dragon[0].ret_y()));
            ice_counter =0;
        }
        vector<Ice>::iterator ice_t;
        for(ice_t = v_ice.begin();ice_t!=v_ice.end();ice_t++)
        {
            ice_t->move(LEFT);
            ice_t->draw(VP);
            if(ice_t->ret_x() < LEFT)
            {
                v_ice.erase(ice_t);
                ice_t--;
            }
            bounding_box_t it;
            it.x = ice_t->ret_x();
            it.y = ice_t->ret_y();
            it.height = 2*ice_t->radius;
            it.width = 2*ice_t->radius;
            if(detect_collision(player_collison,it))
            {
                system("aplay sound/jump.wav &");
                cout<<"Collide"<<endl;
                p.life --;
                if(p.life<0){
                    quit(window);
                }else{
                    p.set_position(-2,-1.9);
                    p.draw(VP);
                }
                v_ice.erase(ice_t);
                ice_t--;
            }
        }
        dragon[0].move(p.ret_y());
        dragon[0].draw(VP);
        bounding_box_t d;
        d.x = dragon[0].ret_x()-0.5*dragon[0].radius;
        d.y = dragon[0].ret_y();
        d.height = 2*dragon[0].radius;
        d.width = 2.5*dragon[0].radius;
        if(detect_collision(player_collison,d))
        {
            system("aplay sound/jump.wav &");
            cout<<"Collide"<<endl;
                p.life --;
                if(p.life<0){
                    quit(window);
                }else{
                    p.set_position(-2,-1.9);
                    p.draw(VP);
                }
        }
        vector<Water>::iterator w_it;
        for(w_it = w.begin();w_it!=w.end();w_it++)
        {
            bounding_box_t w_temp;
            w_temp.x = w_it->ret_x();
            w_temp.y = w_it->ret_y();
            w_temp.height = 2* w_it->radius;
            w_temp.width = 2* w_it->radius;
            if(detect_collision(w_temp,d))
            {
                v_ice.clear();
                dragon.clear();
                system("aplay sound/kill.wav &");
                cout<<"Kill"<<endl;
                p.score += 50;
                break;
            }
        }
    }
}
void create_dragon(){
    double u =GenerateRandom(2,4);
    dragon.push_back(Dragon(u,0));
}
void create_powerup(){
    int p = rand()%2;
    cout<<p<<endl;
    sp.push_back(Special(5.5,-2.2,-2.2,p));
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye (0,0,1);// Now we can view the box from z-axis, it appears 2D
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    screen_draw(VP);
    player_collison = player_bounding_box(p);
    stage_counter++;
    if(stage_counter > 1200){
        stage+= 1;
        stage_counter =0;
    }
    if(stage == 1)
    {
        
        magnet_draw(VP);
        magnet_counter ++;
        if(v_e1.size()==0)
            create_enemy1();
        enemy1_generation(player_collison,VP);
    }
    if(stage == 3)
    {
        semi.clear();
        p.circle=0;
        if(v_e2.size()==0)
            create_enemy2();
        enemy2_lifetime(player_collison,VP);
    }
    if(stage == 2)
    {
        p.circle =1;
        if(semi.size()==0)
            create_semi();
        move_on_semi(VP);
        if(sp.size()<1){
            create_powerup();
        }
        p = special_lifetime(player_collison,VP,p);
        
           
    }
    if(stage == 4)
    {
        if(sp.size()<1){
            create_powerup();
        }
        p = special_lifetime(player_collison,VP,p);
        create_dragon();
        dragon_slayer(player_collison,VP);

    }
    if(stage ==5){
        cout<<"Game over"<<endl;
        quit(window);
    }
    coin_generation(player_collison,VP);
    if(boomer_counter>300){
        boomer_counter =0;
        create_boomer();
    }
    enemy3_generation(player_collison,VP);
    display_score(VP);
    p.draw(VP);
    vector<Water>::iterator w_it;
    for(w_it = w.begin();w_it!=w.end();w_it++)
    {
        
        if(w_it->move()){
            w.erase(w_it);
            w_it--;
        }else{
        w_it->draw(VP);
        }
    }
    vector<Prop>::iterator pit;
    for(pit = jp.begin();pit!=jp.end();pit++)
    {
        if(bool(pit->move())){
            jp.erase(pit);
            pit--;
        }else{
        pit->draw(VP);
        }
    }
    
}

void tick_input(GLFWwindow *window) {
    int left_move  = glfwGetKey(window, GLFW_KEY_LEFT); 
    int right_move = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up_move = glfwGetKey(window, GLFW_KEY_SPACE);
    int x_move = glfwGetKey(window, GLFW_KEY_X);
    int z_zoom = glfwGetKey(window,GLFW_KEY_Z);
    float angle = M_PI/180.0;
    float pos_x = p.ret_x()+p.radius*cos(angle*45);
    float pos_y = p.ret_y()+p.radius*sin(angle*45);
    if (left_move) {
        pos_x -= p.speed_t.v_x;
        p.move_left(LEFT);
    }
    if(right_move) {
        pos_x += p.speed_t.v_x;

        p.move_right(RIGHT);
    }
    if(up_move) {
        pos_y += p.speed_t.v_y;
        jp.push_back(Prop(p.ret_x(),p.ret_y()-2*p.radius,-2.5));
        p.jump();   
    }
    if(x_move){
        //for delay

        w.push_back(Water(pos_x,pos_y,-2.5));
    }
    if(z_zoom){
        //reset_screen zoom
        screen_zoom = 1;
        reset_screen();
    }
    
}

void tick_elements() {
    p.gravity();
    if(m.size()){
        float pos = m[0].ret_x()+2.5*m[0].radius;
        p.magnet(pos,m[0].ret_y(),m[0].radius);
    }
    
    boomer_counter += 1;
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    //Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);
    for(int i=0;i<10;i++)
    {
        double u = GenerateRandom(-1.5,10);
        double v = GenerateRandom(-1.5,3);
        int p = rand()%2+1;
        v_coin.push_back(Coin(u,v,p));
        bounding_box_t coin;
        coin.height = 2*v_coin.back().radius;
        coin.width = 2*v_coin.back().radius;
        coin_collision.push_back(coin);
    }
    p = Player(-2,-1.9,-2,2.8);
    player_collison.width = 2*p.radius;
    player_collison.height = 4*p.radius;
    //
    seg_ones = Segment(3.2,3.6,0,screen_zoom);
    seg_tens = Segment(2.8,3.6,0,screen_zoom);
    seg_hs = Segment(2.4,3.6,0,screen_zoom);
    seg_st = Segment(-3,3.6,1,screen_zoom);
    seg_life = Segment(-2,3.6,2,screen_zoom);
    create_boomer();
    screen_init();
    

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    bounding_box_t b1,b2;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 <= (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
