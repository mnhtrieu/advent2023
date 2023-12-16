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

enum WAY {UP, RIGHT, DOWN, LEFT};

enum OP {NOOP, MIRROR_UP, MIRROR_DOWN, MIRROR_LEFT, MIRROR_RIGHT, SPLITTER_PASS, SPLITTER_CREATE};

typedef pair<ll,ll> coord;

bool is_out(const coord & c, ll n, ll m) {
  auto [y, x] = c;
  return (y < 0 || y >= n || x < 0 || x >= m);
}

coord move(const pair<coord, WAY> & curr, ll n, ll m) {
  static const map<WAY, coord> MOVE = {{UP, {-1,0}}, {RIGHT, {0,1}}, {DOWN, {1,0}}, {LEFT, {0,-1}}};
  auto [y, x] = curr.aa; auto [y2, x2] = MOVE.at(curr.bb);
  return is_out({y+y2, x+x2}, n, m) ? make_pair((ll)-1,(ll)-1) : make_pair(y+y2, x+x2);
}

OP get_op(const WAY & way, const char & c) {
  if (c == '.') return NOOP;
  static const map<WAY, OP> MIRROR = {{UP, MIRROR_RIGHT}, {DOWN, MIRROR_LEFT}, {LEFT, MIRROR_DOWN}, {RIGHT, MIRROR_UP}};
  static const map<WAY, WAY> INVERSE = {{UP, DOWN}, {LEFT, RIGHT}, {DOWN, UP}, {RIGHT, LEFT}};
  if (c == '/') return MIRROR.at(way);
  if (c == '\\') return MIRROR.at(INVERSE.at(way));

  switch (way) {
    case UP: case DOWN: return c == '|' ? SPLITTER_PASS : SPLITTER_CREATE;
    case LEFT: case RIGHT: return c == '|' ? SPLITTER_CREATE : SPLITTER_PASS;
  }

  return NOOP;
}

bool do_action(char c, WAY & way, stack<pair<coord, WAY>> & beams, ll y, ll x) {
  OP op = get_op(way, c);
  static const map<OP, WAY> DIR = {{MIRROR_UP, UP}, {MIRROR_DOWN, DOWN}, {MIRROR_LEFT, LEFT}, {MIRROR_RIGHT, RIGHT}};
  switch(op) {
    case SPLITTER_CREATE: {
      if (c == '-') {
        beams.push({{y, x}, LEFT});
        beams.push({{y, x}, RIGHT});
      }
      else if (c == '|') {
        beams.push({{y, x}, UP});
        beams.push({{y, x}, DOWN});
      }
      return false;
    }
    case SPLITTER_PASS: case NOOP: break;
    default: way = DIR.at(op);
  }
  return true;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> tiles;
  map<coord, set<WAY>> energy;
  stack<pair<coord, WAY>> beams;
  beams.push({{0,-1}, RIGHT});
  while(getline(in, str)) tiles.PB(str);

  ll n = tiles.size(), m = tiles[0].size();
  while(!beams.empty()) {
    auto [pos, way] = beams.top(); beams.pop();
    while (true) {
      auto [y, x] = move({pos, way}, n, m);
      if (energy[{y, x}].contains(way)) break;
      pos = {y, x}; energy[pos].insert(way);
      if (y == -1) break;
      char c = tiles[y][x];
      if (!do_action(c, way, beams, y, x)) break;
    }
  }

  cout << "Part 1: " << energy.size()-1 << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> tiles;
  stack<pair<coord, WAY>> starts;

  while(getline(in, str)) tiles.PB(str);

  ll n = tiles.size(), m = tiles[0].size();
  const WAY ways[] = {UP, RIGHT, DOWN, LEFT};
  FOR(y, 0, n) {
    for_each(begin(ways), end(ways), [&y, &starts](const auto & i) { starts.push({{y, -1}, i}); });
    for_each(begin(ways), end(ways), [&y, &m, &starts](const auto & i) { starts.push({{y, m}, i}); });
  }

  FOR(x, 0, m) {
    for_each(begin(ways), end(ways), [&x, &starts](const auto & i) { starts.push({{-1, x}, i}); });
    for_each(begin(ways), end(ways), [&x, &n, &starts](const auto & i) {  starts.push({{n, x}, i}); });
  }

  ll res = 0;
  while(!starts.empty()) {
    map<coord, set<WAY>> energy;
    stack<pair<coord, WAY>> beams;
    beams.push(starts.top()); starts.pop();
    while(!beams.empty()) {
      auto [pos, way] = beams.top(); beams.pop();
      while (true) {
        auto [y, x] = move({pos, way}, n, m);
        if (energy[{y, x}].contains(way)) break;
        pos = {y, x}; energy[pos].insert(way);
        if (y == -1) break; 
        char c = tiles[y][x];
        if (!do_action(c, way, beams, y, x)) break;
      }
    }
    res = max(res, (ll)energy.size()-1);
  }

  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim) {
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
