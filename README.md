# eecs584

output: load.sql, search.sql

usage: mysql -u root 584test -p

password

source /home/ianzyc/Desktop/load.sql
source /home/ianzyc/Desktop/search.sql

source /home/zhizhong/Desktop/eecs584/eecs584/load.sql

create index:
ALTER TABLE gis ADD SPATIAL INDEX(g);






server-client:

-mini spatialdb client: client is only in charge of reading queries from file, and send it to server one by one, also receive result. 
-sql client: TBD

-mini spatialDB Server: revieve string only, need a parser to parse the 5 queries(drop table, create table, insert, delete, select).

-mini spatialDB: 1. two attribute query(parallelize), 
                 2. spatial query only(),