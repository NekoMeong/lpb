<!DOCTYPE html>
<html>
<body>

<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "alfit";

error_reporting(0);
ini_set('display_errors', true);

//$data = $_POST['file'];

$data = file_get_contents("php://input");
$data = str_replace("'", '"', $data);
$data = json_decode($data, true);
$data=preg_replace('/([^{,:])"(?![},:])/', "$1".'\''."$2",$data);
date_default_timezone_set("Asia/Jakarta");
$date = date("Y-m-d h:i:sa");
$ruang = $data['ruang'];
$Suhu = $data['Suhu'];
$Kelembaban = $data['Kelembaban'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}


$sql = "INSERT INTO sensor (suhu, kelembapan, ruang)
VALUES ('$Suhu','$Kelembaban','$ruang')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>



</body>
</html>