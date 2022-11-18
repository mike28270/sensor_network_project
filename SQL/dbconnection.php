<?php
$servername ="10.50.202.242"; // the IP address of your server
$username = "user04";
$password = "user04";
$dbname = "user04";
//server
// your user name to access the database
// your password to access the database
// the database which is already created on the
//$conn = new mysqli($servername ,$username ,$password ,$dbname) ;
$conn = new mysqli($servername, $username, $password, $dbname); //set up connection to the database on the server
if ( $conn->connect_error ) { // print out the error message if connection fails
  die ("Connection failed : ".$conn->connect_error) ;
}
else{echo "Database connection is successful.";} // print out the successful message if connection is successful.
  $conn->close(); // close the connection
?>
