#pragma once

#include "GapBuffer.h"
#include <string>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

/*
Refactor Test Cases :-
- Complete Testing
- Test Correctly : Know what right answer look like
- Test Validity : No circular logic (you shouldnt need to write tests for tests ) or unfalsifiable tests
- Unit Tests must be correct by inspection.
- use behaviour driven testing : test for expected behaviour where its difficult to get source for expected output.
*/

TEST_CASE("Char insertion at cursor Tests")
{
    GapBuffer buffer;

    // Single Insert;
    buffer.InsertAtCursor('H');
    CHECK(buffer.ToString() == "H");

    // Multiple Insertion;
    buffer.InsertAtCursor('E');
    buffer.InsertAtCursor('L');
    buffer.InsertAtCursor('L');
    buffer.InsertAtCursor('O');

    const std::string test = "HELLO";

    CHECK(buffer.ToString() =="HELLO");

    std::string check(BUFFER_SIZE,'\0');
    for(int i = 0;i < test.size();i++)
    {
        check[i] = test[i];
    }

    REQUIRE(buffer.GetMemorySnapshot() == check);

}



TEST_CASE("Text Insertion and Cursor Movement function")
{

    GapBuffer buffer;

    // Insertion at start

    std::string test1 = "Hello World!";
    buffer.InsertText(test1);
    CHECK(buffer.ToString() == test1);

    // Move Left
    int testTextSize = test1.size();

    buffer.MoveCursor(CURSOR_MOVE_LEFT,6);
    // although buffer indexing start from 0 cursor is expected to be +1 pos ahead of last char of test1
    CHECK(buffer.GetAbsCursorPos() == testTextSize - 6);
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());

    // Insert Text in between

    // Single Character
    buffer.InsertAtCursor('B');
    CHECK(buffer.ToString() == "Hello BWorld!");

    buffer.InsertText("ig ");
    CHECK(buffer.ToString() == "Hello Big World!");


    // Insert More than characters.
    CHECK(buffer.GetBufferSize() == BUFFER_SIZE);
    buffer.InsertText("Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien ");
    CHECK(buffer.ToString() == "Hello Big Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien World!");
    REQUIRE(buffer.GetBufferSize() == BUFFER_SIZE + BUFFER_GROW_SIZE);

    buffer.MoveCursor(CURSOR_MOVE_RIGHT,20);

    REQUIRE(buffer.GetAbsCursorPos() == buffer.GetAbsTextEnd() + 1);
    REQUIRE(buffer.GetBufferSize() == BUFFER_SIZE + 2 * BUFFER_GROW_SIZE);

    // Go Back and insert in between
    buffer.SetCursorPos(0);
    REQUIRE(buffer.GetAbsCursorPos() == 0);
    REQUIRE(buffer.GetGapStart() == 0);

    buffer.MoveCursor(CURSOR_MOVE_RIGHT,6);
    // if i set pos as 0 the cursor should be before the 1st char in text; that mean cursor is representatively at -1


    REQUIRE(buffer.GetAbsCursorPos() == 5);
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());
    buffer.InsertText(" Big ");

    CHECK(buffer.ToString() == "Hello Big  Big Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien World!");
    // after crazy thinking the conclusion is the mental model to keep in mind if cursor is set at pos(4) it is before the character 4 so
    // cursor abs pos = 4 but the character at 4 is shifted to 5 but the string pos of char at 5 is still 4.(CRAZY HUH)
}

TEST_CASE("Check CharAt")
{

    GapBuffer buffer;
    // accessing unassigned
    CHECK(buffer.CharAt(10) == '\0');

    // Checking bunch of random values

    std::string test = "Hello World!";
    buffer.InsertText(test.c_str());

    std::string control(BUFFER_SIZE,'\0');
    for(int i = 0; i < test.size();i++)
    {
        control[i] = test[i];
    }

    // domain check
    SECTION("Domain Check")
    {
        auto indexes = GENERATE(take(50,random(0,BUFFER_SIZE - 1)));
        REQUIRE(buffer.CharAt(indexes) == control[indexes]);
    }

    // negative check
    SECTION("Negative Check")
    {
        auto indexes2 = GENERATE(take(50,random(- BUFFER_SIZE,-1)));
        REQUIRE(buffer.CharAt(indexes2) == '\0');
    }

    // upper boundary check
   SECTION("Upper Boundary Check")
   {
       auto indexes3 = GENERATE(take(50,random(BUFFER_SIZE,BUFFER_SIZE * 2)));
       REQUIRE(buffer.CharAt(indexes3) == '\0');
   }
}


TEST_CASE("Gap Movement")
{
    // simple sanity check
    GapBuffer buffer;
    buffer.InsertText("Hello World!");
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());

    // buffer movement left

    buffer.SetCursorPos(0);
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());
    CHECK(buffer.GetGapStart() == 0);
    CHECK(buffer.CharAt(buffer.GetGapEnd()+1) == 'H');

    // Insert text gap moves in between
    buffer.InsertText("Hello");
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());

    // Inset text at the end gap moves at the end towards right
    buffer.SetCursorPos(buffer.GetAbsTextEnd()+1);
    buffer.InsertText(" WORLD ");
    CHECK(buffer.ToString() == "HelloHello World! WORLD ");
    CHECK(buffer.GetAbsTextEnd()+1 == buffer.GetAbsCursorPos());
    CHECK(buffer.GetAbsCursorPos() == buffer.GetGapStart());



}


