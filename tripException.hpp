#include <exception>

class TripException : public std::exception {
public:
    virtual const char* what() const noexcept override = 0;
};