package darkfeed

import (
	"fmt"

	"./schemas/fb"
)

type Symbol struct {
	Root       string //Root symbol
	ListingExg int    //Exchange code
	Series     byte   //Series (A-Z) or \0
	IssueType  int    //Symbol Issue Type
}

//var symbol_regex, _ = regexp.Compile(`((\w+)\.?(\w{2})?\.?(\w)?)`)

// Parses a symbol from a CTA/SIP style symbology. Eg; BRKB.PR.A
// le: The listing exchange code
/*
func SymbolFromSIPString(le int, sym string) Symbol {
	var s Symbol
	return s
}
*/
var issue_type_codes []string = []string{"", "PR", "WS", "RT", "U", "LV", "NV", "MN", "WI", "WD"}

func get_issue_type_code(s int) string {
	return issue_type_codes[s]
}

//Formats symbol in CTA/CQS/SIP format (eg; BRKB.PR.A)
func (s Symbol) Format() string {
	if s.IssueType == fb.IssueTypenormal {
		if s.Series == '\x00' {
			return s.Root
		} else {
			return fmt.Sprintf("%s.%c", s.Root, s.Series)
		}
	} else if s.Series == '\x00' {
		return fmt.Sprintf("%s.%s", s.Root, get_issue_type_code(s.IssueType))
	}
	return fmt.Sprintf("%s.%s.%c", s.Root, get_issue_type_code(s.IssueType), s.Series)
}

//Checks if two symbols are equivalent
func (s Symbol) Equals(x *Symbol) bool {
	return (s.Root == x.Root) && (s.Series == x.Series) && (s.IssueType == x.IssueType)
}
