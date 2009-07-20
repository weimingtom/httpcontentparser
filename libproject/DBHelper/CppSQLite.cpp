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
#include "stdafx.h"
#include "CppSQLite.h"
#include <cstdlib>


// Named constant for passing to CppSQLiteException when passing it a string
// that cannot be deleted.
static const bool DONT_DELETE_MSG=false;

////////////////////////////////////////////////////////////////////////////////
// Prototypes for SQLite functions not included in SQLite DLL, but copied below
// from SQLite encode.c
////////////////////////////////////////////////////////////////////////////////
int sqlite_encode_binary(const unsigned char *in, int n, unsigned char *out);
int sqlite_decode_binary(const unsigned char *in, unsigned char *out);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

CppSQLiteException::CppSQLiteException(const int nErrCode,
									char* szErrMess,
									bool bDeleteMsg/*=true*/) :
									mnErrCode(nErrCode)
{
	mpszErrMess = sqlite_mprintf("%s[%d]: %s",
								errorCodeAsString(nErrCode),
								nErrCode,
								szErrMess ? szErrMess : "");

	if (bDeleteMsg && szErrMess)
	{
		sqlite_freemem(szErrMess);
	}
}

									
CppSQLiteException::CppSQLiteException(const CppSQLiteException&  e) :
									mnErrCode(e.mnErrCode)
{
	mpszErrMess = 0;
	if (e.mpszErrMess)
	{
		mpszErrMess = sqlite_mprintf("%s", e.mpszErrMess);
	}
}


const char* CppSQLiteException::errorCodeAsString(int nErrCode)
{
	switch (nErrCode)
	{
		case SQLITE_OK          : return "SQLITE_OK";
		case SQLITE_ERROR       : return "SQLITE_ERROR";
		case SQLITE_INTERNAL    : return "SQLITE_INTERNAL";
		case SQLITE_PERM        : return "SQLITE_PERM";
		case SQLITE_ABORT       : return "SQLITE_ABORT";
		case SQLITE_BUSY        : return "SQLITE_BUSY";
		case SQLITE_LOCKED      : return "SQLITE_LOCKED";
		case SQLITE_NOMEM       : return "SQLITE_NOMEM";
		case SQLITE_READONLY    : return "SQLITE_READONLY";
		case SQLITE_INTERRUPT   : return "SQLITE_INTERRUPT";
		case SQLITE_IOERR       : return "SQLITE_IOERR";
		case SQLITE_CORRUPT     : return "SQLITE_CORRUPT";
		case SQLITE_NOTFOUND    : return "SQLITE_NOTFOUND";
		case SQLITE_FULL        : return "SQLITE_FULL";
		case SQLITE_CANTOPEN    : return "SQLITE_CANTOPEN";
		case SQLITE_PROTOCOL    : return "SQLITE_PROTOCOL";
		case SQLITE_EMPTY       : return "SQLITE_EMPTY";
		case SQLITE_SCHEMA      : return "SQLITE_SCHEMA";
		case SQLITE_TOOBIG      : return "SQLITE_TOOBIG";
		case SQLITE_CONSTRAINT  : return "SQLITE_CONSTRAINT";
		case SQLITE_MISMATCH    : return "SQLITE_MISMATCH";
		case SQLITE_MISUSE      : return "SQLITE_MISUSE";
		case SQLITE_NOLFS       : return "SQLITE_NOLFS";
		case SQLITE_AUTH        : return "SQLITE_AUTH";
		case SQLITE_FORMAT      : return "SQLITE_FORMAT";
		case SQLITE_RANGE       : return "SQLITE_RANGE";
		case SQLITE_ROW         : return "SQLITE_ROW";
		case SQLITE_DONE        : return "SQLITE_DONE";
		case CPPSQLITE_ERROR    : return "CPPSQLITE_ERROR";
		default: return "UNKNOWN_ERROR";
	}
}


