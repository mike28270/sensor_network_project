<?php
$servername = "34.91.33.123";
//$servername = "localhost";
$username = "admin";
$password = "admin";
$dbname = "sensornetwork";
$port = 3306;
//server
// your user name to access the database
// your password to access the database
// the database which is already created on the
//$conn = new mysqli($servername ,$username ,$password ,$dbname) ;
echo "Connecting to database...";
$conn = new mysqli($servername, $username, $password, $dbname,  $port); //set up connection to the database on the server
if ( $conn->connect_error ) { // print out the error message if connection fails
  die ("Connection failed : ".$conn->connect_error) ;
}
else{echo "Database connection is successful.";} // print out the successful message if connection is successful.
//  $conn->close(); // close the connection
?>
