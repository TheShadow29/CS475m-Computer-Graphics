#include "mydraw_class.hpp"
#include <vector>
//global variables
color_t red = color_t(1.0f,0.0f,0.0f);
color_t green = color_t(0.0f,1.0f,0.0f);
color_t blue = color_t(0.0f,0.0f,1.0f);
color_t black = color_t(0.0f,0.0f,0.0f);
color_t white = color_t(1.0f,1.0f,1.0f);

//-------------------
// 1. color_t methods

color_t::color_t() :r(0.0f), g(0.0f), b(0.0f){ }
color_t::color_t(const float _r, const float _g, const float _b)
		 :r(_r),g(_g),b(_b) { }

void color_t::set(const float _r, const float _g, const float _b)
{
  r=_r; g=_g; b=_b;
}

float color_t::R(void) { return r; }
float color_t::G(void) { return g; }
float color_t::B(void) { return b; }

//---------------------
// 2. pen_t methods
pen_t::pen_t() : size(1), pen_color(red), mode('d'){};
pen_t::pen_t(int _size, color_t _pen_color, char _mode)
        :size(size), pen_color(_pen_color), mode(_mode) {}
int pen_t::get_size()  { return size; }
color_t pen_t::get_pen_color()  { return pen_color; }
char pen_t::get_mode() { return mode; }

//-----------------------
// 3. fill_t methods
fill_t::fill_t(color_t _current_fill_color) : current_fill_color(_current_fill_color) {};
void fill_t::draw()
{
    //need to implement some fill algorithm
}

//------------------------
// 4. point_t methods
point_t::point_t() :x(0), y(0){ }
point_t::point_t(int _x, int _y) : x(_x), y(_y), point_color(white){};
point_t::point_t(int _x, int _y, color_t _point_color) : x(_x), y(_y), point_color(_point_color){ }
int point_t::getX() { return x; }
int point_t::getY() { return y; }
color_t point_t::get_point_color() { return point_color; }
void point_t::draw()
{

}

//-------------------------
// 5. line_t methods
line_t::line_t(point_t _a, point_t _b) :a(_a), b(_b) { };
void line_t::draw()
{

}

//-------------------------
// 6. triangle_t methods
triangle_t::triangle_t(point_t _a, point_t _b, point_t _c) :a(_a), b(_b), c(_c){ };
void triangle_t::draw()
{

}
//-------------------------------
// 7. drawing_t methods
drawing_t::drawing_t(){}
//drawing_t::drawing_t(vector <line_t> _lines_list, vector <triangle_t> _triangles_list)
//            :lines_list(_lines_list), triangles_list(_triangles_list){ }
drawing_t::drawing_t(std::vector <line_t> _lines_list, std::vector <triangle_t> _triangles_list)
                : lines_list(_lines_list), triangles_list(_triangles_list){ }
void drawing_t::draw()
{

}
//--------------------------
// 8. canvas methods
canvas_t::canvas_t() : width(640), height(480), background_color(white)
{
    pixel_array = new point_t* [height];
    for(int i = 0; i < height; i++)
    {
        pixel_array[i] = new point_t [width];
        for(int j = 0; j < width; j++)
        {
            pixel_array[i][j] = point_t(0,0);
        }
    }
}
canvas_t::canvas_t(int _width, int _height) :width(_width), height(_height), background_color(white)
{
    pixel_array = new point_t* [height];
    for(int i = 0; i < height; i++)
    {
        pixel_array[i] = new point_t [width];
        for(int j = 0; j < width; j++)
        {
            pixel_array[i][j] = point_t(0,0);
        }
    }
}
canvas_t::canvas_t(int _width, int _height, drawing_t _current_drawing, color_t _background_color,
                   point_t **_pixel_array)
                :width(_width), height(_height), background_color(_background_color), pixel_array(_pixel_array){ }
void canvas_t::clear()
{

}
point_t** canvas_t::get_pixel_array() {return pixel_array; }
int canvas_t::getW() { return width; }
int canvas_t::getH() { return height; }
color_t canvas_t::get_bgc() { return background_color; }


