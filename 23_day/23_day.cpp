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

typedef pair<ll,ll> coord;

struct STATE {
  ll steps;
  coord curr;
  set<coord> visited;
};

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
  return {l.aa+r.aa,l.bb+r.bb};                                    
}     

coord WAYS [] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
set<char> SLOPES = {'^', 'v', '>', '<'};

bool is_out(const coord & c, ll n, ll m) {
  auto [y, x] = c;
  return (y < 0 || y >= n || x < 0 || x >= m);
}

pair<coord, bool> adjust(const coord & c, char x) {
  switch(x) {
    case '>': return {c + WAYS[1], true};
    case '<': return {c + WAYS[3], true};
    case 'v': return {c + WAYS[2], true};
    case '^': return {c + WAYS[0], true};
    default: return {c, false};
  }
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> v;
  
  while(getline(in, str)) v.PB(str);
  ll n = v.size(), m = v[0].size();
  coord start = {0,1}, end = {n-1, m-2};
  
  queue<STATE> q;
  q.push({0, start, {start}});

  ll res = 0;
  while(!q.empty()) {
    auto state = q.front(); q.pop();

    if (state.curr == end) {
      res = max(res, state.steps);
      continue;
    }

    for(auto & w: WAYS) {
      coord new_coord = state.curr + w;
      if (is_out(new_coord, n, m) || state.visited.contains(new_coord)) continue;
      if (v[new_coord.aa][new_coord.bb] == '#') continue;

      state.visited.insert(new_coord);
      
      bool adjusted = false;
      tie(new_coord, adjusted) = adjust(new_coord, v[new_coord.aa][new_coord.bb]);
      if (is_out(new_coord, n, m) || (adjusted && state.visited.contains(new_coord))) continue;
      if (adjusted) state.visited.insert(new_coord);
      q.push({state.steps+adjusted+1, new_coord, state.visited});
    }
  }

  cout << "Part 1: " << res << endl;
}

const map<char, coord> ADJUSTED_POS = {{'^', {-1,0}}, {'>', {0,1}}, {'v', {1,0}}, {'<', {0,-1}}};
const map<char, char> REVERSE = {{'^', 'v'}, {'v', '^'}, {'<', '>'}, {'>', '<'}};
set<char> fetch_dirs(const coord & curr, char c, const vector<string> & v) {
  ll n = v.size(), m = v[0].size();
  set<char> res;
  for (auto & [dir, pos]: ADJUSTED_POS) {
    if (dir == REVERSE.at(c)) continue;
    coord tmp = curr + pos;
    if (is_out(tmp, n, m) || v[tmp.aa][tmp.bb] == '#') continue;
    res.insert(dir);
  }

  return res;
}

map<coord, map<coord, ll>> make_nodes(const vector<string> & v) {
  ll n = v.size(), m = v[0].size();
  coord start = {0,1}, end = {n-1, m-2};

  map<coord, map<coord, ll>> nodes;

  set<pair<coord, char>> visited;
  queue<pair<coord, char>> q;
  q.push({start, 'v'});
  while(!q.empty()) {
    auto [curr, dir] = q.front(); q.pop();
    if (visited.contains({curr, dir})) continue;
    visited.insert({curr, dir});
    ll steps = 0;
    coord tmp = curr;
    while (++ steps) {
      tmp = tmp + ADJUSTED_POS.at(dir);
      set<char> dirs = fetch_dirs(tmp, dir, v);
      if (dirs.size() > 1 || tmp == end) {
        nodes[curr][tmp] = steps;
        nodes[tmp][curr] = steps;
        visited.insert({tmp, REVERSE.at(dir)});
        for(auto & i: dirs) {
          if (!visited.contains({tmp, i})) q.push({tmp,i});
        }
        break;
      }
      dir = *dirs.begin();
    }
  }
  return nodes;
}

ll get(const map<pair<coord, set<coord>>, ll> & cache, const pair<coord, set<coord>> & key, ll x) {
  if (!cache.contains(key)) return x;
  return cache.at(key);
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> v;
  while(getline(in, str)) v.PB(str);
  ll n = v.size(), m = v[0].size();
  coord start = {0,1}, end = {n-1, m-2};
  
  queue<STATE> q;
  q.push({0, start, {start}});

  ll res = 0;

  map<coord, map<coord, ll>> nodes = make_nodes(v);

  map<pair<coord, set<coord>>, ll> cache;
  while(!q.empty()) {
    auto state = q.front(); q.pop();

    if (state.curr == end) {
      if (state.steps > res) cout << state.steps << endl;
      res = max(res, state.steps);
      continue;
    }

    if (get(cache, {state.curr, state.visited}, -1) >= state.steps) continue;
    cache[{state.curr, state.visited}] = state.steps;
    set<coord> visited = state.visited;
    visited.insert(state.curr);

    for (auto & [k, v]: nodes[state.curr]) {
      if (visited.contains(k)) continue;
      ll steps = state.steps + v;
      if (get(cache, {k, visited}, 0) >= steps) continue;
      q.push({steps, k, visited});
    }
  }

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
