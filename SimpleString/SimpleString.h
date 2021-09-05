#include <cstring>
#include <stdexcept>

struct SimpleString {
    SimpleString(const size_t max_size) {
        if (max_size == 0) {
            throw std::runtime_error{ "max_size cannot be zero(0)." };
        }
        buffer = new char[max_size];
        buffer[0] = '\0';
        length = 0;
        this->max_size = max_size;
    }

    SimpleString(const SimpleString& other) {
        copySimpleString(other);
    }

    SimpleString(SimpleString&& other) {
        if (this == &other) return;
        moveSimpleString(other);
    }

    ~SimpleString() {
        delete[] buffer;
    }

    SimpleString& operator=(const SimpleString& other) {
        if (this == &other) return *this;
        copySimpleString(other);
        return *this;
    }

    SimpleString& operator=(SimpleString&& other) {
        if (this == &other) return *this;
        moveSimpleString(other);
        return *this;
    }

    void append_line(const char* newline) {
        auto newline_len = strlen(newline);
        // 2 is for '\n' and '\0'
        if (newline_len + length + 2 > max_size) {
            throw std::runtime_error{ "newline is too big for SimpleString" };
        }
        std::strncpy(buffer + length, newline, newline_len + 2);
        length += newline_len;
        buffer[length++] = '\n';
    }

    void print(const char* tag) {
        printf("%s: %s", tag, buffer);
    }
private:
    size_t max_size;
    size_t length;
    char* buffer;
    
    void copySimpleString(const SimpleString& other) {
        buffer = new char[other.max_size];
        std::strncpy(buffer, other.buffer, other.length);
        length = other.length;
        max_size = other.max_size;
    }

    void moveSimpleString(SimpleString& other) {
        buffer = other.buffer;
        length = other.length;
        max_size = other.max_size;
        
        other.buffer = nullptr;
        other.length = 0;
        other.max_size = 0;
    }
};
