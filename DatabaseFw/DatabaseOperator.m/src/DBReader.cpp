//===================================================================
// COPYRIGHT liqiang 2021/05/29
//===================================================================
// DBReader.cpp
// Header definition of class DBReader
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/05/29 Creation: Code generated by the 3DS wizard
//===================================================================

#include "DBReader.h"
#include "CATGetEnvValue.h"
#include "sqlite3/sqlite3.h"
#include <iostream>

using namespace liqiang;
//-----------------------------------------------------------------------------
// DBReader : constructor
//-----------------------------------------------------------------------------

bool DeveloperTest = false;



char* U2G(const char* utf8)  
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);  
	wchar_t* wstr = new wchar_t[len+1];  
	memset(wstr, 0, len+1);  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);  
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);  
	char* str = new char[len+1];  
	memset(str, 0, len+1);  
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);  
	if(wstr) delete[] wstr;  
	return str;  
}  

DBReader::DBReader():
	_isValid(false)
	,db(NULL)
	,_DBType(UNSet)
{
	

	
}

//-----------------------------------------------------------------------------
// DBReader : destructor
//-----------------------------------------------------------------------------

DBReader::~DBReader()
{
	if (db != NULL)
	{
		sqlite3_close(db);
	}
}

bool DBReader::OpenSQLite(const CATUnicodeString &iFile)
{
	_isValid = false;
	if (!sqlite3_open(iFile.ConvertToChar(),&db))
	{
		_isValid = true;
	}

	return _isValid;
}

bool DBReader::RunSQL(const CATUnicodeString &iSQL,std::vector<std::vector<CATUnicodeString>> &oDatas)
{	
	bool isRun = false;
	if (db != NULL)
	{
		std::cout<<"SQL : \n"<<iSQL<<std::endl;
		char **SearchResult;
		int nbRow,nbCol;
		char *ErrorMsg;

		char * UTF8String = new char[4+6*(iSQL.GetLengthInChar())];

		// Converts the CATUnicodeString to UTF8
		size_t UTF8StringByteCount;
		iSQL.ConvertToUTF8(UTF8String, &UTF8StringByteCount);

		// Output the UTF8 string
		char * OutputString = new char[UTF8StringByteCount+1];
		strncpy(OutputString,UTF8String,UTF8StringByteCount);
		OutputString[UTF8StringByteCount] = '\0';

		if (SQLITE_OK == sqlite3_get_table(db,OutputString,&SearchResult,&nbRow,&nbCol,&ErrorMsg))
		{
			for (int IndexOfRow = 0; IndexOfRow <= nbRow ; IndexOfRow++)
			{
				std::vector<CATUnicodeString> Data;
				for (int IndexOfCol = 0; IndexOfCol < nbCol;IndexOfCol++)
				{
					Data.push_back(U2G(SearchResult[(IndexOfRow)*nbCol + IndexOfCol]));
				}
				oDatas.push_back(Data);
			}
			isRun = true	;
		}
		else
		{
			std::cout<<ErrorMsg<<std::endl;
		}
	}
	return isRun;

}

