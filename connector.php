<?php
$pdo = new PDO('mysql:host=35.2.112.23;dbname=584test', 'root', '110110');
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$sql="CREATE TABLE test2 (x int, y int);";
$stmt = $pdo->exec($sql);
echo $stmt;

