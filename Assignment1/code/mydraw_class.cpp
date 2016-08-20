#include "mydraw_class.hpp"
//#include "related_functions.cpp"
#include <iostream>
#include <string>
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
color_t::color_t(float _r, float _g, float _b)
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
        :size(2*_size - 1), pen_color(_pen_color), mode(_mode) {}
pen_t::pen_t(color_t _back_color) : size(1), pen_color(red), mode('d'), back_color(_back_color){ }
pen_t::pen_t(int _size, color_t _pen_color, char _mode, color_t _back_color)
        :size(2*_size-1), pen_color(_pen_color), mode(_mode), back_color(_back_color){ }
int pen_t::get_size()  { return size; }
color_t pen_t::get_pen_color()  { return pen_color; }
char pen_t::get_mode() { return mode; }
void pen_t::set_back_color(color_t color) {back_color = color;}
void pen_t::set_pen_color(color_t color) {pen_color = color; }
color_t pen_t::get_back_color() {return back_color; }
void pen_t::set_pen_size(int _size) { size = 2*_size - 1;}
void pen_t::set_pen_mode(char a) {mode = a;}
void pen_t::toggle_pen_mode()
{
    if (this->mode == 'd')
    {
        this->mode = 'e';
    }
    else
    {
        this->mode = 'd';
    }
    return;
}
std::string pen_t::toString()
{
    //mode, color RGB, size
    std::string s = "P\n";
    if (this->mode == 'd'){s += "1";}
    else{s += "0";}
    s += "\n";
    s += std::to_string(this->get_size());
    s += "\n";
    s += std::to_string(this->pen_color.R());
    s += "\n";
    s += std::to_string(this->pen_color.G());
    s += "\n";
    s += std::to_string(this->pen_color.B());
    s += "\n";
    return s;
}

