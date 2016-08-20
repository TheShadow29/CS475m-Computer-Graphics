//
// Created by arktheshadow on 14/8/16.
//
#include <GL/glut.h>
#include "mydraw_class.hpp"
#include <string>
#include <iostream>
#include <fstream>
color_t red1 = color_t(1.0f,0.0f,0.0f);
color_t mix1 = color_t(1.0f,1.0f,0.0f);

std::vector<point_t> mouse_point_clicks;
drawing_t* drawing = new drawing_t();

std::ofstream ofile;
std::ifstream ifile;

bool line_mode = false;
bool triangle_mode = false;
bool fill_mode = false;


//Window width
int win_width = 1024;
//Window height
int win_height = 768;
canvas_t* canvas = new canvas_t(win_width, win_height,drawing);
pen_t *pen = new pen_t(0,red1,'d', canvas->get_bgc());
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
void disp_string_vec(std::vector<std::string> s, bool to_file)
{
    if (to_file)
    {
        for (int i = 0; i < s.size(); i++)
        {
            ofile << s[i];
        }
    }
    else
    {
        for (int i = 0; i < s.size(); i++)
        {
            std::cout << s[i];
        }
    }
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
std::string get_input_file_from_term()
{
    std::string s;
    std::cout << "Enter the relative file path: ";
    std::cin >> s;
    std::cout << "The file path you have entered is: " << s << std::endl;
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
    drawing->store_drawing(pen->toString());
    return;
}
///change back color not working completely
void change_back_color()
{
    color_t init_back_color = canvas->get_bgc();
    color_t back_color = get_color_from_term();
    canvas->set_back_color(init_back_color, back_color, *pen);
    pen->set_back_color(back_color);
    return;
}
void change_pen_width()
{
    int size = get_size_from_term();
    pen->set_pen_size(size);
    drawing->store_drawing(pen->toString());
    return;
}
void change_fill_color()
{
    mix1 = get_color_from_term();
}
void save_drawing()
{
    ofile.open("saved_drawing.txt");
    std::cout << "started writing to file" << std::endl;
    std::vector<std::string> s = canvas->get_current_drawing()->get_drawing_list();
    disp_string_vec(s,1);
    ofile.close();
}
void load_drawing()
{
    drawing->clear_drawing_list();
//    std::string file_name = get_input_file_from_term();
    std::string file_name = "saved_drawing.txt";
    ifile.open(file_name);
//    std::cout << "ifile.is_open() " << ifile.is_open() << std::endl;
    if (!ifile.is_open())
    {
        std::cout << "file not found.";
        return;
    }
    else
    {
        std::string line;
        std::string s1;
        while(std::getline(ifile, line))
        {
            s1.clear();
            if (line == "t")
            {
                s1 = line + "\n";
                for (int i = 0; i < 6; i++)
                {
                    std::getline(ifile, line);
                    s1 += line + "\n";
                }
                drawing->store_drawing(s1);
            }
            if (line == "l")
            {
                s1 = line + "\n";
                for (int i = 0; i < 4; i++)
                {
                    std::getline(ifile, line);
                    s1 += line + "\n";
                }
                drawing->store_drawing(s1);
            }
            if (line == "P")
            {
                s1 = line + "\n";
                for (int i = 0; i < 5; i++)
                {
                    std::getline(ifile, line);
                    s1 += line + "\n";
                }
                drawing->store_drawing(s1);
            }
            if (line == "F")
            {
                s1 = line + "\n";
                for (int i = 0; i < 5; i++)
                {
                    std::getline(ifile, line);
                    s1 += line + "\n";
                }
                drawing->store_drawing(s1);
            }
            if (line == "C")
            {
                s1 = line + "\n";
                for (int i = 0; i < 6; i++)
                {
                    std::getline(ifile, line);
                    s1 += line + "\n";
                }
                drawing->store_drawing(s1);
            }
        }
//        disp_string_vec(canvas->get_current_drawing()->get_drawing_list(), 0);
        drawing->draw(canvas->get_pixel_array(), pen);
    }
    std::cout << "returning" << std::endl;
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
void fill_triangle()
{
    fill_mode = true;
}
void left_button_function(int x, int y)
{
//        disp_color_t(pen->get_back_color());
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
                    //drawing->lines_list.push_back(l1);
                    drawing->store_drawing(l1.toString());
                }
            }
        }
        else
        {
//            std::cout << "line 119" << std::endl;
            point_t* tmp = new point_t(x, win_height - y, pen->get_pen_color());
            mouse_point_clicks.push_back(*tmp);
//            disp_mouse_pointer_click(mouse_point_clicks);
            delete tmp;
            if (mouse_point_clicks.size()%3 == 0)
            {
                point_t c = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                point_t b = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                point_t a = mouse_point_clicks.back();
                mouse_point_clicks.pop_back();
                triangle_t t1(a,b,c);
                t1.draw(canvas->get_pixel_array(), *pen);
                //drawing->triangles_list.push_back(t1);
                drawing->store_drawing(t1.toString());
            }
        }
        if(fill_mode)
        {
            point_t *tmp = new point_t(x, win_height - y, canvas->get_pixel_array()[y][x].get_point_color());
            //            disp_mouse_pointer_click(mouse_point_clicks);
            mouse_point_clicks.push_back(*tmp);
            delete tmp;

            point_t centroid = mouse_point_clicks.back();
//            std::cout << "line 274" ;
//            disp_color_t(centroid.get_point_color());
//            std::cout << std::endl;
            mouse_point_clicks.pop_back();
            mouse_point_clicks.pop_back();
//            std::cout<<centroid.getY()<<" "<<centroid.getX()<<std::endl;
            fill_t fillTriangle(mix1);
            drawing->store_drawing(fillTriangle.toString(mix1, centroid));
            fillTriangle.draw(centroid.get_point_color(), canvas->get_pixel_array(), centroid);
            fill_mode = false;
            return;
        }

}
