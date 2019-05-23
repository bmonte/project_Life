#include <iostream>
using std::cout;
using std::endl;
#include <locale>
#include <string>

#include "../include/common.h"
#include "../include/file.hpp"
#include "../include/inputReader.hpp"
using namespace libs;
#include "../include/life.hpp"
#include "../dev_canvas/include/canvas.h"

int main(int argc, char const *argv[])
{
    inputReader input(argc, argv);
    input.update();
    File my_file( input.cfg_file() );

    if ( my_file.is_open() ) 
    {
        cout << ">>> Trying to open input file [" << input.cfg_file() << "]... done!" << endl;
        if ( input.maxgen() == 0)
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


        cout << ">>> Grid size read from input file: " << my_life.rows() << " rows by " 
            << my_life.cols() << " cols." << endl;
        cout << ">>> Character that represents a living cell read from input file: '" 
            << my_life.l_cell() << "' " << endl;

        //Read the living cell position    
        for (auto x{0u}; x < my_life.rows(); x++)
        {
            std::string cells = my_file.read_file();
            for (auto y{0u}; y < cells.size(); y++)
                if ( cells[y] == my_life.l_cell()[0] )
                    my_life.set_cell_position(Point2( x, y));
        }
        cout << ">>> Finished reading input data file." << endl;
        my_life.welcome_message();

        auto Gen_cont(1);
        while ( !my_life.extinct() )
        {
            cout << " Generation " << Gen_cont << ":" << endl << endl;
            for (auto i = 0; i < input.fps(); i++)
            {
                my_life.print();
                my_life.update();   
                cout << endl;   
            }
            Gen_cont++;
            if ( my_life.extinct() )
                cout << "ALL CELLS DIED R.I.P YEAR 1 - YEAR " << Gen_cont << endl;
        }
        
        

    }
    return EXIT_SUCCESS;
}
