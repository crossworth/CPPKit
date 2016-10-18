## CPPKit - Simple C++ Functions for everyday use
---

#### Cross-platform C++ functions

`**NOTE:** This is not finished yet, there is a lot to be implemented on Windows and Unix yet.`

**Typedef**
* byte
* int8
* int16
* int32
* int64
* memory_info
* cpu_info


**Typedef: memory_info**
```
struct memory_info {
    int64 virtual_memory_total;`
    int64 virtual_memory_usage;
    int64 virtual_memory_process;
    int64 physical_memory_total;
    int64 physical_memory_usage;
    int64 physical_memory_process;
};
```

**Typedef: cpu_info**
```
struct cpu_info {
    double cpu_usage;
    double cpu_usage_process;
};
```



**Functions**

* `void print_error(const std::string& message)`
* `std::vector<std::string> explode(const std::string& string, const char& delimiter)`
* `std::string implode(const std::vector<std::string>& strings, const char& delimiter)`
* `std::string strtolower(std::string str`
* `std::string strtoupper(std::string str)`
* `std::string str_replace(std::string subject, const std::string& search, const std::string& replace)`
* `std::string str_ireplace(std::string subject, const std::string& search, const std::string& replace)`
* `std::vector<std::string> glob(const std::string& path)`
* `int32 str_word_count()` - ***NOT IMPLEMENTED YET***
* `int64 bits_to_bytes(int64 bits)`
* `int64 bytes_to_kilobytes(int64 bytes)`
* `int64 bytes_to_megabytes(int64 bytes)`
* `int64 bytes_to_gigabytes(int64 bytes)`
* `int64 kilobytes_to_megabytes(int64 kilobytes)`
* `int64 kilobytes_to_gigabytes(int64 kilobytes)`
* `int64 megabytes_to_bytes(int64 megas)`
* `int64 megabytes_to_kilobytes(int64 megas)`
* `int64 megabytes_to_gigabytes(int64 megabytes)`
* `int64 gigabytes_to_bytes(int64 gigas)`
* `int64 gigabytes_to_kilobytes(int64 gigas)`
* `int64 gigabytes_to_megabytes(int64 gigas)`
* `int64 uniqid()`
* `void print_r()` - ***NOT IMPLEMENTED YET***
* `int32 count_chars(const std::string& str, const char& ch)` - ***NOT IMPLEMENTED YET***
* `memory_info get_memory_info()` - ***PARTIALLY IMPLEMENTED (OSX)***
* `cpu_info get_cpu_info()` - ***PARTIALLY IMPLEMENTED (OSX)***
