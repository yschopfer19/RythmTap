#include "Chart.h"

Chart::Chart()
{
}

void Chart::addNote(const ChartNote &note)
{
    notes.push_back(note);
}

const std::vector<ChartNote> &Chart::getNotes() const
{
    return notes;
}
