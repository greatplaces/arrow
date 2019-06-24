// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uint256.h"

#include <atomic>
#include <mutex>
#include <string>

struct AtomicCounter {
    std::atomic<uint64_t> value;

    AtomicCounter() : value {0} { }

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get() const {
        return value.load();
    }
};

class AtomicTimer {
private:
    std::mutex mtx;
    uint64_t threads;
    int64_t start_time;
    int64_t total_time;

public:
    AtomicTimer() : threads(0), start_time(0), total_time(0) {}

    /**
     * Starts timing on first call, and counts the number of calls.
     */
    void start();

    /**
     * Counts number of calls, and stops timing after it has been called as
     * many times as start().
     */
    void stop();

    bool running();

    uint64_t threadCount();

    double rate(const AtomicCounter& count);
};

extern AtomicCounter transactionsValidated;
extern AtomicCounter ehSolverRuns;
extern AtomicCounter solutionTargetChecks;
extern AtomicTimer miningTimer;

void TrackMinedBlock(uint256 hash);

void MarkStartTime();
double GetLocalSolPS();
int EstimateNetHeightInner(int height, int64_t tipmediantime,
                           int heightLastCheckpoint, int64_t timeLastCheckpoint,
                           int64_t genesisTime, int64_t targetSpacing);

void TriggerRefresh();

void ConnectMetricsScreen();
void ThreadShowMetricsScreen();

/**
 * Heart image: https://commons.wikimedia.org/wiki/File:Heart_coraz%C3%B3n.svg
 * License: CC BY-SA 3.0
 *
 * Rendering options:
 * Zcash: img2txt -W 40 -H 20 -f utf8 -d none -g 0.7 Z-yellow.orange-logo.png
 * Heart: img2txt -W 40 -H 20 -f utf8 -d none 2000px-Heart_corazón.svg.png
 */
 const std::string METRICS_ART =
 "                   \e[0;1;30;90;46m:\e[0;1;36;96;46mX\e[0m \n"
 "                  \e[0;1;30;90;46mtt\e[0;1;36;96;46mX@\e[0m \n"
 "                 \e[0;1;30;90;46mXSS\e[0;1;36;96;46m@@@\e[0m \n"
 "                \e[0;1;30;90;46m8888\e[0;1;36;96;46m@@@@\e[0m \n"
 "               \e[0;1;30;90;46m88888\e[0;1;36;96;46m@@@@8\e[0m \n"
 "              \e[0;37;46m8@@@@@@@@@@\e[0;1;36;96;47m8\e[0m \n"
 "             \e[0;36;47m8888888888888\e[0;1;36;96;47m8\e[0m \n"
 "            \e[0;36;47m@88888888888888\e[0;1;36;96;47m@\e[0m \n"
 "           \e[0;1;36;96;47mS\e[0;36;47mXXXX88\e[0;37;46m8\e[0;1;30;90;46m8\e[0;1;36;96;46m8\e[0;36;47m888XXXX\e[0;1;36;96;47mS\e[0m \n"
 "          \e[0;1;37;97;47m8@X\e[0;36;47mX8\e[0;37;46m8\e[0;1;30;90;46m8888\e[0;1;36;96;46m8888\e[0;36;47m8\e[0;1;36;96;47m8X\e[0;1;37;97;47mX@8\e[0m \n"
 "         \e[0;1;37;97;47m8%\e[0;36;47m8\e[0;37;46m88888888\e[0;36;47m88888888\e[0;1;36;96;47m8\e[0;1;37;97;47m@8\e[0m \n"
 "        \e[0;36;47mX8888888888888888888888\e[0;1;36;96;47m@\e[0m \n"
 "       \e[0;1;36;96;47mS\e[0;36;47m888888888888888888888888\e[0;1;36;96;47mX\e[0m \n"
 "      \e[0;1;37;97;47mS\e[0;36;47m888888888888\e[0;1;30;90;47mX\e[0;36;47m8888888888888\e[0;1;37;97;47mS\e[0m \n"
 "     \e[0;1;37;97;47mX\e[0;36;47m@@@@@@@@@X\e[0;37;5;40;100m8\e[0;35;5;40;100m:\e[0;1;30;90;41m@;;X\e[0;35;5;40;100m:\e[0;37;5;40;100m8\e[0;36;47mX@@@@@@@@@\e[0;1;37;97;47mX\e[0m \n"
 "    \e[0;1;37;97;47m8\e[0;1;36;96;47mSSSSSSS\e[0;1;37;97;47mS@\e[0m   \e[0;35;41m8\e[0;1;31;91;41m88888\e[0m   \e[0;1;37;97;47m8S\e[0;1;36;96;47mSSSSSSS\e[0;1;37;97;47m@\e[0m \n"
 "    \e[0;1;37;97;47m@@@@@8\e[0m         \e[0;31;5;41;101m88\e[0m         \e[0;1;37;97;47m8@@@@@\e[0m \n"
 "   \e[0;37;5;47;107m@@@\e[0m                            \e[0;37;5;47;107m@@@\e[0m \n"
 "  \e[0;37;5;47;107m%\e[0m                                  \e[0;37;5;47;107m%\e[0m \n";
