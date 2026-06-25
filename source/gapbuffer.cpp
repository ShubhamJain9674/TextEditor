#include "gapbuffer.h"

/*
 to implement :-
 - delete range
 - (optional) iterators
 - shrink to fit:  (shrink buffer after deletion of most of the characters)
 - read through the code and revisit ideas and improvements.
*/




GapBuffer::GapBuffer()
{
    buffer = (char*)calloc(BUFFER_SIZE,sizeof(char) * BUFFER_SIZE);
    if(buffer == nullptr)
    {
        std::cout << "Mem alloc failed!" << std::endl;
    }

    gapStart     = 0;
    gapEnd       = BUFFER_SIZE - 1;
    cursor        = 0;
    size          = BUFFER_SIZE;
}



GapBuffer::~GapBuffer()
{
    if(buffer != nullptr)
        free(buffer);
}

void GapBuffer::DisplayContent()
{
    for(int i = 0; i < size;i++)
    {
        if(buffer[i] == '\0')
            continue;
        std::cout << buffer[i];
    }
    std::cout << std::endl;
}

std::string GapBuffer::ToString()
{
    std::string text;

    for(int i = 0;i < size;i++)
    {
        if(buffer[i] == '\0')
            continue;
        else
            text += buffer[i];
    }

    return text;
}

char GapBuffer::CharAt(int pos)
{
    if(pos < 0 || pos > size)
        return ' ';

    if(IsInGap(pos))
    {
        int offset = pos - gapStart + 1;
        int trueIndex = gapEnd + offset;
        return buffer[trueIndex];
    }
    else
        return buffer[pos];
}

void GapBuffer::InsertAtCursor(char ch)
{
    int gapSize = gapEnd - gapStart + 1;
    if(gapSize <= 0)
    {
        Grow();
    }

    if(cursor == gapStart)
    {
        buffer[cursor] = ch;
        gapStart++;
        cursor++;
    }
    else
    {
        if(buffer[cursor] == ' ')
        {
            buffer[cursor] = ch;
            cursor++;
        }
        else
        {
            MoveGap();
            buffer[cursor] = ch;
            cursor++;
            gapStart++;
        }
    }
}

void GapBuffer::InsertText(const std::string& s)
{
    for(size_t i = 0 ;i < s.size();i++)
    {
        InsertAtCursor(s[i]);
    }
}

void GapBuffer::DeleteBeforeCursor()
{
    if(cursor == 0)
        return;

    if(cursor != gapStart)
        MoveGap();

    buffer[cursor-1] = '\0';
    gapStart--;
}

void GapBuffer::DeleteAfterCursor()
{
    if(cursor == GetTextEnd() || gapEnd+1 >= size)
        return;

    if(cursor != gapStart)
        MoveGap();

    buffer[gapEnd+1] = '\0';
    gapEnd++;
}

void GapBuffer::DeleteRange(int start,int end)
{
    if(start < 0 || end  > GetTextEnd())
        return;

    if(start > end)
        return;

    SetCursorPos(start);
    for(int i = start;i <= end;i++)
    {
        DeleteAfterCursor();
    }
}

void GapBuffer::MoveCursor(int direction,int amount = 1)
{


    if(direction == 1)
    {
        // will not allow to move beyond allocated block;
        int textEnd = GetTextEnd();

        if(gapEnd + amount > textEnd + 1)
        {
            if(textEnd + 1 == size)
                Grow();
            else
                cursor = textEnd + 1;
        }
        else
        {
            cursor = gapEnd + amount;
        }
    }
    else
    {
        cursor = ((cursor-amount) > 0)? cursor-amount : 0;
    }
    MoveGap();
}

void GapBuffer::SetCursorPos(int pos)
{
    int textEnd = GetTextEnd();
    if(pos > textEnd)
        pos = textEnd;
    else if(pos < 0)
        pos = GetTextStart();
    else if(pos >= gapStart && pos <= gapEnd)  // can this be abstracted out into function getRelative pos
    {
        int offset = pos - gapStart + 1;
        pos = gapEnd + offset;
    }
    cursor = pos;
    MoveGap();
}

// test this function by rewriting it same way as GetTextStart()
int GapBuffer::GetTextEnd()
{
    int i = size - 1;
    while(buffer[i] == '\0')
        i--;
    return i;
}
int GapBuffer::GetTextStart()
{
    if(gapStart == 0)
        return gapEnd+1;
    else
        return 0;
}


void GapBuffer::Grow()
{
    int oldsize = size;
    size = size + BUFFER_GROW_SIZE;

    char* tmp = (char*)realloc(buffer,sizeof(char) * size);
    if(tmp == nullptr){
        std::cout << "Realloc failed!\n" << std::endl;
        free(buffer);
        exit(0);
    }
    buffer = tmp;
    memset(tmp+oldsize,0,size - oldsize);

    gapStart = GetTextEnd() + 1;
    gapEnd = size - 1;

    // idea instead of realloc make buffer a linked list structure :
    // - when Grow is called it mallocs another chunk of memory and the memory are linked doubly (both dir)
    // - effective when the block size is large like 4kb
}

void GapBuffer::MoveGap()
{
    if(gapStart > cursor)
    {
        int lastIndex  = gapStart - 1;

        for(int i = lastIndex;i >= cursor;i--)
        {
            buffer[gapEnd] = buffer[i];
            buffer[i] = '\0';
            gapEnd--;
            gapStart--;
        }
    }
    else if(gapStart < cursor)
    {
        int firstIndex = gapEnd + 1;

        // test for + 1
        // int steps = cursor - firstIndex + 1;

        int steps = cursor - firstIndex;

        for(int i = 0;i < steps;i++)
        {
            buffer[gapStart] = buffer[firstIndex];
            buffer[firstIndex] = '\0';
            gapStart++;
            gapEnd++;
            firstIndex++;
        }
        cursor = gapStart;
    }
}


