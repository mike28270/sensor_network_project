import mysql.connector

class connectMysql:
    def __init__(self, host, port, username, password, database):
        self.conn = mysql.connector.connect(
            host=host, port=port,
            user=username, password=password,
            database=database
            )
        self.mycursor = self.conn.cursor()
    
    def insertTable(self, query):
        self.mycursor.execute(query)
        self.conn.commit()
        return query

    def insertLED(self, id, value):
        query = f"INSERT INTO LED (did, date, time, value) VALUES ('{id}', CURRENT_DATE(), CURRENT_TIME(), {value})"
        query = self.insertTable(query)
        return query

    def insertAngle(self, value):
        query = f"INSERT INTO servo (date, time, value) VALUES (CURRENT_DATE(), CURRENT_TIME(), {value})"
        query = self.insertTable(query)
        return query

    def insertFinger(self, value):
        query = f"INSERT INTO finger (date, time, value) VALUES (CURRENT_DATE(), CURRENT_TIME(), {value})"
        query = self.insertTable(query)
        return query

    def insertSensor(self, value):
        finger, led_r, led_b, led_g, servo_angle, servo_level = value
        query = (f"INSERT INTO sensor (date , time, finger, led_r, led_b, led_g, servo_angle, servo_level) "
                 f"VALUES (CURRENT_DATE(), CURRENT_TIME(), {finger}, {led_r}, {led_b}, {led_g}, {servo_angle}, {servo_level});")
        query = self.insertTable(query)
        return query