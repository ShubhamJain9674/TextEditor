#pragma once

#include "gapbuffer.h"
#include <cstdlib>
#include <string>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>


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
    CHECK(buffer.GetAbsoluteCursorPos() == testTextSize - 6);
    CHECK(buffer.GetAbsoluteCursorPos() == buffer.GetGapStart());

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

    REQUIRE(buffer.GetAbsoluteCursorPos() == buffer.GetTextEnd() + 1);
    REQUIRE(buffer.GetBufferSize() == BUFFER_SIZE + 2 * BUFFER_GROW_SIZE);

    // Go Back and insert in between
    buffer.SetCursorPos(0);
    REQUIRE(buffer.GetAbsoluteCursorPos() == 0);
    REQUIRE(buffer.GetGapStart() == 0);

    buffer.MoveCursor(CURSOR_MOVE_RIGHT,6);
    // if i set pos as 0 the cursor should be before the 1st char in text; that mean cursor is representatively at -1


    REQUIRE(buffer.GetAbsoluteCursorPos() == 5);
    CHECK(buffer.GetAbsoluteCursorPos() == buffer.GetGapStart());
    buffer.InsertText(" Big ");

    CHECK(buffer.ToString() == "Hello Big  Big Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien World!");
    // after crazy thinking the conclusion is the mental model to keep in mind if cursor is set at pos(4) it is before the character 4 so
    // cursor abs pos = 4 but the character at 4 is shifted to 5 but the string pos of char at 5 is still 4.(CRAZY HUH)
}



