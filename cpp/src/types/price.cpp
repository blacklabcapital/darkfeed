#include "darkfeed/types/price.hpp"
#include <iostream>

namespace darkfeed
{
double pow10[16] = {0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
                    100000000, 1000000000};
float pow10f[16] = {0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
                    100000000, 1000000000};
int pow10i[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

inline std::uint32_t round_to_tick_size(std::uint32_t p, std::uint8_t tk)
{
    std::uint32_t cutoff = tk % 2 ? tk / (uint32_t) 2 + 1 : tk / (uint32_t) 2;
    std::uint32_t r = p % tk;
    return r >= cutoff ? p + tk - r : p - r;
}

Price::Price(double p, Currency cur, std::int8_t pr, std::uint8_t tk) noexcept
    : price((std::uint32_t) (p * pow10[POW10ZEROIDX - pr])), precision(pr), tick_size(tk), currency(cur)
{
    if (price % tk)
        price = round_to_tick_size(price, tk);
}

Price::Price(std::uint32_t p, Currency cur, int8_t pr, uint8_t tk) noexcept
    : precision(pr), tick_size(tk), currency(cur)
{
    price = p % tk ? round_to_tick_size(p, tk) : p;
}

Price::Price(const Price &p) : price(p.price), precision(p.precision), tick_size(p.tick_size), currency(p.currency)
{}

void Price::set_precision(std::int8_t pr, std::uint8_t tk)
{
    if (pr == precision)
        return;
    else if (pr < precision)
    {
        price *= pow10i[(precision - pr)];
    }
    else
    {
        int mf = pow10i[(pr - precision)];
        price += mf / 2; //necessary for proper rounding when losing precision
        price /= mf;
    }
    tick_size = tk;
    precision = pr;
    if ((tick_size != 1) && (price % tick_size))
        price = round_to_tick_size(price, tick_size);
}

bool Price::operator<(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price < b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled < b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price < upsampled;
    }
}

bool Price::operator<=(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price <= b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled <= b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price <= upsampled;
    }
}

bool Price::operator>=(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price >= b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled >= b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price >= upsampled;
    }
}

bool Price::operator>(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price > b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled > b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price > upsampled;
    }
}

bool Price::operator==(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price == b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled == b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price == upsampled;
    }
}

bool Price::operator!=(const Price &b) const
{
    //check that currencies are equal
    if (currency != b.currency)
        throw std::invalid_argument("cannot directly compare prices from two different currencies");
    //if precision is the same, use direct comparison
    if (precision == b.precision)
        return price != b.price;
        //upsample this price, then perform direct comparison
    else if (precision > b.precision)
    {
        std::uint32_t upsampled = price * pow10i[precision - b.precision];
        return upsampled != b.price;
    }
    else //upsample other price, then preform direct comparison
    {
        std::uint32_t upsampled = b.price * pow10i[b.precision - precision];
        return price != upsampled;
    }
}

} //darkfeed