CppSQLiteException::~CppSQLiteException()
{
	if (mpszErrMess)
	{
		sqlite_freemem(mpszErrMess);
		mpszErrMess = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteBuffer::CppSQLiteBuffer()
{
	mpBuf = 0;
}


CppSQLiteBuffer::~CppSQLiteBuffer()
{
	clear();
}


void CppSQLiteBuffer::clear()
{
	if (mpBuf)
	{
		sqlite_freemem(mpBuf);
		mpBuf = 0;
	}

}


const char* CppSQLiteBuffer::format(const char* szFormat, ...)
{
	clear();
	va_list va;
	va_start(va, szFormat);
	mpBuf = sqlite_vmprintf(szFormat, va);
	va_end(va);
	return mpBuf;
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteBinary::CppSQLiteBinary() :
						mpBuf(0),
						mnBinaryLen(0),
						mnBufferLen(0),
						mnEncodedLen(0),
						mbEncoded(false)
{
}


CppSQLiteBinary::~CppSQLiteBinary()
{
	clear();
}


void CppSQLiteBinary::setBinary(const unsigned char* pBuf, int nLen)
{
	mpBuf = allocBuffer(nLen);
	memcpy(mpBuf, pBuf, nLen);
}


void CppSQLiteBinary::setEncoded(const unsigned char* pBuf)
{
	clear();

	mnEncodedLen = strlen((const char*)pBuf);
	mnBufferLen = mnEncodedLen + 1; // Allow for NULL terminator

	mpBuf = (unsigned char*)malloc(mnBufferLen);

	if (!mpBuf)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Cannot allocate memory",
								DONT_DELETE_MSG);
	}

	memcpy(mpBuf, pBuf, mnBufferLen);
	mbEncoded = true;
}


const unsigned char* CppSQLiteBinary::getEncoded()
{
	if (!mbEncoded)
	{
		unsigned char* ptmp = (unsigned char*)malloc(mnBinaryLen);
		memcpy(ptmp, mpBuf, mnBinaryLen);
		mnEncodedLen = sqlite_encode_binary(ptmp, mnBinaryLen, mpBuf);
		free(ptmp);
		mbEncoded = true;
	}

	return mpBuf;
}


const unsigned char* CppSQLiteBinary::getBinary()
{
	if (mbEncoded)
	{
		// in/out buffers can be the same
		mnBinaryLen = sqlite_decode_binary(mpBuf, mpBuf);

		if (mnBinaryLen == -1)
		{
			throw CppSQLiteException(CPPSQLITE_ERROR,
									"Cannot decode binary",
									DONT_DELETE_MSG);
		}

		mbEncoded = false;
	}

	return mpBuf;
}


int CppSQLiteBinary::getBinaryLength()
{
	getBinary();
	return mnBinaryLen;
}


unsigned char* CppSQLiteBinary::allocBuffer(int nLen)
{
	clear();

	// Allow extra space for encoded binary as per comments in
	// SQLite encode.c See bottom of this file for implementation
	// of SQLite functions use 3 instead of 2 just to be sure ;-)
	mnBinaryLen = nLen;
	mnBufferLen = 3 + (257*nLen)/254;

	mpBuf = (unsigned char*)malloc(mnBufferLen);

	if (!mpBuf)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Cannot allocate memory",
								DONT_DELETE_MSG);
	}

	mbEncoded = false;

	return mpBuf;
}


void CppSQLiteBinary::clear()
{
	if (mpBuf)
	{
		mnBinaryLen = 0;
		mnBufferLen = 0;
		free(mpBuf);
		mpBuf = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteQuery::CppSQLiteQuery()
{
	mpVM = 0;
	mbEof = true;
	mnCols = 0;
	mpaszValues = 0;
	mpaszColNames = 0;
	mbOwnVM = false;
}


CppSQLiteQuery::CppSQLiteQuery(const CppSQLiteQuery& rQuery)
{
	mpVM = rQuery.mpVM;
	// Only one object can own the VM
	const_cast<CppSQLiteQuery&>(rQuery).mpVM = 0;
	mbEof = rQuery.mbEof;
	mnCols = rQuery.mnCols;
	mpaszValues = rQuery.mpaszValues;
	mpaszColNames = rQuery.mpaszColNames;
	mbOwnVM = rQuery.mbOwnVM;
}


CppSQLiteQuery::CppSQLiteQuery(sqlite_vm* pVM,
							bool bEof,
							int nCols,
							const char** paszValues,
							const char** paszColNames,
							bool bOwnVM/*=true*/)
{
	mpVM = pVM;
	mbEof = bEof;
	mnCols = nCols;
	mpaszValues = paszValues;
	mpaszColNames = paszColNames;
	mbOwnVM = bOwnVM;
}


CppSQLiteQuery::~CppSQLiteQuery()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CppSQLiteQuery& CppSQLiteQuery::operator=(const CppSQLiteQuery& rQuery)
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
	mpVM = rQuery.mpVM;
	// Only one object can own the VM
	const_cast<CppSQLiteQuery&>(rQuery).mpVM = 0;
	mbEof = rQuery.mbEof;
	mnCols = rQuery.mnCols;
	mpaszValues = rQuery.mpaszValues;
	mpaszColNames = rQuery.mpaszColNames;
	mbOwnVM = rQuery.mbOwnVM;
	return *this;
}


int CppSQLiteQuery::numFields()
{
	checkVM();
	return mnCols;
}


const char* CppSQLiteQuery::fieldValue(int nField)
{
	checkVM();

	if (nField < 0 || nField > mnCols-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return mpaszValues[nField];
}


const char* CppSQLiteQuery::fieldValue(const char* szField)
{
	checkVM();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszColNames[nField]) == 0)
			{
				return mpaszValues[nField];
			}
		}
	}

	throw CppSQLiteException(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);
}


