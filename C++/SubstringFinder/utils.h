#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QHash>

#include <functional>
#include <string>

const int BUFFER_SIZE = 1 << 18;
const int SMALL_SHIFT = 16;
const int BIG_SHIFT = 32;

using BMH_SEARCHER = std::boyer_moore_horspool_searcher<QChar*, std::hash<QChar>, std::equal_to<void>>;

namespace std {
    template<> struct hash<QChar> {
        std::size_t operator()(QChar const& s) const noexcept {
            return std::hash<unsigned short>()(s.unicode());
        }
    };

    template<> struct hash<QString> {
        std::size_t operator()(const QString& s) const noexcept {
          return static_cast<size_t>(qHash(s));
        }
    };
}

//std::initializer_list<uint64_t> getTrigramms(QString &line);

std::vector<std::pair<int, int>> searchInFile(QString &, BMH_SEARCHER *searcher);

#endif // UTILS_H
