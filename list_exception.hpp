#ifndef LISTEXCEPTIONS_HPP
#define LISTEXCEPTIONS_HPP

#include <stdexcept>

class list_exception : public std::runtime_error {
    public:
        list_exception(const std::string& msg) : std::runtime_error(msg) {}
};

class empty_list_exception : public list_exception {
    public:
        empty_list_exception(const std::string& msg) : list_exception(msg) {}
};

#endif