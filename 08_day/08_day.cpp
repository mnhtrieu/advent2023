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

ll idx(const char & c) {
  if (c == 'L') return 0;
  else return 1;
}

ll find(map<string, vector<string>> & m, const string & ins) {
  string end = "ZZZ", curr = "AAA";
  ll res = 0;
  while(true) {
    FOR(i, 0, ins.size()) {
      curr = m[curr][idx(ins[i])];
      res ++;
      if (curr == end) return res;
    }
  }
  return res;
}

bool all_end(vector<ll> & ends) {
  for(auto & i: ends) if (i != 2) return false;
  return true;
}

ll find(map<string, vector<string>> & m, const string & ins, vector<string> & currs, vector<string> & copy) {
  vector<ll> steps;
  vector<ll> ends;
  ends.resize(currs.size());
  steps.resize(currs.size());
  while(true) {
    FOR(i, 0, ins.size()) {
      FOR(j, 0, currs.size()) {
        if (currs[j] == copy[j] && ends[j] >= 1) { ends[j] = 2; continue; }
        currs[j] = m[currs[j]][idx(ins[i])];
        steps[j] ++;
        if (currs[j][currs[j].size()-1] == 'Z') ends[j] = 1;
      }
    }
    if (all_end(ends)) break;
  }

  ll res = steps[0];
  FOR(i, 1, steps.size()) res = lcm(res, steps[i]);

  return res;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  string ins;
  getline(in, ins);
  getline(in, str);

  regex r("([0-9A-Z]*) = \\(([0-9A-Z]*), ([0-9A-Z]*)\\)");
  map<string, vector<string>> m;
  while(getline(in, str)) {
    sregex_iterator it(str.begin(), str.end(), r), end;
    while (it != end) {
      m[(*it)[1]].PB((*it)[2]);
      m[(*it)[1]].PB((*it)[3]);
      it++;
    }
  }
  
  cout << "Part 1: " << find(m, ins) << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  string ins;
  getline(in, ins);
  getline(in, str);

  regex r("([0-9A-Z]*) = \\(([0-9A-Z]*), ([0-9A-Z]*)\\)");
  map<string, vector<string>> m;
  vector<string> currs;
  while(getline(in, str)) {
    sregex_iterator it(str.begin(), str.end(), r), end;
    while (it != end) {
      string n = (*it)[1];
      if (n[n.size()-1] == 'A') currs.PB(n);
      m[n].PB((*it)[2]);
      m[n].PB((*it)[3]);
      it++;
    }
  }
  
  cout << "Part 2: " << find(m, ins, currs, currs) << endl;
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

