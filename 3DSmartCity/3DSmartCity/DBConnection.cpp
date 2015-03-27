#include "StdAfx.h"
#include "DBConnection.h"


DBConnection::DBConnection(void)
{
}

DBConnection::~DBConnection(void)
{
}

bool DBConnection::ConnectToDB(PGconn *&conn,char *pghost,char *pgport,char *dbname,char *user,char *pwd)
{
	char * pgoptions, *pgtty;
	pgoptions=NULL;
	pgtty=NULL;

	conn=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,user,pwd);	
	if (PQstatus(conn)==CONNECTION_BAD)
	{
		std::cout<<"Connection db "<<dbname<<" failed!"<<std::endl;
		std::cout<<PQerrorMessage(conn)<<std::endl;
		return false;
	} 
	else
	{
		std::cout<<"Connection db "<<dbname<<" sucess!"<<std::endl;
		return true;
	}
}

bool DBConnection::ConnectToDB(char *pghost,char *pgport,char *dbname,char *user,char *pwd)
{
	char * pgoptions, *pgtty;
	pgoptions=NULL;
	pgtty=NULL;

	conn=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,user,pwd);	
	if (PQstatus(conn)==CONNECTION_BAD)
	{
		std::cout<<"Connection db "<<dbname<<" failed!"<<std::endl;
		std::cout<<PQerrorMessage(conn)<<std::endl;
		return false;
	} 
	else
	{
		std::cout<<"Connection db "<<dbname<<" sucess!"<<std::endl;
		return true;
	}
}



PGresult * DBConnection::ExecSQL(PGconn * conn,const char *sql, int * row_num)
{
	PGresult *res=NULL;
	if (conn==NULL)
	{
		std::cout<<"connection is null"<<std::endl;
		return NULL;
	} 
	else
	{
		PQsetClientEncoding(conn,"gbk");
		res=PQexec(const_cast<PGconn *>(conn),sql);	
		*row_num=PQntuples(res);
	}
	return res;
}

PGresult * DBConnection::ExecSQL(const char *sql)
{
	PGresult *res=NULL;
	if (conn==NULL)
	{
		std::cout<<"connection is null"<<std::endl;
		return NULL;
	} 
	else
	{
		PQsetClientEncoding(conn,"gbk");
		res=PQexec(conn,sql);
	}
	return res;
}
