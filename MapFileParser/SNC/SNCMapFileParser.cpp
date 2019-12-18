#include "SNCMapFileParser.h"
#include <sstream>
#include <algorithm>

namespace mapfileparser
{
/*
SNC map files place fields at fixed column positions, e.g.

Address  Size     Align Out     In      File    Symbol
=================================================================
UNDEFINED
                                                module_start
                                                module_stop
                                                module_exit
81000000 003bd4d8     4 .text
81000000 00000154     4         .text
81000000 00000154     4                 E:\UnityInternal\Test Projects\il2cpp\Test-Stacktrace\Temp\StagingArea\il2cppOutput\Assembly-CSharpAttributes.o
81000000 00000000     0                         $t
81000061 000000f4     0                         __sti___29_Assembly_CSharpAttributes_cpp_19687d34
*/

// Column positions and widths for each field.
    static const size_t kAddress = 0;
    static const size_t kAddressWidth = 8;
    static const size_t kSize = 9;
    static const size_t kSizeWidth = 8;
// No widths for the following; if the field is not empty then read to eol.
    static const size_t kOut = 24;
    static const size_t kIn = 32;
    static const size_t kFile = 40;
    static const size_t kSymbol = 48;

    static std::string GetColumnString(const std::string& line, size_t column, size_t width = 0)
    {
        if (column >= line.length())
        {
            return "";
        }

        if (line[column] == ' ')
        {
            return "";
        }

        if (width)
        {
            return line.substr(column, width);
        }

        return line.substr(column);
    }

    static SegmentType SegmentTypeFromName(const std::string& name)
    {
        // Only interested in the .text section so treat everything else as data.
        if (name == ".text")
        {
            return kSegmentTypeCode;
        }

        return kSegmentTypeData;
    }

    static bool SectionFilter(const Section& section)
    {
        // Only interested in code sections.
        return section.segmentType == kSegmentTypeCode;
    }

    static bool StringToLong(const std::string& text, int64_t& value)
    {
        char* endPtr = NULL;
        value = strtoul(text.c_str(), &endPtr, 16);
        return endPtr != text.c_str();
    }

    bool symbolSort(Symbol i, Symbol j)
    {
        return (i.start < j.start);
    }

    MapFile SNCMapFileParser::Parse(std::istream& is)
    {
        bool foundFirstSection = false;
        bool ProcessAsXMap = false; // if the first section start address is 0, then we assume it's a X map

        MapFile mapFile;
        std::string line;
        std::string currFile;
        Section currSection;

        // Skip column headings.
        std::getline(is, line);
        std::getline(is, line);

        while (!is.eof())
        {
            std::getline(is, line);

            std::string address = GetColumnString(line, kAddress, kAddressWidth);
            int64_t addrVal = 0;
            if (StringToLong(address.c_str(), addrVal))
            {
                std::string size = GetColumnString(line, kSize, kSizeWidth);
                unsigned long sizeVal = strtol(size.c_str(), NULL, 16);

                std::string outSection = GetColumnString(line, kOut);
                if (outSection.length())
                {
                    // if the first section start address is 0, then we assume it's a X map
                    if (foundFirstSection == false)
                    {
                        if (addrVal == 0)
                        {
                            ProcessAsXMap = true;
                        }
                        foundFirstSection = true;
                    }
                    currSection.segmentType = SegmentTypeFromName(outSection);
                    currSection.start = addrVal;
                    currSection.length = sizeVal;
                    currSection.name = outSection;
                    currSection.segmentName = outSection;
                    if (SectionFilter(currSection))
                    {
                        mapFile.sections.push_back(currSection);
                    }
                    continue;
                }

                if (SectionFilter(currSection) && sizeVal != 0)
                {
                    if (GetColumnString(line, kIn).length())
                    {
                        continue;
                    }

                    if (ProcessAsXMap == false)
                    {
                        // Subtract the section base address, il2cpp stack trace expects 0 based offsets for symbols.
                        addrVal -= currSection.start;

                        // Mask off the 2 lowest bits of the address, LSB indicates thumb code on Vita, Il2cpp stack
                        // trace assumes thumb or thumb2 where thumb2 is the second LSB.
                        addrVal = addrVal & ~3;
                    }

                    std::string file = GetColumnString(line, kFile);
                    if (file.length())
                    {
                        currFile = file;
                        continue;
                    }

                    std::string name = GetColumnString(line, kSymbol);
                    Symbol symbol;
                    symbol.start = addrVal;
                    symbol.length = sizeVal;
                    symbol.name = name;
                    symbol.objectFile = currFile;
                    symbol.segmentType = currSection.segmentType;
                    mapFile.symbols.push_back(symbol);
                }
            }
        }
        std::sort(mapFile.symbols.begin(), mapFile.symbols.end(), symbolSort);
        return mapFile;
    }
}
