#pragma once
#include <iostream>
#include <libpq-fe.h>
#include <vector>
using namespace std;

#include "PipePoint.h"

class DBConnection
{
public:
	DBConnection(void);
	~DBConnection(void);

	bool ConnectToDB(PGconn *&conn,char *pghost,char *pgport,char *dbname,char *user,char *pwd);
	bool ConnectToDB(char *pghost,char *pgport,char *dbname,char *user,char *pwd);
	PGresult * DBConnection::ExecSQL(PGconn * conn,const char *sql, int * row_num);
	PGresult * DBConnection::ExecSQL(const char *sql);
	void DBConnection::ParseResult(PGresult* res,vector<PipePoint>& pts);
private:
	PGconn* conn;
};

