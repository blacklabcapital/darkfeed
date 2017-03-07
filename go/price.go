package darkfeed

var pow10 = []float64{0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}
var pow10f = []float32{0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}
var pow10u32 = []uint32{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}
const POW10ZEROIDX = 6 //offset of 10^0 for float pow10 arrays

type Price struct {
	Price     uint32
	Precision int8
	TickSize  uint8
	Currency  uint8
}

func roundToTickSize(p uint32, tk uint8) uint32 {
	var cutoff uint32
	var r uint32 = p % uint32(tk)
	if tk%2 != 0 {
		cutoff = uint32(tk)/2 + 1
	} else {
		cutoff = uint32(tk)
	}
	if r >= cutoff {
		return p + uint32(tk) - r
	}
	return p - r
}

// Loads a price from a double precision float.
// price: The price in whole units of currency with fractional units. Eg; in USD 132.28 represents 138 dollars and 28 cents.
// precision: The quoted precision as a power of 10. Eg; with USD -2 represents cents, 0 represents dollars, etc.
// ticksize: The minimum quoted tick size as a multiple of precision units. Eg; if precision is -2 and ticksize is 5, the price is always a multiple of 5 cents
// currency: The currency code
func PriceFromFloat64(price float64, precision int8, ticksize uint8, currency uint8) Price {
	pr := uint32(price * pow10[POW10ZEROIDX-precision])
	if pr%uint32(ticksize) != 0 {
		pr = roundToTickSize(pr, ticksize)
	}
	var p = Price{
		Price: pr,
		Precision: precision,
		TickSize: ticksize,
		Currency: currency,
	}
	return p
}

// Loads a price from an unsigned integer (in multiples of the quoted fractional unit
// price: The price in fractional units of currency. Eg; if precision is -2, price represents cents
// precision: The quoted precision as a power of 10. Eg; with USD -2 represents cents, 0 represents dollars, etc.
// ticksize: The minimum quoted tick size as a multiple of precision units. Eg; if precision is -2 and ticksize is 5, the price is always a multiple of 5 cents
// currency: The currency code
func PriceFromUInt32(price uint32, precision int8, ticksize uint8, currency uint8) Price {
	var p = Price {
		Price: price,
		Precision: precision,
		TickSize: ticksize,
		Currency: currency,
	}
	if price % uint32(ticksize) != 0 {
		p.Price = roundToTickSize(price,ticksize)
	}
	return p
}

// Resamples price using the given precision
// precision The desired precision
// ticksize The new desired minimum tick size
func (p Price) SetPrecision(precision int8, ticksize uint8) {
	if precision == p.Precision {
		return
	} else if precision < p.Precision {
		p.Price *= pow10u32[p.Precision - precision]
	} else {
		mf := pow10u32[precision - p.Precision]
		p.Price += mf / 2 //necessary for proper rounding when reducing precision
		p.Price /= mf
	}
	p.TickSize = ticksize
	p.Precision = precision
	if (ticksize != 1) && (p.Price % uint32(p.TickSize) != 0) {
		p.Price = roundToTickSize(p.Price,p.TickSize)
	}
}
