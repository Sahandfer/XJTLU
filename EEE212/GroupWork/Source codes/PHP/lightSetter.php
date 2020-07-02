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

$lightNum= $_GET['lightNum'];
$status= $_GET['status'];

$query= "UPDATE `lightStatus` SET ".$lightNum."= '$status'";
echo  "UPDATE `lightStatus` SET ".$lightNum."= '$status'";

$res = mysqli_query($conn, $query);

?>