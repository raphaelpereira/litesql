/* LiteSQL - PostgreSQL-backend implementation
 * 
 * The list of contributors at http://litesql.sf.net/ 
 * 
 * See LICENSE for copyright information. */
#include "compatibility.hpp"
#include "postgresql.hpp"
#ifdef HAVE_LIBPQ
#include <string>
namespace litesql {
using namespace std;

PostgreSQL::Result::~Result() {
    PQclear(res);
}
size_t PostgreSQL::Result::fieldNum() const {
    return PQnfields(res);
}
Record PostgreSQL::Result::fields() const {
    Record r;
    r.reserve(fieldNum());
    for (size_t i = 0; i < fieldNum(); i++)
        r.push_back(PQfname(res, i));
    return r;
}
size_t PostgreSQL::Result::recordNum() const {
    return PQntuples(res);
}  
Records PostgreSQL::Result::records() const {
    Records recs;
    recs.resize(recordNum());
    for (size_t i = 0; i < recordNum(); i++) {
        recs[i].reserve(fieldNum());
        for (size_t i2 = 0; i2 < fieldNum(); i2++) 
            recs[i].push_back(PQgetvalue(res, i, i2));
    }
    return recs;
}
int PostgreSQL::Cursor::sid = 1;
size_t PostgreSQL::Cursor::cacheSize = 30;
void PostgreSQL::Cursor::setCacheSize(int v) {
    if (v > 1)
        cacheSize = v;
}
PostgreSQL::Cursor::Cursor(const PostgreSQL& p, string q) 
    : pq(p), name("cursor" + toString(sid++)), cachePos(0),
      createdTransaction(false) {
    if (!pq.transaction) {
        createdTransaction = true;
        pq.begin();
    }
    delete pq.execute("DECLARE \"" + name + "\" CURSOR FOR "+ q);
}
Record PostgreSQL::Cursor::fetchOne() {
    if (cache.size() == 0 || cachePos >= cache.size()) {
        cachePos = 0;
        Backend::Result* r = pq.execute("FETCH " + toString(cacheSize)
                                        + " FROM " + name + ";");
        cache = r->records();
        delete r;
    }
    if (cachePos >= cache.size())
        return Record();
    return cache[cachePos++];
}
PostgreSQL::Cursor::~Cursor() {
    if (pq.transaction)
        delete pq.execute("CLOSE "+name+";");
    if (createdTransaction)
        pq.commit();
}
PostgreSQL::PostgreSQL(const string& connInfo) : conn(NULL), transaction(0) {
    Split params(connInfo,";");
    string pq_connInfo;
    for (size_t i = 0; i < params.size(); i++) {
        Split param(params[i], "=");
        if (param.size() == 1)
            continue;
        if (param[0] == "host")
            pq_connInfo += "host=" + param[1] + " ";
        else if (param[0] == "database")
            pq_connInfo += "dbname=" + param[1] + " ";
        else if (param[0] == "password")
            pq_connInfo += "password=" + param[1] + " ";
        else if (param[0] == "user")
            pq_connInfo += "user=" + param[1] + " ";
    }

    conn = PQconnectdb(pq_connInfo.c_str());
    if (PQstatus(conn) != CONNECTION_OK)
        throw DatabaseError("PostgreSQL connection " + pq_connInfo + " failed: " 
                            + string(PQerrorMessage(conn)));
}
bool PostgreSQL::supportsSequences() const {
    return true;
}
void PostgreSQL::begin() const {
  if (!transaction) {
    delete execute("BEGIN;");
  } else {
    delete execute("SAVEPOINT level_" + toString(transaction) + ";");
  }
  transaction++;
}
void PostgreSQL::commit() const {
    if (!transaction) return;
    if (transaction == 1) {
        delete execute("COMMIT;");
    } else {
        delete execute("RELEASE SAVEPOINT level_" + toString(transaction-1) + ";");
    }
    transaction--;
}
void PostgreSQL::rollback() const {
    if (!transaction) return;
    if (transaction == 1) {
      delete execute("ROLLBACK;");
    } else {
      delete execute("ROLLBACK TO SAVEPOINT level_" + toString(transaction-1) + ";");
    }
    transaction--;
}
Backend::Result* PostgreSQL::execute(const string& _query) const {
    string query = _query + ";";
    PGresult * res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK 
        && PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw Except("Query:" + query + " failed: " + 
                     string(PQerrorMessage(conn)));
    }
    return new Result(res);    
}
Backend::Cursor* PostgreSQL::cursor(const string& query) const {
    return new Cursor(*this, query + ";");
}

string PostgreSQL::getSQLType(AT_field_type fieldType, const string& length) const
{
    switch(fieldType) {
        case A_field_type_integer: return "INTEGER";
		case A_field_type_bigint: return "BIGINT";
		case A_field_type_string: return "TEXT";
		case A_field_type_float: return "FLOAT";
		case A_field_type_double: return "DOUBLE PRECISION";
		case A_field_type_boolean: return "INTEGER";
		case A_field_type_date: return "INTEGER";
		case A_field_type_time: return "INTEGER";
		case A_field_type_datetime: return "INTEGER";
		case A_field_type_blob: return "BLOB";
		default: return "";
	}
}

PostgreSQL::~PostgreSQL() {
    if (transaction)
        commit();
    PQfinish(conn);
}
}
#endif
