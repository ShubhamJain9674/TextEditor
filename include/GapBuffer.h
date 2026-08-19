#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_SIZE 50
#define BUFFER_GROW_SIZE 50
#define BUFFER_SHRINK_MARGIN static_cast<int>(0.10 * BUFFER_SIZE)





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

    void Clear();

    void MoveCursor(int direction,int amount);

    void SetCursorPos(int pos); // User's view of pos (pos considering no gap)

    int GetCursorPos()const; //user's view as well as imple as cursor will always be before gap

    int GetCursorCharacterPos() { return GetAbsCursorPos(); } // user's view


    int GetAbsTextEnd(); // Mem View

    int GetTextEnd(); // User View

    int GetTextStart();

    std::string ToString();

    int GetTextSize();

    char CharAt(int pos);




#ifndef NDEBUG

    std::string GetMemorySnapshot();

    int GetAbsCursorPos() { return cursor; }

    char GetValueAtAbsPos(int cursor);

    int GetGapStart() { return gapStart; }

    int GetGapEnd() { return gapEnd; }

    bool IsInGapDebug(int pos) { return IsInGap(pos); }

    int GetBufferSize() { return size; }


#endif

protected:

    void Grow();
    void Shrink();
    void MoveGap();

    int GetCursorCharacterTrueIndex();



private:
    inline bool IsInGap(int pos)
    {
        return pos >= gapStart && pos <= gapEnd;
    }

    inline int GetGapSize()
    {
        return gapEnd - gapStart + 1;
    }


    char* buffer;
    int gapStart;
    int gapEnd;
    int cursor;
    int size;
};
