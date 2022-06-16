#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

struct RS_data {
    int code; // code num
    string op;
    bool busy = false;
    bool empty = true;
    int rd;
    bool rs_done[2];
    int rs_num[2] = {0};
};

const int reg_num = 10;
const int RS_times[4] = {1, 2, 10, 20}; // add sub mul div
vector<int> RF;
map<string, int> Reg_name;
vector<vector<string>> code;
vector<RS_data> RS(5); // 0~2 add/sub 3~4 mul/div
vector<int> RAT;
int do_buffer[2]; // 0: add/sub 1: mul/div val=rs_num
int buffer_cycle[2];
void read_code(string path);
void do_code();

ofstream debug_out("ALCO/test_data/test_out.txt");
// #define cout debug_out

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string path = "";

    path = argv[1];

    read_code(path);

    RF.assign(reg_num, 0);
    RAT.assign(reg_num, -1);
    for (int i = 0; i < 32; i++) {
        Reg_name["R" + to_string(i)] = i;
    }

    for (int i = 0; i < 2; i++) {
        do_buffer[i] = -1;
        buffer_cycle[i] = 0;
    }

    do_code();

    // system("pause");
    return 0;
}
void read_code(string path) {
    ifstream fin(path);
    if (!fin) {
        cout << "open file failed" << endl;
        exit(-1);
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty())
            continue;
        for (auto &i : line) {
            if (i == ',')
                i = ' ';
        }
        vector<string> line_code;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            line_code.push_back(word);
        }
        code.push_back(line_code);
    }
    for (auto i : code) {
        cout << i[0] << " " << i[1] << " " << i[2] << " " << i[3] << endl;
    }
    cout << "----------------------------------------------------\n";
}

