package darkfeed

import (
	"./schemas/fb"
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestSymbol_Format(t *testing.T) {
	s1 := Symbol{
		Root:       "BRK",
		Series:     'A',
		IssueType:  fb.IssueTypepreferred,
		ListingExg: fb.MICXNYS,
	}
	assert.Equal(t, "BRK.PR.A", s1.Format())
	s2 := Symbol{
		Root:       "MSFT",
		Series:     '\x00',
		IssueType:  fb.IssueTypepreferred,
		ListingExg: fb.MICXNGS,
	}
	assert.Equal(t, "MSFT.PR", s2.Format())
	s3 := Symbol{
		Root:       "BRK",
		Series:     'B',
		IssueType:  fb.IssueTypenormal,
		ListingExg: fb.MICXNYS,
	}
	assert.Equal(t, "BRK.B", s3.Format())
}

func TestSymbol_Equals(t *testing.T) {
	s1 := Symbol{
		Root:       "BRK",
		Series:     'A',
		IssueType:  fb.IssueTypepreferred,
		ListingExg: fb.MICXNYS,
	}
	s2 := Symbol{
		Root:       "BRK",
		Series:     'A',
		IssueType:  fb.IssueTypepreferred,
		ListingExg: fb.MICXNYS,
	}
	assert.True(t, s1.Equals(&s2))
	s3 := Symbol{
		Root:       "BRK",
		Series:     'B',
		IssueType:  fb.IssueTypepreferred,
		ListingExg: fb.MICXNYS,
	}
	assert.False(t, s1.Equals(&s3))
	s4 := Symbol{
		Root:       "BRK",
		Series:     'A',
		IssueType:  fb.IssueTypenormal,
		ListingExg: fb.MICXNYS,
	}
	assert.False(t, s1.Equals(&s4))
}
