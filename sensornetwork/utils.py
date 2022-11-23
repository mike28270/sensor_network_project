from serial.tools.list_ports import comports

def findFreePort(startwith='/dev/cu.usbmodem'):
    ports = [port for port in comports()]
    for port in ports:
        a_list = list(port)
        for item in a_list: 
            if item.startswith(startwith):
                result = item
                break
    return result