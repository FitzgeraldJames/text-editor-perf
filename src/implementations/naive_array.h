#pragma once
#include "editor_interface.h"
#include <string>
#include <string_view>

class NaiveArray : public EditorInterface {
public:
    NaiveArray() : cursor_({0,0}), buffer_({""}) {}
    explicit NaiveArray(std::string_view initial);

    CursorPosition cursor_pos() const override;
    size_t length() const override;
    std::string buffer() const override;
    //string_view slice(size_t len) const override;
    /* Movement commands */
    void move_to(CursorPosition pos) override;
    void move_up(size_t lines = 1) override;
    void move_down(size_t lines = 1) override;
    void move_left(size_t cols = 1) override;
    void move_right(size_t cols = 1) override;
    /* modify */
    void insert(std::string_view text) override;
    void remove(size_t length) override;


private:
    std::vector<std::string> buffer_;
    CursorPosition cursor_;
};
