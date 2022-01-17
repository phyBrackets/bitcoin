// Copyright (c) 2016-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <bench/bench.h>
#include <common/bloom.h>

static void RollingBloom(benchmark::Bench& bench)
{
    CRollingBloomFilter filter(120000, 0.000001);
    std::vector<unsigned char> data(32);
    uint32_t count = 0;
    bench.run([&] {
        count++;
        for(int i = 0; i <= 3; i++){
            data[i] = (count >> 8*i) & 0xFF;
        }
        filter.insert(data);
        
        for(int i = 3; i >= 0; i--){
            data[i] = (count >> 8*(3-i)) & 0xFF;
        }
        filter.contains(data);
    });
}

static void RollingBloomReset(benchmark::Bench& bench)
{
    CRollingBloomFilter filter(120000, 0.000001);
    bench.run([&] {
        filter.reset();
    });
}

BENCHMARK(RollingBloom);
BENCHMARK(RollingBloomReset);
