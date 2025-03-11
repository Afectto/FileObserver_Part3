#ifndef STRATEGYOUTPUTHANDLER_H
#define STRATEGYOUTPUTHANDLER_H
#include <QString>

class StrategyOutputHandler {
public:
    static void printResults(const std::vector<QPair<QString, QString>>& dataList);
};

#endif // STRATEGYOUTPUTHANDLER_H
