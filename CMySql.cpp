#include "CMySql.h"

/*
*/
CMySql::CMySql()
{
	memset(this, 0x00, sizeof(CMySql));
}

/*
*/
CMySql::CMySql(const char* database)
{
    memset(this, 0x00, sizeof(CMySql));

    m_connection = mysql_init(0);

    if (m_connection == 0)
    {
        return;
    }

    if (mysql_real_connect(m_connection, "localhost", "root", "mysql", database, 26106, 0, 0) == 0)
    {
        mysql_close(m_connection);

        m_connection = 0;

        return;
    }
}

/*
*/
CMySql::~CMySql()
{
    if (m_result)
    {
        mysql_free_result(m_result);
    }

    if (m_connection)
    {
        mysql_close(m_connection);
    }
}

/*
*/
MYSQL_ROW CMySql::FetchRow()
{
    if (m_result == 0)
    {
        return nullptr;

    }

    m_rowset = mysql_fetch_row(m_result);

    return m_rowset;
}

/*
*/
int32_t CMySql::GetFieldCount()
{
    if (m_result == 0)
    {
        return 0;
    }

    m_fieldCount = mysql_num_fields(m_result);

    return m_fieldCount;
}

/*
*/
bool CMySql::PerformQuery(const char* query)
{
    if (m_connection == 0)
    {
        return false;
    }

    if (mysql_query(m_connection, query))
    {
        mysql_close(m_connection);

        m_connection = 0;

        return false;
    }

    m_result = mysql_store_result(m_connection);

    if (m_result == 0)
    {
        mysql_close(m_connection);

        m_connection = 0;

        return false;
    }

    return true;
}

/*
    CMySql* m = new CMySql("aviation");

    m->PerformQuery("SELECT icao,name from aptairport limit 10");

    int32_t n = m->GetFieldCount();

    MYSQL_ROW r = m->FetchRow();

    while (r)
    {
        for (int32_t i = 0; i < n; i++)
        {
            printf("%s|", r[i]);
        }

        printf("\n");

        r = m->FetchRow();
    }

    SAFE_DELETE(m);
*/