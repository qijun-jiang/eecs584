# eecs584

#compile and execution

- server compile command: g++ server.cpp executor.cpp parser.cpp -o server -fopenmp -std=c++11

- server execute command: ./server -l load_file

Example: ./server -l sql/load_test_int.sql

- change parallel exucution mode in RTree.h,  comment the one not needed:
  //SearchContain(m_root, &rect, foundCount, a_resultCallback, a_context, a_context_size);
  //ParallelSearchContain(m_root, &rect, foundCount, a_resultCallback, a_context, a_context_size);
  P2PSearchContain(m_root, &rect, foundCount, a_resultCallback, a_context, a_context_size);



- client compile commnad: g++ client.cpp -o client -std=c++11

- client execute command: ./client -s hostname:portname -q search_file

Example: ./client -s beyster111.engin.umich.edu:17284 -q sql/search_test_int.sql

- generate load data for server compile command: g++ genLoad.cpp -o genload  -std=c++11 
- generate load data for server execute command: ./genload
- sql/load_N10M.sql will be generated with 10M insert operation in it.

- generate search data for client compile command: g++ genSearch -o gensearch -std=c++11
- generate search data for client execute command: ./gensearch [number of query] [percentage of search area] [percetage of selectivity]
Example: ./gensearch 1000 5 30


#Mysql source code load
output: load.sql, search.sql

usage: mysql -u root 584test -p

password

source /home/ianzyc/Desktop/load.sql
source /home/ianzyc/Desktop/search.sql

source /home/zhizhong/Desktop/eecs584/eecs584/load.sql

create index:
ALTER TABLE gis ADD SPATIAL INDEX(g);

# project design:


-server:

data structure: table(consists of (1)array of rows and (2) rtree index) (3) string map

row contains(rectangle and attribute)

rtree index

string map maps string to double

-parser: 
parse the 5 queries(drop table, create table, insert, delete, select)

return a struct

{query type, table name, rectangle, spatial function(intersect/ contain),
  attribute(as double), compare operator}

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
-serial legacy implementation: https://github.com/nushoin/RTree

-execution plan: 1.parallel check 2nd attribute in the tree search process.
                 2.store all row id into a data structure and sort afterwards, parallelize scan process again. 
