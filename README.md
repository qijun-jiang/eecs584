# eecs584

output: load.sql, search.sql

usage: mysql -u root 584test -p

password

source /home/ianzyc/Desktop/load.sql
source /home/ianzyc/Desktop/search.sql

source /home/zhizhong/Desktop/eecs584/eecs584/load.sql

create index:
ALTER TABLE gis ADD SPATIAL INDEX(g);