#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <random>

using namespace std;
#define pb push_back
#define mp make_pair

vector<char> cast(string p) {
    vector<char> res;
    for (int i = 0; i < (int)p.size(); i++) {
        res.push_back(p[i]);
    }
    return res;
}

class rubick {
public:
    class edge {
    public:
        edge() {
            ed.resize(3, vector<char>(3));
        }

        void make(vector<vector<char> > m) {
            for (int i = 0; i < (int)m.size(); i++) {
                for (int j = 0; j < (int)m[i].size(); j++) {
                    ed[i][j] = m[i][j];
                }
            }
        }

        vector<char> get_row(int u) {
            return ed[u];
        }

        vector<char> get_column(int u) {
            vector<char> rs;
            for (int i = 0; i < 3; i++) {
                rs.push_back(ed[i][u]);
            }
            return rs;
        }

        void set_row(int u, vector<char> p) {
            ed[u] = p;
        }

        void set_column(int u, vector<char> p) {
            for (int i = 0; i < 3; i++) {
                ed[i][u] = p[i];
            }
        }

        void tran1() {
            vector<vector<char> > tp(3, vector<char>(3));
            for (int i = 0; i < 3; i++) {
                for (int j = 2; j >= 0; j--) {
                    tp[2 - j][i] = ed[i][j];
                }
            }
            ed = tp;
        }

        void tran2() {
            vector<vector<char> > tp(3, vector<char>(3));
            for (int i = 2; i >= 0; i--) {
                for (int j = 0; j < 3; j++) {
                    tp[j][2 - i] = ed[i][j];
                }
            }
            ed = tp;
        }

