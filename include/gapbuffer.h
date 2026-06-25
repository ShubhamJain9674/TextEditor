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




#ifndef NDEBUG

    std::string GetMemorySnapshot();

    int GetAbsoluteCursorPos() { return cursor; }

    char GetValueAtAbsPos(int cursor);

    int GetGapStart() { return gapStart; }

    int GetGapEnd() { return gapEnd; }

    bool IsInGapDebug(int pos) { return IsInGap(pos); }

    int GetBufferSize() { return size; }

#endif

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

#ifndef NDEBUG

std::string GapBuffer::GetMemorySnapshot()
{
    std::string memorySnap = "";

    for(int i = 0;i < size;i++)
    {
        memorySnap += buffer[i];
    }

    return memorySnap;
}



#endif
