#include "animate_class.hpp"
//---------------------

using namespace std;

//-------reader class-----------
reader::reader() {file_name = "keyframes.txt"; }
reader::reader(string _file_name) {file_name = _file_name; }

void reader::set_file_name(string _file_name)
{
    file_name = _file_name;
}

void reader::read_from_file()
{
    //depends on how we store the data
}

void reader::write_to_file(string s)
{
    //depends on how we encode the information
}









