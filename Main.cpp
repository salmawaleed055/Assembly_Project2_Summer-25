#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
using namespace std;

#define DBG 1
#define DRAM_SIZE (64*1024*1024)
#define CACHE_SIZE (64*1024)

// Cache configuration constants
#define L1_SIZE (16*1024)        // 16 KB
#define L2_SIZE (128*1024)       // 128 KB
#define L2_LINE_SIZE 64          // Fixed 64B for L2
#define L1_ASSOCIATIVITY 4       // 4-way set associative
#define L2_ASSOCIATIVITY 8       // 8-way set associative

// Timing constants
#define L1_HIT_TIME 1
#define L2_HIT_TIME 10
#define DRAM_ACCESS_TIME 50

enum cacheResType {MISS=0, HIT=1};

// Cache line structure
struct CacheLine {
    bool valid;
    unsigned int tag;
    unsigned int lru_counter;
    bool dirty;  // For write-back
};

// Cache structure
struct Cache {
    CacheLine** lines;
    int sets;
    int ways;
    int line_size;
    int set_bits;
    int offset_bits;
};

// Global cache instances
Cache L1_cache, L2_cache;
int L1_line_size = 32;  // Variable line size for L1

/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55; /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902; /* must not be zero, nor 0x9068ffff */

unsigned int rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w; /* 32-bit result */
}

// Helper functions for random number generation
double getRandomDouble() {
    return (double)rand_() / UINT_MAX;
}

int getRandomInt(int max) {
    return rand_() % max;
}

unsigned int memGen1()
{
    static unsigned int addr=0;
    return (addr++)%(DRAM_SIZE);
}

unsigned int memGen2()
{
    static unsigned int addr=0;
    return rand_()%(24*1024);
}

unsigned int memGen3()
{
    return rand_()%(DRAM_SIZE);
}

unsigned int memGen4()
{
    static unsigned int addr=0;
    return (addr++)%(4*1024);
}

unsigned int memGen5()
{
    static unsigned int addr=0;
    return (addr+=32)%(64*16*1024);
}

void initCache(Cache* cache, int size, int line_size, int ways) {
    cache->line_size = line_size;
    cache->ways = ways;
    cache->sets = size / (line_size * ways);

    // Calculate bit positions
    cache->offset_bits = 0;
    int temp = line_size;
    while (temp > 1) {
        cache->offset_bits++;
        temp >>= 1;
    }

    cache->set_bits = 0;
    temp = cache->sets;
    while (temp > 1) {
        cache->set_bits++;
        temp >>= 1;
    }

    // Allocate memory for cache lines
    cache->lines = new CacheLine*[cache->sets];
    for (int i = 0; i < cache->sets; i++) {
        cache->lines[i] = new CacheLine[ways];
        for (int j = 0; j < ways; j++) {
            cache->lines[i][j].valid = false;
            cache->lines[i][j].tag = 0;
            cache->lines[i][j].lru_counter = 0;
            cache->lines[i][j].dirty = false;
        }
    }
}

void cleanupCache(Cache* cache) {
    for (int i = 0; i < cache->sets; i++) {
        delete[] cache->lines[i];
    }
    delete[] cache->lines;
}

unsigned int getTag(unsigned int addr, Cache* cache) {
    return addr >> (cache->offset_bits + cache->set_bits);
}

unsigned int getSet(unsigned int addr, Cache* cache) {
    unsigned int mask = (1 << cache->set_bits) - 1;
    return (addr >> cache->offset_bits) & mask;
}