        void print() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << ed[i][j] << ' ';
                }
                cout << endl;
            }
        }

        void print_in_file(string f_name) {
            ofstream fout(f_name, ios_base::app);
            fout.open(f_name, ios_base::app);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    fout << ed[i][j] << ' ';
                }
                fout << endl;
            }
            fout << endl;
        }

        bool is_corect() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (ed[i][j] != ed[0][0]) {
                        return 0;
                    }
                }
            }
            return 1;
        }

        vector<vector<char> > get_ed() {
            return ed;
        }

    private:
        vector<vector<char> > ed;
    };

    void make_move(int type, int pos, bool up) {
        if (type == 1) {
            move1(pos, up);
        }
        if (type == 2) {
            move2(pos, up);
        }
        if (type == 3) {
            move3(pos, up);
        }
    }

    void move1(int pos, bool up) {
        vector<char> p0, p2, p4, p5;
        p0 = edges[0].get_column(pos);
        p2 = edges[2].get_column(pos);
        p4 = edges[4].get_column(pos);
        p5 = edges[5].get_column(pos);
        if (up) {
            edges[0].set_column(pos, p2);
            edges[2].set_column(pos, p4);
            edges[4].set_column(pos, p5);
            edges[5].set_column(pos, p0);
        } else {
            edges[0].set_column(pos, p5);
            edges[2].set_column(pos, p0);
            edges[4].set_column(pos, p2);
            edges[5].set_column(pos, p4);
        }
        if (pos == 0) {
            if (up) {
                edges[1].tran1();
            } else {
                edges[1].tran2();
            }
        } else {
            if (up) {
                edges[3].tran2();
            } else {
                edges[3].tran1();
            }
        }
    }

    void move2(int pos, bool up) {
        vector<char> p1, p2, p3, p5;
        p1 = edges[1].get_row(pos);
        p2 = edges[2].get_row(pos);
        p3 = edges[3].get_row(pos);
        p5 = edges[5].get_row((pos == 0) ? 2 : 0);
        if (up) {
            edges[1].set_row(pos, p2);
            edges[2].set_row(pos, p3);
            edges[3].set_row(pos, p5);
            edges[5].set_row((pos == 0) ? 2 : 0, p1);
        } else {
            edges[1].set_row(pos, p5);
            edges[2].set_row(pos, p1);
            edges[3].set_row(pos, p2);
            edges[5].set_row((pos == 0) ? 2 : 0, p3);
        }
        if (pos == 0) {
            if (up) {
                edges[0].tran2();
            } else {
                edges[0].tran1();
            }
        } else {
            if (up) {
                edges[4].tran1();
            } else {
                edges[4].tran2();
            }
        }
    }

    void move3(int pos, bool up) {
        vector<char> p0, p3, p4, p1;
        p0 = edges[0].get_row(pos);
        p3 = edges[3].get_column((pos == 0) ? 2 : 0);
        p4 = edges[4].get_row((pos == 0) ? 2 : 0);
        p1 = edges[1].get_column(pos);

        if (up) {
            edges[0].set_row(pos, p3);
            edges[3].set_column((pos == 0) ? 2 : 0, p4);
            edges[4].set_row((pos == 0) ? 2 : 0, p1);
            edges[1].set_column(pos, p0);
        } else {
            edges[0].set_row(pos, p1);
            edges[3].set_column((pos == 0) ? 2 : 0, p0);
            edges[4].set_row((pos == 0) ? 2 : 0, p3);
            edges[1].set_column(pos, p4);
        }
        if (pos == 0) {
            if (up) {
                edges[5].tran2();
            } else {
                edges[5].tran1();
            }
        } else {
            if (up) {
                edges[2].tran1();
            } else {
                edges[2].tran2();
            }
        }
    }

    void get(string fname) {
        ifstream in(fname);
        if (in.is_open()) {
            string line;
            for (int i = 0; i < 6; i++) {
                edge e;
                vector<vector<char> > cur;
                getline(in, line);
                cur.push_back(cast(line));
                getline(in, line);
                cur.push_back(cast(line));
                getline(in, line);
                cur.push_back(cast(line));
                e.make(cur);
                edges.push_back(e);
            }
        }
    }

    void pull() {
        for (int i = 0; i < (int)edges.size(); i++) {
            edges[i].print();
            cout << endl;
        }
    }

    void pull_in_f(string f_name) {
        ofstream fout;
        fout.open(f_name);
        for (int i = 0; i < (int)edges.size(); i++) {
            vector<vector<char> > cur = edges[i].get_ed();
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    fout << cur[k][l] << ' ';
                }
                fout << endl;
            }
        }
    }

    void can() {
        vector<edge> edges_ = edges;
        for (int i = 0; i < 1000; i++) {
            edges = edges_;
            for (int i = 0; i < 12; i++) {
                make_move((rand() % 3) + 1, rand() % 2 ? 0 : 2, rand() % 2);
                if (corect()) {
                    cout << "CORRECT " << endl;
                    return;
                }
            }
        }
        cout << "INCORRECT" << endl;
    }

    void rnd() {
        for (int i = 0; i < 5; i++) {
            make_move((rand() % 3) + 1, rand() % 2 ? 0 : 2, rand() % 2);
        }
    }

    void assem() {
        vector<edge> edges_ = edges;
        while (!corect()) {
            edges = edges_;
            vector<pair<int, int> > cmd;
            for (int i = 0; i < 12; i++) {
                int x1 = (rand() % 3) + 1;
                int x2 = rand() % 2 ? 0 : 2;
                int x3 = rand() % 2;
                make_move(x1, x2, x3);
                if (x1 == 1 && x2 == 0) {
                    cmd.pb(mp(2, x3));
                }
                if (x1 == 1 && x2 == 2) {
                    cmd.pb(mp(4, x3));

                }
                if (x1 == 2 && x2 == 0) {
                    cmd.pb(mp(1, x3));

                }
                if (x1 == 2 && x2 == 2) {
                    cmd.pb(mp(5, x3));

                }
                if (x1 == 3 && x2 == 0) {
                    cmd.pb(mp(6, x3));

                }
                if (x1 == 3 && x2 == 2) {
                    cmd.pb(mp(3, x3));

                }
                if (corect()) {
                    for (int i = 0; i < (int)cmd.size(); i++) {
                        cout << cmd[i].first << ' ' << cmd[i].second << endl;
                    }
                    break;
                }
            }
        }
    }

    bool corect() {
        bool ok = 1;
        for (int i = 0; i < (int)edges.size(); i++) {
            ok &= edges[i].is_corect();
        }
        return ok;
    }

private:
    vector<edge> edges;
};

int main() {
    srand(time(0));
    rubick r;
    r.get("cur.txt");
    cout << "Type operation: " << endl << "-out print in console" << endl
         << "-iscor check the correctness" << endl
         << "-read fname read from fname file" << endl <<
         "-find find solution" << endl <<
         "-gen generate correct pattern of Rubick" << endl
         << "-move x1 x2" << endl <<
         "x1 is edge x2 is direction 1 - up 0 - down";
    cout << endl;
    string cmd;
    int p, q;
    while (1) {
        cin >> cmd;
        if (cmd == "-out") {
            r.pull();
        }
        if (cmd == "-iscor") {
            r.can();
        }
        if (cmd == "-read") {
            cin >> cmd;
            r.get(cmd);
        }
        if (cmd == "-find") {
            r.assem();
        }
        if (cmd == "-gen") {
            r.rnd();
        }
        if (cmd == "-move") {
            cin >> p >> q;
            if (p == 1) {
                r.make_move(2, 0, q);
            }
            if (p == 2) {
                r.make_move(1, 0, q);
            }
            if (p == 3) {
                r.make_move(3, 2, q);
            }
            if (p == 4) {
                r.make_move(1, 2, q);
            }
            if (p == 5) {
                r.make_move(2, 2, q);
            }
            if (p == 6) {
                r.make_move(3, 1, q);
            }
        }
    }
    r.pull();
    return 0;
}