#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "gravitationLib.h"

using namespace std;


int main(int argc, char** argv)
{
    int seed = 1230;
    srand(seed);
    
    string src;
    cout << "There is one premade file for checking program it is called: data.csv\n";
    cout << "Load file, if you want to get your simulation with random values enter number of random elemetns: ";
    cin >> src;


    canvas Canvas1(1000, 1000, "Gravitational Force");
    cout << "\nGenerating canvas\nPress Escape key to exit Allegro window\n";


    /**
    * @brief This block is made for chacking file and input data 
    */
    if (!check_number(src)) {
        ifstream data(src);
        if (data.is_open()) {
            string temp;
            while (getline(data, temp)){
                replace(temp.begin(), temp.end(), ',', ' ');
                int x, y, m, r, vx, vy;
                bool color;
                stringstream ss;
                ss << temp;
                ss >> x >> y >> m >> r >> color >> vx >> vy;
                addParticle(x, y, m, r, color, vx, vy);
            }
            data.close();

        }
        else {
            cout << "There is a problem with opening the file\n";
            return 1;
        }

    } else {
        particleInit(stoi(src));
    }

    //particleDebug();


    while (Canvas1.endCondition()) {

        if (Canvas1.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            addParticle(Canvas1.event.mouse.x, Canvas1.event.mouse.y);
        }

            if (Canvas1.FrameInit()) return 0;
                // Code goes here -

            particleDraw();
            movement();

                // - end of code 
            Canvas1.keyframe();
    }
    return 0;
}






