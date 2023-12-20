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
unordered_set<string> explode(string const & s, char delim);
string trim(string s);

enum TYPE {
  BROADCASTER,
  CONJUCTION,
  FLIP_FLOP,
};

struct MODULE {
  bool on;
  TYPE type;
  unordered_set<string> dest;
};

map<string, bool> copy_state(map<string, MODULE> & mods) {
  map<string, bool> m;
  for(auto & [k, v]: mods) m[k] = v.on;
  return m;
}

tuple<ll, ll> exec(map<string, MODULE> & mods, map<string, map<string, bool>> cons) {
  map<bool, ll> res = {{false, 0}, {true, 0}};
  ll cycles = 0;
  while(cycles++ < 1000) {
    queue<tuple<string,string,bool>> q;
    q.push({"broadcaster", "button", false});
    while(!q.empty()) {
      auto [m, s, in] = q.front(); q.pop();
      bool out = in;
      res[in] ++;
      if (!mods.contains(m)) continue;
      if (mods[m].type == FLIP_FLOP && in) continue;
      if (mods[m].type == CONJUCTION) { cons[m][s] = in; out = !all_of(cons[m].begin(), cons[m].end(), [](auto & i) { return i.bb; }); }
      else if (mods[m].type == FLIP_FLOP) out = mods[m].on = !mods[m].on;

      for(auto & i: mods[m].dest) q.push({i, m, out});
    }
  }
  return {res[true], res[false]};
}

map<string, ll> exec2(map<string, MODULE> & mods, map<string, map<string, bool>> cons) {
  map<string, ll> rxs;
  for(auto [k,v]: cons["dd"]) rxs[k] = -1;
  ll cycles = 0;
  while(++cycles) {
    queue<tuple<string,string,bool>> q;
    q.push({"broadcaster", "button", false});
    if (all_of(rxs.begin(), rxs.end(), [](auto & i) { return i.bb > -1;})) return rxs;
    while(!q.empty()) {
      auto [m, s, in] = q.front(); q.pop();
      bool out = in;
      if (!mods.contains(m)) continue;
      if (mods[m].type == FLIP_FLOP && in) continue;
      if (mods[m].type == CONJUCTION) { 
        cons[m][s] = in; 
        out = !all_of(cons[m].begin(), cons[m].end(), [](auto & i) { return i.bb; });
      }
      else if (mods[m].type == FLIP_FLOP) out = mods[m].on = !mods[m].on;

      for(auto & i: mods[m].dest) {
        if (i == "rx") 
          for(auto & [k, v]: cons[m]) 
            if (v) { rxs[k] = cycles; }
        
        q.push({i, m, out});
      }
    }
  }
  return rxs;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  map<string, MODULE> mods;
  map<string, map<string, bool>> cons;
  unordered_set<string> c;
  while(getline(in, str)) {
    string m = trim(str.substr(0, str.find(" ->")));
    string d = trim(str.substr(str.find("->") + 2));
    if (m[0] == '%') mods[m.substr(1)] = {false, FLIP_FLOP, explode(d, ',')};
    else if (m[0] == '&') {mods[m.substr(1)] = {false, CONJUCTION, explode(d, ',')}; c.insert(m.substr(1)); }
    else if (m[0] == 'b') mods[m] = {true, BROADCASTER, explode(d, ',')};
  }

  for(auto & i: c) 
    for(auto & [k, v]: mods)
      if (v.dest.contains(i)) cons[i][k] = false;      

  auto [high, low] = exec(mods, cons);
  cout << "Part 1: " << high * low << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  map<string, MODULE> mods;
  map<string, map<string, bool>> cons;
  unordered_set<string> c;
  while(getline(in, str)) {
    string m = trim(str.substr(0, str.find(" ->")));
    string d = trim(str.substr(str.find("->") + 2));
    if (m[0] == '%') mods[m.substr(1)] = {false, FLIP_FLOP, explode(d, ',')};
    else if (m[0] == '&') {mods[m.substr(1)] = {false, CONJUCTION, explode(d, ',')}; c.insert(m.substr(1)); }
    else if (m[0] == 'b') mods[m] = {true, BROADCASTER, explode(d, ',')};
  }

  for(auto & i: c) 
    for(auto & [k, v]: mods) 
      if (find(v.dest.begin(), v.dest.end(), i) != v.dest.end()) cons[i][k] = false;      

  map<string, ll> tmp = exec2(mods, cons);
  ll res = 1;
  for(auto & [k,v]: tmp) res = lcm(res, v);
  cout << "Part 2: " << res << endl;
}

unordered_set<string> explode(string const & s, char delim) {
  unordered_set<string> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);)
    res.insert(token);

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
