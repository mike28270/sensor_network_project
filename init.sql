CREATE USER 'admin'@'localhost' IDENTIFIED BY 'sensor';
CREATE USER 'admin'@'%' IDENTIFIED BY 'sensor';
CREATE USER 'grafana'@'localhost' IDENTIFIED BY 'sensor';
CREATE USER 'grafana'@'%' IDENTIFIED BY 'sensor';
CREATE USER 'web'@'localhost' IDENTIFIED BY 'sensor';
CREATE USER 'web'@'%' IDENTIFIED BY 'sensor';
GRANT ALL PRIVILEGES ON * . * TO 'admin'@'localhost';
GRANT ALL PRIVILEGES ON * . * TO 'admin'@'%';
GRANT ALL PRIVILEGES ON * . * TO 'grafana'@'localhost';
GRANT ALL PRIVILEGES ON * . * TO 'grafana'@'%';
GRANT ALL PRIVILEGES ON * . * TO 'web'@'localhost';
GRANT ALL PRIVILEGES ON * . * TO 'web'@'%';
FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS sensornetwork;
USE sensornetwork;

-- CREATE TABLE IF NOT EXISTS LED(rid SERIAL, did INT, date DATE , time TIME, value INT);
-- CREATE TABLE IF NOT EXISTS finger(rid SERIAL, date DATE , time TIME, value INT);
-- CREATE TABLE IF NOT EXISTS servo(rid SERIAL, date DATE , time TIME, value INT);
CREATE TABLE IF NOT EXISTS sensor(eid SERIAL, date DATE , time TIME, finger INT, led_r INT, led_b INT, led_g INT, servo_angle INT, servo_level INT);

