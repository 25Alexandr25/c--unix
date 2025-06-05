#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;


void hanoy(int disk_num, int from_stick, int to_stick, int med_stick, list<string> &route) {
    if (disk_num == 0) {
        return;
    }
    hanoy(disk_num - 1, from_stick, med_stick, to_stick, route);
    stringstream d_num, f_st, t_st;
    d_num << disk_num;
    f_st << from_stick;
    t_st << to_stick;
    string step = d_num.str() + f_st.str() + t_st.str();
    route.push_back(step);
    hanoy(disk_num - 1, med_stick, to_stick, from_stick, route);
}

int main() {
    int disk_num = 3, final_stick = 3, med_stick = 2, first_stick = 1;
    list<string> route;
    int iterations = pow(2, disk_num) - 1;
    hanoy(disk_num, first_stick, final_stick, med_stick, route);
    if (iterations != route.size()) {
        cout << "Algorithm is not complete correctly";
        return 1;
    }
    copy(route.begin(), route.end(), ostream_iterator<string>(cout, "\n"));
    cout << "Theoretical iterations " << iterations << "\n" << "Algorithmic iterations " << route.size() << "\n";
    route.clear();
    return 0;
}
