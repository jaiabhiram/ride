#ifndef TRIP_NOT_FOUND_EXCEPTION_HPP
#define TRIP_NOT_FOUND_EXCEPTION_HPP

#include <exception>
#include <string>
#include "tripException.hpp"

class TripNotFoundException : public TripException  {
public:
    explicit TripNotFoundException(const std::string& tripId);

    const char* what() const noexcept override;

private:
    std::string message;
};

#endif // TRIP_NOT_FOUND_EXCEPTION_HPP
