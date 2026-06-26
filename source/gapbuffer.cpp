#include "gapbuffer.h"

/*
 to implement :-
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
        return '\0';

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

    Shrink();
}

void GapBuffer::DeleteAfterCursor()
{
    if(cursor == GetAbsTextEnd() || gapEnd+1 >= size)
        return;

    if(cursor != gapStart)
        MoveGap();

    buffer[gapEnd+1] = '\0';
    gapEnd++;
    Shrink();
}

void GapBuffer::DeleteRange(int start,int end)
{
    if(start < 0)
        start = 0;

    int textEnd = GetAbsTextEnd();

    if(end > textEnd)
        end = textEnd;


    if(start > end)
        return;

    int originalCursorPos = GetCursorCharacterPos();

    SetCursorPos(start);

    for(int i = start;i <= end;i++)
    {
        DeleteAfterCursor();
    }

    SetCursorPos(originalCursorPos);
}

void GapBuffer::Clear()
{
    // (NOTE) it would be good to realloc to default size if we clear everything but
    // what if the person does undo.

    char* tmp = nullptr;
    tmp = (char*)realloc(buffer,BUFFER_SIZE);

    if(tmp == nullptr)
    {
        std::cout << "Realloc failed" << std::endl;
        return;
    }

    buffer = tmp;
    memset((void*)buffer,'\0',BUFFER_SIZE);
    cursor = 0;
    gapStart = 0;
    gapEnd = BUFFER_SIZE - 1;
    size = BUFFER_SIZE;

}

int GapBuffer::GetCursorPos()
{
    // if(IsInGap(cursor))
    // {
    //     int offset = cursor - gapStart + 1;
    //     return gapEnd + offset;
    // }

    return cursor;

}


int GapBuffer::GetCursorCharacterTrueIndex()
{
    if(IsInGap(cursor))
    {
        int offset = cursor - gapStart + 1;
        return gapEnd + offset;
    }

    return cursor;
}


void GapBuffer::MoveCursor(int direction,int amount = 1)
{


    if(direction == 1)
    {
        // will not allow to move beyond allocated block;
        int textEnd = GetAbsTextEnd();

        if(gapEnd + amount > textEnd + 1)
        {
            if(textEnd + 1 == size)
                Grow();

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

    // pos in user's view


    int textEnd = GetAbsTextEnd();
    if(pos > textEnd)
    {
        if(textEnd+1 == size)
            Grow();
        pos = textEnd + 1;
    }
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

int GapBuffer::GetTextEnd()
{
    // returns position of last character . (user's view)
    int end = GetAbsTextEnd();
    if(gapEnd < end)
    {
        int noOfCharFromEnd = end - gapEnd; // inclusive last char
        int posBeforeGap = gapStart - 1;
        return posBeforeGap + noOfCharFromEnd;
    }
    return end;

}

// test this function by rewriting it same way as GetTextStart()
int GapBuffer::GetAbsTextEnd()
{
    int i = size - 1;
    while(buffer[i] == '\0' && i >= 0)
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

    gapStart = GetAbsTextEnd() + 1;
    gapEnd = size - 1;

    // idea instead of realloc make buffer a linked list structure :
    // - when Grow is called it mallocs another chunk of memory and the memory are linked doubly (both dir)
    // - effective when the block size is large like 4kb
}

void GapBuffer::Shrink()
{
    // if the cursor is at the border of buffer and user is continuously adding and deleting text
    // it will grow and shrink repeatedly wasting cycles


    // int requiredSize = (GetAbsTextEnd() + BUFFER_SIZE - 1) / BUFFER_SIZE; //  ceil int division

    std::string text = ToString();
    int requiredSize = ((text.size() + BUFFER_SIZE - 1) / BUFFER_SIZE) * BUFFER_SIZE;  // ceil int division and round up to next integral.
    requiredSize = (requiredSize <= 0)? BUFFER_SIZE : requiredSize;

    // std::cout << "text :" << text << std::endl;
    // std::cout << "requiredSize : " << requiredSize << std::endl;
    // std::cout << "size : " << size << std::endl;
    // std::cout << "requiredSize == size " << (requiredSize == size)<< std::endl;


    if(requiredSize == size)
        return;

    else if(text.size() < (requiredSize - BUFFER_SHRINK_MARGIN))
    {
        int originalCursorPos = GetCursorPos(); // users view of cursor pos stored.
        SetCursorPos(GetTextEnd() + 1);
        // moving cursor to the end so that gap moves before realloc
        // could be done by just moving gap directly but Think about if it can bring inconsistency to cursor pos and gap pos.

        char* temp = nullptr;
        temp = (char*)realloc(buffer,requiredSize);
        if(temp == nullptr)
        {
            std::cout << "Realloc failed!" << std::endl;
            return;
        }

        buffer = temp;
        size = requiredSize;

        gapStart = GetAbsTextEnd() + 1;
        gapEnd = size - 1;

        SetCursorPos(originalCursorPos); // restored users view of cursor pos.
    }
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


