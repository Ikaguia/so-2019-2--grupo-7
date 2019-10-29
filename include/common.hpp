#ifndef MODULO_COMMON
#define MODULO_COMMON

#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;

#define FOR(i, mn, mx) for(int i = mn;   i <  mx; i++)
#define ROF(i, mn, mx) for(int i = mx-1; i >= mn; i--)

#define W(x) cerr << #x << " = '" << x << "'" << endl;

bool file_exists(const string &file_path);

#endif//MODULO_COMMON