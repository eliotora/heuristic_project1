//
// Created by eliotora on 15/05/23.
//
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string path = "VNDResults";
    int i = 0;
    long total_time50 = 0;
    long total_time100 = 0;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        i++;
        fstream file;
        string fpath = entry.path();
        file.open(fpath, ios::in);
        vector<string> row;
        string line, word, temp;
        int j = 0;
        getline(file, line);
        while (file >> temp) {
            row.clear();

            getline(file, line);
            stringstream s(line);

            while (getline(s, word, ',')) row.emplace_back(word);

            if (j < 50) total_time50 += stoi(row[1]);
            else total_time100 += stoi(row[1]);
            j++;
        }
    }
    cout << "Total time for instance of size 50: " << total_time50/(8*50) << endl;
    cout << "Total time for instance of size 100: " << total_time100/(8*50) << endl;
}

//Total time for instance of size 50: 451860 = 0.451860 sec
// 0.45 * 500 = 225 sec
//Total time for instance of size 100: 6410621 = 6.410621 sec
// 6.41 * 500 = 3205 sec


