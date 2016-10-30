#include "all_lighting.cpp"
#include "animate_class.hpp"
#include <sstream>
using namespace std;

void write_file();
void clear_file();
void play_back_vector();
void play_back_line(int);
void interpolate_raw_values(int fps);
void screen_shot();

bool record_mode = false;
bool save_it = false;
bool play_back = false;
bool take_screenshot = false;
reader_writer* reader_writer1 = new reader_writer();
vector<string> raw_values;
vector<string> interpolated_values;
int counter_frames = 0;
int msecs = 1000;
int interpolate_ratio;
int fps = 30;
float time_between_frames = 1000/fps;

void write_file()
{
    if (record_mode && save_it)
    {
        stringstream ss2;
        int cmode = camera_mode - '0';
        ss2 << bic_frame2->ry << " " << bic_frame_main->tx << " " << bic_frame_main->ty << " " << bic_frame_main->tz <<
        " ";
        ss2 << bic_frame_main->rx << " " << bic_frame_main->ry << " " << bic_frame_main->rz << " ";
        ss2 << head_light << " " << L_check << " " << angle << " " << cmode;
        string s2 = ss2.str();
        reader_writer1->write_to_file(s2);
        save_it = false;
    }
}

void play_back_vector()
{
    cout << "line 42" << endl;
    interpolate_raw_values(1);
    for(int i = 0; i < interpolated_values.size(); i++)
    {cout << interpolated_values[i] << endl;}
    if (interpolated_values.size() != 0)
    {
        interpolate_ratio = 0;
        counter_frames = 0;
        play_back_line(time_between_frames);
    }
}

void play_back_line(int time)
{
    float handle_angle_c, handle_angle_n;
    float tx1_c,tx1_n, ty1_c, ty1_n, tz1_c, tz1_n, rx1_c, rx1_n, ry1_c, ry1_n, rz1_c, rz1_n;
    float angle_c, angle_n;
    char camera_mode_c;
    bool hl,hl2, lc,lc2;
    string line;
    line = interpolated_values[counter_frames];
    istringstream s1(line);
    s1 >> handle_angle_c >> tx1_c >> ty1_c >> tz1_c >> rx1_c >> ry1_c >> rz1_c >> hl >> lc >> angle_c;
    s1 >> camera_mode_c;
    line = interpolated_values[counter_frames+1];
    istringstream s2(line);
    s2 >> handle_angle_n >> tx1_n >> ty1_n >> tz1_n >> rx1_n >> ry1_n >> rz1_n >> hl2 >> lc2 >> angle_n;

    bic_frame_main->tx = tx1_c + (tx1_n - tx1_c)*interpolate_ratio*1.0/fps;
    bic_frame_main->ty = ty1_c + (ty1_n - ty1_c)*interpolate_ratio*1.0/fps;
    bic_frame_main->tz = tz1_c + (tz1_n - tz1_c)*interpolate_ratio*1.0/fps;
    bic_frame_main->rx = rx1_c + (rx1_n - rx1_c)*interpolate_ratio*1.0/fps;
    bic_frame_main->ry = ry1_c + (ry1_n - ry1_c)*interpolate_ratio*1.0/fps;
    bic_frame_main->rz = rz1_c + (rz1_n - rz1_c)*interpolate_ratio*1.0/fps;
    camera_pos(camera_mode_c);
    bic_frame2->ry = handle_angle_c + (handle_angle_n - handle_angle_c)*interpolate_ratio*1.0/fps;
    angle = angle_c + (angle_n - angle_c)*interpolate_ratio*1.0/fps;
    head_light = hl;
//    cout << "line 77 " << hl << endl;
    L_check = lc;
//    cout << "line 79 " << lc << endl;
    if(L_check ==1)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    if(head_light ==1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    glutPostRedisplay();
    interpolate_ratio++;
    if (interpolate_ratio == fps)
    {
        interpolate_ratio = 0;
        counter_frames++;
    }
    if (counter_frames < interpolated_values.size() - 2)
    {
        screen_shot();
        glutTimerFunc(time, play_back_line, time_between_frames);
    }
    if (counter_frames == interpolated_values.size() - 2)
    {
        line = interpolated_values[counter_frames];
        istringstream s1(line);
        s1 >> handle_angle_c >> tx1_c >> ty1_c >> tz1_c >> rx1_c >> ry1_c >> rz1_c >> hl >> lc;
        bic_frame_main->tx = tx1_c;
        bic_frame_main->ty = ty1_c;
        bic_frame_main->tz = tz1_c;
        bic_frame_main->rx = rx1_c;
        bic_frame_main->ry = ry1_c;
        bic_frame_main->rz = rz1_c;
        head_light = hl;
        L_check = lc;
        if(L_check ==1)
            glEnable(GL_LIGHT0);
        else
            glDisable(GL_LIGHT0);
        if(head_light ==1)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);
        bic_frame2->ry = handle_angle_c;
        screen_shot();
        glutPostRedisplay();
    }

//    cout << "line 94 " << bic_frame_main->tx << endl;
//    cout << "out " << tx1 << ty1 << tz1 << rx1 << ry1 << rz1 << endl;
//    cout << "line 59 " << counter_frames << endl;
//    counter_frames++;
}

