<?php
include "dbconnection.php";

$did = $_POST['did'];
$led_status = $_POST['led_status'];

$sql = "INSERT INTO LED (did, date, time, state) VALUES ('$did', CURRENT_DATE(), CURRENT_TIME(), $led_status)"; // insert data into temperature table
if ($conn ->query($sql) === TRUE) {
    echo "New record created successfully";
    } else {
    echo "Error: " . $sql . "<br>" . $conn->error;
    }
?>