//-----------------------
// 3. fill_t methods
fill_t::fill_t(color_t _current_fill_color) : current_fill_color(_current_fill_color) {};
std::string fill_t::toString(color_t color, point_t point)
{
    std::string s ="F\n";
    s += std::to_string(color.R());
    s+= "\n";
    s += std::to_string(color.G());
    s+= "\n";
    s += std::to_string(color.B());
    s+= "\n";
    s += std::to_string(point.getX());
    s+= "\n";
    s += std::to_string(point.getY());
    s+= "\n";
    return s;
}
void fill_t::draw(color_t _background_color, point_t** pixel_array, point_t node)
{
    std::vector<point_t> pixels;
    pixels.push_back(node);
    int counter =0;
    while(!pixels.empty())
    {
        int y = pixels[0].getY();
        int x = pixels[0].getX();
        int w = x;
        int e = x;
        int c = y;
        bool left_move = true;
        bool right_move =  true;
        if(!pixel_array[y][x].checkIfSameColor(_background_color))
        {
            left_move = false;
            right_move = false;
            e--;
        }
        while (left_move || right_move)
        {
            if(pixel_array[c][w-1].checkIfSameColor(_background_color) && left_move)
                w--;
            else left_move = false;
            if(pixel_array[c][e+1].checkIfSameColor(_background_color) && right_move)
                e++;
            else right_move = false;
        }
        for(int var = w; var<=e; var++)
        {
            pixel_array[y][var].set_point_color(current_fill_color);
            if(pixel_array[y+1][var].checkIfSameColor(_background_color))
                pixels.push_back(pixel_array[y+1][var]);
            if(pixel_array[y-1][var].checkIfSameColor(_background_color));
            pixels.push_back(pixel_array[y-1][var]);
        }
//        std::cout<<pixels.size()<<std::endl;
        pixels.erase(pixels.begin());
        counter++;
//        std::cout<<"line 180:"<<counter<<" "<<pixels.size()<<std::endl;
    }
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
std::string point_t::toString()
{
//    std::string s = "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    std::string s = std::to_string(this->x) + "\n" + std::to_string(this->y) + "\n";
    return s;
}
bool point_t::checkIfSameColor(color_t color_compare)
{
    color_t color_base = point_color;
    //color_t color_compare = point.get_point_color();
    bool same = false;
    if(color_base.R() == color_compare.R() && color_base.G() == color_compare.G() && color_base.B() == color_compare.B())
        same = true;
    return same;

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
    else if (pen.get_mode() == 'e')
    {
        color = pen.get_back_color();
    }

    int y_min = (y - thick > 0)?(y-thick):0;
    int x_min = (x - thick > 0)?(x-thick):0;

    for (int i = y_min; i <= y + thick; i++)
    {
        for (int j = x_min; j <= x + thick; j++)
        {
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
std::string line_t::toString()
{
    std::string s = "l\n" + a.toString() + b.toString();
    return  s;
}
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
//    std::cout << "line 103 a_x=" << x1 << " a_y=" << y1 << std::endl;
//    std::cout << "line 104 b_x=" << x2 << " b_y=" << y2 << std::endl;
//    std::cout << "line 105 delX=" << delX << std::endl;
//    std::cout << "line 106 delY=" << delY << std::endl ;
//    std::cout << "line 107 is_steep" << is_steep << std::endl;
    int x11 = x1, y11 = y1;
//    std::cout << "line 119 x11=" << x11 << std::endl;
//    std::cout << "line 120 y11=" << y11 << std::endl;
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
//            std::cout << "line 129" << std::endl;
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
std::string triangle_t::toString()
{
    std::string s = "t\n" +  a.toString() + b.toString() + c.toString();
    return s;
}
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

// 7. drawing_t methods
drawing_t::drawing_t(){}
drawing_t::drawing_t(std::vector <std::string> _drawing_list) : drawing_list(_drawing_list){ }
std::vector<std::string> drawing_t::get_drawing_list() { return drawing_list; }
void drawing_t::store_drawing(std::string s)
{
    std::string s1 = s + "\n";
    drawing_list.push_back(s1);
}
void drawing_t::set_drawing_list(std::vector <std::string> _drawing_list)
{
    drawing_list.clear();
    drawing_list = _drawing_list;
    return;
}
void drawing_t::clear_drawing_list()
{
    drawing_list.clear();
    return;
}
void drawing_t::draw(point_t **pixel_array, pen_t* pen)
{
    std::string line;
    std::string x1_s, y1_s;
    std::vector<point_t> P;
    std::vector<float> P_f;
    std::vector<int> P_i;
    int x1, y1;
    float x2;
    for (int i = 0; i < drawing_list.size(); i++)
    {
        int j = 0;
        line = drawing_list[i];
        P.clear();
        P_f.clear();
        P_i.clear();
        if (line[j] == 't')
        {
            j++;
            j++;
            for(int k = 0; k < 3; k++)
            {
                x1_s.clear();
                y1_s.clear();
                while(line[j] != '\n')
                {
                    x1_s += line[j];
                    j++;
                }
                x1 = std::stoi(x1_s);
                j++;
                while(line[j] != '\n')
                {
                    y1_s += line[j];
                    j++;
                }
                y1 = std::stoi(y1_s);
                j++;
                P.push_back(point_t(x1,y1));
            }

            triangle_t t1(P[0],P[1],P[2]);
//            std::cout << "line 362" << pen->get_pen_color().G() << std::endl;
            t1.draw(pixel_array, *pen);
        }
        else if (line[j] == 'l')
        {
            j++;
            j++;
            for(int k = 0; k < 2; k++)
            {
                x1_s.clear();
                y1_s.clear();
                while(line[j] != '\n')
                {
                    x1_s += line[j];
                    j++;
                }
                x1 = std::stoi(x1_s);
                j++;
                while(line[j] != '\n')
                {
                    y1_s += line[j];
                    j++;
                }
                y1 = std::stoi(y1_s);
                j++;
                P.push_back(point_t(x1,y1));
            }
            line_t l1(P[0],P[1]);
            l1.draw(pixel_array,*pen);
        }
        else if (line[j] == 'P')
        {
//            std::cout << "line395 " << line << std::endl;
            ++j;
            if(line[++j] == '1')//j=2
            {pen->set_pen_mode('d');}
            else{pen->set_pen_mode('e');}
            j++;//j=3
            x1_s="";
            while (line[++j] != '\n')
            {
                x1_s += line[j];
            }

            y1 = std::stoi(x1_s);
            pen->set_pen_size(y1);
            for(int k = 0; k < 3; k++)
            {
                x1_s.clear();
                ++j;
                while(line[j] != '\n')
                {
                    x1_s += line[j++];
                }
//                std::cout << "line 417: " << x1_s<< std::endl;
                x2 = std::stof(x1_s);
//                std::cout<<"check x2: "<<x2<<std::endl;
                P_f.push_back(x2);
            }
            color_t color1 = color_t(P_f[0], P_f[1],P_f[2]);
            pen->set_pen_color(color1);
        }
        else if (line[j] == 'F')
        {
            ++j;
            for(int k = 0; k < 3; k++)
            {
                x1_s.clear();
                while (line[++j] != '\n')
                {
                    x1_s += line[j];
                }
                x2 = std::stof(x1_s);
                P_f.push_back(x2);
            }

            color_t* col = new color_t(P_f[0], P_f[1], P_f[2]);
            for(int k = 0; k < 2; k++)
            {
                y1_s.clear();
                while (line[++j] != '\n')
                {
                    y1_s += line[j];
                }
                y1 = std::stoi(y1_s);
                P_i.push_back(y1);
            }
            point_t* poi = new point_t(P_i[0], P_i[1]);
            fill_t fi1(*col);
            fi1.draw(pixel_array[poi->getY()][poi->getX()].get_point_color(), pixel_array,*poi);
            delete poi;
            delete col;
        }
        else if (line[j] == 'C')
        {
            ++j;
            for(int k = 0; k < 3; k++)
            {
                x1_s.clear();
                while (line[++j] != '\n')
                {
                    x1_s += line[j];
                }
                x2 = std::stof(x1_s);
                P_f.push_back(x2);
            }
            color_t* init_col = new color_t(P_f[0], P_f[1], P_f[2]);
            P_f.clear();
            for(int k = 0; k < 2; k++)
            {
                y1_s.clear();
                while (line[++j] != '\n')
                {
                    y1_s += line[j];
                }
                y1 = std::stoi(y1_s);
                P_i.push_back(y1);
            }
            color_t* new_col = new color_t(P_f[0], P_f[1], P_f[2]);
//            can->set_back_color(*init_col, *new_col, *pen);
        }

    }
    return;
}
//--------------------------
// 8. canvas methods
canvas_t::canvas_t() : width(640), height(480), background_color(white)
{
    current_drawing = new drawing_t();
    this->clear();
}
canvas_t::canvas_t(int _width, int _height) :width(_width), height(_height), background_color(white)
{
    current_drawing = new drawing_t();
    this->clear();
}
canvas_t::canvas_t(int _width, int _height, color_t _background_color)
            :width(_width), height(_height), background_color(_background_color)
{
    current_drawing = new drawing_t();
    this->clear();
}
canvas_t::canvas_t(int _width, int _height, drawing_t* _current_drawing, color_t _background_color,
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
canvas_t::canvas_t(drawing_t* _current_drawing) :width(640), height(480), background_color(white),
            current_drawing(_current_drawing)
{
    this->clear();
}
canvas_t::canvas_t(int _width, int _height, drawing_t *_current_drawing) :width(_width), height(_height),
                 current_drawing(_current_drawing), background_color(white)
{
    this->clear();
}
std::string canvas_t::toString(color_t init_color, color_t new_color)
{
    std::string s ="C\n";
    s += std::to_string(init_color.R());
    s+= "\n";
    s += std::to_string(init_color.G());
    s+= "\n";
    s += std::to_string(init_color.B());
    s+= "\n";
    s += std::to_string(new_color.R());
    s+= "\n";
    s += std::to_string(new_color.G());
    s+= "\n";
    s += std::to_string(new_color.B());
    s+= "\n";
    return s;
}
void canvas_t::set_back_color(color_t init_back_color, color_t color, pen_t pen)
{
    background_color = color;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (pixel_array[i][j].checkIfSameColor(init_back_color))
            {
                pixel_array[i][j] = point_t(j,i, background_color);
            }
        }
    }
//    current_drawing->draw(pixel_array,&pen);
}
drawing_t* canvas_t::get_current_drawing() { return current_drawing; }

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
//    std::cout << "line 219 delX=" << delX << std::endl;
//    std::cout << "line 219 delY=" << delY << std::endl;
//    std::cout << "line 238 x11=" << x11 << std::endl;
//    std::cout << "line 239 y11=" << y11 << std::endl;
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