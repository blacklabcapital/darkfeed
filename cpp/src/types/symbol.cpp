#include "darkfeed/types/symbol.hpp"
#include <re2/re2.h>
#include <iostream>
#include <xxhash.h>

namespace darkfeed
{
Symbol::Symbol()
{
    std::memset(root, '\0', DARKFEED_ROOT_SYMBOL_SIZE);
    series = 0;
    listing_exg = Exchange(MIC::NONE);
    issue_type = IssueType::normal;
}

Symbol::Symbol(const char *r, const Exchange &le, const char s, const IssueType t)
{
    std::strncpy(root, r, DARKFEED_ROOT_SYMBOL_SIZE);
    listing_exg = le;
    series = s;
    issue_type = t;
}

std::string Symbol::issuetype_str() const
{
    return schemas::fb::EnumNameIssueType(issue_type);
}

static const char *issuetype_codes[]{"", "PR", "WS", "RT", "U", "LV", "NV", "MN", "WI", "WD"};

inline const char *get_symboltype_code(IssueType s)
{ return issuetype_codes[static_cast<unsigned int>(s)]; }

/// @brief The XXH32 hash corresponding to the various symbol type suffixes
enum struct SymbolTypeXXH32 : std::uint32_t {
    preferred = 333294448,
    warrant = 309429529,
    right = 3220934945,
    unit = 3125720569,
    limited_voting = 1906204892,
    non_voting = 2806107673,
    mini = 1397761802,
    when_issued = 1328018266,
    when_distributed = 2638047514,
};

IssueType str_to_issue_type(const char *str)
{
    auto hash = static_cast<SymbolTypeXXH32>(XXH32(str, 2, 0));
    switch (hash)
    {
    case SymbolTypeXXH32::preferred:return IssueType::preferred;
    case SymbolTypeXXH32::warrant:return IssueType::warrant;
    case SymbolTypeXXH32::right:return IssueType::right;
    case SymbolTypeXXH32::unit:return IssueType::unit;
    case SymbolTypeXXH32::limited_voting:return IssueType::non_voting;
    case SymbolTypeXXH32::non_voting:return IssueType::non_voting;
    case SymbolTypeXXH32::mini:return IssueType::mini;
    case SymbolTypeXXH32::when_distributed:return IssueType::when_issued;
    case SymbolTypeXXH32::when_issued:return IssueType::when_issued;
    default:return IssueType::other;
    }
}

std::string Symbol::format() const
{
    char out_sym[DARKFEED_ROOT_SYMBOL_SIZE * 2];
    if (issue_type == IssueType::normal)
    {
        if (!series)
            return std::string(root);
        else
            std::sprintf(out_sym, "%s.%c", root, series);
    }
    else if (!series)
        std::sprintf(out_sym, "%s.%s", root, get_symboltype_code(issue_type));
    else
        std::sprintf(out_sym, "%s.%s.%c", root, get_symboltype_code(issue_type), series);
    return std::string(out_sym);
}

static re2::RE2 symbol_regex(R"((\w+)\.?(\w{2})?\.?(\w)?)");

Symbol::Symbol(const Exchange &le, const char *s)
{
    std::string root_part;
    std::string type_part;
    std::string series_part;
    bool match_successful = RE2::FullMatch(s, symbol_regex, &root_part, &type_part, &series_part);
    if (match_successful)
    {
        std::strncpy(root, root_part.c_str(), root_part.size() + 1);
        if (type_part.size())
            issue_type = str_to_issue_type(type_part.c_str());
        else
            issue_type = IssueType::normal;

        if (!series_part.empty())
        {
            series = series_part.c_str()[0];
        }
        else
        {
            series = 0;
        }
        listing_exg = le;
    }
    else
    {
        root[0] = '\0';
        listing_exg = MIC::NONE;
        series = 0;
        issue_type = IssueType::normal;
    }
}

bool Symbol::operator==(const Symbol &b) const
{
    return !std::strncmp(root, b.root, DARKFEED_ROOT_SYMBOL_SIZE) && (series == b.series)
           && (issue_type == b.issue_type);
}

}//darkfeed
