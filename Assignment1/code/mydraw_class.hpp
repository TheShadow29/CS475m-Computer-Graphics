#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_
#include <vector>
//Define all classes like the color class, adding appropriate methods and data members. 
//Implementation of the methods go into the corresponding cpp files
//------------------------

//1. color_t class

class color_t
{
private:
  float r,g,b;
public:
  color_t();
    color_t(const float _r, const float _g, const float _b);

  void set(const float _r, const float _g, const float _b);
  float R(void);
  float G(void);
  float B(void);
};
//------------------
//2. pen_t class

class pen_t
{
private:
    int size;
    color_t pen_color;
    char mode;  // 'd' for draw and 'e' for eraser
public:
    pen_t();
    pen_t(int _size, color_t _pen_color, char _mode);
    int get_size();
    color_t get_pen_color();
    char get_mode();
};


//------------------------
// 3. fill_t
class fill_t
{
private:
    color_t current_fill_color;
public:
    fill_t(color_t _current_fill_color);
    void draw();
};

//-----------------------------
//4. point_t class
class point_t
{
private:
    int x;
    int y;
    color_t point_color;
public:
    point_t();
    point_t(int _x, int _y);
    point_t(int _x, int _y, color_t _point_color);
    int getX();
    int getY();
    color_t get_point_color();
    void set_point_color(color_t color);
    void draw_direct(point_t** pixel_array);
    void draw(point_t** pixel_array, pen_t pen);
};
//-------------------
//5. line_t class
class line_t
{
private:
    point_t a;
    point_t b;
public:
    line_t(point_t _a, point_t _b);
    void draw(point_t** pixel_array, pen_t pen);    //draws line with current color, use draw method from current class
};

//---------------------
//6. triangle_t class
class triangle_t
{
private:
    point_t a;
    point_t b;
    point_t c;
    color_t border_color;
public:
    triangle_t(point_t _a, point_t _b, point_t _c);
    void draw();
};

//----------------------
// 7. drawing_t class
class drawing_t
{
private:
    std::vector<line_t> lines_list;
    std::vector<triangle_t> triangles_list;
public:
    drawing_t();
    drawing_t(std::vector<line_t> _lines_list, std::vector<triangle_t> _triangles_list);
    void draw();
};

//----------------------
// 8. Canvas class
class canvas_t
{
private:
    drawing_t current_drawing;
    int width;
    int height;
    color_t background_color;
    point_t** pixel_array;
public:
    canvas_t();
    canvas_t(int _width, int _height);
    canvas_t(int _width, int _height, drawing_t _current_drawing, color_t _background_color,
                point_t** _pixel_array);
    canvas_t(int _width, int _height, color_t _background_color);
    void clear();
    int getW();
    int getH();
    color_t get_bgc();
    point_t** get_pixel_array();
    void display_to_screen();
    //2D array implementation
};

#endif

