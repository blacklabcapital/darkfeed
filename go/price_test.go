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
