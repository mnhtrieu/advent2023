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
set<ll> explode(string const & s, char delim);
string trim(string s);

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll res = 0;
  
  while(getline(in, str)) {
    str = str.substr(str.find(": ")+2);
    ll pos = str.find(" | ");
    set<ll> wins = explode(str.substr(0, pos), ' ');
    set<ll> nums = explode(str.substr(pos+3), ' ');
    
    ll m = 0, tmp = 1;
    for (auto & i: nums) if (wins.contains(i)) ++ m;

    if (m == 0) tmp = 0;
    else FOR(i, 0, m-1) tmp <<= 1;

    res += tmp;
  }
  
  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  ll res = 0, idx = 1;
  map<ll, ll> m;
  map<ll, ll> cnt;

  while(getline(in, str)) {
    m[idx] ++;
    str = str.substr(str.find(": ")+2);
    ll pos = str.find(" | ");
    set<ll> wins = explode(str.substr(0, pos), ' ');
    set<ll> nums = explode(str.substr(pos+3), ' ');

    while(true) {
      if (m[idx] <= 0) break;
      cnt[idx] ++;
      
      ll m2 = 0;
      for (auto & i: nums) if (wins.contains(i)) ++ m2;
      FOR(i, 1, m2+1) m[idx+i]++;
      m[idx]--;
    }    
    idx ++;
  }

  for(const auto [k,v] : cnt) res += v;
  cout << "Part 2: " << res << endl;
}

set<ll> explode(string const & s, char delim)
{
    set<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
    
      if (token.size() <= 0) continue;
      res.insert(stoi(trim(token)));
    }

    return res;
}

string trim(string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());

    return s;
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

