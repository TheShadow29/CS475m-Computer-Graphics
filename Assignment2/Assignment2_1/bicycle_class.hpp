#ifndef _BICYCLE_CLASS_HPP_
#define _BICYCLE_CLASS_HPP_
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>

class bic_node
{
private:
    float tx, ty, tz;
    float rx, ry, rz;
    int glist;
    std::vector<bic_node*> children;
    bic_node* parent;
public:
    bic_node();
    bic_node (bic_node* _parent, int _glist);
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
};

#endif
