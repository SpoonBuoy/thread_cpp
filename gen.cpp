#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;


int main() {
    printf("creating test files \n");
    vector<thread> threads;
    for(int i=1;i<=100;i++){
        threads.push_back(thread([i]{
          fstream file;
          string fname = to_string(i) + ".txt";
          file.open(fname, ios::out);
          if(file) {
            for(int j=1;j<=1000;j++) {
                file<<j<<endl;
            }
         }
        }));
    }
    for(auto &t:threads) {
        t.join();
    }
    printf("creating test files done");
    return 0;
}