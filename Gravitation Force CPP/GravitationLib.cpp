#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#define pi 3.14159265359
#define eps 6
#define depth 200
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

#include "GravitationLIb.h"


Line line;
vector<Particle> particles;
int GlobalX = 1, GlobalY = 1;

bool check_number(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

int RAND(int X, int Y) {
    return (rand() % (Y - X)) + X;
}



Particle::Particle(double tx, double ty, double tr, double tvx, double tvy, double tm) {
    double x = tx; //absolute x position
    double y = ty; //absolute y position
    double r = tr; //radius
    double vx = tvx;//velocity in x vector
    double vy = tvy;//velocity in y vector  
    double m = tm; //mass
    double color[3];
}
Particle::Particle() {
    double x = 0; //absolute x position
    double y = 0; //absolute y position
    double r = 0; //radius
    double vx = 0;//velocity in x vector
    double vy = 0;//velocity in y vector  
    double m = 0; //mass
    double color[3] = {255,255,255};
}

void Particle :: valueOfProp(int index, double value) {
    switch (index) {
    case 0:
        name = to_string(value);
    case 1:
        mass = value;
    case 2:
        relation = to_string(value);
    case 3:
        distance = value;
    case 4:
        speed = value;
    }
}
void Particle :: valueOfProp(int index, string value) {
    switch (index) {
    case 0:
        name = value;
    case 1:
        mass = atof(value.c_str());//atof - cstyle string to float (c converts float to double) | c_str - string to cstyle string
        //Usage of this functions was necessery - otherwise there is memory problem (in stod function), atof() was a safer choice
    case 2:
        relation = value;
    case 3:
        distance = atof(value.c_str());
    case 4:
        speed = atof(value.c_str());
    }
}
void Particle :: printAll() {
    cout << "(" << name << ", " << mass << ", " << relation << ", " << distance << ", " << speed << ")" << endl;
}

Particle::~Particle() {}

void addParticle(float x, float y, float m, float r, bool randColor, float vx, float vy)
{
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = vx / 50;
    p.vy = vy / 50;
    p.m = m;
    p.r = r;
    if (randColor)
    {
        p.color[0] = RAND(0, 255);
        p.color[1] = RAND(0, 255);
        p.color[2] = RAND(0, 255);
    }
    else
    {
        p.color[0] = 255;
        p.color[1] = 255;
        p.color[2] = 0;
    }
    particles.push_back(p);

    if (line.x1 != 0)
        line.x1 = line.x2 = line.y1 = line.y2 = 0;
}

void addParticle(float m, float r, bool randColor, float vx, float vy)
{
    Particle p;
    p.x = RAND(0, GlobalX);
    p.y = RAND(0, GlobalY);
    p.vx = vx / 50;
    p.vy = vy / 50;
    p.m = m;
    p.r = r;
    if (randColor)
    {
        p.color[0] = RAND(0, 255);
        p.color[1] = RAND(0, 255);
        p.color[2] = RAND(0, 255);
    }
    else
    {
        p.color[0] = 255;
        p.color[1] = 255;
        p.color[2] = 0;
    }
    particles.push_back(p);

    if (line.x1 != 0)
        line.x1 = line.x2 = line.y1 = line.y2 = 0;
}

void addParticle(float x, float y)
{
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = (RAND(0, 150) - 75) / 50;
    p.vy = (RAND(0, 150) - 75) / 50;
    p.m = RAND(10, 4000);
    p.r = RAND(5, 30);
    p.color[0] = RAND(0, 255);
    p.color[1] = RAND(0, 255);
    p.color[2] = RAND(0, 255);

    particles.push_back(p);

    if (line.x1 != 0)
        line.x1 = line.x2 = line.y1 = line.y2 = 0;
}

void movement() {
    for (int i = 0; i < particles.size(); i++)
    {
        Particle& p = particles[i];
        bool not_fall = true;
        for (int j = 0; j < particles.size(); j++)
        {
            if (j == i || p.m >= 10000) continue; //For these masses we can consider them as infinite 


            const Particle& p1 = particles[j];

            float d = sqrt((p1.x - p.x) * (p1.x - p.x) + (p1.y - p.y) * (p1.y - p.y));

            if (d > p1.r)
            {
                p.vx += 0.02 * p1.m / (d * d) * (p1.x - p.x) / d; //f = ma => a = f/m
                p.vy += 0.02 * p1.m / (d * d) * (p1.y - p.y) / d;
            }
            else
                not_fall = false;
        }

        if (not_fall)
        {
            p.x += p.vx;
            p.y += p.vy;
        }
        else
            particles.erase(particles.begin() + i);

    }

}

//canvas

void particleInit(int n) {
    Particle p;
    //initial centered Huge mass particle
    p.x = GlobalX/2;
    p.y = GlobalY/2;
    p.vx = p.vy = 0;
    p.m = 10000;
    p.r = 30;
    p.color[0] = 255;
    p.color[1] = 255;
    p.color[2] = 255;
    particles.push_back(p);

    for (int i = 0; i < n; i++) {
        addParticle(RAND(10, 4000), RAND(5, 30), true, RAND(0, 100) -50, RAND(0, 100)-50);
    }
}

void particleDebug() {
    cout << "Elements: " << particles.size() << endl;

    Particle part;
    for (auto& part : particles) {
        cout << "Position (" << part.x << ", " << part.y << ") | raduis = " << part.r << endl;
    }
}
void particleDraw() {
    for (int i = 0; i < particles.size(); i++) {
        Particle& p = particles[i];
        al_draw_circle(p.x, p.y, p.r, al_map_rgb(p.color[0], p.color[1], p.color[2]), 3);
    }
}

canvas::canvas(int ix, int iy, const char* ititle) : x{ ix }, y{ iy } 
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    display = al_create_display(x, y);
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_window_title(display, ititle);
    GlobalX = x;
    GlobalY = y;
    eQueue = al_create_event_queue();
    al_register_event_source(eQueue, al_get_display_event_source(display));
    al_register_event_source(eQueue, al_get_mouse_event_source());
}

void canvas::keyframe() {
    al_flip_display();
    al_rest(0.005);
}
bool canvas::endCondition() {
    return !al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE);
}
bool canvas::FrameInit(ALLEGRO_COLOR bg) {
    al_get_next_event(eQueue, &event);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { return true; }
    al_get_keyboard_state(&keyboard);
    al_clear_to_color(bg);
    return false;
}

canvas::~canvas() {
    al_destroy_display(display);
    al_destroy_event_queue(eQueue);
}
