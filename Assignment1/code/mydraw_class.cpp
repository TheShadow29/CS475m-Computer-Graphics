#include "mydraw_class.hpp"
#include <iostream>
#define sgn(x) (x>0)?1:((x<0)?-1:0)

//global variables
color_t red = color_t(1.0f,0.0f,0.0f);
color_t green = color_t(0.0f,1.0f,0.0f);
color_t blue = color_t(0.0f,0.0f,1.0f);
color_t black = color_t(0.0f,0.0f,0.0f);
color_t white = color_t(1.0f,1.0f,1.0f);
void bresenham_octant(int delX, int delY, int x11, int y11, pen_t pen, point_t** pixel_array, bool is_steep);
void bresenham_octant_negative(int delX, int delY, int x11, int y11, pen_t pen, point_t** pixel_array, bool is_steep);

int abs(int x)
{
    if (x >= 0)
    { return  x;}
    else
    {
        return -x;
    }
}

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
        :size(2*_size+1), pen_color(_pen_color), mode(_mode) {}
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
void point_t::set_point_color(color_t color) {point_color = color; }
void point_t::draw_direct(point_t** pixel_array)
{
    pixel_array[y][x] = *this;
}
void point_t::draw(point_t** pixel_array, pen_t pen)
{
    pixel_array[y][x] = *this;
    int thick = pen.get_size()/2;
    color_t color = pen.get_pen_color();
    int y_min = (y - thick > 0)?(y-thick):0;
    int x_min = (x - thick > 0)?(x-thick):0;

    for (int i = y_min; i <= y + thick; i++)
    {
        for (int j = x_min; j <= x + thick; j++)
        {
//            std::cout << "line 59 " << "pen_size" << pen.get_size() << std::endl;
//            std::cout << "line 68 " << "i=" << i << " j=" << j << std::endl;
//            std::cout << "line 69 " << "x_min=" << x_min << " y_min=" << y_min << std::endl;
//            std::cout << "line 69 " << "x+thick=" << x + thick << " y+thick=" << y+thick << std::endl;
            point_t* c = new point_t(j,i,color);
            c->draw_direct(pixel_array);
            delete c;
        }
    }
}

//-------------------------
// 5. line_t methods
line_t::line_t(point_t _a, point_t _b) :a(_a), b(_b) { };
void line_t::draw(point_t** pixel_array, pen_t pen)
{
    color_t color = pen.get_pen_color();
    int s1 = sgn(b.getX() - a.getX());
    if (s1 == -1)
    {
        point_t* tmp = new point_t(a.getX(),a.getY(),a.get_point_color());
        a = b;
        b = *tmp;
        delete tmp;
    }
    // a stores the left point
    int eps_dash = 0;
    int x1 = a.getX(), y1 = a.getY(), x2 = b.getX(), y2 = b.getY();
    int delX = abs(x2 - x1);
    int delY = abs(y2 - y1);
    bool is_steep = delY > delX;
    std::cout << "line 103 a_x=" << x1 << " a_y=" << y1 << std::endl;
    std::cout << "line 104 b_x=" << x2 << " b_y=" << y2 << std::endl;
    std::cout << "line 105 delX=" << delX << std::endl;
    std::cout << "line 106 delY=" << delY << std::endl ;
    std::cout << "line 107 is_steep" << is_steep << std::endl;
    int x11 = x1, y11 = y1;
    std::cout << "line 119 x11=" << x11 << std::endl;
    std::cout << "line 120 y11=" << y11 << std::endl;
    s1 = sgn(x2 - x1);
    int s2 = sgn(y2 - y1);
    int slope_dir = sgn(s1 * s2);
    bool slope_pos = (slope_dir>=0);


    if (!is_steep)
    {
        if (slope_pos)
        {
            bresenham_octant(delX,delY,x11,y11,pen,pixel_array, is_steep);
        }
        else
        {
            bresenham_octant_negative(x2 - x1,y2 - y1,x11,y11,pen,pixel_array, is_steep);
        }
    }
    else
    {
        if(slope_pos)
        {
            bresenham_octant(delY, delX, y11, x11, pen, pixel_array, is_steep);
        }
        else
        {
            std::cout << "line 129" << std::endl;
            bresenham_octant_negative(y1 - y2,x1 - x2,b.getY(),b.getX(),pen,pixel_array,is_steep);
        }
    }
    return;
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
drawing_t::drawing_t(std::vector <line_t> _lines_list, std::vector <triangle_t> _triangles_list)
                : lines_list(_lines_list), triangles_list(_triangles_list){ }
void drawing_t::draw()
{

}
//--------------------------
// 8. canvas methods
canvas_t::canvas_t() : width(640), height(480), background_color(white)
{
    this->clear();
}
canvas_t::canvas_t(int _width, int _height) :width(_width), height(_height), background_color(white)
{
    this->clear();
}
canvas_t::canvas_t(int _width, int _height, color_t _background_color)
            :width(_width), height(_height), background_color(_background_color)
{
    this->clear();
}
canvas_t::canvas_t(int _width, int _height, drawing_t _current_drawing, color_t _background_color,
                   point_t **_pixel_array)
                :width(_width), height(_height), background_color(_background_color), pixel_array(_pixel_array){}

void canvas_t::clear()
{
    pixel_array = new point_t* [height];
    for(int i = 0; i < height; i++)
    {
        pixel_array[i] = new point_t [width];
        for(int j = 0; j < width; j++)
        {
            pixel_array[i][j] = point_t(j,i, background_color);
        }
    }
}
point_t** canvas_t::get_pixel_array() {return pixel_array; }
int canvas_t::getW() { return width; }
int canvas_t::getH() { return height; }
color_t canvas_t::get_bgc() { return background_color; }

void bresenham_octant(int delX, int delY, int x11, int y11, pen_t pen, point_t** pixel_array, bool is_steep)
{
    int eps_dash = 0;
    color_t color = pen.get_pen_color();
    for (int i = 0; i < delX; ++i)
    {
        point_t* c = new point_t();
        if (!is_steep)
        {
            *c = point_t(x11,y11, color);
        }
        else
        {
            *c = point_t(y11,x11,color);
        }
        c->draw(pixel_array, pen);
        delete c;
        if (2*(eps_dash + delY) < delX)
        {
            eps_dash += delY;
        }
        else
        {
            eps_dash += delY - delX;
            y11 += 1;
        }
        x11 += 1;
    }
}
void bresenham_octant_negative(int delX, int delY, int x11, int y11, pen_t pen, point_t** pixel_array, bool is_steep)
{
    int eps_dash = 0;
    color_t color = pen.get_pen_color();
    std::cout << "line 219 delX=" << delX << std::endl;
    std::cout << "line 219 delY=" << delY << std::endl;
    std::cout << "line 238 x11=" << x11 << std::endl;
    std::cout << "line 239 y11=" << y11 << std::endl;
    for (int i = 0; i < delX; ++i)
    {

        point_t* c = new point_t();
        if (!is_steep){*c = point_t(x11,y11,color);}
        else{*c = point_t(y11,x11,color);}
        c->draw(pixel_array,pen);
        delete c;
        if (2*(eps_dash + delY) > -delX)
        {
            eps_dash = eps_dash + delY;
        }
        else
        {
            y11 -= 1;
            eps_dash = eps_dash + delY + delX;
        }
        x11 += 1;
    }
}