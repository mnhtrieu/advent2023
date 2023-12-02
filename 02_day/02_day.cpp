#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

#define FILE "demo.in"
//#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);
string trim(string s);

void part_1(const string & file) {
  ifstream in(file);
  string str;
  regex r("([0-9]*) (blue|red|green)");
  ll idx = 1, res = 0;
  while (getline(in, str)) {
    map<string, ll> cubes = {{"blue", 0}, {"red", 0}, {"green", 0}};
    smatch m;
    sregex_iterator it(str.begin(), str.end(), r);
    sregex_iterator end;
    while (it != end) {
      cubes[(*it)[2]] = std::max(stoll((*it)[1]), cubes[(*it)[2]]);
      it++;
    }

    if (cubes["blue"] <= 14 && cubes["red"] <= 12 && cubes["green"] <= 13) res += idx;
    ++idx;
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;
  regex r("([0-9]*) (blue|red|green)");
  ll idx = 1, res = 0;
  while (getline(in, str)) {
    map<string, ll> cubes = {{"blue", 0}, {"red", 0}, {"green", 0}};
    smatch m;
    sregex_iterator it(str.begin(), str.end(), r);
    sregex_iterator end;
    while (it != end) {
      cubes[(*it)[2]] = std::max(stoll((*it)[1]), cubes[(*it)[2]]);
      it++;
    }

    res += cubes["blue"] * cubes["red"] * cubes["green"];
    ++idx;
  }

  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim)
{
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      if (token == "x") res.PB(1);
      else res.PB(stoi(token));
    }

    return res;
}

string trim(string str) {
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    return str;
}

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  part_2(file);
  return 0;
}

