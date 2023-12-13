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

vector<string> transpose(const vector<string> & m) {
  vector<string> n;
  FOR(i, 0, strlen(m[0].c_str())) {
    string a;
    FOR(j, 0, m.size()) a += m[j][i];
    n.PB(a);
  }

  return n;
}

string trim(const string & line) {
    string str;
    for (auto & c : line) {
      if (c == '\n' || c == '\r') continue;
      str += c;
    }

    return str;
}

ll calc(const vector<string> & strs) {
  FOR(i, 1, strs.size()) {
    bool all_good = true;
    FOR(j, 0, min(i, (ll)strs.size()-i)) {
      if (strs[i-j-1] != strs[i+j]) {
        all_good = false;
        break;
      }
    }
    if (all_good) return i;
  }

  return 0;
}

ll cnt(const string & s1, const string & s2) {
  ll res = 0;
  FOR(i, 0, s1.size()) if (s1[i] != s2[i]) res++;
  return res;
}


ll calc2(const vector<string> & strs) {
  FOR(i, 1, strs.size()) {
    bool all_good = true, fixed = false;
    FOR(j, 0, min(i, (ll)strs.size()-i)) {
      if (strs[i-j-1] != strs[i+j]) {
        ll err = cnt(strs[i-j-1], strs[i+j]);
        if (err == 1 && !fixed) { fixed = true; continue; }
        all_good = false;
        break;
      }
    }
    if (all_good && fixed) return i;
  }

  return 0;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll res = 0;
  vector<string> strs;
  while(getline(in, str)) {
    str = trim(str);
    if (str.size() == 0 || str == "") {
      res += calc(transpose(strs));
      res += calc(strs) * 100;
      strs.clear();
      continue;
    }
    strs.PB(str);
  }

  cout << "Part 1: " << res << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  ll res = 0;
  vector<string> strs;
  while(getline(in, str)) {
    str = trim(str);
    if (str.size() == 0 || str == "") {
      res += calc2(transpose(strs));
      res += calc2(strs) * 100;
      strs.clear();
      continue;
    }
    strs.PB(str);
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

