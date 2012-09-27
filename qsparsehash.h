#ifndef QSPARSEHASH_H
#define QSPARSEHASH_H

#include <sparsehash/sparse_hash_map>
#include <sparsehash/dense_hash_map>
#include <qglobal.h>
#include <QHash>
#include <QDataStream>

/*
 * QHash-like wrapper for google::sparse_hash_map and google::dense_hash_map
 */


/* stl-compatible qHash wrappers for some basic Qt datatypes
 * It's easy to implement a new one if you need to store custom datatype.
 */
namespace std {
namespace tr1 {
template <>
class hash<QByteArray> {
public:
    size_t operator()(const QByteArray &k) const {
        return qHash(k);
    }
};

template <>
class hash<QChar> {
public:
    size_t operator()(const QChar &k) const {
        return qHash(k);
    }
};

template <>
class hash<QString> {
public:
    size_t operator()(const QString &k) const {
        return qHash(k);
    }
};

}
}

/*
 *Basic hash wrapper which maintains partial compatibility with QHash
 */
template <class Container, class Key, class T>
class QGoogleHash: public Container
{
public:
    QGoogleHash() {
        this->set_deleted_key(Key());
    }
    void insert(const Key &key, const T &value) {
        (*this)[key] = value;
    }
    T value(const Key &key) {
        typename Container::const_iterator i;
        i = this->find(key);
        if (i != this->end())
            return i->second;
        else
            return T();
    }
    bool contains(const Key &key) const {
        return (this->find(key) != this->end());
    }
    int count() const {
        return this->size();
    }
    void print() const {
        typename Container::const_iterator i = this->begin();
        while (i != this->end()) {
            printf("key: %s value: %d\n", qPrintable(i->first), i->second);
            i++;
        }
    }
    void remove(const Key &key) {
        this->remove(key);
    }
};

/* typedef-like class definition for QSparseHash as a wrapper to google::sparse_hash_map
 */
template <class Key, class T>
class QSparseHash: public QGoogleHash<google::sparse_hash_map<Key, T>, Key, T> {};

template <class Key, class T>
class QDenseHash: public QGoogleHash<google::dense_hash_map<Key, T>, Key, T> {};

/* Serialization and deserialization routines
 */
template <class Key, class T>
QDataStream & operator<< ( QDataStream & out, const QSparseHash<Key, T> & hash ) {
    out << hash.count();
    typename QSparseHash<Key, T>::const_iterator i = hash.begin();
    while (i != hash.end()) {
        out << i->first << i->second;
        i++;
    }
    return out;
}

template <class Key, class T>
QDataStream & operator>> ( QDataStream & in, QSparseHash<Key, T> & hash ) {
    int size;
    in >> size;
    for (int i=0; i<size; ++i) {
        Key key;
        T value;
        in >> key;
        in >> value;
        hash.insert(key, value);
    }
    return in;
}

template <class Key, class T>
QDataStream & operator<< ( QDataStream & out, const QDenseHash<Key, T> & hash ) {
    out << hash.count();
    typename QDenseHash<Key, T>::const_iterator i = hash.begin();
    while (i != hash.end()) {
        out << i->first << i->second;
        i++;
    }
    return out;
}

template <class Key, class T>
QDataStream & operator>> ( QDataStream & in, QDenseHash<Key, T> & hash ) {
    int size;
    in >> size;
    for (int i=0; i<size; ++i) {
        Key key;
        T value;
        in >> key;
        in >> value;
        hash.insert(key, value);
    }
    return in;
}

#endif // QSPARSEHASH_H