int CppSQLiteQuery::getIntField(int nField, int nNullValue/*=0*/)
{
	if (fieldIsNull(nField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(nField));
	}
}


int CppSQLiteQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if (fieldIsNull(szField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(szField));
	}
}


double CppSQLiteQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(nField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(nField));
	}
}


double CppSQLiteQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(szField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(szField));
	}
}


const char* CppSQLiteQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(nField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(nField);
	}
}


const char* CppSQLiteQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(szField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(szField);
	}
}


bool CppSQLiteQuery::fieldIsNull(int nField)
{
	checkVM();
	return (fieldValue(nField) == 0);
}


bool CppSQLiteQuery::fieldIsNull(const char* szField)
{
	checkVM();
	return (fieldValue(szField) == 0);
}


const char* CppSQLiteQuery::fieldName(int nCol)
{
	checkVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return mpaszColNames[nCol];
}


const char* CppSQLiteQuery::fieldType(int nCol)
{
	checkVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return mpaszColNames[mnCols+nCol];
}


bool CppSQLiteQuery::eof()
{
	checkVM();
	return mbEof;
}


void CppSQLiteQuery::nextRow()
{
	checkVM();

	int nRet = sqlite_step(mpVM, &mnCols, &mpaszValues, &mpaszColNames);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		mbEof = true;
	}
	else if (nRet == SQLITE_ROW)
	{
		// more rows, nothing to do
	}
	else
	{
		char *szError = 0;
		nRet = sqlite_finalize(mpVM, &szError);
		mpVM = 0;
		throw CppSQLiteException(nRet, szError);
	}
}


void CppSQLiteQuery::finalize()
{
	if (mpVM && mbOwnVM)
	{
		char *szError = 0;
		int nError = sqlite_finalize(mpVM, &szError);
		mpVM = 0;

		if (nError != SQLITE_OK)
		{
			throw CppSQLiteException(nError, szError);
		}
	}
}


void CppSQLiteQuery::checkVM()
{
	if (mpVM == 0)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Null Virtual Machine pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteTable::CppSQLiteTable()
{
	mpaszResults = 0;
	mnRows = 0;
	mnCols = 0;
	mnCurrentRow = 0;
}


CppSQLiteTable::CppSQLiteTable(const CppSQLiteTable& rTable)
{
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<CppSQLiteTable&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
}


CppSQLiteTable::CppSQLiteTable(char** paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults;
	mnRows = nRows;
	mnCols = nCols;
	mnCurrentRow = 0;
}


CppSQLiteTable::~CppSQLiteTable()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CppSQLiteTable& CppSQLiteTable::operator=(const CppSQLiteTable& rTable)
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<CppSQLiteTable&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
	return *this;
}


void CppSQLiteTable::finalize()
{
	if (mpaszResults)
	{
		sqlite_free_table(mpaszResults);
		mpaszResults = 0;
	}
}


int CppSQLiteTable::numFields()
{
	checkResults();
	return mnCols;
}


int CppSQLiteTable::numRows()
{
	checkResults();
	return mnRows;
}


const char* CppSQLiteTable::fieldValue(int nField)
{
	checkResults();

	if (nField < 0 || nField > mnCols-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
	return mpaszResults[nIndex];
}


const char* CppSQLiteTable::fieldValue(const char* szField)
{
	checkResults();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszResults[nField]) == 0)
			{
				int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
				return mpaszResults[nIndex];
			}
		}
	}

	throw CppSQLiteException(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);
}


int CppSQLiteTable::getIntField(int nField, int nNullValue/*=0*/)
{
	if (fieldIsNull(nField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(nField));
	}
}


int CppSQLiteTable::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if (fieldIsNull(szField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(szField));
	}
}


double CppSQLiteTable::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(nField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(nField));
	}
}


double CppSQLiteTable::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(szField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(szField));
	}
}


const char* CppSQLiteTable::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(nField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(nField);
	}
}


const char* CppSQLiteTable::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(szField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(szField);
	}
}


bool CppSQLiteTable::fieldIsNull(int nField)
{
	checkResults();
	return (fieldValue(nField) == 0);
}


