////////////////////////////////////////////////////////////////////////////////
// CppSQLite - A C++ wrapper around the SQLite embedded database library.
//
// Copyright (c) 2004 Rob Groves. All Rights Reserved. rob.groves@btinternet.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// V1.0		05/03/2004	-Initial Version
//
// V1.1		09/03/2004	-Added CppSQLiteException::errorCodeAsString()
//						-Renamed CppSQLiteException::errorMess() - errorMessage()
//						-2 different CppSQLiteException constructors
//						-Added CppSQLiteBinary
//						-Now call sqlite_finalize() straight after error with
//						 sqlite_step()
//
// V1.2		02/04/2004	-Utilise sqlite_busy_timeout() and sqlite_interrupt()
//						 to help with multithreaded use
//						-Revert to single CppSQLiteException constructor
//						-Removed dependency on a Microsoft specific extension
//						-Added CppSQLiteQuery::fieldType()
//						-Added code to check for null pointers
//						-Added CppSQLiteStatement for SQLite pre-compiled statements
//						-Added CppSQLiteDB::execScalar()
//
// V1.3		03/05/2004	-Added license block to source files
//						-Added getIntField(), getStringField(), getFloatField()
//						-Added overloaded functions to access fields by name.
//						-Fixed bug(s) on bind()
//						-CppSQLiteDB::ExecDML() implemented with sqlite_exec() so
//						 multiple statements can be executed at once.
//
// V1.4		30/08/2004	-Removed source for sqlite_encode/decode_binary() as
//						 they are now exported from SQLite DLL
////////////////////////////////////////////////////////////////////////////////
#ifndef _CppSQLite_H_
#define _CppSQLite_H_

#include "sqlite.h"
#include <cstdio>
#include <cstring>

#define CPPSQLITE_ERROR 1000

class CppSQLiteException
{
public:

    CppSQLiteException(const int nErrCode,
                    char* szErrMess,
                    bool bDeleteMsg=true);

    CppSQLiteException(const CppSQLiteException&  e);

    virtual ~CppSQLiteException();

    const int errorCode() { return mnErrCode; }

    const char* errorMessage() { return mpszErrMess; }

    static const char* errorCodeAsString(int nErrCode);

private:

    int mnErrCode;
    char* mpszErrMess;
};


class CppSQLiteBuffer
{
public:

    CppSQLiteBuffer();

    ~CppSQLiteBuffer();

    const char* format(const char* szFormat, ...);

    operator const char*() { return mpBuf; }

    void clear();

private:

    char* mpBuf;
};


class CppSQLiteBinary
{
public:

    CppSQLiteBinary();

    ~CppSQLiteBinary();

    void setBinary(const unsigned char* pBuf, int nLen);
    void setEncoded(const unsigned char* pBuf);

    const unsigned char* getEncoded();
    const unsigned char* getBinary();

    int getBinaryLength();

    unsigned char* allocBuffer(int nLen);

    void clear();

private:

    unsigned char* mpBuf;
    int mnBinaryLen;
    int mnBufferLen;
    int mnEncodedLen;
    bool mbEncoded;
};


class CppSQLiteQuery
{
public:

    CppSQLiteQuery();

    CppSQLiteQuery(const CppSQLiteQuery& rQuery);

    CppSQLiteQuery(sqlite_vm* pVM,
                bool bEof,
                int nCols,
                const char** paszValues,
                const char** paszColNames,
                bool bOwnVM=true);

    CppSQLiteQuery& operator=(const CppSQLiteQuery& rQuery);

    virtual ~CppSQLiteQuery();

    int numFields();

    const char* fieldName(int nCol);

    const char* fieldType(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    bool eof();

    void nextRow();

    void finalize();

private:

    void checkVM();

    sqlite_vm* mpVM;
    bool mbEof;
    int mnCols;
    const char** mpaszValues;
    const char** mpaszColNames;
    bool mbOwnVM;
};


class CppSQLiteTable
{
public:

    CppSQLiteTable();

    CppSQLiteTable(const CppSQLiteTable& rTable);

    CppSQLiteTable(char** paszResults, int nRows, int nCols);

    virtual ~CppSQLiteTable();

    CppSQLiteTable& operator=(const CppSQLiteTable& rTable);

    int numFields();

    int numRows();

    const char* fieldName(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    void setRow(int nRow);

    void finalize();

private:

    void checkResults();

    int mnCols;
    int mnRows;
    int mnCurrentRow;
    char** mpaszResults;
};


class CppSQLiteStatement
{
public:

    CppSQLiteStatement();

    CppSQLiteStatement(const CppSQLiteStatement& rStatement);

    CppSQLiteStatement(sqlite* pDB, sqlite_vm* pVM);

    virtual ~CppSQLiteStatement();

    CppSQLiteStatement& operator=(const CppSQLiteStatement& rStatement);

    int execDML();

    CppSQLiteQuery execQuery();

    void bind(int nParam, const char* szValue);
    void bind(int nParam, const int nValue);
    void bind(int nParam, const double dwValue);
    void bindNull(int nParam);

    void reset();

    void finalize();

private:

    void checkDB();
    void checkVM();

    sqlite* mpDB;
    sqlite_vm* mpVM;
};


class CppSQLiteDB
{
public:

    CppSQLiteDB();

    virtual ~CppSQLiteDB();

    void open(const char* szFile);

    void close();

    int execDML(const char* szSQL);

    CppSQLiteQuery execQuery(const char* szSQL);

    int execScalar(const char* szSQL);

    CppSQLiteTable getTable(const char* szSQL);

    CppSQLiteStatement compileStatement(const char* szSQL);

    int lastRowId();

    void interrupt() { sqlite_interrupt(mpDB); }

    void setBusyTimeout(int nMillisecs);

    static const char* SQLiteVersion() { return SQLITE_VERSION; }

private:

    CppSQLiteDB(const CppSQLiteDB& db);
    CppSQLiteDB& operator=(const CppSQLiteDB& db);

    sqlite_vm* compile(const char* szSQL);

    void checkDB();

    sqlite* mpDB;
    int mnBusyTimeoutMs;
};

#endif
