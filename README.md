# eecs584

output: load.sql, search.sql

usage: mysql -u root 584test -p

password

source /home/ianzyc/Desktop/load.sql
source /home/ianzyc/Desktop/search.sql

source /home/zhizhong/Desktop/eecs584/eecs584/load.sql

create index:
ALTER TABLE gis ADD SPATIAL INDEX(g);

#compile and execution

server compile command: g++ server.cpp executor.cpp parser.cpp -o server

server execute command: ./server

client compile commnad: g++ client.cpp -o client

client execute command: ./client -s <hostname:port> -q <useless opt, whatever string>

# project design:

-client:

-server:

data structure: table(consists of (1)array of rows and (2) rtree index) (3) string map

row contains(rectangle and attribute)

rtree index

string map maps string to double

-parser: 
parse the 5 queries(drop table, create table, insert, delete, select)

return a struct

query type

table name

rectangle

spatial function(intersect/ contain)

attribute(as double)

compare operator

-executor:

depend on query type:

drop table, create table, just change the table list,

insert: just insert the rectangle

query:	
1. based on spatial function and compare operator, pass two function pointer to rtree class, and collect result.

execution mode: 1.parallel check 2nd attribute in the tree search process. 2.store all row id into a data structure and sort afterwards, parallelize scan process again.


# server-client:
-mini spatialdb client: client is only in charge of reading queries from file, and send it to server one by one, also receive result. 
-sql client: TBD

-mini spatialDB Server: revieve string only, need a parser to parse the 5 queries(drop table, create table, insert, delete, select).

-mini spatialDB: 1. two attribute query(parallelize), 
                 2. spatial query only(),
                 
                 

#Rtree implementation
-serial implementation: https://github.com/nushoin/RTree

-execution mode: 1.parallel check 2nd attribute in the tree search process.
                 2.store all row id into a data structure and sort afterwards, parallelize scan process again. 
