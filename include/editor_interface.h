// include/editor_interface.h
#pragma once
#include <string>
#include <string_view>

struct CursorPosition {
    size_t l;   // 0-indexed line number
    size_t c;   // 0-indexed column (byte offset within line)
    bool operator==(const CursorPosition&) const = default;  // C++20
};

constexpr CursorPosition CURSOR_ORIGIN{0, 0};

class EditorInterface {
public:
    virtual ~EditorInterface() = default;
    /* info */
    virtual CursorPosition cursor_pos() const = 0;
    virtual size_t length() const = 0;
    virtual std::string buffer() const = 0;
    // virtual std::string_view slice(size_t len) const = 0;
    /* Movement commands */
    virtual void move_to(CursorPosition pos) = 0;
    virtual void move_up(size_t lines = 1) = 0;
    virtual void move_down(size_t lines = 1) = 0;
    virtual void move_left(size_t cols = 1) = 0;
    virtual void move_right(size_t cols = 1) = 0;
    /* moidfy operations */
    virtual void insert(std::string_view text) = 0;
    virtual void remove(size_t length) = 0;
};
