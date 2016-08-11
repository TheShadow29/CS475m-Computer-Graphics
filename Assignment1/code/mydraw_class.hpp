#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_

//Define all classes like the color class, adding appropriate methods and data members. 
//Implementation of the methods go into the corresponding cpp file

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
    color_t color;
    char mode;  // 'd' for draw and 'e' for eraser
public:
    pen_t();
    pen_t(int _size, color_t _color, char _mode);
};


//------------------------
// 3. fill_t
class fill_t
{
private:
    color_t current_fill_color;
public:
    fill_t();
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
public:
    point_t(int _x, int _y);
    void draw();
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
    void draw();    //draws line with current color, use draw method from current class
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
    vector<line_t> lines_list;
    vector<triangle_t> triangles_list;
public:
    drawing_t();
    drawing_t(vector<line_t> _lines_list, vector<triangle_t> _triangles_list);
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
public:
    canvas_t();
    canvas_t(int _width, int _height, drawing_t _current_drawing, color_t background_color);
    void clear();
    //2D array implementation

};

#endif

