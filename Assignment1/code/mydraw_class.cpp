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
void disp_point1(point_t p)
{
    std::cout << "x=" << p.getX() << " y=" << p.getY() << " rgb=" << p.get_point_color().R()
    << p.get_point_color().G() << p.get_point_color().B();
    return;
}
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
pen_t::pen_t(int _size, color_t _pen_color, char _mode, color_t _back_color)
        :size(2*_size+1), pen_color(_pen_color), mode(_mode), back_color(_back_color){ }
int pen_t::get_size()  { return size; }
color_t pen_t::get_pen_color()  { return pen_color; }
char pen_t::get_mode() { return mode; }
void pen_t::set_back_color(color_t color) {back_color = color;}
void pen_t::set_pen_color(color_t color) {pen_color = color; }
color_t pen_t::get_back_color() {return back_color; }
void pen_t::set_pen_size(int _size) { size = 2*_size + 1;}

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
    color_t color;
    if (pen.get_mode() == 'd')
    {
       color = pen.get_pen_color();
    }
    else
    {
        color = pen.get_pen_color();
    }

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
point_t line_t::getA() { return a; }
point_t line_t::getB() { return b; }
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
point_t triangle_t::getA() { return a; }
point_t triangle_t::getB() { return b; }
point_t triangle_t::getC() { return c; }
void triangle_t::draw(point_t **pixel_array, pen_t pen)
{
    line_t* l1 = new line_t(a,b);
    line_t* l2 = new line_t(b,c);
    line_t* l3 = new line_t(c,a);
    l1->draw(pixel_array,pen);
    l2->draw(pixel_array,pen);
    l3->draw(pixel_array,pen);
    delete l1;
    delete l2;
    delete l3;
}
//-------------------------------
// 7. drawing_t methods
drawing_t::drawing_t(){}
drawing_t::drawing_t(std::vector <line_t> _lines_list, std::vector <triangle_t> _triangles_list)
                : lines_list(_lines_list), triangles_list(_triangles_list){ }
std::vector<line_t> drawing_t::get_lines_list() { return lines_list; }
std::vector<triangle_t> drawing_t::get_triangles_list() { return triangles_list; }
void drawing_t::draw(point_t **pixel_array, pen_t pen)
{
    for (int i = 0; i < lines_list.size(); i++)
    {
        lines_list[i].draw(pixel_array, pen);
    }
    for (int i = 0; i < lines_list.size(); i++)
    {
        disp_point1(triangles_list[i].getA());
        disp_point1(triangles_list[i].getB());
        disp_point1(triangles_list[i].getC());
        triangles_list[i].draw(pixel_array,pen);
    }
    return;
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
canvas_t::canvas_t(drawing_t _current_drawing) :width(640), height(480), background_color(white),
            current_drawing(_current_drawing)
{
    this->clear();
}
void canvas_t::set_back_color(color_t color, pen_t pen)
{
    background_color = color;
    this->clear();
    //current_drawing.draw(pixel_array, pen);
}
drawing_t canvas_t::get_current_drawing() { return current_drawing; }

///BRESENHAM WORKING
/////DONOT EDIT ANYTHING PLZZ
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