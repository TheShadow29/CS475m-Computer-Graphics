//
// Created by arktheshadow on 14/8/16.
//
#include <GL/glut.h>
#include "mydraw_class.hpp"
#include <iostream>
#include <fstream>
color_t red1 = color_t(1.0f,0.0f,0.0f);
color_t mix1 = color_t(1.0f,1.0f,0.0f);
pen_t *pen = new pen_t(0,red1,'d');
std::vector<point_t> mouse_point_clicks;
drawing_t* drawing = new drawing_t();
canvas_t* canvas = new canvas_t(*drawing);

std::ofstream ofile;

bool line_mode = false;
bool triangle_mode = true;
bool fill_mode = false;

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
color_t get_color_from_term()
{
    float r,g,b;
    std::cout << "Enter floats [0-1] rgb: ";
    std::cin >> r >> g >> b;
    return color_t(r,g,b);
}
int get_size_from_term()
{
    int s;
    std::cout << "Enter pen thickness: ";
    std::cin >> s;
    return s;
}
void write_point_to_file(point_t p)
{
    ofile << "x=" << p.getX() << " y=" << p.getY() << " rgb=" << p.get_point_color().R()
    << p.get_point_color().G() << p.get_point_color().B();
    return;
}

void InitCanvas()
{
    color_t bgcolor = get_color_from_term();
    canvas_t* new_canvas = new canvas_t(win_width, win_height, bgcolor);
    canvas = new_canvas;
    pen->set_back_color(bgcolor);
    return;
}
void change_pen_color()
{
    color_t pen_color = get_color_from_term();
    pen->set_pen_color(pen_color);
    return;
}
///change back color not working completely
void change_back_color()
{
    color_t back_color = get_color_from_term();
    canvas->set_back_color(back_color, *pen);
    canvas->clear();
    drawing->draw(canvas->get_pixel_array(),*pen);
    return;
}
void change_pen_width()
{
    int size = get_size_from_term();
    pen->set_pen_size(size);
    return;
}
void save_drawing()
{
    ofile.open("saved_drawing.txt");
    std::cout << "started writing to file" << std::endl;
    ofile << "lets start"<< std::endl;
    drawing_t drawing1 = canvas->get_current_drawing();
    std::vector<line_t> l1 = drawing1.get_lines_list();
    std::vector<triangle_t> t1 = drawing1.get_triangles_list();
    for (int i = 0; i < l1.size(); i++)
    {
        ofile << "line" << i << " A=";
        write_point_to_file(l1[i].getA());
        ofile << "B=";
        write_point_to_file(l1[i].getB());
    }
    for (int i = 0; i < t1.size(); i++)
    {
        ofile << "triangle" << i << " A=";
        write_point_to_file(t1[i].getA());
        ofile << "B=";
        write_point_to_file(t1[i].getB());
        ofile << "C=";
        write_point_to_file(t1[i].getC());
    }
    ofile<<"ending";
    ofile.close();
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

void fill_triangle()
{
    fill_mode = true;
}


void left_button_function(int x, int y)
{
    if (pen->get_mode() == 'd')
    {
        if (!triangle_mode)
        {
            if (line_mode)
            {
                point_t *tmp = new point_t(x, win_height - y, pen->get_pen_color());
                //            disp_mouse_pointer_click(mouse_point_clicks);
                mouse_point_clicks.push_back(*tmp);
                delete tmp;
                if (mouse_point_clicks.size() % 2 == 0)
                {
                    std::cout << "line 97" << std::endl;
                    point_t b = mouse_point_clicks.back();
                    mouse_point_clicks.pop_back();
                    point_t a = mouse_point_clicks.back();
                    mouse_point_clicks.pop_back();
                    line_t l1(a, b);
                    l1.draw(canvas->get_pixel_array(), *pen);
                    drawing->lines_list.push_back(l1);
                }
            }
        }
        else
        {
            std::cout << "line 119" << std::endl;
            point_t* tmp = new point_t(x, win_height - y, pen->get_pen_color());
            mouse_point_clicks.push_back(*tmp);
            disp_mouse_pointer_click(mouse_point_clicks);
            delete tmp;
            bool fill = false;
            if (mouse_point_clicks.size()%3 == 0)
            {
                point_t c = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                point_t b = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                point_t a = mouse_point_clicks.back();
                std::cout<<a.getY()<<" "<<a.getX()<<std::endl;
                mouse_point_clicks.pop_back();
                triangle_t t1(a,b,c);
                std::cout<<mouse_point_clicks.empty()<<" check condition"<<std::endl;   
                //point_t centroid((a.getX()+b.getX()+c.getX())/3, (a.getY()+b.getY()+c.getY())/3); 
                //fill_t fillTriangle(red1);
                t1.draw(canvas->get_pixel_array(), *pen);       
                //fillTriangle.draw(canvas->get_bgc(), red1, red1, canvas->get_pixel_array(), centroid);

                drawing->triangles_list.push_back(t1);
                return;
            }
        }
        //std::cout<<fill_mode<<" "<<triangle_mode<<std::endl;

        if(fill_mode)
        {
            point_t centroid = mouse_point_clicks.back();
            mouse_point_clicks.pop_back();
            std::cout<<centroid.getY()<<" "<<centroid.getX()<<std::endl;
            fill_t fillTriangle(red1);
            fillTriangle.draw(canvas->get_bgc(), red1, mix1, canvas->get_pixel_array(), centroid);
            fill_mode = false;
            return;
        }

    }
    
}
