#pragma once

#include <vector>
#include <memory>
#include "../notes/Note.h"

struct ChartNote
{
    float time;
    int lane;
    float duration;
};

class Chart
{
public:
    Chart();

    std::string musicPath;

    void addNote(const ChartNote &note);

    const std::vector<ChartNote> &getNotes() const;

private:
    std::vector<ChartNote> notes;
};
