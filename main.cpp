#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <mysql.h>
#include <thread>
#include <chrono>
#include <sstream>
#include<stdio.h>
#include <cstdio>
using namespace std;

int main()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    //int qstate; //stores query status after execution 0 if error and non zero if successful
    //int last_row_id = -1;
    int num_fields;
    conn = mysql_init(0);
    if (conn) //if successful
        cout << "connection object ok" << endl;
    else
        cout << "conn object problem" << mysql_error(conn) << endl;
    conn = mysql_real_connect(conn, "localhost", "root", "", "usdjpy", 0, NULL, 0);
    int previous_last_id = 0, last_id = 0;
    string last_time;

   while(true)
    {
      mysql_query(conn, " select close,id, time from fivemin order by id  DESC LIMIT 5 ");
      result = mysql_store_result(conn);
      num_fields = mysql_num_fields(result);
      float sum = 0;

    while((row=mysql_fetch_row(result)))
        {
                     sum += atof(row[0]);
                     if (last_id < atoi(row[1])) {
                        last_id = atoi(row[1]);
                        last_time = row[2];
                        cout << "Time:" << last_time << endl;
                     }
                    // time=(row[2]);
        }
        float ma;
        ma=sum/5.0;

    if(previous_last_id != last_id)
            {
            cout << "Simple moving Average: " << ma << endl;
            previous_last_id = last_id;

            char str[80];
                 std::sprintf(str,"insert into sma(sma,date) values('%f', '%s')",ma, last_time.c_str());
                 mysql_query(conn,str);
            }
         Sleep(1000);
    }
    return 0;
}
