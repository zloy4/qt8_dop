#include "filesearcher.h"
#include <QFile>
#include <QTextStream>

QVector<QFileInfo> FileSearcher::search(const QString& directoryPath, const SearchCriteria& criteria) {
    QVector<QFileInfo> results;
    QDir dir(directoryPath);
    if (!dir.exists())
        return results;

    searchDirectory(dir, criteria, results);
    return results;
}

void FileSearcher::searchDirectory(const QDir& dir, const SearchCriteria& criteria, QVector<QFileInfo>& results) {
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo& entry : entries) {
        if (entry.isDir()) {
            searchDirectory(QDir(entry.absoluteFilePath()), criteria, results);
        } else if (fileMatches(entry, criteria)) {
            results.append(entry);
        }
    }
}

bool FileSearcher::fileMatches(const QFileInfo& fileInfo, const SearchCriteria& criteria) {
    if (!criteria.extension.isEmpty() && fileInfo.suffix() != criteria.extension)
        return false;

    if (criteria.minSize >= 0 && fileInfo.size() < criteria.minSize)
        return false;

    if (criteria.maxSize >= 0 && fileInfo.size() > criteria.maxSize)
        return false;

    if (criteria.dateFrom.isValid() && fileInfo.lastModified() < criteria.dateFrom)
        return false;

    if (criteria.dateTo.isValid() && fileInfo.lastModified() > criteria.dateTo)
        return false;

    if (criteria.regex.isValid() && !criteria.regex.pattern().isEmpty()) {
        if (!criteria.regex.match(fileInfo.fileName()).hasMatch())
            return false;
    }

    if (!criteria.content.isEmpty()) {
        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            if (!content.contains(criteria.content, Qt::CaseInsensitive))
                return false;
        } else {
            return false;
        }
    }

    return true;
}



