#include "Kit.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    string str = "this is my test string";

    auto strings = Kit::explode(str, ' ');

    cout << endl;
    cout << "String explode test" << endl;

    for (auto it : strings) {
        cout << it << endl;
    }

    cout << endl;
    cout << "String replace" << endl;

    string str2 = Kit::str_ireplace(str, "stRing", "replace text");
    cout << str2 << endl;

    cout << endl;
    cout << "Glob" << endl;

    auto files = Kit::glob("./*.cpp");

    for (auto it : files) {
        cout << it << endl;
    }

    cout << endl;
    cout << "MEMORY USAGE" << endl;
    cout << "Physical Memory Total: " << Kit::bytes_to_megabytes(Kit::get_memory_info().physical_memory_total) << "mb" << endl;
    cout << "Physical Memory Usage: " << Kit::bytes_to_megabytes(Kit::get_memory_info().physical_memory_usage) << "mb" << endl;
    cout << "Physical Memory Process: " << Kit::bytes_to_megabytes(Kit::get_memory_info().physical_memory_process) << "mb" << endl;
    cout << "Virtual Memory Total: " << Kit::bytes_to_megabytes(Kit::get_memory_info().virtual_memory_total) << "mb" << endl;
    cout << "Virtual Memory Usage: " << Kit::bytes_to_megabytes(Kit::get_memory_info().virtual_memory_usage) << "mb" << endl;
    cout << "Virtual Memory Process: " << Kit::bytes_to_megabytes(Kit::get_memory_info().virtual_memory_process) << "mb" << endl;


    cout << endl;
    cout << "CPU USAGE" << endl;
    cout << "CPU Usage: " << Kit::get_cpu_info().cpu_usage << "%" << endl;


    return 0;
}
