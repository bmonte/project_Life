#include "../include/inputReader.hpp"

using namespace libs;
using std::cout;
using std::endl;

    void inputReader::help_message( void ){
        cout << "Usage: glife [<options>] <input_cfg_file>" << endl;
        cout << " Simulation options:" << endl
             << "  --help         \tPrint this help text." << endl
             << "  --rule <code> \tSpecify simulation rules by a 'B3/S23' code" << endl
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
        bool is_help_used=false;

        if ( m_args.size() == 1 and !(m_args[0] == "-h" or m_args[0] == "--help"))
        {
            m_cfg_file.first = m_args[0]; 
            m_cfg_file.second = true;
        }
        else
            for (size_t i=0; i < m_args.size(); i+=2)
            {
                if ( (m_args[i] == "-h" or m_args[i] == "--help") and !is_help_used )
                { 
                    help_message(); 
                    is_help_used = true; 
                    i--;
                }
                else if ( m_args[i] == "--imgdir" )
                { 
                    if ( !m_imgdir.second )
                        m_imgdir.first = m_args[i + 1];
                    m_imgdir.second = true;  
                }
                else if ( m_args[i] == "--maxgen" )
                { 
                    if ( !m_maxgen.second )
                        m_maxgen.first = stoi(m_args[i + 1]); 
                    m_maxgen.second = true;
                }
                else if ( m_args[i] == "--fps" )
                { 
                    if ( !m_fps.second )
                        m_fps.first = stoi(m_args[i + 1]); 
                    m_fps.second = true; 
                }
                else if ( m_args[i] == "--blocksize" )
                { 
                    if ( !m_blocksize.second )
                        m_blocksize.first = stoi( m_args[i + 1] ); 
                    m_blocksize.second = true;
                }
                else if ( m_args[i] == "--bkgcolor" )
                { 
                    if ( !m_bkgcolor.second )
                        m_bkgcolor.first = m_args[i + 1]; 
                    m_bkgcolor.second = true; 
                }
                else if ( m_args[i] == "--alivecolor" )
                { 
                    if ( !m_alivecolor.second )
                        m_alivecolor.first = m_args[i + 1]; 
                    m_alivecolor.second = true; 
                }
                else if ( m_args[i] == "--outfile" )
                { 
                    if ( !m_outfile.second )
                        m_outfile.first = m_args[i + 1]; 
                    m_outfile.second = true; 
                }
                else if ( m_args[i] == "--rule" )
                { 
                    if ( !m_rules.second )
                        m_rules.first = m_args[i + 1]; 
                    m_rules.second = true; 
                }
                else
                {
                    m_cfg_file.first = m_args[i];
                    m_cfg_file.second = true;
                    i--;
                }
        }
    }

    void inputReader::output( void )
    {
        if ( !m_imgdir.second )
        {
            canvas_output = false;
            
            if ( !m_outfile.second ) 
            {
                cout_output = true;
                txt_output = false;   
            }
            else
            {
                cout_output = true;
                txt_output = true;  
            }
        }
        else
        {
            canvas_output = true;

            if ( !m_outfile.second ) 
            {
                cout_output = false;
                txt_output = false;   
            }
            else
            {
                cout_output = false;
                txt_output = true;  
            }
        }
    }