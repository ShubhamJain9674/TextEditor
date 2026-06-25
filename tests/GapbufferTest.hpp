#pragma once

#include "gapbuffer.h"

#include <catch2/catch_test_macros.hpp>


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
