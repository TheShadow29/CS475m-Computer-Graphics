#include <sstream>
#include <fstream>
#include "animate_class.hpp"
//---------------------

using namespace std;

//-------reader_writer class-----------
reader_writer::reader_writer() {file_name = "key_frames.txt"; }
reader_writer::reader_writer(string _file_name) {file_name = _file_name; }

void reader_writer::set_file_name(string _file_name)
{
    file_name = _file_name;
}

void reader_writer::read_from_file()
{
    //depends on how we store the data
    string line;
    ifstream inp_file;
    inp_file.open(this->file_name.c_str());
    while(!inp_file.eof())
    {
        getline(inp_file,line);
        inp_from_file.push_back(line);
    }
}

void reader_writer::write_to_file(string s)
{
    //depends on how we encode the information
    //encoding
    //bicycle handle angle, bicycle main frame tx,ty,tz,rx,ry,rz,
    //bicycle light on/off, room light on/off
    stringstream ss;
    ofstream out_file;
    //out_file.open("key_frames.txt");
    //char* f = (char *) this->file_name.c_str();
    out_file.open(this->file_name.c_str(), ofstream::app);
    ss << s << endl;
    out_file << ss.rdbuf();
    out_file.close();
}

void reader_writer::clear_file()
{
    ofstream out_file;
    out_file.open(this->file_name.c_str(), ofstream::trunc);
    out_file.close();
}