void do_code() {
    int cycle = 1;
    int inst_num = code.size();
    int inst_finished = 0;
    int inst_pointer = 0;
    bool done = false;
    int add_sub_inst_num = 0;
    int mul_div_inst_num = 0;
    bool change = false;
    vector<string> code_tmp;
    while (!done) {

        change = false;

        if (do_buffer[0] != -1) {
            buffer_cycle[0]--;
        }

        if (do_buffer[1] != -1) {
            buffer_cycle[1]--;
        }

        if (buffer_cycle[0] == 0 && do_buffer[0] != -1) {

            if (RS[do_buffer[0]].op == "ADD" || RS[do_buffer[0]].op == "ADDI") {
                RF[RS[do_buffer[0]].rd] = RS[do_buffer[0]].rs_num[0] + RS[do_buffer[0]].rs_num[1];
            } else if (RS[do_buffer[0]].op == "SUB") {
                RF[RS[do_buffer[0]].rd] = RS[do_buffer[0]].rs_num[0] - RS[do_buffer[0]].rs_num[1];
            }
            RAT[RS[do_buffer[0]].rd] = -1;
            add_sub_inst_num--;
            RS[do_buffer[0]].busy = false;
            RS[do_buffer[0]].empty = true;
            buffer_cycle[0] = 0;
            do_buffer[0] = -1;
            change = true;
        }
        if (buffer_cycle[1] == 0 && do_buffer[1] != -1) {

            code_tmp = code[RS[do_buffer[1]].code];
            if (RS[do_buffer[1]].op == "MUL") {
                RF[RS[do_buffer[1]].rd] = RS[do_buffer[1]].rs_num[0] * RS[do_buffer[1]].rs_num[1];
            } else if (RS[do_buffer[1]].op == "DIV") {
                RF[RS[do_buffer[1]].rd] = RS[do_buffer[1]].rs_num[0] / RS[do_buffer[1]].rs_num[1];
            }
            RAT[RS[do_buffer[1]].rd] = -1;
            mul_div_inst_num--;
            RS[do_buffer[1]].busy = false;
            RS[do_buffer[1]].empty = true;
            buffer_cycle[1] = 0;
            do_buffer[1] = -1;
            change = true;
        }

        for (int i = 0; i < 5; i++) {
            if (!RS[i].empty && !RS[i].busy) {
                for (int j = 0; j < 2; j++) {
                    if (!RS[i].rs_done[j]) {
                        if (RAT[RS[i].rs_num[j]] == -1) {
                            RS[i].rs_done[j] = true;
                            RS[i].rs_num[j] = RF[RS[i].rs_num[j]];
                            change = true;
                        }
                    }
                }
            }
        }

        if (do_buffer[0] == -1) {
            for (int i = 0; i < 3; i++) {
                if (!RS[i].empty && !RS[i].busy) {
                    if (RS[i].rs_done[0] && RS[i].rs_done[1]) {
                        RS[i].busy = true;
                        do_buffer[0] = i;
                        if (code[RS[i].code][0] == "ADD" || code[RS[i].code][0] == "ADDI") {
                            buffer_cycle[0] = RS_times[0];
                        } else if (code[RS[i].code][0] == "SUB") {
                            buffer_cycle[0] = RS_times[1];
                        }
                        change = true;
                    }
                }
            }
        }
        if (do_buffer[1] == -1) {
            for (int i = 3; i < 5; i++) {
                if (!RS[i].empty && !RS[i].busy) {
                    if (RS[i].rs_done[0] && RS[i].rs_done[1]) {
                        RS[i].busy = true;
                        do_buffer[1] = i;
                        if (code[RS[i].code][0] == "MUL") {
                            buffer_cycle[1] = RS_times[2];
                        } else if (code[RS[i].code][0] == "DIV") {
                            buffer_cycle[1] = RS_times[3];
                        }
                        change = true;
                    }
                }
            }
        }

        if (inst_pointer != inst_num && (add_sub_inst_num < 3 || mul_div_inst_num < 2)) {
            code_tmp = code[inst_pointer];
            if ((code_tmp[0] == "ADD" || code_tmp[0] == "ADDI" || code_tmp[0] == "SUB") && add_sub_inst_num < 3) {
                for (int i = 0; i < 3; i++) {
                    if (RS[i].empty) {
                        RS[i].code = inst_pointer;
                        RS[i].op = code_tmp[0];
                        RS[i].rd = Reg_name[code_tmp[1]];
                        // cout << "RS[" << i << "].rd = " << RS[i].rd << endl;
                        if (RAT[Reg_name[code_tmp[2]]] == -1) {
                            RS[i].rs_num[0] = RF[Reg_name[code_tmp[2]]];
                            RS[i].rs_done[0] = true;
                        } else {
                            RS[i].rs_num[0] = Reg_name[code_tmp[2]];
                            RS[i].rs_done[0] = false;
                        }
                        if (code_tmp[0] == "ADDI") {
                            RS[i].rs_num[1] = stoi(code_tmp[3]);
                            RS[i].rs_done[1] = true;
                        } else {

                            if (RAT[Reg_name[code_tmp[3]]] == -1) {
                                RS[i].rs_num[1] = RF[Reg_name[code_tmp[3]]];
                                RS[i].rs_done[1] = true;
                            } else {
                                RS[i].rs_num[1] = Reg_name[code_tmp[3]];
                                RS[i].rs_done[1] = false;
                            }
                        }
                        RS[i].empty = false;
                        RAT[RS[i].rd] = i;
                        break;
                    }
                }
                add_sub_inst_num++;
                change = true;
                inst_pointer++;
            } else if ((code_tmp[0] == "MUL" || code_tmp[0] == "DIV") && mul_div_inst_num < 2) {
                for (int i = 3; i < 5; i++) {
                    if (RS[i].empty) {
                        RS[i].code = inst_pointer;
                        RS[i].op = code_tmp[0];
                        RS[i].rd = Reg_name[code_tmp[1]];
                        if (RAT[Reg_name[code_tmp[2]]] == -1) {
                            RS[i].rs_num[0] = RF[Reg_name[code_tmp[2]]];
                            RS[i].rs_done[0] = true;
                        } else {
                            RS[i].rs_num[0] = Reg_name[code_tmp[2]];
                            RS[i].rs_done[0] = false;
                        }

                        if (RAT[Reg_name[code_tmp[3]]] == -1) {
                            RS[i].rs_num[1] = RF[Reg_name[code_tmp[3]]];
                            RS[i].rs_done[1] = true;
                        } else {
                            RS[i].rs_num[1] = Reg_name[code_tmp[3]];
                            RS[i].rs_done[1] = false;
                        }
                        RS[i].empty = false;
                        RAT[Reg_name[code_tmp[1]]] = i;
                        break;
                    }
                }
                mul_div_inst_num++;
                inst_pointer++;
                change = true;
            }
        }

        if (change) {

            cout << "cycle: " << cycle << "\n";
            cout << "RF:\n";
            for (int i = 0; i < reg_num; i++) {
                cout << "R" << i << ": " << RF[i];
                cout << "\n";
            }
            cout << "\n";
            cout << "RAT:\n";
            for (int i = 0; i < reg_num; i++) {
                cout << "R" << i << ": " << (RAT[i] == -1 ? "-" : "RS" + to_string(RAT[i] + 1));
                cout << "\n";
            }
            cout << "\n";
            cout << "RS:\n";
            for (int i = 0; i < 3; i++) {
                cout << "RS" << i + 1 << ": ";
                if (RS[i].empty) {
                    cout << "-\n";
                    continue;
                } else {
                    if (code[RS[i].code][0] == "ADD" || code[RS[i].code][0] == "ADDI") {
                        cout << "+ ";
                    } else if (code[RS[i].code][0] == "SUB") {
                        cout << "- ";
                    }
                }
                if (RS[i].rs_done[0]) {
                    cout << RS[i].rs_num[0] << " ";
                } else {
                    cout << "RS" << RAT[RS[i].rs_num[0]] + 1 << " ";
                }
                if (RS[i].rs_done[1]) {
                    cout << RS[i].rs_num[1] << " ";
                } else {
                    cout << "RS" << RAT[RS[i].rs_num[1]] + 1 << " ";
                }
                cout << "\n";
            }

            cout << "\n";
            cout << "buffer: ";
            if (do_buffer[0] == -1) {
                cout << "-";
            } else {
                cout << "RS" << do_buffer[0] + 1 << " ";
                cout << RS[do_buffer[0]].rs_num[0] << " ";
                if (RS[do_buffer[0]].op == "ADD" || RS[do_buffer[0]].op == "ADDI") {
                    cout << "+ ";
                } else {
                    cout << "- ";
                }
                cout << RS[do_buffer[0]].rs_num[1] << " ";
            }

            cout << "\n\n";

            for (int i = 3; i < 5; i++) {
                cout << "RS" << i + 1 << ": ";
                if (RS[i].empty) {
                    cout << "-\n";
                    continue;
                } else {
                    if (code[RS[i].code][0] == "MUL") {
                        cout << "* ";
                    } else if (code[RS[i].code][0] == "DIV") {
                        cout << "/ ";
                    }
                }
                if (RS[i].rs_done[0]) {
                    cout << RS[i].rs_num[0] << " ";
                } else {
                    cout << "RS" << RAT[RS[i].rs_num[0]] + 1 << " ";
                }
                if (RS[i].rs_done[1]) {
                    cout << RS[i].rs_num[1] << " ";
                } else {
                    cout << "RS" << RAT[RS[i].rs_num[1]] + 1 << " ";
                }
                cout << "\n";
            }
            cout << "\n";
            cout << "buffer: ";
            if (do_buffer[1] == -1) {
                cout << "-";
            } else {
                cout << "RS" << do_buffer[1] + 1 << " ";
                cout << RS[do_buffer[1]].rs_num[0] << " ";
                if (RS[do_buffer[1]].op == "MUL") {
                    cout << "* ";
                } else {
                    cout << "/ ";
                }
                cout << RS[do_buffer[1]].rs_num[1] << " ";
            }
            cout << "\n\n";
            cout << "-----------------------------------------------------\n";
        }
        cycle++;
        if (inst_pointer == inst_num && add_sub_inst_num == 0 && mul_div_inst_num == 0) {
            done = true;
        }

        // system("pause");
    }
}