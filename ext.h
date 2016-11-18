#ifndef __EXT_H__
#define __EXT_H__

#include <string>
#include <vector>

using namespace std;


namespace ext {


void split_string(const string &str, char sym, vector<string> &out);

const string current_datetime();

const string ftoa(float num);


}


#endif
