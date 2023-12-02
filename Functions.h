#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Music_Commands.h"

void music_op(const Music_Command_Params & command);

template <typename T = string>
vector<T*> to_pointers(const vector<T> & vec)
{
  vector<T*> ret;
  for(long i{0}; i < static_cast<long>(vec.size()); ++i)
  {
    ret.push_back(new T{vec[i]});
    ++mem;
  }
  return ret;
}

void crash(const string & message);

#endif