QSparseHash
===========

A small Qt wrapper for [Google sparse_hash_map](https://code.google.com/p/sparsehash/) (and dense_hash_map also).

**Installation**

The wrapper itself is a single c++ header file (qsparsehash.h). Just include it to your project.

**Compatibility**

QSparseHash is tested with Qt 4.8 and sparsehash 2.0.2. It may work with older versions, but I've not tested it.

**How to use**

QSparseHash class derives sparse_hash_map (QDenseHash derives dense_hash_map), so it's 100% API compatible with original Google implementation. But it also has some methods to be partially compatible with QHash (to be used as a drop-in QHash replacement). Also keep in mind that QSparseHash has QHash-incompatible iterators, there's a bit different syntax (see example below).

**Examples**

Creating, inserting and removing values:

    QSparseHash<QString, int> hash;
    hash.insert("foo", 1);
    hash.insert("bar", 2);
    hash["baz"] = 3;
    // accessing values
    printf("baz: %d\n", hash["baz"]);
    // removing
    hash.remove("foo");
    printf("count: %d\n", hash.count());
    
Iterating over hash:

    QSparseHash<QString, int> hash;
    hash.insert("foo", 1);
    hash.insert("bar", 2);
    QSparseHash<QString, int>::const_iterator i = hash.begin();
    while (i != hash.end()) {
        printf("%s: %d\n", qPrintable(i->first), i->second); // iterator points to std::pair<Key,Value>
        i++;
    }
    
Does hash contain a key?

    QSparseHash<QString, int> hash;
    hash.insert("foo", 1);
    hash.insert("bar", 2);
    if (hash.contains("baz"))
        printf("hash contains baz\n");
    if (hash.contains("foo"))
        printf("hash contains foo\n);
        
**More documentation**

You may also be interested in these external docs:
* [Google sparsehash](http://sparsehash.googlecode.com/svn/trunk/doc/index.html);
* [Qt's QHash](http://qt-project.org/doc/qt-4.8/qhash.html);
* QHash, sparsehash, boost:unordered_map, std::unordered_map, ruby & python maps [benchmark](http://blog.aggregateknowledge.com/2011/11/27/big-memory-part-3-5-google-sparsehash/).