#include <iostream>
#include <fstream>

using namespace std;


int main() {
    printf("creating test files \n");
    for(int i=1;i<=100;i++){
        fstream file;
        string fname = to_string(i) + ".txt";
        file.open(fname, ios::out);
        if(file) {
            for(int j=1;j<=300;j++) {
                file<<j<<endl;
            }
        }
    }
    printf("creating test files done");
    return 0;
}