#pragma once

#include <fstream>
#include "pool.hpp"

void mergeFile(uint64_t numberSeria, std::string outputStr, std::string t1, std::string t2, uint64_t count1, uint64_t count2) {
    std::ifstream in1(t1, std::ios::in);
    std::ifstream in2(t2, std::ios::in);
    std::ofstream out(outputStr, std::ios::out);

    uint64_t i1 = 0, i2 = 0, l1 = 0, l2 = 0;
    uint64_t x1, x2;
    bool f1, f2;
    while(1){
        if(!f1) in1 >> x1;
        if(!f2) in2 >> x2;
        f1 = false;
        f2 = false;
        if(i1 == (1ull << (numberSeria - 1)) && i2 == (1ull << (numberSeria - 1))){
            i1 = 0;
            i2 = 0;
        }

        if((l1 < count1) && (l2 < count2)){
            if(i1 < (1ull << (numberSeria - 1)) && i2 < (1ull << (numberSeria - 1))){
                if(x1 > x2){
                    f1 = true;
                    out << x2 << ' ';
                    ++i2;
                    ++l2;
                } else {
                    f2 = true;
                    out << x1 << ' ';
                    ++i1;
                    ++l1;
                }
            } else if(i1 < (1ull << (numberSeria - 1))){
                f2 = true;
                out << x1 << ' ';
                ++i1;
                ++l1;
            } else if(i2 < (1ull << (numberSeria - 1))){
                f1 = true;
                out << x2 << ' ';
                ++i2;
                ++l2;
            }
        } else if(l1 < count1){
            out << x1 << ' ';
            ++i1;
            ++l1;
        } else if(l2 < count2){
            out << x2 << ' ';
            ++i2;
            ++l2;
        } else{
            break;
        }
    }

    in1.close();
    in2.close();
    out.close();
}

void getSeria(uint64_t numberSeria, std::string outputStr, std::string t1, std::string t2, uint64_t &count1, uint64_t &count2){
    count1 = 0;
    count2 = 0;

    std::ifstream in(outputStr, std::ios::in);
    std::ofstream out1(t1, std::ios::out);
    std::ofstream out2(t2, std::ios::out);

    uint64_t x;
    for(uint64_t i = 0; in >> x; ++i){
        if(i /(1ull << (numberSeria - 1)) & 1){
            ++count1;
            out1 << x << ' ';
        } else {
            ++count2;
            out2 << x << ' ';
        }
    }

    out1.close();
    out2.close();
    in.close();
}

void mergeFileSort(std::string inputStr, std::string outputStr, std::string t1, std::string t2){
    std::ifstream in(inputStr, std::ios::in);
    std::ofstream out1(t1, std::ios::out);
    std::ofstream out2(t2, std::ios::out);
    uint64_t count = 0, count1 = 0, count2;
    uint64_t x;
    for(int i = 0; in >> x; ++i){
        ++count;
        if(i & 1){
            ++count1;
            out1 << x << ' ';
        } else {
            out2 << x << ' ';
        }
    }
    count2 = count - count1;
    out1.close();
    out2.close();
    in.close();
    mergeFile(1, outputStr, t1, t2, count1, count2);
    uint64_t k = 2;
    while(count > (1u << (k - 1))){
        getSeria(k, outputStr, t1, t2, count1, count2);
        mergeFile(k, outputStr, t1, t2, count1, count2);
        ++k;
    }
    remove(t1.c_str());
    remove(t2.c_str());
}

void mergeFileSortThread(std::string inputStr, std::string outputStr){
    std::ifstream in(inputStr, std::ios::in);
    std::ofstream t1("InMergeFile1.txt", std::ios::out);
    std::ofstream t2("InMergeFile2.txt", std::ios::out);
    uint64_t count = 0, count1 = 0, count2;
    uint64_t x;
    for(int i = 0; in >> x; ++i){
        ++count;
        if(i & 1){
            ++count1;
            t1 << x << ' ';
        } else {
            t2 << x << ' ';
        }
    }

    count2 = count - count1;
    t1.close();
    t2.close();
    in.close();

    ThreadPool pool(2);
    auto task1 = pool.exec(mergeFileSort, "InMergeFile1.txt", "OutMergeFile1.txt", "file1_1.txt", "file1_2.txt");
    task1.get();
    auto task2 = pool.exec(mergeFileSort, "InMergeFile2.txt", "OutMergeFile2.txt", "file2_1.txt", "file2_2.txt");
    task2.get();

    remove("InMergeFile1.txt");
    remove("InMergeFile2.txt");

    std::ifstream in1("OutMergeFile1.txt", std::ios::in);
    std::ifstream in2("OutMergeFile2.txt", std::ios::in);
    std::ofstream out(outputStr, std::ios::out);

    uint64_t l1 = 0, l2 = 0;
    uint64_t x1, x2;
    bool f1, f2;
    while(1){
        if(!f1) in1 >> x1;
        if(!f2) in2 >> x2;
        f1 = false;
        f2 = false;

        if((l1 < count1) && (l2 < count2)){
            if(x1 > x2){
                f1 = true;
                out << x2 << ' ';
                ++l2;
            } else {
                f2 = true;
                out << x1 << ' ';
                ++l1;
            }
        } else if(l1 < count1){
            out << x1 << ' ';
            ++l1;
        } else if(l2 < count2){
            out << x2 << ' ';
            ++l2;
        } else{
            break;
        }
    }

    in1.close();
    in2.close();
    remove("OutMergeFile1.txt");
    remove("OutMergeFile2.txt");
}