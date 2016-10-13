#ifndef _BICYCLE_CLASS_HPP_
#define _BICYCLE_CLASS_HPP_
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
class color_t
{
private:
    float r,g,b;
public:
    color_t();
    color_t(float _r, float _g, float _b);

    void set(const float _r, const float _g, const float _b);
    float R(void);
    float G(void);
    float B(void);
    std::string toString();
};


class bic_node
{
private:
    float tx, ty, tz;
    float rx, ry, rz;
    int glist;
    color_t color;
    std::vector<bic_node*> children;
    bic_node* parent;
public:
    bic_node();
    bic_node (bic_node* _parent, int _glist);
    void set_color(color_t color1);
    void set_parent(bic_node* _parent);
    void set_glist(int _glist);
    void add_child(bic_node* _child);
    void render();
    void render_tree();
    void change_params(float _tx, float _ty, float _tz, float _rx, float _ry, float _rz);
    void inc_rx();
    void inc_ry();
    void inc_rz();
    void dec_rx();
    void dec_ry();
    void dec_rz();
    float get_rx();
    float get_ry();
    float get_rz();

    void inc_tx();
    void inc_ty();
    void inc_tz();


    void dec_tx();
    void dec_ty();
    void dec_tz();

    void dec_angle(float angle, float orientation);

    float sgn (float n);
    
};



#endif
