#include <algorithm>
#include <iterator>
#include <optional>
#include <string>

#include "EngineOptions.hpp"

// i stole this template its mine now
template <class C, typename T> bool contains(C&& c, T e) {
    return std::find(std::begin(c), std::end(c), e) != std::end(c);
};

namespace neoskye {

EngineOptions::EngineOptions() {}

EngineOptions EngineOptions::GenerateOptionsFromArgv(const int argc, const char** argv) {
    EngineOptions opts;
    for (int i = 0; i < argc; i++) {
        const auto item = argv[i];
        bool isFlag = contains(flagOpts, item);
        bool isSwitch = contains(switchOpts, item);
        if (isFlag && isSwitch)
            throw "Duplicate flag and switch!";
        if (isSwitch) {
            std::string flag(item);
            opts.switches[flag] = true;
        }
        if (isFlag) {
            // can we look ahead one element?
            i++;
            if (i > argc)
                throw "Out of range for flag";
            std::string _switch(item);
            std::string value(argv[i]);
            opts.flags[_switch] = value;
        }
        // otherwise silently continue
    }
    return opts;
}

inline std::optional<usize> EngineOptions::GetUnsignedFlag(const std::string key) {
    std::optional<usize> retVal;
    if (this->flags.count(key) == 0) {
        return retVal;
    }
    usize thingy = std::stoul(this->flags[key]);
    retVal = std::make_optional(thingy);
    return retVal;
}

inline std::optional<isize> EngineOptions::GetSignedFlag(const std::string key) {
    std::optional<usize> retVal;
    if (this->flags.count(key) == 0) {
        return retVal;
    }
    isize thingy = std::stoi(this->flags[key]);
    retVal = std::make_optional(thingy);
    return retVal;
}

inline std::optional<std::string> EngineOptions::GetStringFlag(const std::string key) {
    std::optional<std::string> retVal;
    if (this->flags.count(key) == 0)
        return retVal;
    std::string thingy = this->flags[key];
    retVal = std::make_optional(thingy);
    return retVal;
}

} // namespace neoskye
