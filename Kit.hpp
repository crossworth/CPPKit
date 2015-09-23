#ifndef KIT_HPP
#define KIT_HPP
#include <glob.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#ifdef _WIN32
    #include "windows.h"

#elif __APPLE__
    #include <sys/sysctl.h>
    #include <sys/param.h>
    #include <sys/mount.h>
    #include <mach/mach.h>
    #include <mach/vm_statistics.h>
    #include <mach/mach_types.h>
    #include <mach/mach_init.h>
    #include <mach/mach_host.h>
    #include <mach/mach_error.h>
    #include <mach/vm_map.h>

#elif __linux
    #include "sys/types.h"
    #include "sys/sysinfo.h"

#endif

namespace Kit {

typedef unsigned char byte;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

// we can override the print_error function
// by defining CUSTOM_PRINT_ERROR_FUNC and
// a void print_error(const std::string&) function
#ifndef CUSTOM_PRINT_ERROR_FUNC
#define CUSTOM_PRINT_ERROR_FUNC
void print_error(const std::string& message) {
    std::cerr << message << std::endl;
}
#endif

std::vector<std::string> explode(const std::string& string, const char& delimiter) {
    std::vector<std::string> result;
    std::istringstream iss(string);

    for (std::string token; std::getline(iss, token, delimiter); ) {
        result.push_back(std::move(token));
    }

    return result;
}

std::string implode(const std::vector<std::string>& strings, const char& delimiter = '\0') {
    std::string final_str;

    for (auto it : strings) {
        if (delimiter != '\0') {
            final_str = final_str + delimiter + it;
        } else {
            final_str = final_str + it;
        }
    }

    return final_str;
}

std::string strtolower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string strtoupper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::string str_replace(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::string str_ireplace(std::string subject, const std::string& search, const std::string& replace) {
    std::string subject_tmp = subject;
    std::string search_tmp = search;

    std::transform(subject_tmp.begin(), subject_tmp.end(), subject_tmp.begin(), ::tolower);
    std::transform(search_tmp.begin(), search_tmp.end(), search_tmp.begin(), ::tolower);

    size_t pos = 0;
    while ((pos = subject_tmp.find(search_tmp, pos)) != std::string::npos) {
         subject.replace(pos, search_tmp.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::vector<std::string> glob(const std::string& path) {
    using namespace std;
    glob_t glob_result;
    glob(path.c_str(), GLOB_TILDE, NULL, &glob_result);
    vector<string> ret;
    for(unsigned int i = 0; i < glob_result.gl_pathc; ++i){
        ret.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return ret;
}

int32 str_word_count() {
    return 0;
}

int64 bits_to_bytes(int64 bits) {
    return (bits / 8);
}

int64 bytes_to_kilobytes(int64 bytes) {
    return (bytes / 1000);
}

int64 bytes_to_megabytes(int64 bytes) {
    return ((bytes / 1000) / 1000);
}

int64 bytes_to_gigabytes(int64 bytes) {
    return (((bytes / 1000) / 1000) / 1000);
}

int64 kilobytes_to_megabytes(int64 kilobytes) {
    return (kilobytes / 1000);
}

int64 kilobytes_to_gigabytes(int64 kilobytes) {
    return ((kilobytes / 1000) / 1000);
}

int64 megabytes_to_bytes(int64 megas) {
    return ((megas * 1000) * 1000);
}

int64 megabytes_to_kilobytes(int64 megas) {
    return (megas * 1000);
}

int64 megabytes_to_gigabytes(int64 megabytes) {
    return (megabytes / 1000);
}

int64 gigabytes_to_bytes(int64 gigas) {
    return (((gigas * 1000) * 1000) * 1000);
}

int64 gigabytes_to_kilobytes(int64 gigas) {
    return ((gigas * 1000) * 1000);
}

int64 gigabytes_to_megabytes(int64 gigas) {
    return (gigas * 1000);
}

int64 uniqid() {

    return 0;
}

void print_r();

int32 count_chars(const std::string& str, const char& ch) {

    return 0;
}

struct memory_info {
    int64 virtual_memory_total;
    int64 virtual_memory_usage;
    int64 virtual_memory_process;
    int64 physical_memory_total;
    int64 physical_memory_usage;
    int64 physical_memory_process;
};

memory_info get_memory_info() {
    memory_info info = {};

    #ifdef _WIN32
    //TODO(pedro): Window port

    #elif __APPLE__

    // virtual memory
    xsw_usage vmusage = {};
    size_t size = sizeof(vmusage);
    if (sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0) !=0) {
        print_error("unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)");
    }

    info.virtual_memory_total = vmusage.xsu_total;
    info.virtual_memory_usage = vmusage.xsu_used;

    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO,
                                 (task_info_t)&t_info, &t_info_count)) {
        print_error("error while getting virtual_memory_process");
    }

    info.virtual_memory_process = t_info.virtual_size;

    // we can get the physical from the task_basic_info as well
    info.physical_memory_process = t_info.resident_size;

    // physical memory
    int mib[2];
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;

    size_t return_size = sizeof(info.physical_memory_total);
    if (sysctl(mib, 2, &info.physical_memory_total, &return_size, NULL, 0) == -1) {
        print_error("error in sysctl call");
    }

    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count)) {

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        info.physical_memory_usage = used_memory;
    } else {
        print_error("error while getting physical_memory_usage");
    }

    #elif __linux
    //TODO(pedro): linux port
    #endif

    return info;
}

struct cpu_info {
    double cpu_usage;
    double cpu_usage_process;
};


#ifdef __APPLE__
namespace {
static unsigned long long previous_total_ticks = 0;
static unsigned long long previous_idle_ticks = 0;

float calculate_cpu_load(unsigned long long idle_ticks, unsigned long long total_ticks) {
    unsigned long long total_ticks_since_last_time = total_ticks - previous_total_ticks;
    unsigned long long idle_ticks_since_last_time  = idle_ticks- previous_idle_ticks;
    float ret = 1.0f - ((total_ticks_since_last_time > 0) ? ((float)idle_ticks_since_last_time) / total_ticks_since_last_time : 0);
    previous_total_ticks = total_ticks;
    previous_idle_ticks  = idle_ticks;
    return ret;
}

float get_cpu_load() {
    host_cpu_load_info_data_t cpu_info;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpu_info, &count) == KERN_SUCCESS) {
        unsigned long long total_ticks = 0;
        for(int i = 0; i < CPU_STATE_MAX; i++)  {
            total_ticks += cpu_info.cpu_ticks[i];
        }
        return calculate_cpu_load(cpu_info.cpu_ticks[CPU_STATE_IDLE], total_ticks);
    } else {
        return -1.0f;
    }
}



}

#endif // __APPLE__

cpu_info get_cpu_info() {
    cpu_info info = {};

    #ifdef _WIN32

    #elif __APPLE__
    // We have to call this multiple times to get a better result;
    get_cpu_load();
    get_cpu_load();
    get_cpu_load();
    info.cpu_usage = static_cast<double>(get_cpu_load());
    info.cpu_usage_process = 0;

    #elif __linux

    #endif

    return info;
}

}

#endif // KIT_HPP
