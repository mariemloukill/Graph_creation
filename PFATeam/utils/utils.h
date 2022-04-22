//
// Created by ramizouari on 21/04/22.
//

#ifndef PFAPROJECT_UTILS_H
#define PFAPROJECT_UTILS_H
#include <string>
#include <regex>
#include <chrono>
namespace PFA
{

    auto split_regex(const std::string &S, const std::string &regex) -> std::vector<std::string>
    {
        std::regex rgx(regex);
        std::sregex_token_iterator iter(S.begin(),
                                        S.end(),
                                        rgx,
                                        -1);
        std::sregex_token_iterator end;
        std::vector<std::string> tokens;
        for (; iter != end; ++iter)
            tokens.push_back(*iter);
        return tokens;
    }

    template<typename Duration=std::chrono::milliseconds>
    Duration parse_duration(const std::string &str)
    {
        auto it1=std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); });
        std::string time_str(str.begin(),it1);
        auto it2=std::find_if(it1, str.end(), [](char c) { return std::isalpha(c); });
        std::string unit(it2,std::find_if(it2, str.end(), [](char c) { return !std::isalpha(c); }));
        if(unit=="ns")
            return std::chrono::duration_cast<Duration>(std::chrono::nanoseconds(std::stoi(time_str)));
        else if(unit=="us" || unit=="µs")
            return std::chrono::duration_cast<Duration>(std::chrono::microseconds(std::stoi(time_str)));
        else if(unit=="ms" || unit.empty())
            return std::chrono::milliseconds(std::stoi(time_str));
        else if(unit=="s")
            return std::chrono::duration_cast<Duration>(std::chrono::seconds(std::stoi(time_str)));
        else if(unit=="m")
            return std::chrono::duration_cast<Duration>(std::chrono::minutes(std::stoi(time_str)));
        else if(unit=="h")
            return std::chrono::duration_cast<Duration>(std::chrono::hours(std::stoi(time_str)));
        else
            throw std::runtime_error("Unknown time unit");
    }
}
#endif //PFAPROJECT_UTILS_H
