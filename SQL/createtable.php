<?php
$servername ="10.50.202.242"; // the IP address of your server
$username = "user04"; // your user name to access the database
$password = "user04"; // your password to access the database
$dbname = "user04"; // the database which is already created on the server
$conn = new mysqli( $servername , $username , $password , $dbname ); //set up connection to the database on the server
if ( $conn->connect_error ) { // print out the error message if connection fails
die ( "Connection failed : ".$conn->connect_error ); 
}
else{echo "Database connection is successful.";} // print out the successful message if connection is successful.
$sql = "CREATE TABLE IF NOT EXISTS temperature(rid SERIAL, did INT, date DATE , time TIME, temperature FLOAT)"; // create a table called temperature
if ($conn->query($sql) === TRUE) { //use this SQL to query the databse 
    echo "New table created successfully";
} else {
echo "Error: " . $sql . "<br>" . $conn->error; // print out the error
//message if the query fails
}
$conn->close(); // close the connection

$sql = "INSERT INTO temperature (did, date, time, temperature) VALUES ('$did', CURRENT_DATE(), CURRENT_TIME(), '$temperature')"; // insert data into temperature table
if ($conn ->query($sql) === TRUE) {
    echo "New record created successfully";
    } else {
    echo "Error: " . $sql . "<br>" . $conn->error;
    }
?>
