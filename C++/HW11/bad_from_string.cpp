#include "bad_from_string.h"

bad_from_string::bad_from_string(char const *message) : mMessage(message) {}

char const *bad_from_string::what() const noexcept {
    return mMessage.c_str();
}
