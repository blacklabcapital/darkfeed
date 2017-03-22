package darkfeed

import (
	"./schemas/fb"
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestPrice_SetPrecision(t *testing.T) {
	p := Price{
		Price:     1385216,
		Precision: -4,
		TickSize:  7,
		Currency:  fb.CurrencyGBP,
	}
	p.SetPrecision(-6, 1)
	assert.Equal(t, 138521600, int(p.Price))
	assert.Equal(t, -6, int(p.Precision))
	assert.Equal(t, 1, int(p.TickSize))
	p.SetPrecision(-2, 5)
	assert.Equal(t, 13850, int(p.Price))
	assert.Equal(t, -2, int(p.Precision))
	assert.Equal(t, 5, int(p.TickSize))
}

func TestPriceFromFloat64(t *testing.T) {
	p := PriceFromFloat64(132.15, -2, 1, fb.CurrencyUSD)
	assert.Equal(t, 13215, int(p.Price))
	assert.Equal(t, -2, int(p.Precision))
	assert.Equal(t, 1, int(p.TickSize))
	assert.Equal(t, uint8(fb.CurrencyUSD), p.Currency)
	p2 := PriceFromFloat64(132.155, -3, 5, fb.CurrencyCAD)
	assert.Equal(t, 132155, int(p2.Price))
	assert.Equal(t, -3, int(p2.Precision))
	assert.Equal(t, 5, int(p2.TickSize))
	assert.Equal(t, uint8(fb.CurrencyCAD), p2.Currency)
}

func TestPriceFromUInt32(t *testing.T) {
	p := PriceFromUInt32(13852, -2, 1, fb.CurrencyUSD)
	assert.Equal(t, 13852, int(p.Price))
	assert.Equal(t, -2, int(p.Precision))
	assert.Equal(t, 1, int(p.TickSize))
	assert.Equal(t, uint8(fb.CurrencyUSD), p.Currency)

	p2 := PriceFromUInt32(1385216, -4, 7, fb.CurrencyGBP)
	assert.Equal(t, 1385216, int(p2.Price))
	assert.Equal(t, -4, int(p2.Precision))
	assert.Equal(t, 7, int(p2.TickSize))
	assert.Equal(t, uint8(fb.CurrencyGBP), p2.Currency)

}

func TestPrice_AsInt(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, fb.CurrencyGBP)
	assert.Equal(t, 1385223, int(p.Price))
}

func TestPrice_AsFloat32(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, fb.CurrencyGBP)
	fp := p.AsFloat32()
	assert.Equal(t, float32(138.5223), fp)
}

func TestPrice_AsFloat64(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, fb.CurrencyGBP)
	fp := p.AsFloat64()
	assert.Equal(t, float64(138.5223), fp)
}

func TestPrice_LessThan(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, fb.CurrencyGBP)
	assert.False(t, p.LessThan(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThan(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThan(p3))
	//higher price, greater precision
	p4 := PriceFromFloat64(138.52, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThan(p4))
	//lower price, greater precision
	p5 := PriceFromFloat64(138.49, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThan(p5))
	//higher price, lower precision
	p6 := PriceFromFloat64(138.6, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThan(p6))
	//lower price, lower precision
	p7 := PriceFromFloat64(138.49, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThan(p7))
}

func TestPrice_GreaterThan(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, fb.CurrencyGBP)
	assert.False(t, p.LessThan(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThan(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThan(p3))
	//higher price, greater precision
	p4 := PriceFromFloat64(138.52, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThan(p4))
	//lower price, greater precision
	p5 := PriceFromFloat64(138.49, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThan(p5))
	//higher price, lower precision
	p6 := PriceFromFloat64(138.6, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThan(p6))
	//lower price, lower precision
	p7 := PriceFromFloat64(138.49, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThan(p7))
}

func TestPrice_LessThanEq(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, fb.CurrencyGBP)
	assert.False(t, p.LessThanEq(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThanEq(p3))
	//equal price, equal precision
	p4 := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p4))

	//higher price, greater precision
	p5 := PriceFromFloat64(138.52, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p5))
	//lower price, greater precision
	p6 := PriceFromFloat64(138.49, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThanEq(p6))
	//equal price, greater precision
	p7 := PriceFromFloat64(138.50, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p7))

	//higher price, lower precision
	p8 := PriceFromFloat64(138.6, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p8))
	//lower price, lower precision
	p9 := PriceFromFloat64(138.49, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.LessThan(p9))
	//equal price, lower precision
	p10 := PriceFromFloat64(138.50, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p10))
}

func TestPrice_GreaterThanEq(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, fb.CurrencyGBP)
	assert.False(t, p.GreaterThanEq(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThanEq(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p3))
	//equal price, equal precision
	p4 := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p4))

	//higher price, greater precision
	p5 := PriceFromFloat64(138.52, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThanEq(p5))
	//lower price, greater precision
	p6 := PriceFromFloat64(138.49, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p6))
	//equal price, greater precision
	p7 := PriceFromFloat64(138.50, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p7))

	//higher price, lower precision
	p8 := PriceFromFloat64(138.6, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.GreaterThanEq(p8))
	//lower price, lower precision
	p9 := PriceFromFloat64(138.49, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p9))
	//equal price, lower precision
	p10 := PriceFromFloat64(138.50, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.GreaterThanEq(p10))
}

func TestPrice_Equals(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, fb.CurrencyGBP)
	assert.False(t, p.Equals(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p3))
	//equal price, equal precision
	p4 := PriceFromFloat64(138.50, -2, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p4))

	//higher price, greater precision
	p5 := PriceFromFloat64(138.52, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p5))
	//lower price, greater precision
	p6 := PriceFromFloat64(138.49, -4, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p6))
	//equal price, greater precision
	p7 := PriceFromFloat64(138.50, -4, 1, fb.CurrencyUSD)
	assert.True(t, p.LessThanEq(p7))

	//higher price, lower precision
	p8 := PriceFromFloat64(138.6, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p8))
	//lower price, lower precision
	p9 := PriceFromFloat64(138.49, -1, 1, fb.CurrencyUSD)
	assert.False(t, p.Equals(p9))
	//equal price, lower precision
	p10 := PriceFromFloat64(138.50, -1, 1, fb.CurrencyUSD)
	assert.True(t, p.Equals(p10))
}