bool CppSQLiteTable::fieldIsNull(const char* szField)
{
	checkResults();
	return (fieldValue(szField) == 0);
}


const char* CppSQLiteTable::fieldName(int nCol)
{
	checkResults();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return mpaszResults[nCol];
}


void CppSQLiteTable::setRow(int nRow)
{
	checkResults();

	if (nRow < 0 || nRow > mnRows-1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid row index requested",
								DONT_DELETE_MSG);
	}

	mnCurrentRow = nRow;
}


void CppSQLiteTable::checkResults()
{
	if (mpaszResults == 0)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Null Results pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteStatement::CppSQLiteStatement()
{
	mpDB = 0;
	mpVM = 0;
}


CppSQLiteStatement::CppSQLiteStatement(const CppSQLiteStatement& rStatement)
{
	mpDB = rStatement.mpDB;
	mpVM = rStatement.mpVM;
	// Only one object can own VM
	const_cast<CppSQLiteStatement&>(rStatement).mpVM = 0;
}


CppSQLiteStatement::CppSQLiteStatement(sqlite* pDB, sqlite_vm* pVM)
{
	mpDB = pDB;
	mpVM = pVM;
}


CppSQLiteStatement::~CppSQLiteStatement()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CppSQLiteStatement& CppSQLiteStatement::operator=(const CppSQLiteStatement& rStatement)
{
	mpDB = rStatement.mpDB;
	mpVM = rStatement.mpVM;
	// Only one object can own VM
	const_cast<CppSQLiteStatement&>(rStatement).mpVM = 0;
	return *this;
}


int CppSQLiteStatement::execDML()
{
	checkDB();
	checkVM();

	int nCols(0);
	char* szError=0;
	const char** paszValues=0;
	const char** paszColNames=0;

	int nRet = sqlite_step(mpVM, &nCols, &paszValues, &paszColNames);

	if (nRet == SQLITE_DONE)
	{
		int nRowsChanged = sqlite_last_statement_changes(mpDB);

		nRet = sqlite_reset(mpVM, &szError);

		if (nRet != SQLITE_OK)
		{
			throw CppSQLiteException(nRet, szError);
		}

		return nRowsChanged;
	}
	else
	{
		nRet = sqlite_reset(mpVM, &szError);
		throw CppSQLiteException(nRet, szError);
	}
}


CppSQLiteQuery CppSQLiteStatement::execQuery()
{
	checkDB();
	checkVM();

	int nCols(0);
	const char** paszValues=0;
	const char** paszColNames=0;

	int nRet = sqlite_step(mpVM, &nCols, &paszValues, &paszColNames);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		return CppSQLiteQuery(mpVM, true/*eof*/, nCols, paszValues, paszColNames, false);
	}
	else if (nRet == SQLITE_ROW)
	{
		// at least 1 row
		return CppSQLiteQuery(mpVM, false/*eof*/, nCols, paszValues, paszColNames, false);
	}
	else
	{
		char* szError=0;
		nRet = sqlite_finalize(mpVM, &szError);
		throw CppSQLiteException(nRet, szError);
	}
}


void CppSQLiteStatement::bind(int nParam, const char* szValue)
{
	checkVM();
	int nRes = sqlite_bind(mpVM, nParam, szValue, -1, 1);

	if (nRes != SQLITE_OK)
	{
		throw CppSQLiteException(nRes,
								"Error binding parameter",
								DONT_DELETE_MSG);
	}
}


void CppSQLiteStatement::bind(int nParam, const int nValue)
{
	char buf[16];
	sprintf(buf, "%d", nValue);
	bind(nParam, buf);
}


void CppSQLiteStatement::bind(int nParam, const double dValue)
{
	char buf[16];
	sprintf(buf, "%f", dValue);
	bind(nParam, buf);
}


void CppSQLiteStatement::bindNull(int nParam)
{
	checkVM();
	int nRes = sqlite_bind(mpVM, nParam, 0, -1, 1);

	if (nRes != SQLITE_OK)
	{
		throw CppSQLiteException(nRes,
								"Error binding Null parameter",
								DONT_DELETE_MSG);
	}
}


void CppSQLiteStatement::reset()
{
	if (mpVM)
	{
		char *szError = 0;
		int nError = sqlite_reset(mpVM, &szError);

		if (nError != SQLITE_OK)
		{
			throw CppSQLiteException(nError, szError);
		}
	}
}


