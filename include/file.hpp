#ifndef _FILE_HPP_
#define _FILE_HPP_

#include<iostream> //cout, cin
#include<string> // std::string
#include<fstream>
#include<sstream> //std::ifstream, std::ofstream

namespace libs{

  class File{
    public:
      //==== Special methods
      /// Default constructor
      File(std::string);
      File(std::string, std::string);
      File(void) = delete;
      /// Default destructor
      ~File();
      //=== Support methods.
      bool is_eof(void); ///Checks whether we reached the "end of file".
      bool is_open(void);
      int line_lenght(void);
      //=== In/Out methods.
      std::string read_file(void);
      char read_character(void);
      void write_file(std::string);
    private:
      //==== Private members.
      std::ifstream f_input; //!<
      std::ofstream f_output; //!<

  };
  
} //namespace

#endif

