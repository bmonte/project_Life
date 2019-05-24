#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>
#include <chrono>
#include <thread>

#include "../include/common.h"
#include "../include/file.hpp"
#include "../include/inputReader.hpp"
using namespace libs;
#include "../include/life.hpp"
#include "../dev_canvas/include/canvas.h"
using namespace life;

/// Saves an image as a **ascii** PPM file.
bool save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ )
{
    std::ofstream ofs_file( file_name_, std::ios::out  );
    if ( not ofs_file.is_open() )
        return false;

    ofs_file << "P3\n"
        << w << " " << h << "\n"
        << "255\n";

    size_t i{0};
    while ( i < (w*h*d) )
    {
        // depth traversal, usually 3.
        for( auto id{0u} ; id < 3 ; id++ )
            ofs_file << (int) *(data + i++ ) << " ";
        ofs_file << std::endl;
        i++; // to skip alpha channel.
    }

    // Did it not fail?
    auto result = not ofs_file.fail();

    ofs_file.close();

    return result;
}

int main(int argc, char const *argv[])
{
    inputReader input(argc, argv);
    input.update();
    input.output(); //Set the output option
    
    File my_file( input.cfg_file() );
    
    if ( my_file.is_open() ) 
    {
        cout << ">>> Trying to open input file [" << input.cfg_file() << "]... done!" << endl;
        if ( input.maxgen() == -1)
            cout << ">>> Running simulation up to infinite generations, or until extinction/stability"
                << "is reached." << endl;
        else
            cout << "Running simulation up to " << input.maxgen() << " generations, or until" 
                << "extinction/stability is reached, whichever comes first."<< endl;

        //Processing data
        cout << ">>> Processing data, please wait..." << endl;
        //Read row and col
        auto iterator = 0; size_t life_size[2];
        auto line = my_file.read_file();
        
        std::stringstream tmp_str(line);    
        for (std::string num; tmp_str >> num; )
        {
            if (iterator >= 2) break;
            life_size[iterator] = stoi(num);
            iterator++;
        }
        //Read the living cell character
        line = my_file.read_file(); 
        Life my_life(life_size[0], life_size[1], line);
        //Set simulation rules
        my_life.set_rule((int)(input.rules().at(1)-'0'), (int)(input.rules().at(4)-'0'), 
                         (int)(input.rules().at(5)-'0'));

        cout << ">>> Grid size read from input file: " << my_life.rows() << " rows by " 
            << my_life.cols() << " cols." << endl;
        cout << ">>> Character that represents a living cell read from input file: '" 
            << my_life.l_cell() << "' " << endl;

        //Read the living cell position
        int length; //Define the lenght of cols in the file    
        for (auto x{0u}; x < my_life.rows(); x++)
        {
            std::string cells = my_file.read_file();
            length = cells.size() < my_life.cols() ? cells.size() : my_life.cols(); 
            for (auto y{0}; y < length; y++)
                if ( cells[y] == my_life.l_cell()[0] )
                    my_life.set_cell_position(Point2( x, y));
        }
        cout << ">>> Finished reading input data file." << endl;
        my_life.welcome_message();

        // Cout output
        if ( input.cout_output )
        {
            auto Gen_cont(0);
            while ( Gen_cont != input.maxgen() )
            {
                cout << " Generation " << Gen_cont + 1 << ":" << endl << endl;
                for (auto i = 0; i < input.fps(); i++)
                {
                    my_life.print();
                    my_life.update();   
                    cout << endl;   
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
                Gen_cont++;
                if ( my_life.extinct() )
                {
                    cout << "ALL CELLS DIED R.I.P YEAR 1 - YEAR " << Gen_cont << endl;
                    break;
                }
                if ( my_life.stable() )
                {
                    cout << ">>> All the cells are stable" << endl;
                    break;
                }
            }
        }
    } 

    return EXIT_SUCCESS;
}
