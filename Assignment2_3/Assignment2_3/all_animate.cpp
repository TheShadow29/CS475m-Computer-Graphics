#include "all_lighting.cpp"
#include "animate_class.hpp"
#include <sstream>
using namespace std;

void write_file();
void clear_file();
void play_back_vector(int);
//void play_back_line(int);
void interpolate_raw_values(int fps);


bool record_mode = false;
bool save_it = false;
bool play_back = false;
reader_writer* reader_writer1 = new reader_writer();
vector<string> raw_values;
vector<string> interpolated_values;
int counter_frames = 0;
int msecs = 10000;

void write_file()
{
    if (record_mode && save_it)
    {
        stringstream ss2;
        ss2 << bic_frame2->ry << " " << bic_frame_main->tx << " " << bic_frame_main->ty << " " << bic_frame_main->tz <<
        " ";
        ss2 << bic_frame_main->rx << " " << bic_frame_main->ry << " " << bic_frame_main->rz << " ";
        ss2 << head_light << " " << L_check;
        string s2 = ss2.str();
        reader_writer1->write_to_file(s2);
        save_it = false;
    }
}

void play_back_vector(int timer_func_msecs)
{
    if (play_back)
    {
        interpolate_raw_values(1);
        if (counter_frames < interpolated_values.size())
        {
            float handle_angle;
            float tx1, ty1, tz1, rx1, ry1, rz1, hl, lc;
            string line;
            line = interpolated_values[counter_frames];
            istringstream s1(line);
            s1 >> handle_angle >> tx1 >> ty1 >> tz1 >> rx1 >> ry1 >> rz1 >> hl >> lc;
            bic_frame_main->tx = tx1;
            bic_frame_main->ty = ty1;
            bic_frame_main->tz = tz1;
            bic_frame2->ry = handle_angle;
            head_light = hl;
            L_check = lc;
            glutPostRedisplay();
            glutTimerFunc(timer_func_msecs, play_back_vector, 0);
            cout << "out " << tx1 << ty1 << tz1 << rx1 << ry1 << rz1 << endl;
            cout << "line 59 " << counter_frames << endl;
            counter_frames++;
        }
        else
        {
            counter_frames = 0;
            play_back = false;
        }
    }

}

//void play_back_line(int counter)
//{
//
//}

void interpolate_raw_values(int fps)
{
    interpolated_values = raw_values;
}

void clear_file()
{
    reader_writer1->clear_file();
}

void draw_all()
{
    write_file();
    play_back_vector(msecs);
    draw();
}