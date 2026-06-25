#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_SIZE 50
#define BUFFER_GROW_SIZE 50
#define CURSOR_MOVE_RIGHT 1
#define CURSOR_MOVE_LEFT -1




class GapBuffer{

public:
    GapBuffer();
    ~GapBuffer();

    void DisplayContent();

    void InsertAtCursor(char ch);

    void InsertText(const std::string& s);

    void DeleteBeforeCursor();

    void DeleteAfterCursor();

    void DeleteRange(int start,int end);

    void MoveCursor(int direction,int amount);

    void SetCursorPos(int pos);

    int GetTextEnd();

    int GetTextStart();

    std::string ToString();

    char CharAt(int pos);

protected:

    void Grow();
    void MoveGap();

private:
    inline bool IsInGap(int pos)
    {
        return pos >= gapStart && pos <= gapEnd;
    }

    char* buffer;
    int gapStart;
    int gapEnd;
    int cursor;
    int size;
};
