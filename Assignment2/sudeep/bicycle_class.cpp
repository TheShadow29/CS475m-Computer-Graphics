#include "bicycle_class.hpp"
using namespace std;
bic_node::bic_node()
{
    tx = ty =tz = rx = ry = rz = 0;
}
void bic_node::set_color(color_t color1)
{
    color = color1;
}
bic_node::bic_node(bic_node *_parent, int _glist) : glist(_glist)
{
    if (_parent != NULL)
    {
        parent = _parent;
    }
    tx = ty =tz = rx = ry = rz = 0;
}
void bic_node::set_parent(bic_node *_parent)
{
    if (_parent != NULL)
    {
        parent = _parent;
    }
}

void bic_node::set_glist(int _glist)
{
    glist = _glist;
}

void bic_node::add_child(bic_node *_child)
{
    children.push_back(_child);
}
void bic_node::change_params(float _tx, float _ty, float _tz, float _rx, float _ry, float _rz)
{
    tx = _tx; ty = _ty; tz = _tz;
    rx = _rx; ry = _ry; rz = _rz;
}
void bic_node::dec_rx()
{
    rx--;
    if  (rx < 0){rx += 360;}
}
void bic_node::dec_ry()
{
    ry--;
    if (ry < 0){ry += 360;}
}
void bic_node::dec_rz()
{
    rz--;
    if(rz < 0){rz += 360;}
}
void bic_node::inc_rx()
{
    rx++;
    if (rx > 360){rx -= 360;}
}
void bic_node::inc_ry()
{
    ry++;
    if (ry > 360){ry -= 360;}
}
void bic_node::inc_rz()
{
    rz++;
    if (rz > 360){rz -= 360;}
}
float bic_node::get_rx()
{
    return rx;
}
float bic_node::get_ry()
{
    return ry;
}
float bic_node::get_rz()
{
    return rz;
}
void bic_node::render()
{
    glTranslatef(tx,ty,tz);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    glCallList(this->glist);
}
void bic_node::render_tree()
{
    glPushMatrix();
    render();
    for (int i = 0; i < children.size(); ++i)
    {
        //cout << "line 81" << endl;
        children[i]->render_tree();
    }
    glPopMatrix();
}

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