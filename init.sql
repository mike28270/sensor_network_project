CREATE USER 'admin'@'localhost' IDENTIFIED BY 'admin';
CREATE USER 'admin'@'%' IDENTIFIED BY 'admin';
GRANT ALL PRIVILEGES ON * . * TO 'admin'@'localhost';
GRANT ALL PRIVILEGES ON * . * TO 'admin'@'%';
FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS sensornetwork;
USE sensornetwork;

CREATE TABLE IF NOT EXISTS LED(rid SERIAL, did INT, date DATE , time TIME, value INT);
CREATE TABLE IF NOT EXISTS finger(rid SERIAL, date DATE , time TIME, value INT);