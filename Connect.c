#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

//declare some variables


static char *host = "localhost";
static char *user = "root";
static char *pass = "root"; // don't judge me
static char *dbname = "test";

unsigned int port = 92126; // the port mysql is using can be found with 
                           // user@bash:~$ ss | grep mysql
static char *unix_socket = NULL;
unsigned int flag = 0;


// main function to check connnection + run query
int main() {

        MYSQL *conn; 
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);

//if connection unsuccessful print  error and the error code 

        if (!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag )))
        {

        fprintf(stderr, "\nError: %s [%d]\n", mysql_error(conn), mysql_errno(conn));

        }

//if connection successful, print connection successful
        printf("Connection Successful!\n\n");

//run this query
        mysql_query(conn, "SELECT * from bdays");

        res = mysql_store_result(conn);
//https://dev.mysql.com/doc/c-api/8.0/en/mysql-fetch-row.html
        while(row = mysql_fetch_row(res))
        {

//print results to stdout with tabs as columns and all as string        
        printf("%s\t%s\t%s\t%s\t%s\t%s\n",
        row[0],row[1],row[2],row[3],row[4],row[5] );


        }


mysql_close(conn);
return 0;


}

// compile with 
// user@bash:~$ gcc -o output $(mysql_config --cflags) Connect.c $(mysql_config --libs) 
       
