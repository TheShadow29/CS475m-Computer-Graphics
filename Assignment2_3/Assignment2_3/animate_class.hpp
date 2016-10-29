#ifndef _ANIMATE_CLASS_HPP_
#define _ANIMATE_CLASS_HPP_

#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
//Define all classes like the color class, adding appropriate methods and data members.
//Implementation of the methods go into the corresponding cpp file
class reader_writer
{
private:
    string file_name;
public:
    vector<string> inp_from_file;
    reader_writer();
    reader_writer(string _file_name);
    void set_file_name(string _file_name);
    void read_from_file();
    void write_to_file(string s);
    void clear_file();

};

#endif