TEST_CASE("test DeleteBeforeCursor func")
{
    GapBuffer buffer;
    //Case 1 empty buffer
    std::string Control(BUFFER_SIZE,'\0');
    buffer.DeleteBeforeCursor();

    CHECK(buffer.GetMemorySnapshot() == Control);

    // Case 2 : Delete At end
    buffer.InsertText("Hello Worldd");
    buffer.DeleteBeforeCursor();
    CHECK(buffer.ToString() == "Hello World");

    // Case 3 : Delete in middle
    buffer.SetCursorPos(5);

    buffer.InsertAtCursor('A');
    buffer.SetCursorPos(buffer.GetTextEnd() + 1);
    buffer.SetCursorPos(6);
    buffer.DeleteBeforeCursor();
    CHECK(buffer.ToString() == "Hello World");

    // case 4 : Delete first Character
    buffer.SetCursorPos(1);
    buffer.DeleteBeforeCursor();
    CHECK(buffer.ToString() == "ello World");

}

TEST_CASE("Testing Delete After")
{
    // Case 1 : Empty buffer
    GapBuffer buffer;
    std::string control(BUFFER_SIZE,'\0');
    buffer.DeleteAfterCursor();
    REQUIRE(buffer.GetMemorySnapshot() == control);

    //case 2 : At the start
    buffer.InsertText("hHelloo worldd");
    buffer.SetCursorPos(0);
    buffer.DeleteAfterCursor();
    CHECK(buffer.ToString() == "Helloo worldd");

    //case 3 : At the middle
    buffer.SetCursorPos(5);
    buffer.DeleteAfterCursor();
    CHECK(buffer.ToString() == "Hello worldd");

    // case 4 : At the end
    buffer.SetCursorPos(buffer.GetAbsTextEnd());
    buffer.DeleteAfterCursor();
    CHECK(buffer.ToString() == "Hello world");
}


TEST_CASE("Delete Range")
{
    // case 1 : Empty buffer
    GapBuffer buffer;
    std::string control(BUFFER_SIZE,'\0');
    buffer.DeleteRange(0,10);
    REQUIRE(buffer.GetMemorySnapshot() == control);

    // Case 2 : at the beginning
    buffer.InsertText("Hello World!");
    buffer.DeleteRange(0,4);

    CHECK(buffer.ToString() == " World!");
    CHECK(buffer.ToString()[0] == ' ');

    // Case 3 : At the end
    buffer.SetCursorPos(0);
    buffer.InsertText("Hello");
    buffer.DeleteRange(5,11);

    CHECK(buffer.ToString() == "Hello");

    // Case 4 : in the middle

    buffer.SetCursorPos(5);
    buffer.InsertText("World world");
    buffer.DeleteRange(5,9);
    CHECK(buffer.ToString() == "Hello world");

    // case 5 : overshoot start indexes

    buffer.DeleteRange(-10,10);
    CHECK(buffer.ToString() == "");

    // case 6 : overshoot end
    buffer.InsertText("HELLO");
    buffer.DeleteRange(0,100);
    CHECK(buffer.ToString() == "");

    // case 7 : start > end

    buffer.InsertText("HELLO");
    buffer.DeleteRange(4,3);
    CHECK(buffer.ToString() == "HELLO");

    // case 8 :  absurd values

    buffer.DeleteRange(-2385,8706);
    CHECK(buffer.ToString() == "");

}


TEST_CASE("Clear Buffer")
{
    GapBuffer buffer;

    buffer.InsertText("Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien ");

    CHECK(buffer.ToString() == "Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien ");

    buffer.Clear();

    REQUIRE(buffer.GetBufferSize() == BUFFER_SIZE);
    REQUIRE(buffer.GetAbsCursorPos() == 0);
    REQUIRE(buffer.GetGapStart() == 0);
    REQUIRE(buffer.GetGapEnd() == BUFFER_SIZE-1);

    std::string control(BUFFER_SIZE,'\0');
    REQUIRE(buffer.GetMemorySnapshot() == control);

}

TEST_CASE("Shrink test")
{
    GapBuffer buffer;

    for(int i = 0;i < BUFFER_SIZE;i++)
    {
        buffer.InsertAtCursor('A');
    }

    buffer.InsertText("LAST");

    CHECK(buffer.GetBufferSize() == 2 * BUFFER_SIZE);

    buffer.SetCursorPos(0);

    buffer.DeleteRange(0,20);
    CHECK(buffer.GetCursorPos() == 0);  // correct Cursor check.
    REQUIRE(buffer.GetGapStart() == 0);
    REQUIRE(buffer.GetBufferSize() == BUFFER_SIZE);
    REQUIRE(buffer.GetGapEnd() < BUFFER_SIZE);


}
