#include <bits/stdc++.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EPS (1e-10)
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

#define FILE "demo.in"
//#define FILE "input.in"

typedef tuple<ll,ll,ll> coord;

void part_1(const string & file);
void part_2(const string & file);
coord explode(string const & s, char delim);
string trim(string s);

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<coord> pos, vel;

  while(getline(in, str)) {
    pos.PB(explode(trim(str.substr(0, str.find(" @ "))), ','));
    vel.PB(explode(trim(str.substr(str.find("@")+2)), ','));
  }

  ll res = 0, least = 200000000000000, most = 400000000000000;
  FOR(i, 0, pos.size()) {
    FOR(j, i+1, pos.size()) {
      auto [x1,y1,z1] = pos[i]; auto [vx1, vy1, vz1] = vel[i];
      auto [x2,y2,z2] = pos[j]; auto [vx2, vy2, vz2] = vel[j];

      ld a = ((ld)vy1/vx1), b = ((ld)vy2/vx2);
      ld c = y1 - a * x1, d = y2 - b * x2;
      
      ld x = (d - c) / (a - b);
      ld y = a * x + c;
     
      if (EQ(a,b)) continue;
      if (x >= least && x <= most && y >= least && y <= most) {
        if ((x - x1) / vx1 < 0 || (x - x2) / vx2 < 0) continue;  
        res++;
      }
    }
  }

  cout << "Part 1: " << res << endl;
}

Eigen::Matrix3d cross (const Eigen::Vector3d & v) {
    Eigen::Matrix3d result;
    result << 0, -v[2], v[1], 
    v[2], 0, -v[0], 
    -v[1], v[0], 0;
    return result;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<Eigen::Vector3d> pos;
  vector<Eigen::Vector3d> vel;
  while(getline(in, str)) {
    Eigen::Vector3d tmp, tmp2;

    tie(tmp[0], tmp[1], tmp[2]) = explode(trim(str.substr(0, str.find(" @ "))), ',');
    tie(tmp2[0], tmp2[1], tmp2[2]) = explode(trim(str.substr(str.find("@")+2)), ',');

    pos.PB(tmp);
    vel.PB(tmp2);
  }

  ld res = 0;
  Eigen::MatrixXd M(6, 6);
  Eigen::VectorXd Y(6);
  Y.segment<3>(0) = -pos[0].cross(vel[0]) + pos[1].cross(vel[1]);
  Y.segment<3>(3) = -pos[0].cross(vel[0]) + pos[2].cross(vel[2]);
  M.block<3, 3>(0, 0) = cross(vel[0]) - cross(vel[1]);
  M.block<3, 3>(3, 0) = cross(vel[0]) - cross(vel[2]);
  M.block<3, 3>(0, 3) = -cross(pos[0]) + cross(pos[1]);
  M.block<3, 3>(3, 3) = -cross(pos[0]) + cross(pos[2]);

  Eigen::VectorXd calc = M.inverse() * Y;
  FOR(i, 0, 3) res += calc[i];
  cout << fixed << "Part 2: " << (ll)round(res) << endl;
}

coord explode(string const & s, char delim) {
  vector<ll> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);)
    res.PB(stol(token));

  return {res[0], res[1], res[2]};
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
