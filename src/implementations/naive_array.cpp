#include "naive_array.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

NaiveArray::NaiveArray(std::string_view initial) : cursor_({0,0}), buffer_({""}) { 
        // create string buffer
        std::string current = buffer_[0];
        for(size_t i=0;i<initial.size();i++) {
            char c = initial[i];
            if(c=='\n') {
                buffer_.push_back("");
                current = buffer_[buffer_.size()-1];
            }
            current+=c;
        }
    }

CursorPosition NaiveArray::cursor_pos() const { return cursor_; }
size_t NaiveArray::length() const {
    size_t len = -1; // start at -1 to offset newline count
    for(auto line:buffer_){ len += line.size(); len+=1; /* newlines */ }
    return len;
}

std::string NaiveArray::buffer() const {
    bool first = true;
    std::string out;
    for(auto line:buffer_) {
        if(!first) out.append("\n");
        first=false;
        out.append(line);
    }
    return out;
}

/* Movement operations*/
void NaiveArray::move_to(CursorPosition pos) { 
    // Rebase to 0
    pos = {std::max(0UL,pos.l), std::max(0UL, pos.c)};
    cursor_.l= std::min(pos.l, buffer_.size()-1);
    cursor_.c= std::min(pos.c, buffer_[cursor_.l].size()-1); 
}
void NaiveArray::move_up(size_t n) { 
    auto line = buffer_[cursor_.l];
    cursor_.l = std::min(0UL, cursor_.l-n);
}
void NaiveArray::move_down(size_t n) {
    auto line = buffer_[cursor_.l];
    if(buffer_.size() < cursor_.l+1) {
        cursor_.l++;
        cursor_.c= std::min(line.size()-1, cursor_.c+n);
    }
}
void NaiveArray::move_left(size_t n) { 
    auto line = buffer_[cursor_.l];
    cursor_.c= std::max(0UL,cursor_.c-1);
}
void NaiveArray::move_right(size_t n) { 
    auto line = buffer_[cursor_.l];
    cursor_.c = std::min(line.size()-1,cursor_.c+n-1);
}
/*
 * Moidfy 
 */
void NaiveArray::insert( std::string_view text) {
    std::string& line = buffer_[cursor_.l];
    for(size_t i=0;i<text.size();i++){
        char c = text[i];
        if(c=='\n') {
            // add a new line if there isn't one
            if(++cursor_.l > buffer_.size()-1) { buffer_.push_back(""); }
            line = buffer_[cursor_.l++];
            cursor_.c = 0; // reset to start of line
        }
        line.insert(cursor_.c++,1, c);
        std::cout << "." << cursor_.c << " ";
    }
}

// ------------------------------------------------------------------ remove ---

void NaiveArray::remove(size_t length) {
    bool first = true;
    while(length) {
        std::string& line = buffer_[cursor_.l];
        size_t to_remove = std::min(length, line.size()-cursor_.c);
        std::cout << length << " " << to_remove <<  " " << cursor_.c << " " << cursor_.l <<" " << line.size() - cursor_.c << " " << line;
        length -= to_remove;

        if(first) {
            line.erase(cursor_.c, to_remove);
            move_down();
            cursor_.c = 0;
            first = false; 
            continue;
        }
        // delete whole line
        if(length) { buffer_.erase(buffer_.begin() + cursor_.l); }
        line.erase(cursor_.c, to_remove);

    }
}
