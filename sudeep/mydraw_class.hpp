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
    color_t back_color;
    char mode;  // 'd' for draw and 'e' for eraser
public:
    pen_t();
    pen_t(int _size, color_t _pen_color, char _mode);
    pen_t(int _size, color_t _pen_color, char _mode, color_t _back_color);
    int get_size();
    color_t get_pen_color();
    color_t get_back_color();
    void set_back_color(color_t color);
    void set_pen_color(color_t color);
    void set_pen_size(int _size);
    char get_mode();
};




//-----------------------------
//3. point_t class
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
    bool checkIfSameColor(color_t color_compare);
};

//------------------------
// 4. fill_t
class fill_t
{
private:
    color_t current_fill_color;
public:
    fill_t(color_t _current_fill_color);
    void draw(color_t _background_color, color_t line_color, color_t _fill_color, point_t** pixel_array, point_t node);
};

//5. line_t class
class line_t
{
private:
    point_t a;
    point_t b;
public:
    line_t(point_t _a, point_t _b);
    void draw(point_t** pixel_array, pen_t pen);    //draws line with current color, use draw method from current class
    point_t getA();
    point_t getB();
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
    void draw(point_t** pixel_array, pen_t pen);
    point_t getA();
    point_t getB();
    point_t getC();
};

//----------------------
// 7. drawing_t class
class drawing_t
{
public:
    std::vector<line_t> lines_list;
    std::vector<triangle_t> triangles_list;
public:
    drawing_t();
    drawing_t(std::vector<line_t> _lines_list, std::vector<triangle_t> _triangles_list);
    void draw(point_t** pixel_array, pen_t pen);
    std::vector<line_t> get_lines_list();
    std::vector<triangle_t> get_triangles_list();
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
    canvas_t(drawing_t _current_drawing);
    void clear();
    int getW();
    int getH();
    color_t get_bgc();
    point_t** get_pixel_array();
    drawing_t get_current_drawing();
    void display_to_screen();
    void set_back_color(color_t color, pen_t pen);
    //2D array implementation
};

#endif

