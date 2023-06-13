#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define YELLOW   "\x1b[33m"
#define BLUE     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"
#define RESET    "\x1b[0m"

using namespace std;

#define RESULT_NUM 2

#if     RESULT_NUM == 1
    #define RESULT_FILE "result_1.txt"

#elif   RESULT_NUM == 2
    #define RESULT_FILE "result_2.txt"

#elif   RESULT_NUM == 4
    #define RESULT_FILE "result_4.txt"

#elif   RESULT_NUM == 5
    #define RESULT_FILE "result_5.txt"

#elif   RESULT_NUM == 8
    #define RESULT_FILE "result_8.txt"

#elif   RESULT_NUM == 16
    #define RESULT_FILE "result_16.txt"
#endif

int get_time(string line, int pos) {
    string str = line.substr(pos + 1);
    
    return stoi(str);
}

int get_iter(string line, int pos) {

    if (line.find("[INFO] Start") != string::npos || line.find("[INFO] End") != string::npos) {
        return 0;
    }

    string str = line.substr(pos + 1, 3);
    
    return stoi(str);
}



void read_data(std::string file_name, vector<pair<string, int>> &vector) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    string line;

    while (getline(fs, line)) {

        if (line.find("point") != string::npos) {
            
            string str;

            int pos_iter = line.find("]");
            int iter     = get_iter(line, pos_iter);

            int pos_time = line.find(":");
            int time     = get_time(line, pos_time);

            if (line.find("Start") != string::npos) {
                str = "START";
            }
            else if (line.find("End") != string::npos) {
                str = "END";
            }


            if (line.find("DMA") != string::npos) {
                str += "_DMA_" + to_string(iter);
                
            }
            else if (line.find("ACC") != string::npos) {
                str += "_ACC_" + to_string(iter);
            }
            else if (line.find("Intr") != string::npos) {
                str += "_ITR_" + to_string(iter);
            }
            
            vector.push_back(make_pair(str, time));

        }
    }

}

bool compare(pair<string, int> &a, pair<string, int> &b ){
	return a.second < b.second;
}

void print(vector<pair<string, int>> &vector) {

    for (auto v : vector) {
        if (v.first.find("DMA") != string::npos) 
            cout << YELLOW "[" << setw(12) << v.first << ", " << setw(8) << v.second << "]" RESET << "\n";
        else if (v.first.find("ACC") != string::npos) 
            cout << MAGENTA"[" << setw(12) << v.first << ", " << setw(8) << v.second << "]" RESET << "\n";
        else if (v.first.find("ITR") != string::npos) continue;
            // cout << CYAN   "[" << setw(12) << v.first << ", " << setw(8) << v.second << "]" RESET << "\n";
        else 
            cout << "[" << setw(12) << v.first << ", " << setw(8) << v.second << "]" RESET << "\n";
    }
}


int main (void) {

    vector<pair<string, int>> result;

    read_data(string(RESULT_FILE), result);

    sort(result.begin(), result.end(), compare);

    print(result);
}