void interpolate_raw_values(int fps)
{
    interpolated_values = raw_values;
//    string curr_line, next_line;
//    float handle_angle_c, handle_angle_n;
//    float tx1_c,tx1_n, ty1_c, ty1_n, tz1_c, tz1_n, rx1_c, rx1_n, ry1_c, ry1_n, rz1_c, rz1_n;
//    for(int i = 0; i < raw_values.size(); i++)
//    {
//        curr_line = raw_values[i];
//        next_line = raw_values[i+1];
//        istringstream s_curr(line);
//        s_curr >> handle_angle_c >> tx1_c >> ty1_c >> tz1_c >> rx1_c >> ry1_c >> rz1_c;
//        istringstream s_next(line);
//        s_next >> handle_angle_n >> tx1_n >> ty1_n >> tz1_n >> rx1_n >> ry1_n >> rz1_n;
//    }
}

void screen_shot()
{
    if (!take_screenshot)
    { return;}
    // we will store the image data here
    unsigned char *pixels;
    // the thingy we use to write files
    //FILE * shot;
    FILE* img_data_file;
    // we get the width/height of the screen into this array
    int screenStats[4];

    // get the width/height of the window
    glGetIntegerv(GL_VIEWPORT, screenStats);

    // generate an array large enough to hold the pixel data
    // (width*height*bytesPerPixel)
    pixels = new unsigned char[screenStats[2]*screenStats[3]*3];
    // read in the pixel data, TGA's pixels are BGR aligned
    glReadPixels(0, 0, screenStats[2], screenStats[3], GL_BGR,
                 GL_UNSIGNED_BYTE, pixels);

    // open the file for writing. If unsucessful, return 1
    //
    stringstream ff;
    ff << "./img_files/img_" << interpolate_ratio + counter_frames*fps << ".tga";
    string f = ff.str();
    cout << "line 175" << endl;
//    if(img_data_file = fopen(f.c_str()));
    if((img_data_file = fopen(f.c_str(), "wb"))==NULL)
    {
        cout << "line 172 couldn't open " << f << endl;
    }
    else
    {
        cout << "line 178 writing to file " << f << endl;
    }
    // this is the tga header it must be in the beginning of
    // every (uncompressed) .tga
    unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
    // the header that is used to get the dimensions of the .tga
    // header[1]*256+header[0] - width
    // header[3]*256+header[2] - height
    // header[4] - bits per pixel
    // header[5] - ?
    unsigned char header[6]={((int)(screenStats[2]%256)),
                             ((int)(screenStats[2]/256)),
                             ((int)(screenStats[3]%256)),
                             ((int)(screenStats[3]/256)),24,0};

    // write out the TGA header
    fwrite(TGAheader, sizeof(unsigned char), 12, img_data_file);
    // write out the header
    fwrite(header, sizeof(unsigned char), 6, img_data_file);
    // write the pixels
    fwrite(pixels, sizeof(unsigned char),
           screenStats[2]*screenStats[3]*3, img_data_file);

    // close the file
    fclose(img_data_file);
    // free the memory
    delete [] pixels;

}

void clear_file()
{
    reader_writer1->clear_file();
}

void draw_all()
{
    write_file();
    draw();
}