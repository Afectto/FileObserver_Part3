#include "strategyoutputhandler.h"
#include <QDebug>

void StrategyOutputHandler::printResults(const std::vector<QPair<QString, QString>>& dataList)
{
    for (const auto &entry : dataList) {
        qDebug() << entry.first << ":" << entry.second;
    }
}
