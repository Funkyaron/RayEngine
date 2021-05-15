#ifndef IMAGEH
#define IMAGEH

#include "../lib/lodepng/lodepng.h"
#include "vec3.h"

class REImage {
    public:
    REImage() {}
    REImage(unsigned _width, unsigned _height) {
        width = _width;
        height = _height;
        pixels.resize(width * height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                pixels[x + width * y] = vec3(0,0,0);
            }
        }
    }

    inline void set_pixel(int x, int y, vec3 color);
    inline vec3 get_pixel(int x, int y);

    inline unsigned get_width() {return width;}
    inline unsigned get_height() {return height;}


    //void print_to_png(const char* filename);
    void print_to_png(std::string filename);

    private:
    unsigned width;
    unsigned height;
    std::vector<vec3> pixels;
};

inline void REImage::set_pixel(int x, int y, vec3 color) {
    x = x % width;
    x = x < 0 ? x + width : x;
    y = y % height;
    y = y < 0 ? y + height : y;
    /*if(color[0] < 0) color[0] = 0;
    if(color[0] > 1) color[0] = 1;
    if(color[1] < 0) color[1] = 0;
    if(color[1] > 1) color[1] = 1;
    if(color[2] < 0) color[2] = 0;
    if(color[2] > 1) color[2] = 1;*/
    pixels[x + width * y] = color;
}

inline vec3 REImage::get_pixel(int x, int y) {
    x = x % width;
    x = x < 0 ? x + width : x;
    y = y % height;
    y = y < 0 ? y + height : y;
    return pixels[x + width * y];
}

//void REImage::print_to_png(const char* filename) {
void REImage::print_to_png(std::string filename) {
    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            vec3 col = pixels[x + width * y];
            // Gamma correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            image[4 * width * y + 4 * x + 0] = char(255.99 * col[0]);
            image[4 * width * y + 4 * x + 1] = char(255.99 * col[1]);
            image[4 * width * y + 4 * x + 2] = char(255.99 * col[2]);
            image[4 * width * y + 4 * x + 3] = 255; // Alpha
        }
    }

    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

#endif