#include <gtest/gtest.h>
#include "naive_array.h"
// #include "gap_buffer.h"
// #include "piece_table.h"
// #include "rope.h"

// ============================================================================
// Typed test suite — every test runs against all registered implementations.
// To add a new implementation, just add it to the EditorTypes list below.
// ============================================================================

template <typename T>
class EditorTest : public ::testing::Test {
protected:
    T editor;
};

using EditorTypes = ::testing::Types<
    NaiveArray
    // GapBuffer,
    // PieceTable,
    // Rope
>;

TYPED_TEST_SUITE(EditorTest, EditorTypes);

// ============================================================================
// Basic state
// ============================================================================

TYPED_TEST(EditorTest, StartsEmpty) {
    EXPECT_EQ(this->editor.length(), 0);
}

TYPED_TEST(EditorTest, CursorStartsAtZero) {
    EXPECT_EQ(this->editor.cursor_pos(), CURSOR_ORIGIN);
}

// ============================================================================
// Insert
// ============================================================================

TYPED_TEST(EditorTest, InsertAtBeginningOfEmptyBuffer) {
    this->editor.insert("hello");
    EXPECT_EQ(this->editor.length(), 5);
    //EXPECT_EQ(this->editor.slice(0, 5), "hello");
}

TYPED_TEST(EditorTest, InsertAtEnd) {
    this->editor.insert("hello");
    this->editor.insert(" world");
    EXPECT_EQ(this->editor.length(), 11);
    //EXPECT_EQ(this->editor.slice(0, 11), "hello world");
}

TYPED_TEST(EditorTest, InsertAtMiddle) {
    this->editor.insert("hello d");
    this->editor.move_left();
    this->editor.insert("worl");
    EXPECT_EQ(this->editor.length(), 11);
    ///EXPECT_EQ(this->editor.slice(0, 11), "hello world");
}

// TYPED_TEST(EditorTest, InsertAtBeginningOfNonEmptyBuffer) {
//     this->editor.insert("world");
//     this->editor.insert("hello ");
//     EXPECT_EQ(this->editor.slice(0, 11), "hello world");
// }
// 
// TYPED_TEST(EditorTest, InsertEmptyStringIsNoop) {
//     this->editor.insert(0, "hello");
//     this->editor.insert(2, "");
//     EXPECT_EQ(this->editor.length(), 5);
//     EXPECT_EQ(this->editor.slice(0, 5), "hello");
// }
// 
// TYPED_TEST(EditorTest, InsertMultipleTimesSequentially) {
//     this->editor.insert(0, "a");
//     this->editor.insert(1, "b");
//     this->editor.insert(2, "c");
//     EXPECT_EQ(this->editor.slice(0, 3), "abc");
// }
// 
// TYPED_TEST(EditorTest, InsertOutOfRangeThrows) {
//     EXPECT_THROW(this->editor.insert(99, "x"), std::out_of_range);
// }
// 
// // ============================================================================
// // Remove
// // ============================================================================
// 
TYPED_TEST(EditorTest, RemoveFromMiddle) {
    this->editor.insert("hello world");
    this->editor.move_left(5);
    this->editor.remove(5);
    EXPECT_EQ(this->editor.buffer(), "hello");
    EXPECT_EQ(this->editor.length(), 5);
}
// 
// TYPED_TEST(EditorTest, RemoveFromBeginning) {
//     this->editor.insert(0, "hello world");
//     this->editor.remove(0, 6);
//     EXPECT_EQ(this->editor.slice(0, 5), "world");
// }
// 
// TYPED_TEST(EditorTest, RemoveFromEnd) {
//     this->editor.insert(0, "hello world");
//     this->editor.remove(5, 6);
//     EXPECT_EQ(this->editor.slice(0, 5), "hello");
// }
// 
// TYPED_TEST(EditorTest, RemoveEntireBuffer) {
//     this->editor.insert(0, "hello");
//     this->editor.remove(0, 5);
//     EXPECT_EQ(this->editor.length(), 0);
// }
// 
// TYPED_TEST(EditorTest, RemoveWithLengthBeyondEndClampsGracefully) {
//     this->editor.insert(0, "hello");
//     // Ask to delete 100 chars from pos 3 — should just delete "lo"
//     this->editor.remove(3, 100);
//     EXPECT_EQ(this->editor.slice(0, 3), "hel");
//     EXPECT_EQ(this->editor.length(), 3);
// }
// 
// TYPED_TEST(EditorTest, RemoveZeroLengthIsNoop) {
//     this->editor.insert(0, "hello");
//     this->editor.remove(2, 0);
//     EXPECT_EQ(this->editor.length(), 5);
//     EXPECT_EQ(this->editor.slice(0, 5), "hello");
// }
// 
// TYPED_TEST(EditorTest, RemoveOutOfRangeThrows) {
//     EXPECT_THROW(this->editor.remove(99, 1), std::out_of_range);
// }
// 
// // ============================================================================
// // Slice
// // ============================================================================
// 
// TYPED_TEST(EditorTest, SliceEntireBuffer) {
//     this->editor.insert(0, "hello");
//     EXPECT_EQ(this->editor.slice(0, 5), "hello");
// }
// 
// TYPED_TEST(EditorTest, SliceSubstring) {
//     this->editor.insert(0, "hello world");
//     EXPECT_EQ(this->editor.slice(6, 5), "world");
// }
// 
// TYPED_TEST(EditorTest, SliceAtEnd) {
//     this->editor.insert(0, "hello");
//     EXPECT_EQ(this->editor.slice(4, 1), "o");
// }
// 
// TYPED_TEST(EditorTest, SliceWithLengthBeyondEndClampsGracefully) {
//     this->editor.insert(0, "hello");
//     EXPECT_EQ(this->editor.slice(3, 100), "lo");
// }
// 
// TYPED_TEST(EditorTest, SliceZeroLengthReturnsEmpty) {
//     this->editor.insert(0, "hello");
//     EXPECT_EQ(this->editor.slice(2, 0), "");
// }
// 
// TYPED_TEST(EditorTest, SliceOutOfRangeThrows) {
//     EXPECT_THROW(this->editor.slice(99, 1), std::out_of_range);
// }
// 
// // ============================================================================
// // Cursor
// // ============================================================================
// 
// TYPED_TEST(EditorTest, MoveCursorToValidPosition) {
//     this->editor.insert(0, "hello");
//     this->editor.move_cursor(3);
//     EXPECT_EQ(this->editor.cursor_pos(), 3);
// }
// 
// TYPED_TEST(EditorTest, MoveCursorToEnd) {
//     this->editor.insert(0, "hello");
//     this->editor.move_cursor(5);
//     EXPECT_EQ(this->editor.cursor_pos(), 5);
// }
// 
// TYPED_TEST(EditorTest, MoveCursorToBeginning) {
//     this->editor.insert(0, "hello");
//     this->editor.move_cursor(5);
//     this->editor.move_cursor(0);
//     EXPECT_EQ(this->editor.cursor_pos(), CURSOR_ORIGIN);
// }
// 
// TYPED_TEST(EditorTest, MoveCursorOutOfRangeThrows) {
//     this->editor.insert(0, "hello");
//     EXPECT_THROW(this->editor.move_cursor(99), std::out_of_range);
// }
// 
// 
