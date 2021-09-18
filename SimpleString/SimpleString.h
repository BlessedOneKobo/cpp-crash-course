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
        copy_from(other);
    }

    SimpleString(SimpleString&& other) {
        if (this == &other) return;
        move_from(other);
    }

    ~SimpleString() {
        delete[] buffer;
    }

    SimpleString& operator=(const SimpleString& other) {
        if (this == &other) return *this;
        copy_from(other);
        return *this;
    }
    SimpleString& operator=(SimpleString&& other) {
        if (this == &other) return *this;
        move_from(other);
        return *this;
    }
    SimpleString& operator+(SimpleString& other) {
        SimpleString* simple_string = new SimpleString{ max_size + other.max_size };
        simple_string->length = length + other.length;
        std::strncpy(simple_string->buffer, buffer, length);
        std::strncpy(simple_string->buffer + length, other.buffer, other.length);
        return *simple_string;
    }
    SimpleString& operator+=(SimpleString& other) {
        const char* old_buffer = buffer;
        
        max_size += other.max_size;
        buffer = new char[max_size];
        std::strncpy(buffer, old_buffer, length);
        std::strncpy(buffer + length, other.buffer, other.length);
        length += other.length;
        delete[] old_buffer;
        return *this;
    }
    SimpleString& operator*(unsigned short n) {
        SimpleString* new_str = new SimpleString{ max_size * n };
        new_str->length = length * n;
        new_str->buffer = new char[new_str->max_size];
        
        for (unsigned short i = 0; i < n; i++) {
            std::strncpy(new_str->buffer + length * i, buffer, length);
        }

        return *new_str;
    }
    SimpleString& operator*=(unsigned short n) {
        char* old_buffer = buffer;
        max_size *= n;
        buffer = new char[max_size];

        for (unsigned short i = 0; i < n; i++) {
            std::strncpy(buffer + length * i, old_buffer, length);
        }

        delete[] old_buffer;
        length *= n;
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
    
    void copy_from(const SimpleString& other) {
        buffer = new char[other.max_size];
        std::strncpy(buffer, other.buffer, other.length);
        length = other.length;
        max_size = other.max_size;
    }

    void move_from(SimpleString& other) {
        buffer = other.buffer;
        length = other.length;
        max_size = other.max_size;
        
        other.buffer = nullptr;
        other.length = 0;
        other.max_size = 0;
    }
};