/*

void TestSimple(GapBuffer& buffer)
{

    // insert at start;
    buffer.InsertText("Hello World!");
    buffer.DisplayContent();

    // Move Left;
    buffer.MoveCursor(CURSOR_MOVE_LEFT,6);

    // Insert text in between.
    // single char
    buffer.InsertAtCursor('B');
    //requires buffer movement.
    buffer.InsertText("ig ");
    buffer.DisplayContent();

    //add more than 50 character so buffer needs to grow.

    buffer.InsertText("Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien");
    buffer.DisplayContent();

    //testing space insertion when moving right;
    buffer.MoveCursor(CURSOR_MOVE_RIGHT,20);

    // testing large text
    buffer.InsertText("Lorem ipsum dolor sit amet consectetur adipiscing elit quisque \
faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus \
duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla.");


    buffer.DisplayContent();

    // going back and inserting in between.

    buffer.SetCursorPos(0);
    buffer.MoveCursor(CURSOR_MOVE_RIGHT,6);
    buffer.InsertText(" Big ");
    buffer.DisplayContent();
}

void TestBufferMoveRight(GapBuffer& buffer)
{
    buffer.InsertText("Hello World!");
    buffer.DisplayContent();
    buffer.SetCursorPos(0);
    buffer.InsertText("Hello");
    buffer.DisplayContent();
    buffer.SetCursorPos(buffer.GetTextEnd());
    buffer.InsertText(" WORLD ");
    buffer.DisplayContent();
}

void TestBufferToString(GapBuffer& buffer)
{
    buffer.InsertText("Hello World!");
    buffer.SetCursorPos(0);
    buffer.InsertText("Hello ");
    buffer.SetCursorPos(buffer.GetTextEnd());
    buffer.InsertText(" WORLD ");

    std::string text = buffer.ToString();
    std::cout << text << std::endl;
}

void TestCharAt(GapBuffer& buffer)
{
    std::cout << "accessing unassigned : " << buffer.CharAt(10) << std::endl;
    buffer.InsertText("Hello World!");
    std::cout << "Accesing  correct pos(0, 3 , 4 ,6, 11) for text : Hello World! : "<< buffer.CharAt(0) << ","
                << buffer.CharAt(3) << ","
                << buffer.CharAt(4) << ","
                << buffer.CharAt(6) << ","
                << buffer.CharAt(11) << ","
                << std::endl;

    buffer.SetCursorPos(0);
    std::cout << "Accesing  pos(0, 3 , 4 ,6, 11) for text : Hello World! when buffer is left end : "<< buffer.CharAt(0) << ","
                << buffer.CharAt(3) << ","
                << buffer.CharAt(4) << ","
                << buffer.CharAt(6) << ","
                << buffer.CharAt(11) << ","
                << std::endl;

    buffer.SetCursorPos(4);
    std::cout << "Buffer At Middle : " << buffer.CharAt(0) << ","
                << buffer.CharAt(3) << ","
                << buffer.CharAt(4) << ","
                << buffer.CharAt(6) << ","
                << buffer.CharAt(11) << ","
                << std::endl;
    buffer.SetCursorPos(11);
    std::cout << "Buffer At end : " << buffer.CharAt(0) << ","
                << buffer.CharAt(3) << ","
                << buffer.CharAt(4) << ","
                << buffer.CharAt(6) << ","
                << buffer.CharAt(11) << ","
                << std::endl;
}

void TestDeleteBefore(GapBuffer& buffer)
{
    // case : 1
    std::cout << "Delete Empty buffer" << std::endl;
    buffer.DeleteBeforeCursor();

    // case : 2
    buffer.InsertText("Hello worldd");
    buffer.DisplayContent();
    std::cout << "Normal Case :-" << std::endl;
    buffer.DeleteBeforeCursor();
    buffer.DisplayContent();

    // case : 3
    buffer.SetCursorPos(5);
    buffer.InsertAtCursor('A');
    std::cout << "Text In middle: " << std::endl;
    buffer.DisplayContent();
    buffer.SetCursorPos(buffer.GetTextEnd());
    buffer.SetCursorPos(6);
    buffer.DeleteBeforeCursor();
    std::cout << "After delete : " << std::endl;
    buffer.DisplayContent();

    // case : 4
    buffer.SetCursorPos(1);
    buffer.DeleteBeforeCursor();
    buffer.DisplayContent();
}

void TestDeleteAfter(GapBuffer& buffer)
{
    // case : 1
    std::cout << "Delete Empty buffer" << std::endl;
    buffer.DeleteAfterCursor();

    // case : 2 At The Start
    buffer.InsertText("hHelloo worldd");
    buffer.DisplayContent();
    std::cout << "At the start :-" << std::endl;
    buffer.SetCursorPos(0);
    buffer.DeleteAfterCursor();
    buffer.DisplayContent();

    // case : 3 At the middle
    buffer.SetCursorPos(4);
    std::cout << "Text In middle: " << std::endl;
    buffer.DisplayContent();
    buffer.DeleteAfterCursor();
    std::cout << "After delete : " << std::endl;
    buffer.DisplayContent();

    // case : 4 At the End
    std::cout << "text at the end : " << std::endl;
    buffer.SetCursorPos( buffer.GetTextEnd() - 1);
    buffer.DeleteAfterCursor();
    buffer.DisplayContent();
}

void TestDeleteRange(GapBuffer& buffer)
{

    // case 1 : Empty Buffer.
    buffer.DeleteRange(0,10);

    // case 2 : in beganing
    buffer.InsertText("Hello World!");
    std::cout << "Before : " << buffer.ToString() << std::endl;
    buffer.DeleteRange(0,4);
    std::cout << "After : " << buffer.ToString() << std::endl;


    //case 3 : in end
    buffer.SetCursorPos(0);
    buffer.InsertText("Hello");
    std::cout << "Before : " << buffer.ToString() << std::endl;
    buffer.DeleteRange(5,11);
    std::cout << "Afer : " << buffer.ToString() << std::endl;

    // case 4 : in Middle

    buffer.SetCursorPos(5);
    buffer.InsertText("WORLD world");
    std::cout << "before : " << buffer.ToString() << std::endl;
    buffer.DeleteRange(5,10);
    std::cout << "after : " << buffer.ToString() << std::endl;



}

*/
