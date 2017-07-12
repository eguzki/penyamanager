#ifndef DATATYPES_H
#define DATATYPES_H

// standard C library headers
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// STL includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <list>
#include <algorithm>
#include <time.h>
#include <functional>
#include <cstdlib>

#include <QString>
#include <QSharedPointer>

using namespace std::placeholders;  // for _1, _2, _3...

// macro to remove unused parameter warnings
#define UNUSEDPARAMETER(x)    ((void)x)

typedef char                Char8;

typedef wchar_t             Char16;

typedef char                Int8;
typedef unsigned char       Uint8;

typedef short               Int16;
typedef unsigned short      Uint16;

typedef int                 Int32;
typedef unsigned int        Uint32;

typedef long long           Int64;
typedef unsigned long long  Uint64;

typedef Uint8               Byte;
typedef void                Void;
typedef bool                Bool;
typedef float               Float;

typedef std::vector<Uint8>  ByteVector;
typedef std::vector<Uint32> Uint32Vector;
typedef std::vector<Uint64> Uint64Vector;

//
typedef std::map<Int32, Int32> RowIdMap;
typedef std::map<Int32, QString> RowIdStrMap;

//
typedef struct {
    Float f;
    bool b;
}FloatBoolPair;

//
class FloatBoolPairResult
{
    public:
        //
        FloatBoolPairResult()
            :
            m_error(0),
            m_pair({0.0, false})
        {}
        //
        virtual ~FloatBoolPairResult(){}

    public:
        //
        Int32              m_error;
        //
        FloatBoolPair      m_pair;
};

typedef QSharedPointer<FloatBoolPairResult> FloatBoolPairResultPtr;

//
typedef struct {
    Int32 error;
    bool result;
}BoolResult;

//
typedef struct {
    Int32 error;
    Float result;
}FloatResult;

#endif // DATATYPES_H
