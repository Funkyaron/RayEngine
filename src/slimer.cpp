#include "REImage.h"
#include "vec3.h"
#include "util.h"

/**
 * Basic idea: Multiple Neighbourhood Cellular Automata simulation developed by Slackermanz
 */

struct ring {
    int min_rad;
    int max_rad;
    float alive_min;
    float alive_max;
    float dead_min;
    float dead_max;
    float correction;
    float critical_correction;
};

int main() {
    int width = 400;
    int height = 300;

    REImage* current = new REImage(width, height);
    REImage* previous = new REImage(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            current->set_pixel(x, y, vec3(get_random_number(), 0, 0));
        }
    }

    int num_rings = 2;
    ring* rings = new ring[num_rings];

    rings[0].min_rad = 1;
    rings[0].max_rad = 3;
    rings[0].alive_min = 0.65;
    rings[0].alive_max = 0.95;
    rings[0].dead_min = 0.07;
    rings[0].dead_max = 0.3;
    rings[0].correction = 0.1;
    rings[0].critical_correction = 0.4;

    rings[1].min_rad = 4;
    rings[1].max_rad = 5;
    rings[1].alive_min = 0.7;
    rings[1].alive_max = 0.9;
    rings[1].dead_min = 0.05;
    rings[1].dead_max = 0.3;
    rings[1].correction = -0.13;
    rings[1].critical_correction = -0.56;

    current->print_to_png("slimer-0.png");

    int num_frames = 2000;
    for(int frame = 1; frame <= num_frames; frame++) {
        std::cout << "Current frame: " << frame << std::endl;
        REImage* temp = current;
        current = previous;
        previous = temp;
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                float current_state = previous->get_pixel(x, y).r();
                for(int r = 0; r < num_rings; r++) {
                    float neighborhood_state = 0.0f;
                    int neighborhood_size = 0;
                    for(int neighy = -rings[r].max_rad; neighy <= rings[r].max_rad; neighy++) {
                        for(int neighx = -rings[r].max_rad; neighx <= rings[r].max_rad; neighx++) {
                            if(abs(neighx) < rings[r].min_rad && abs(neighy) < rings[r].min_rad) continue;
                            neighborhood_state += previous->get_pixel(x + neighx, y + neighy).r();
                            neighborhood_size++;
                        }
                    }
                    neighborhood_state /= float(neighborhood_size);
                    if(neighborhood_state >= rings[r].alive_min && neighborhood_state <= rings[r].alive_max) {
                        current_state += rings[r].correction;
                    } else if(neighborhood_state >= rings[r].dead_min && neighborhood_state <= rings[r].dead_max) {
                        current_state -= rings[r].correction;
                    } else if(neighborhood_state >= rings[r].alive_max) {
                        current_state -= rings[r].critical_correction;
                    } else if(neighborhood_state <= rings[r].dead_min) {
                        current_state += rings[r].critical_correction;
                    } else {
                        //Don't change state
                    }
                }
                if(current_state > 1) current_state = 1;
                if(current_state < 0) current_state = 0;
                current->set_pixel(x, y, vec3(current_state, 0, 0));
            }
        }
        std::string filename = "slimer-" + std::to_string(frame) + ".png";
        current->print_to_png(filename);
    }
    
    return 0;
}