# Darkfeed
![circleci](https://circleci.com/gh/blacklabcapital/darkfeed/tree/master.svg?style=shield&circle-token=860686d1cde81bd808bf2eb611ccdd96f5cf9412)

##Description

Darkfeed aims to provide simple, cross-platform, cross-language, open-source implementations of commonly used data structures and tools used in electronic trading.

You can use darkfeed to power your electronic trading systems, consolidated market feeds, order management systems, and more. Implementations in C++ and Go are under active development. Future implementations for Java and Rust are planned.

##Disclaimer

Darkfeed is in pre-alpha and under active development as we migrate some of our proprietary in-house code to use darkfeed's open implementations. While we do make an effort to provide thorough testing, you may encounter bugs. Please make sure you do your own sanity checking before deploying to production. If you do encounter an issue, report it or submit a pull request!

##Design Philosophy

Darkfeed strives for simple, practical implementations that cover typical use cases instead of unwieldly complex implementations that aim to be a "one size fits all". But if it doesn't, it's usually easy enough to extend existing data structures yourself (and provide your own serialization/deserialization functions).

While we aim to maximize performance, a great deal of effort has gone into convenience and safety. We could certainly squeeze out a few microseconds of latency by removing error checking code, but in most cases you'll want the sanity checking there. If your strategy depends on ultra low latency, you should be using native HDL on FGPAs and not a CPU-based library anyways.

##Contributing

###Branches

`master` holds the latest current stable version of darkfeed. Once it reaches a 1.0 release, Master will hold the latest stable commit. Commits within a major version are guaranteed to have no breaking API changes. Only feature additions and bug fixes.

`devel` holds the latest commits and is where active development takes place. If you submit a pull request, this is what it should be against (unless fixing a bug only in an older version).

`<major.minor>` are version branches. Tested changes from devel are staged for a release by merging into the appropriate version branch. Once the version is sufficiently vetted, 

##Features

### Variable Precision Pricing

Instruments are quoted in a variety of ways on different exchanges around the world. It might be tempting to operate on prices using floating point operations; however, this can lead to nasty problems with numerical instability and underflow/overflow.

DarkFeed features a `Price` type that internally stores an integer representation of the price along with valuable information like minimum quoted tick size, currency, and lot precision. This enables working with instruments that are quoted in variable lot sizes and also enables easy support for equities participating in the FINRA tick pilot program.

Since the currency is stored, this enables easy currency conversions if, for instance, you wanted to maintain worldwide prices of precious metals across global exchanges.

###Multi-Instrument Support
While currently only equities and options are supported, support for futures, futures options, commodities, forex, and other exotic derivatives is planned. The design of DarkFeed is extensible so you can always create your own custom instrument by inheriting from an existing one.

###Low Overhead
Dynamic memory allocation is minimized in the hot code path (currently only in serialization) and should soon be eliminated altogether in the C++ implementation.

Lockfree data structures using hardware support in modern CPUs ensure reliable performance even in high fanout environments (many threads reading from a single data structure).

In addition, the C++ implementation takes advantage of SSE instructions available on modern CPUs when available.

###Simple Serialization
Darkfeed allows you to serialize your market data using any of the built in serializers or you can write your own. Currently Google Flatbuffers and Simple Binary Encoding are both supported. The former offers broader language support while the latter offers superior performance.

###FIX Conformance
Exchanges have plenty of unique ways of sending common fields like quote and trade conditions. We default to the definitions in the latest FIX standard (currently 5.0SP2). This enables consolidation of dedicated feeds into a sensible common representation.

We also use ISO 10383 MIC codes to represent trading venues rather than often incompatible string representations.

###Timestamp Operations
We use Google's CCTZ to provide civil time operations but maintain an internal absolute time representation using the UNIX epoch and microseconds. This enables easy and performant comparison between timestamps and calculation of elapsed times, etc.
