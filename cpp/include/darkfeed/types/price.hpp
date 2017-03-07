#pragma once
#include <cstdint>
#include "darkfeed/generated/flatbuffers/currency_generated.h"
#include "darkfeed/generated/flatbuffers/price_generated.h"

namespace darkfeed
{
#define POW10ZEROIDX 6 //location of 10^0 in pow10 lookup array
extern double pow10[16]; //double precision pow10 lookup array
extern float pow10f[16]; //single precision pow10 lookup array

typedef schemas::fb::Currency Currency;


/// @brief price including original precision and tick size
/// @warning precision must be in the range [-6,6]
/// @ingroup types
struct Price {
    std::uint32_t price = 0; ///< zero out by default
    std::int8_t precision = -2; ///< power of 10 precision of price relative to base currency. -2 = cents if base is USD
    std::uint8_t tick_size = 1; ///< minimum quoted tick size in increments of 'precision' units
    Currency currency = Currency::USD; ///< currency for this price. USD by default.
    /*
     * Constructors
     */
    /// @brief Constructor using decimal price (double precision arithmetic)
    /// @warning If the resulting price is not a multiple of the tick size, it will be rounded accordingly
    /// @param p Price in decimal currency
    /// @param cur Currency used for this price
    /// @param pr Precision as a power of 10 (eg; -2 refers to cent precision)
    /// @param tk Minimum quoted tick size as a multiple of precision (eg; 5 means 5 cent tick if pr is -2).
    explicit Price(double p, Currency cur = Currency::USD, std::int8_t pr = -2, std::uint8_t tk = 1) noexcept;
    /// @brief Constructor using integral price (eg; in cents)
    /// @warning If the resulting price is not a multiple of the tick size, it will be rounded accordingly
    /// @param p The price
    /// @param cur Currency used for this price
    /// @param pr The precision/units of the price as a power of 10 (eg; -2 means cents)
    /// @param tk Minimum quoted tick size as a multiple of precision (eg; 5 means 5 cents if pr=-2)
    explicit Price(std::uint32_t p = 0, Currency cur = Currency::USD, std::int8_t pr = -2, std::uint8_t tk = 1) noexcept;
    /// @brief Copy constructor
    /// @param p The price to copy from
    Price(const Price &p);
    /*
     * Modifiers
     */
    /// @brief resamples price using the given precision
    /// @param pr The desired precision
    /// @param tk The new desired minimum tick size (defaults to 1)
    void set_precision(std::int8_t pr, std::uint8_t tk = 1);

    /*
     * Conversions
     */
    ///@brief Conversion to integral type (returns price member)
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type as() const
    {
        return static_cast<T>(price);
    };

    /// @brief Returns price using double-precision using the quoted precision
    template<typename T>
    typename std::enable_if<std::is_same<T, double>::value, T>::type as() const
    {
        assert(precision < 6 && precision >= -6);
        return static_cast<T>(price * pow10[POW10ZEROIDX + precision]);
    };

    /// @brief Returns price using single-precision using the quoted precision
    template<typename T>
    typename std::enable_if<std::is_same<T, float>::value, T>::type as() const
    {
        assert(precision < 6 && precision >= -6);
        return static_cast<T>(price * pow10f[POW10ZEROIDX + precision]);
    };
    /*
     * Comparison Operators
     */
    /// @brief Checks if the current price is less than a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices
    /// @param b The reference price
    /// @return True if the current price is less than the reference price
    bool operator<(const Price &b) const;
    /// @brief Checks if the current price is greater than a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices.
    /// @param b The reference price
    /// @return True if the current price is greater than the reference price
    bool operator>(const Price &b) const;
    /// @brief Checks if the current price is less than or equal to a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices.
    /// @param b The reference price
    /// @return True if the current price is less than or equal to the reference price
    bool operator<=(const Price &b) const;
    /// @brief Checks if the current price is greater than or equal to a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices.
    /// @param b The reference price
    /// @return True if the current price is greater than or equal to the reference price
    bool operator>=(const Price &b) const;
    /// @brief Checks if the current price is equal to a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices.
    /// @param b The reference price
    /// @return True if the current price is equal to the reference price
    bool operator==(const Price &b) const;
    /// @brief Checks if the current price is not equal to a reference price
    /// @warning Both prices must use the same currency. If not, an invalid argument exception will be thrown. You should perform a currency conversion before comparing prices.
    /// @param b The reference price
    /// @return True if the current price is not equal to the reference price
    bool operator!=(const Price &b) const;
};
} //darkfeed