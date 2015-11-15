<?php
$pdo = new PDO('mysql:host=localhost;dbname=584test', 'root', 'northern');
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

$sqlhandle = fopen("search.sql", "r");

if ($sqlhandle) {
        $starttime = microtime(true);
        while (($sql = fgets($sqlhandle, 4096)) !== false) {
                $stmt = $pdo->exec($sql);
                echo $stmt."\n";
        }
        if (!feof($sqlhandle)) {
                echo "Error: unexpected fgets() fail\n";
        }
        //$sql="CREATE TABLE test5 (x int, y int);";
        //$stmt = $pdo->exec($sql);
        $endtime = microtime(true);
        fclose($sqlhandle);
        $timediff = $endtime - $starttime;
        echo $timediff."\n";
}