cacheResType accessCache(unsigned int addr, Cache* cache, bool is_write) {
    unsigned int set = getSet(addr, cache);
    unsigned int tag = getTag(addr, cache);

    // Check for hit
    for (int i = 0; i < cache->ways; i++) {
        if (cache->lines[set][i].valid && cache->lines[set][i].tag == tag) {
            // Hit - update LRU
            cache->lines[set][i].lru_counter = 0;
            for (int j = 0; j < cache->ways; j++) {
                if (j != i) cache->lines[set][j].lru_counter++;
            }
            if (is_write) cache->lines[set][i].dirty = true;
            return HIT;
        }
    }

    // Miss - find victim using random replacement
    int victim = getRandomInt(cache->ways);

    // Check if victim is dirty (for write-back)
    bool victim_dirty = cache->lines[set][victim].dirty;

    // Install new line
    cache->lines[set][victim].valid = true;
    cache->lines[set][victim].tag = tag;
    cache->lines[set][victim].dirty = is_write;
    cache->lines[set][victim].lru_counter = 0;

    // Update LRU counters
    for (int j = 0; j < cache->ways; j++) {
        if (j != victim) cache->lines[set][j].lru_counter++;
    }

    return MISS;
}

int simulateMemoryAccess(unsigned int addr, bool is_write) {
    int cycles = 0;

    // Try L1 cache
    if (accessCache(addr, &L1_cache, is_write) == HIT) {
        cycles += L1_HIT_TIME;
    } else {
        // L1 miss - try L2 cache
        cycles += L1_HIT_TIME;  // L1 access time

        if (accessCache(addr, &L2_cache, is_write) == HIT) {
            cycles += L2_HIT_TIME;
        } else {
            // L2 miss - access DRAM
            cycles += L2_HIT_TIME + DRAM_ACCESS_TIME;
        }
    }

    return cycles;
}

char *msg[2] = {"Miss","Hit"};

int main() {
    // Array of memory generators
    unsigned int (*memGens[5])() = {memGen1, memGen2, memGen3, memGen4, memGen5};
    string genNames[5] = {"memGen1", "memGen2", "memGen3", "memGen4", "memGen5"};

    // L1 line sizes to test
    int lineSizes[4] = {16, 32, 64, 128};

    cout << "Two-Level Cache Performance Simulator\n";
    cout << "=====================================\n\n";

    // Results storage
    double results[5][4];  // [generator][line_size]

    for (int genIdx = 0; genIdx < 5; genIdx++) {  // Fixed variable name collision
        for (int ls = 0; ls < 4; ls++) {
            L1_line_size = lineSizes[ls];

            // Initialize caches
            initCache(&L1_cache, L1_SIZE, L1_line_size, L1_ASSOCIATIVITY);
            initCache(&L2_cache, L2_SIZE, L2_LINE_SIZE, L2_ASSOCIATIVITY);

            unsigned long long total_cycles = 0;
            const int ITERATIONS = 1000000;

            cout << "Running " << genNames[genIdx] << " with L1 line size "
                 << L1_line_size << "B..." << endl;

            for (int inst = 0; inst < ITERATIONS; inst++) {
                // 35% probability of memory access instruction
                double p = getRandomDouble();

                if (p <= 0.35) {
                    // Memory access instruction
                    unsigned int addr = memGens[genIdx]();

                    // 50% of memory accesses are reads
                    double rdwr = getRandomDouble();
                    bool is_write = (rdwr >= 0.5);  // 50% write, 50% read

                    total_cycles += simulateMemoryAccess(addr, is_write);
                } else {
                    // Non-memory instruction
                    total_cycles += 1;  // Base CPI = 1
                }
            }

            double cpi = (double)total_cycles / ITERATIONS;
            results[genIdx][ls] = cpi;

            cout << "  CPI = " << fixed << setprecision(3) << cpi << endl;

            // Cleanup
            cleanupCache(&L1_cache);
            cleanupCache(&L2_cache);
        }
        cout << endl;
    }

    // Print results table
    cout << "Final Results:\n";
    cout << "==============\n";
    cout << setw(12) << "Generator";
    for (int i = 0; i < 4; i++) {
        cout << setw(12) << (to_string(lineSizes[i]) + "B");
    }
    cout << endl;
    cout << string(60, '-') << endl;

    for (int genIdx = 0; genIdx < 5; genIdx++) {
        cout << setw(12) << genNames[genIdx];
        for (int ls = 0; ls < 4; ls++) {
            cout << setw(12) << fixed << setprecision(3) << results[genIdx][ls];
        }
        cout << endl;
    }

    return 0;
}
