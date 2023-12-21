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

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
  return {l.aa+r.aa,l.bb+r.bb};                                    
}             

typedef pair<ll,ll> coord;

coord WAYS [] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

bool is_out(const coord & c, ll n, ll m) {
  auto [y, x] = c;
  return (y < 0 || y >= n || x < 0 || x >= m);
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> v;
  coord start;
  while(getline(in, str)) {
    size_t pos = 0; if ((pos = str.find("S")) != string::npos) start = {v.size(), pos};
    v.PB(str);
  }

  queue<coord> q; q.push(start);
  ll steps = 0, n = v.size(), m = v[0].size();
  while(steps++ < 64) {
    queue<coord> tmp;
    set<coord> visited;
    while(!q.empty()) {
      auto c = q.front(); q.pop();
      for(auto & w: WAYS) {
        coord new_coord = c + w;
        if (is_out(new_coord, n, m) || visited.contains(new_coord)) continue;
        if (v[new_coord.aa][new_coord.bb] == '#') continue;
        tmp.push(new_coord);
        visited.insert(new_coord);
      }
    }
    swap(q, tmp);
  }
  cout << "Part 1: " << q.size() << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> v;
  coord start;
  while(getline(in, str)) {
    size_t pos = 0; if ((pos = str.find("S")) != string::npos) start = {v.size(), pos};
    v.PB(str);
  }

  queue<pair<coord, ll>> q; q.push({start, 0});
  ll n = v.size(), m = v[0].size();
  map<coord, ll> visited;
  while(!q.empty()) {
    auto [c, steps] = q.front(); q.pop();
    if (visited.contains(c)) continue;
    visited[c] = steps;
    for(auto & w: WAYS) {
      coord new_coord = c + w;
      if (is_out(new_coord, n, m) || visited.contains(new_coord)) continue;
      if (v[new_coord.aa][new_coord.bb] == '#') continue;
      q.push({new_coord, steps + 1});
    }
  }

  ll even_corners = count_if(visited.begin(), visited.end(), [](auto & i) { return i.bb % 2 == 0 && i.bb > 65; });
  ll odd_corners = count_if(visited.begin(), visited.end(), [](auto & i) { return i.bb % 2 == 1 && i.bb > 65; });
  ll even = count_if(visited.begin(), visited.end(), [](auto & i) { return i.bb % 2 == 0; });
  ll odd = count_if(visited.begin(), visited.end(), [](auto & i) { return i.bb % 2 == 1; });
  ll x = 202300;
  ll res = ((x+1)*(x+1)) * odd + (x*x) * even - (x+1) * odd_corners + x * even_corners;

  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim) {
  vector<ll> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);)
    res.PB(stoi(token));

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
