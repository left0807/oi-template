#include <bits/stdc++.h>
#define sz(a) (int)a.size()
using namespace std; 

const int N = 1e5 + 10;

struct Point {
    double x, y, ang;
    Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
} p[N];

double dis(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

bool cmp(Point p1, Point p2){
    if(p1.ang == p2.ang){
        return dis(p1, p[1]) < dis(p2, p[1]);
    }
    return p1.ang < p2.ang;
}

double cross(Point p1, Point p2){ return p1.x * p2.y - p1.y * p2.x; }



int main(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
    for(int i = 2; i <= n; i++){
        if(p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)){
            swap(p[1], p[i]);
        }
    }
    for (int i = 2; i <= n; ++i) {
        p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
    }
    sort(p + 2, p + n + 1, cmp);
    vector<int> sta{1};
    for(int i = 2; i <= n; i++){
        while(sz(sta) >= 2 && cross(p[sta[sz(sta) - 1]] - p[sta[sz(sta) - 2]], p[i] - p[sta[sz(sta) - 1]]) <= 0) sta.pop_back();
        sta.push_back(i);
    }
    sta.push_back(1);
    double ans = 0;
    for(int i = 0; i + 1 < sz(sta); i++){
        ans += dis(p[sta[i]], p[sta[i + 1]]);
    }

    cout << fixed << setprecision(2) << ans << '\n';
}