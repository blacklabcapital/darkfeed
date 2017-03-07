#include "darkfeed/types/exchanges.hpp"

namespace darkfeed
{

static const char **MICNames = schemas::fb::EnumNamesMIC();
static const char **AbbrevNames = EnumNamesExgName();

Exchange::Exchange()
{ mic = MIC::NONE; }

Exchange::Exchange(MIC m)
{ mic = m; }

//TODO is there a better way to do this using hashes?
Exchange::Exchange(const std::string &exg)
{
    mic = MIC::NONE;
    const char *exg_str = exg.c_str();
    //iterate over MICs
    for (int i = 0; i <= static_cast<int>(MIC::MAX); ++i)
    {
        if (!std::strncmp(exg_str, MICNames[i], exg.size()))
        {
            mic = MIC(i);
            return;
        }
    }
    //iterate over abbreviations
    for (int i = 0; i <= static_cast<int>(MIC::MAX); ++i)
    {
        if (!std::strncmp(exg_str, AbbrevNames[i], exg.size()))
        {
            mic = MIC(i);
            return;
        }
    }
}

std::string Exchange::mic_str() const
{
    const char *str = schemas::fb::EnumNameMIC(mic);
    if (str == nullptr) //just in case
        str = "";
    return str;
}

std::string Exchange::abbrev_str() const
{
    const char *str = EnumNameExgName(mic);
    if (str == nullptr) //just in case
        str = "";
    return str;
}
}  // darkfeed