void CppSQLiteStatement::finalize()
{
	if (mpVM)
	{
		char *szError = 0;
		int nError = sqlite_finalize(mpVM, &szError);
		mpVM = 0;

		if (nError != SQLITE_OK)
		{
			throw CppSQLiteException(nError, szError);
		}
	}
}


void CppSQLiteStatement::checkDB()
{
	if (mpDB == 0)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);
	}
}


void CppSQLiteStatement::checkVM()
{
	if (mpVM == 0)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Null Virtual Machine pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CppSQLiteDB::CppSQLiteDB()
{
	mpDB = 0;
	mnBusyTimeoutMs = 60000; // 60 seconds
}


CppSQLiteDB::CppSQLiteDB(const CppSQLiteDB& db)
{
	mpDB = db.mpDB;
	mnBusyTimeoutMs = 60000; // 60 seconds
}


CppSQLiteDB::~CppSQLiteDB()
{
	close();
}


CppSQLiteDB& CppSQLiteDB::operator=(const CppSQLiteDB& db)
{
	mpDB = db.mpDB;
	mnBusyTimeoutMs = 60000; // 60 seconds
	return *this;
}


void CppSQLiteDB::open(const char* szFile)
{
	char *szError = 0;
	mpDB = sqlite_open(szFile, 0, &szError);

	if (!mpDB)
	{
		throw CppSQLiteException(SQLITE_CANTOPEN, szError);
	}

	setBusyTimeout(mnBusyTimeoutMs);
}


void CppSQLiteDB::close()
{
	if (mpDB)
	{
		sqlite_close(mpDB);
		mpDB = 0;
	}
}


CppSQLiteStatement CppSQLiteDB::compileStatement(const char* szSQL)
{
	checkDB();

	sqlite_vm* pVM = compile(szSQL);
	return CppSQLiteStatement(mpDB, pVM);
}


int CppSQLiteDB::execDML(const char* szSQL)
{
	checkDB();

	char* szError=0;

	int nRet = sqlite_exec(mpDB, szSQL, 0, 0, &szError);

	if (nRet == SQLITE_OK)
	{
		return sqlite_changes(mpDB);
	}
	else
	{
		throw CppSQLiteException(nRet, szError);
	}
}


CppSQLiteQuery CppSQLiteDB::execQuery(const char* szSQL)
{
	checkDB();

	sqlite_vm* pVM = compile(szSQL);

	int nCols(0);
	const char** paszValues=0;
	const char** paszColNames=0;

	int nRet = sqlite_step(pVM, &nCols, &paszValues, &paszColNames);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		return CppSQLiteQuery(pVM, true/*eof*/, nCols, paszValues, paszColNames);
	}
	else if (nRet == SQLITE_ROW)
	{
		// at least 1 row
		return CppSQLiteQuery(pVM, false/*eof*/, nCols, paszValues, paszColNames);
	}
	else
	{
		char* szError=0;
		nRet = sqlite_finalize(pVM, &szError);
		throw CppSQLiteException(nRet, szError);
	}
}


int CppSQLiteDB::execScalar(const char* szSQL)
{
	CppSQLiteQuery q = execQuery(szSQL);

	if (q.eof() || q.numFields() < 1)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Invalid scalar query",
								DONT_DELETE_MSG);
	}

	return atoi(q.fieldValue(0));
}


CppSQLiteTable CppSQLiteDB::getTable(const char* szSQL)
{
	checkDB();

	char* szError=0;
	char** paszResults=0;
	int nRet;
	int nRows(0);
	int nCols(0);

	nRet = sqlite_get_table(mpDB, szSQL, &paszResults, &nRows, &nCols, &szError);

	if (nRet == SQLITE_OK)
	{
		return CppSQLiteTable(paszResults, nRows, nCols);
	}
	else
	{
		throw CppSQLiteException(nRet, szError);
	}
}


int CppSQLiteDB::lastRowId()
{
	return sqlite_last_insert_rowid(mpDB);
}


void CppSQLiteDB::setBusyTimeout(int nMillisecs)
{
	mnBusyTimeoutMs = nMillisecs;
	sqlite_busy_timeout(mpDB, mnBusyTimeoutMs);
}


void CppSQLiteDB::checkDB()
{
	if (!mpDB)
	{
		throw CppSQLiteException(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);
	}
}


sqlite_vm* CppSQLiteDB::compile(const char* szSQL)
{
	checkDB();

	char* szError=0;
	const char* szTail=0;
	sqlite_vm* pVM;

	int nRet = sqlite_compile(mpDB, szSQL, &szTail, &pVM, &szError);

	if (nRet != SQLITE_OK)
	{
		throw CppSQLiteException(nRet, szError);
	}

	return pVM;
}
