#pragma once

#include "framework.h"

class CMySql
{
public:

	MYSQL* m_connection;

	MYSQL_RES* m_result;

	MYSQL_ROW m_rowset;
	
	int32_t m_fieldCount;

	CMySql();
	CMySql(const char* database);
	~CMySql();

	MYSQL_ROW FetchRow();
	int32_t GetFieldCount();
	bool PerformQuery(const char* query);
};