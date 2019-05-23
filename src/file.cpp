#include "../include/file.hpp"
#include <system_error>   // std::system_error

//Constructor
libs::File::File(std::string f_input_path){
  try { f_input.open(f_input_path); }
  catch( const std::ios_base::failure &err ){ /* EMPTY */ }
}
libs::File::File(std::string f_input_path, std::string f_output_path){
  try { f_input.open(f_input_path); }
  catch( const std::ios_base::failure &err ){ /* EMPTY */ }
  try { f_output.open(f_output_path); }
  catch( const std::ios_base::failure &err ){ /* EMPTY */ }
}
//Destructor
libs::File::~File(){
  f_input.close();
  f_output.close();
}
//Support methods
bool libs::File::is_eof(void){
  return f_input.eof();
}

bool libs::File::is_open(void){
  return f_input.is_open();
}
//Input method
std::string libs::File::read_file(){
  std::string line;

  std::getline(f_input, line);

  return line;
}
char libs::File::read_character(){
  char c;

  f_input >> c;

  return c;
}
void libs::File::write_file(std::string line){
	try{ f_output << line << "\n"; }
  catch( const std::ios_base::failure &err ){}
}
