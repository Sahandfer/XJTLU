<?php
$servername = "localhost";
$username = "id9384097_sahandsabour";
$password = "SAHANDsa2020";
$database = "id9384097_arduino";

$conn = new mysqli($servername, $username, $password);
if (!$conn) {
    die("Connection failed: " . $conn->connect_error);
}

mysqli_select_db($conn,$database) or die ("Couldn't find database!");
$query= "SELECT * FROM `lightStatus` WHERE appID='1'";

$res = mysqli_query($conn, $query);
while($row= mysqli_fetch_array($res)){
    $light1= $row['light1'];
    $light2= $row['light2'];
    $light3= $row['light3'];
    $lock= $row['doorlock'];
    echo $light1." ".$light2." ".$light3." ".$lock;
}

?>