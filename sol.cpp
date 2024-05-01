#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
class Reader {
     public:
     Reader(int t) {
        this->total_files = t;
        this->total_sum = 0;
    }

    int concurrent_sum() {
        //this will send each file to a new thread
        //each file sum will be computed in parallel threads
        this->total_sum = 0;
        for(int i=1;i<=this->total_files;i++) {
            string fname = get_file_name(i);
           
            threads.push_back(thread(&Reader::work, this, fname));
        }
        //wait for threads to complete
        for (auto &t : threads) {
            t.join();
        }
        threads.clear();
        return total_sum;
    }
    int sum() {
        //normal sum that runs on single thread for benchmarking purpose
        this->total_sum = 0;
         for(int i=1;i<=this->total_files;i++) {
            string fname = get_file_name(i);
            work(this, fname);
        }
        return total_sum;
    }

    private:
    int total_files;
    int total_sum;
    std::mutex m;
    vector<thread> threads;
    vector<ifstream> files;
    string get_file_name(int i) {
        //gets a file name in format ./[i].txt
        string name = to_string(i) + ".txt";
        name = "./" + name;
        return name;
    }
    void static work(Reader *r, string fname) {
        ifstream f;
        f.open(fname);
        if (f.fail()) {
            //panic on failure to open a file
            printf("failed to open file %s", fname);
            exit(0);
        }
        int a;
        int tot = 0;
        while(f >> a) {
            tot += a;
        }
        //f.close();
        //total sum from file will be summed to to total sum
        //which should be guarded by a mutex
        r->m.lock();
        r->total_sum += tot;
        r->m.unlock();
    }

};


int main() {
    //new reader takes an integer parameter of total files to be read from 
    Reader *r = new Reader(100);
    auto start = chrono::high_resolution_clock::now();
    int tot = r->concurrent_sum();
    auto end = chrono::high_resolution_clock::now();
    auto duration_concurrent = chrono::duration_cast<chrono::microseconds>(end - start);
    
    printf("total sum by concurrent run: %d \n", tot);

    start = chrono::high_resolution_clock::now();
    tot = r->sum();
    end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    printf("total sum by single thread run: %d \n", tot);


    printf("concurrent took %ld microseconds \nnormal run took %ld microseconds", duration_concurrent.count(), duration.count());
    delete r;
    return 0;
}