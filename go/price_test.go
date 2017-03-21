package darkfeed

import (
	"./schemas"
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestPrice_SetPrecision(t *testing.T) {
	p := Price{
		Price:     1385216,
		Precision: -4,
		TickSize:  7,
		Currency:  schemas.CurrencyGBP,
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
	p := PriceFromFloat64(132.15, -2, 1, schemas.CurrencyUSD)
	assert.Equal(t, 13215, int(p.Price))
	assert.Equal(t, -2, int(p.Precision))
	assert.Equal(t, 1, int(p.TickSize))
	assert.Equal(t, uint8(schemas.CurrencyUSD), p.Currency)
	p2 := PriceFromFloat64(132.155, -3, 5, schemas.CurrencyCAD)
	assert.Equal(t, 132155, int(p2.Price))
	assert.Equal(t, -3, int(p2.Precision))
	assert.Equal(t, 5, int(p2.TickSize))
	assert.Equal(t, uint8(schemas.CurrencyCAD), p2.Currency)

}

func TestPriceFromUInt32(t *testing.T) {
	p := PriceFromUInt32(13852, -2, 1, schemas.CurrencyUSD)
	assert.Equal(t, 13852, int(p.Price))
	assert.Equal(t, -2, int(p.Precision))
	assert.Equal(t, 1, int(p.TickSize))
	assert.Equal(t, uint8(schemas.CurrencyUSD), p.Currency)

	p2 := PriceFromUInt32(1385216, -4, 7, schemas.CurrencyGBP)
	assert.Equal(t, 1385216, int(p2.Price))
	assert.Equal(t, -4, int(p2.Precision))
	assert.Equal(t, 7, int(p2.TickSize))
	assert.Equal(t, uint8(schemas.CurrencyGBP), p2.Currency)

}

func TestPrice_AsInt(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, schemas.CurrencyGBP)
	assert.Equal(t, 1385223, int(p.Price))
}

func TestPrice_AsFloat32(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, schemas.CurrencyGBP)
	fp := p.AsFloat32()
	assert.Equal(t, float32(138.5223), fp)
}

func TestPrice_AsFloat64(t *testing.T) {
	p := PriceFromUInt32(1385221, -4, 7, schemas.CurrencyGBP)
	fp := p.AsFloat64()
	assert.Equal(t, float64(138.5223), fp)
}

func TestPrice_LessThan(t *testing.T) {
	p := PriceFromFloat64(138.50, -2, 1, schemas.CurrencyUSD)
	gbp := PriceFromFloat64(138.50, -2, 1, schemas.CurrencyGBP)
	assert.False(t, p.LessThan(gbp))

	//higher price, equal precision
	p2 := PriceFromFloat64(138.52, -2, 1, schemas.CurrencyUSD)
	assert.True(t, p.LessThan(p2))
	//lower price, equal precision
	p3 := PriceFromFloat64(138.49, -2, 1, schemas.CurrencyUSD)
	assert.False(t, p.LessThan(p3))
	//higher price, greater precision
	p4 := PriceFromFloat64(138.52, -4, 1, schemas.CurrencyUSD)
	assert.True(t, p.LessThan(p4))
	//lower price, greater precision
	p5 := PriceFromFloat64(138.49, -4, 1, schemas.CurrencyUSD)
	assert.False(t, p.LessThan(p5))
	//higher price, lower precision
	p6 := PriceFromFloat64(138.6, -1, 1, schemas.CurrencyUSD)
	assert.True(t, p.LessThan(p6))
	//lower price, lower precision
	p7 := PriceFromFloat64(138.49, -1, 1, schemas.CurrencyUSD)
	assert.False(t, p.LessThan(p7))
}
