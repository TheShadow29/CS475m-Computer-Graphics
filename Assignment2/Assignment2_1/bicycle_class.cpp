#include "bicycle_class.hpp"
using namespace std;
bic_node::bic_node()       // basic default initialisation
{
    tx = ty =tz = rx = ry = rz = 0;
}
void bic_node::set_color(color_t color1)    // change the color
{
    color = color1;
}
bic_node::bic_node(bic_node *_parent, int _glist) : glist(_glist)           // constructor with parent and glist defined
{
    if (_parent != NULL)
    {
        parent = _parent;
    }
    tx = ty =tz = rx = ry = rz = 0;
}
void bic_node::set_parent(bic_node *_parent)        //function to set the parent node  
{
    if (_parent != NULL)
    {
        parent = _parent;
    }
}

void bic_node::set_glist(int _glist)      // set the glist 
{
    glist = _glist;
}

void bic_node::add_child(bic_node *_child)   // add a particular node as the child of the current element of the bicycle
{
    children.push_back(_child);
}
void bic_node::change_params(float _tx, float _ty, float _tz, float _rx, float _ry, float _rz)   // change the spatial coordinates parameters
{
    tx = _tx; ty = _ty; tz = _tz;
    rx = _rx; ry = _ry; rz = _rz;
}
void bic_node::dec_rx()    // decrement the rotation angle along the x axis
{
    rx--;
    if  (rx < 0){rx += 360;}
} 
void bic_node::dec_ry()      // decrement the rotation angle along the y axis
{
    ry--;
    if (ry < 0){ry += 360;}
} 
void bic_node::dec_rz()   // decrement the rotation angle along the z axis
{
    rz--;
    if(rz < 0){rz += 360;}
}
void bic_node::inc_rx()       // increment the rotation angle along the x axis
{
    rx++;
    if (rx > 360){rx -= 360;}
}
void bic_node::inc_ry()    // increment the rotation angle along the y axis
{
    ry++;
    if (ry > 360){ry -= 360;}
}
void bic_node::inc_rz()     // increment the rotation angle along the z axis
{
    rz++;
    if (rz > 360){rz -= 360;}
}
float bic_node::get_rx()         // get the angle current rotation angle along the x axis
{
    return rx;
}
float bic_node::get_ry()      // get the angle current rotation angle along the y axis
{
    return ry;
}
float bic_node::get_rz()       // get the angle current rotation angle along the z axis
{
    return rz;
}
void bic_node::render()                // render the node 
{ 
    glTranslatef(tx,ty,tz);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    glCallList(this->glist);
}
void bic_node::render_tree()       // render the entire tree and also its nodes
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