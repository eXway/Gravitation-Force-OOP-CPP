#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#define pi 3.14159265359
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;


/**
 * @brief Function used for obtaining random integer number between X and Y
 */
int RAND(int X, int Y);

/**
* @bief Function for checking if the string input could be considered as a number
*/
bool check_number(string str);

/**
 * @brief Structure for defining line, the idea was to use it for mouse input
 */
struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
};

/**
 * @brief Class for Particle (or just element) with needed parameters
 * \param x = absolute (in px) horizontal position
 * \param y = absolute (in px) vertical position
 * \param r = radius of element (visual purpuses)
 * \param vx = velocity (or delta position) in horizontal vector
 * \param vy = velocity (or delta position) in vertical vector
 * \param m = true mass for calculating force
 * \param rest = rest parameters was made for relational positioning, not absolute
 */
class Particle {
public:
    double x;
    double y;
    double r;
    double vx;
    double vy;
    double m;
    double color[3];

    string name;
    double mass;
    string relation;
    double distance;
    double speed;

    Particle(double tx, double ty, double tr, double tvx, double tvy, double tm);
    Particle();

 /**
 * @brief Function for converting floating point values of relational values into right data type
 * \param index = what data is to be changed 
 * \param value = value of data to be changed
 */
    void valueOfProp(int index, double value);

/**
* @brief Function for converting string values of relational values into right data type
* \param index = what data is to be changed
* \param value = value of data to be changed
*/
    void valueOfProp(int index, string value);
/**
* @brief Debuging function for printing particle data
*/
    void printAll();
    ~Particle();
};

/**
 * @brief Function for adding one static and n number of random moving objects 
 * \param n = Number of randomly generated object
 */
void particleInit(int n);

/**
* @brief Debuging function for printing number of all particles, their position and mass
*/
void particleDebug();

/**
* @brief Utility function that uses Allegro library to draw all elements
*/
void particleDraw();

/**
* @brief Function for adding particle to particles Vector with set position
*/
void addParticle(float x, float y, float m, float r, bool randColor, float vx, float vy);

/**
* @brief Function for adding particle to particles Vector with random position
*/
void addParticle(float m, float r, bool randColor, float vx, float vy);

/**
* @brief Function for adding particle with random parameters to particles Vector
*/
void addParticle(float x, float y);

/**
* @brief Function for updating particle coodinates using velocity and gravitational force
*/
void movement();


/**
 * @brief Class for Allegro 5 canvas initiation and animation handling
 * \param x = width of an Allegro 5 window
 * \param y = height of an Allego 5 window
 */
class canvas {
    int x{};
    int y{};
    
public:
    ALLEGRO_EVENT_QUEUE* eQueue{};
    ALLEGRO_DISPLAY* display{};
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_KEYBOARD_STATE keyboard{};
    ALLEGRO_EVENT event{};
    canvas(int ix = 1000, int iy = 1000, const char* ititle = "3D program");
    void keyframe();
    bool endCondition();
    bool FrameInit(ALLEGRO_COLOR bg = al_map_rgb(0, 0, 0));
    ~canvas();
};