DROP TABLE runtime;
CREATE TABLE runtime (time TIMESTAMP(3));
INSERT INTO runtime VALUES (CURRENT_TIMESTAMP(3));
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 35832.7 80654, 48080.2 80654, 48080.2 92901.5, 35832.7 92901.5, 35832.7 80654 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 61929.2 58196.5, 74176.7 58196.5, 74176.7 70443.9, 61929.2 70443.9, 61929.2 58196.5 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 42550.6 48790.8, 54798 48790.8, 54798 61038.2, 42550.6 61038.2, 42550.6 48790.8 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 47872.4 16744.3, 60119.9 16744.3, 60119.9 28991.7, 47872.4 28991.7, 47872.4 16744.3 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 43338.6 9264.53, 55586 9264.53, 55586 21512, 43338.6 21512, 43338.6 9264.53 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 87614.6 41440.5, 99862.1 41440.5, 99862.1 53688, 87614.6 53688, 87614.6 41440.5 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 5870.31 74704.6, 18117.8 74704.6, 18117.8 86952, 5870.31 86952, 5870.31 74704.6 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 66591.7 12596.2, 78839.2 12596.2, 78839.2 24843.7, 66591.7 24843.7, 66591.7 12596.2 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 70034 22392.9, 82281.5 22392.9, 82281.5 34640.4, 70034 34640.4, 70034 22392.9 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 69343 64179.8, 81590.5 64179.8, 81590.5 76427.2, 69343 76427.2, 69343 64179.8 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 10777.4 69112, 23024.8 69112, 23024.8 81359.5, 10777.4 81359.5, 10777.4 69112 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 76534.8 4.87013, 88782.2 4.87013, 88782.2 12252.3, 76534.8 12252.3, 76534.8 4.87013 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 55513.5 93853.2, 67761 93853.2, 67761 106101, 55513.5 106101, 55513.5 93853.2 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 16334.3 88436.7, 28581.7 88436.7, 28581.7 100684, 16334.3 100684, 16334.3 88436.7 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 7502.13 13687.6, 19749.6 13687.6, 19749.6 25935.1, 7502.13 25935.1, 7502.13 13687.6 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 93852.4 66421.3, 106100 66421.3, 106100 78668.7, 93852.4 78668.7, 93852.4 66421.3 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 57548.7 58444.5, 69796.2 58444.5, 69796.2 70691.9, 57548.7 70691.9, 57548.7 58444.5 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 63911 70651.1, 76158.5 70651.1, 76158.5 82898.5, 63911 82898.5, 63911 70651.1 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 7163.79 3112.87, 19411.2 3112.87, 19411.2 15360.3, 7163.79 15360.3, 7163.79 3112.87 ))'), g) AND val < '50';
SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 24630.3 58366, 36877.8 58366, 36877.8 70613.4, 24630.3 70613.4, 24630.3 58366 ))'), g) AND val < '50';
INSERT INTO runtime VALUES(CURRENT_TIMESTAMP(3));
SELECT * from runtime;