DROP TABLE gis1;
CREATE TABLE gis1 (g GEOMETRY NOT NULL, color INT, SPATIAL INDEX(g)) ENGINE=MyISAM;
INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 0 0, 2 0, 2 2, 0 2, 0 0 ))'), '1');
INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 5 5, 7 5, 7 7, 5 7, 5 5 ))'), '2');
INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 8 5, 9 5, 9 6, 8 6, 8 5 ))'), '3');
INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 7 1, 9 1, 9 2, 7 2, 7 1 ))'), '4');
INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 9.9 6.4, 91 6.4, 91 21, 9.9 21, 9.9 6.4 ))'), '5');