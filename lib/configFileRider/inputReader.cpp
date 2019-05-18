#include "inputReader.h"

using namespace libs;
using std::cout;
using std::endl;

    void inputReader::help_message( void ){
        cout << "Usage: glife [<options>] <input_cfg_file>" << endl;
        cout << " Simulation options:" << endl
             << "  --help         \tPrint this help text." << endl
             << "  --imgdir <path> \tSpecify directory where output images are written to." << endl
             << "  --maxgen <num> \tMaximum number of generations to simulate." << endl
             << "  --fps <num>     \tNumber of generations presented per second." << endl
             << "  --blocksize <num> \tPixel size of a cell. Default = 5." << endl
             << "  --bkgcolor <color> \tColor name for the background. Default GREEN." << endl
             << "  --alivecolor <color> \tColor name for representing alive cells. Default RED." << endl
             << "  --outfile <filename> \tWrite the text representation of the simulation"
             << " to the given filename." << endl;
        cout << endl;
        cout << " Available colors are:" << endl
             << "  BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE" << endl
             << "  GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW ORANGE RED" << endl
             << "  STEEL_BLUE WHITE YELLOW" << endl;
    }

    void inputReader::update( void ){
        bool used[8] = {false};
        for (size_t i=0; i < m_args.size(); i++)
        {
            if ( (m_args[i] == "-h" or m_args[i] == "--help") and used[0] == false )
            { help_message(); used[0] = true; }
            else if ( m_args[i] == "--imgdir" and used[1] == false )
            { m_imgdir = m_args[i + 1]; used[1] = true; }
            else if ( m_args[i] == "--maxgen" and used[2] == false )
            { m_maxgen = stoi(m_args[i + 1]); used[2] = true; }
            else if ( m_args[i] == "--fps" and used[3] == false )
            { m_fps = stoi(m_args[i + 1]); used[3] = true; }
            else if ( m_args[i] == "--blocksize" and used[4] == false )
            { m_blocksize = stoi( m_args[i + 1] ); used[4] = true; }
            else if ( m_args[i] == "--bkgcolor" and used[5] == false )
            { m_bkgcolor = m_args[i + 1]; used[5] = true; }
            else if ( m_args[i] == "--alivecolor" and used[6] == false )
            { m_alivecolor = m_args[i + 1]; used[6] = true; }
            else if ( m_args[i] == "--outfile" and used[7] == false )
            { m_alivecolor = m_args[i + 1]; used[7] = true; }
        }
    }