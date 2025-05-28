#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QVector>
#include <QDateTime>
#include <QRegularExpression>

class FileSearcher {
public:
    struct SearchCriteria {
        QString extension;
        QString content;
        qint64 minSize = -1;
        qint64 maxSize = -1;
        QDateTime dateFrom;
        QDateTime dateTo;
        QRegularExpression regex;
    };

    QVector<QFileInfo> search(const QString& directoryPath, const SearchCriteria& criteria);

private:
    void searchDirectory(const QDir& dir, const SearchCriteria& criteria, QVector<QFileInfo>& results);
    bool fileMatches(const QFileInfo& fileInfo, const SearchCriteria& criteria);
};

#endif // FILESEARCHER_H



