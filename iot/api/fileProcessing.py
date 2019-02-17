import time
#from time import sleep
from datetime import datetime

def lcdFetch():
    #get current time
    currentTime = datetime.now().strftime('%d-%m-%Y %H:%M:%S')
    
    #tick count
    with open("tick.txt") as tick:
        second = tick.read()
        second = int(second)

        if second >= 0:
            second = second + 1

    with open("tick.txt", 'w') as tickWrite:
        tickWrite.write(str(second))

    #get the lastest value from the LCD
    with open("LCD.txt") as file:
        i = file.read()
        
        listGetValue = i.split(",")

        temperature = str(listGetValue[-4])
        brightness = str(listGetValue[-3])
        lightStatus = str(listGetValue[-2])
        newLine = str(listGetValue[-1])

    #TEXT file
    with open("output.txt", 'w') as outputTXT:
        outputTXT.write(currentTime + "," + temperature + "," + brightness + "," + lightStatus + newLine)

    #JSON file
    with open("output.json", 'w') as outputJSON:
        outputJSON.write(
            "{" + "\"TimeStamp\" : " + "\"" + currentTime + "\"" + ", " +
                        "\"Temperature\" : " + temperature + ", " + 
                        "\"Brightness\" : " + brightness + ", " +
                        "\"LightStatus\" : " + "\"" + lightStatus + "\"" + 
                        "}"
                        )

while True:
    lcdFetch()

    #delay for 1 second
    time.sleep(1)
