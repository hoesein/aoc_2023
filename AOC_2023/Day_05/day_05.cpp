#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <stack>
#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("input.txt");
    if (!input_file.is_open())
    {
        std::cerr << "Error opening file\n";
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

struct Range
{
    long long start;
    long long end;
};

struct Mapping
{
    long long dest_start;
    long long src_start;
    long long length;
};

std::vector<Range> apply_mapping(const std::vector<Range> &ranges, const std::vector<Mapping> &rules)
{
    std::vector<Range> result;
    std::vector<Range> to_process = ranges;

    for (const auto &rule : rules)
    {
        std::vector<Range> next_round;

        long long src_start = rule.src_start;
        long long src_end = rule.src_start + rule.length - 1;
        long long dest_start = rule.dest_start;
        long long offset = dest_start - src_start;

        for (Range &range : to_process)
        {
            // Case 1: No overlap
            if (range.end < src_start || range.start > src_end)
            {
                next_round.push_back(range);
                continue;
            }

            // Case 2: Complete overlap
            if (range.start >= src_start && range.end <= src_end)
            {
                result.push_back({range.start + offset, range.end + offset});
                continue;
            }

            // Case 3: Partial overlap (split into 3 parts)
            // Left non-overlapping part
            if (range.start < src_start)
            {
                next_round.push_back({range.start, src_start - 1});
            }

            // Middle overlapping part
            result.push_back({std::max(range.start, src_start) + offset,
                              std::min(range.end, src_end) + offset});

            // Right non-overlapping part
            if (range.end > src_end)
            {
                next_round.push_back({src_end + 1, range.end});
            }
        }
        to_process = std::move(next_round);
    }

    // Add any remaining unmapped ranges
    result.insert(result.end(), to_process.begin(), to_process.end());
    return result;
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data in file." << std::endl;
    }

    std::vector<long long> seeds;
    std::vector<std::vector<long long>> current_map;
    std::vector<std::vector<std::vector<long long>>> maps;

    for (long long i = 0; i < lines.size(); i++)
    {
        // searching for seeds line
        if (i == 0)
        {
            long long current_seed = 0;
            std::vector<std::string> seed_line = tools::separator(lines[i], ":");
            seeds = tools::remove<long long>(seed_line[1], ' ');
        }

        if (lines[i].size() == 0) // empty line
        {
            if (!current_map.empty())
            {
                maps.push_back(current_map);
                current_map.clear();
                continue;
            }
        }

        // push every digit line to maps vector
        if (isdigit(lines[i][0]))
        {
            current_map.push_back(tools::remove<long long>(lines[i]));
        }

        if (i == lines.size() - 1)
        {
            maps.push_back(current_map);
        }
    }

    std::vector<long long> location_num;
    for (long long seed : seeds)
    {
        for (long long i = 0; i < maps.size(); i++)
        {
            std::vector<std::vector<long long>> current_map = maps[i];
            for (long long j = 0; j < current_map.size(); j++)
            {
                std::vector<long long> current_range = current_map[j];
                if ((seed >= current_range[1]) && (seed < current_range[1] + current_range[2]))
                {
                    long long diff = current_range[0] - current_range[1];
                    seed += diff;
                    break;
                }
            }
        }
        location_num.push_back(seed);
    }

    long long result = 1000000000;
    for (long long loc : location_num)
    {
        result = std::min(result, loc);
    }
    return std::to_string((int)result);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data in file." << std::endl;
    }

    std::vector<std::vector<long long>> seeds; // {{seed, range}, {seed, range}}
    std::vector<std::vector<long long>> current_map;
    std::vector<std::vector<std::vector<long long>>> maps;

    for (long long i = 0; i < lines.size(); i++)
    {
        // searching for seeds line
        if (i == 0)
        {
            std::vector<long long> temp_seed = {};
            std::vector<std::string> seed_line = tools::separator(lines[i], ":");
            temp_seed = tools::remove<long long>(seed_line[1], ' ');

            if (temp_seed.size() % 2 != 0)
            {
                std::cerr << "Invalid seed size." << std::endl;
            }
            else
            {
                for (long long i = 0; i < temp_seed.size(); i += 2)
                {
                    seeds.push_back({temp_seed[i], temp_seed[i + 1]});
                }
            }
        }

        if (lines[i].size() == 0) // empty line
        {
            if (!current_map.empty())
            {
                maps.push_back(current_map);
                current_map.clear();
                continue;
            }
        }

        // push every digit line to maps vector
        if (isdigit(lines[i][0]))
        {
            current_map.push_back(tools::remove<long long>(lines[i]));
        }

        if (i == lines.size() - 1)
        {
            maps.push_back(current_map);
        }
    }

    std::vector<Range> current_ranges;
    for (const auto &seed : seeds)
    {
        current_ranges.push_back({seed[0], seed[0] + seed[1] - 1});
    }

    std::vector<std::vector<Mapping>> all_mappings;
    for (const auto &mappings : maps)
    {
        std::vector<Mapping> mmm;
        for (const auto &mm : mappings)
        {
            Mapping m = {mm[0], mm[1], mm[2]};
            mmm.push_back(m);
        }
        all_mappings.push_back(mmm);
    }

    for (const auto &mappings : all_mappings)
    {
        // correct for seed to soid, only for one mappings, need to consider for all mappings
        current_ranges = apply_mapping(current_ranges, mappings);
    }

    long long min_location = LLONG_MAX;
    for (const auto &range : current_ranges)
    {
        min_location = std::min(min_location, range.start);
    }

    // std::vector<RangeMapper> range_mapper;
    // for (int8_t i = 0; i < maps.size(); i++)
    // {
    //     RangeMapper curr_range_mapper(maps[i]);
    //     range_mapper.push_back(curr_range_mapper);
    // }

    // std::vector<long long> location_num;
    // for (int a = 0; a < seeds.size(); a++)
    // {
    //     long long range_start = seeds[a][0];
    //     long long range_length = seeds[a][1];

    //     std::stack<std::vector<long long>> seed_range;
    //     seed_range.push({range_start, range_start + range_length});

    /*
        COOPER GAMBLE WAY
    */
    // for(RangeMapper map: maps)
    // {
    //     seed_range = map.map(seed_range);
    // }

    // long long min_interval = 100000000000;
    // std::stack<std::vector<long long>> seed_range_copy = seed_range;
    // while (!seed_range_copy.empty())
    // {
    //     std::vector<long long> curr_interval = seed_range_copy.top();
    //     seed_range_copy.pop();
    //     min_interval = std::min(min_interval, curr_interval[0]);
    // }

    // location_num.push_back(min_interval);

    /*
        MY WAY
    */
    // for (int b = seeds[a][0]; b < seeds[a][0] + seeds[a][1]; b++)
    // {
    //     long long current_seed = b;
    //     for (long long i = 0; i < maps.size(); i++)
    //     {
    //         std::vector<std::vector<long long>> current_map = maps[i];
    //         for (long long j = 0; j < current_map.size(); j++)
    //         {
    //             std::vector<long long> current_range = current_map[j];
    //             if ((current_seed >= current_range[1]) && (current_seed < current_range[1] + current_range[2]))
    //             {
    //                 long long diff = current_range[0] - current_range[1];
    //                 current_seed += diff;
    //                 break;
    //             }
    //         }
    //     }
    //     location_num.push_back(current_seed);
    //     current_seed = 0;
    // }

    /*
        DEEP SEEK WAY
    */
    // struct Range
    // {
    //     long long start;
    //     long long end;
    // };

    //     std::vector<Range> current_ranges = {{range_start, range_start + range_length}};

    //     for(const auto& current_map: maps)
    //     {
    //         std::vector<Range> new_ranges;
    //         while(!current_ranges.empty())
    //         {
    //             Range r = current_ranges.back();
    //             current_ranges.pop_back();

    //             bool mapped = false;
    //             for(const auto& mapping: current_map)
    //             {
    //                 long long src_start = mapping[1];
    //                 long long src_end = src_start + mapping[2];
    //                 long long offset = mapping[0] - src_start;

    //                 // Check for overlap
    //                 long long overlap_start = std::max(r.start, src_start);
    //                 long long overlap_end = std::min(r.end, src_end);

    //                 if(overlap_start < overlap_end)
    //                 {
    //                     new_ranges.push_back({overlap_start + offset, overlap_end + offset});

    //                     if(r.start < overlap_start)
    //                     {
    //                         current_ranges.push_back({r.start, overlap_start});
    //                     }
    //                     if(overlap_end < r.end)
    //                     {
    //                         current_ranges.push_back({overlap_end, r.end});
    //                     }
    //                     mapped = true;
    //                     break;
    //                 }
    //             }
    //             if(!mapped)
    //             {
    //                 new_ranges.push_back(r);
    //             }
    //         }
    //         current_ranges = std::move(new_ranges);
    //     }

    //     long long min_location = std::numeric_limits<long long>::max();
    //     for(const auto& r: current_ranges)
    //     {
    //         if(r.start < min_location)
    //         {
    //             min_location = r.start;
    //         }
    //         // for(long long loc = r.start; loc < r.end; loc++)
    //         // {
    //         //     location_num.push_back(loc);
    //         // }
    //     }
    // }

    // long long result;
    // for (long long loc : location_num)
    // {
    //     result = std::min(result, loc);
    // }

    return std::to_string(min_location);
}

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    std::string p1 = part_one();
    std::string p2 = part_two();

    std::cout << "Part One: " << p1 << std::endl;
    std::cout << "Part Two: " << p2 << std::endl;

    auto stop = high_resolution_clock::now();
    auto dura = duration_cast<milliseconds>(stop - start);
    std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

    return 0;
}
