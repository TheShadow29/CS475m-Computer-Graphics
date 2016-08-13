//
// Created by arktheshadow on 14/8/16.
//
#include <GL/glut.h>
#include "mydraw_class.hpp"
#include <iostream>
color_t red1 = color_t(1.0f,0.0f,0.0f);
canvas_t* canvas = new canvas_t();
pen_t *pen = new pen_t(1,red1,'d');
std::vector<point_t> mouse_point_clicks;
bool line_mode = true;
bool triangle_mode = false;

//Window width
int win_width = 640;
//Window height
int win_height = 480;

void canvas_t::display_to_screen()
{
    GLubyte checkImage[this->height][this->width][3];
    point_t** arr = this->get_pixel_array();
    for(int i = 0; i < this-> height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            checkImage[i][j][0] = (GLubyte) int(arr[i][j].get_point_color().R()*255);
            checkImage[i][j][1] = (GLubyte) int(arr[i][j].get_point_color().G()*255);
            checkImage[i][j][2] = (GLubyte) int(arr[i][j].get_point_color().B()*255);
        }
    }
    glRasterPos2i(0,0);
    glDrawPixels(this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, checkImage);
}
void disp_color_t(color_t elm)
{
    std::cout << "red" << elm.R();
    std::cout << "green" << elm.G();
    std::cout << "blue" << elm.B()<< std::endl;
}

void disp_canv_array(canvas_t* canv)
{
    int w = canv -> getW();
    int h = canv -> getH();
    point_t** arr = canv->get_pixel_array();
    for(int i = 0; i < h; i++)
    {
        for (int j=0; j < w; j++)
        {
            std::cout << "i=" << i << " j=" << j << std::endl;
            disp_color_t(arr[i][j].get_point_color());
            std::cout << std::endl;
        }
    }
    return;
}

void InitCanvas()
{
    float r,g,b;
    std::cout << "Enter floats [0-1] rgb: ";
    std::cin >> r >> g >> b;
    color_t bgcolor(r,g,b);
    canvas_t* new_canvas = new canvas_t(win_width, win_height, bgcolor);
    canvas = new_canvas;
    return;
}
void disp_point(point_t p)
{
    std::cout << "x=" << p.getX() << " y=" << p.getY() << " rgb=" << p.get_point_color().R()
        << p.get_point_color().G() << p.get_point_color().B();
    return;
}

void disp_mouse_pointer_click(std::vector<point_t> mouse_clicks)
{
    for(std::vector<point_t>::const_iterator i = mouse_clicks.begin(); i != mouse_clicks.end(); ++i)
    {
        disp_point(*i);
    }
    return;
}


void left_button_function(int x, int y)
{
    if (pen->get_mode() == 'd')
    {
        if (line_mode)
        {
            point_t* tmp = new point_t(x,y,pen->get_pen_color());
            mouse_point_clicks.push_back(*tmp);
            delete tmp;
            if (mouse_point_clicks.size()%2 == 0)
            {
                std::cout << "line 97" << std::endl;
                point_t b = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                point_t a = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                line_t l1(a,b);
                l1.draw(canvas->get_pixel_array(), *pen);
            }
        }
    }
}
