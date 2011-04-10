'''By the command line, we have to pass the following arguments:
   -> python wirelessSignalParser.py [filename] [interval time] [number of tests]
'''

import sys, time, commands

#Dictionary to match a given MAC address with its quality over time.
#It will receive a tuple, constituted by the average signal strength, as
#well as the number of tries.
macAddresses = { }

def main():
	
	#Makes the initial setup of the values.
	if (len(sys.argv) < 3):
		print "Too few arguments...\n python wirelessSignalParser.py [interval time] [number of tests]"
		sys.exit()	
	try:
		interval = int(sys.argv[1])
		noTries = int(sys.argv[2])
	except:
		print "Invalid arguments.\n python wirelessSignalParser.py [interval time] [number of tests]"
		sys.exit()
		

	#Performs the analyzes.
	for i in xrange(noTries):
		#Executes the iwlist command, so we can get new values for the signal
		#strength.
		print "Scanning the network..."
		outcome = commands.getoutput("iwlist wlan0 scan")
		print "Analyzing the file..."
		fileParser(outcome)
		
		
		#Won't sleep in the last iteration.
		if (i < noTries - 1):
			print "Waiting..."
			time.sleep(interval)
	
	#Now that we collected all the data, we have to print the average values.
	for i in macAddresses.keys():
		print i + ": " + str(round(macAddresses[i]*1.0/noTries, 2)) + " dBm"
			
	print "Operations finished."

#This function opens the file with the output of the iwlist command
#and parses its contents.
def fileParser(file):
	
	text = file.split("\n")
	
	for i in xrange(len(text)):
		line = text[i].lstrip().split(" ")
		
		#This is a new cell, we need to find the corresponding strength.
		if (line[0] == "Cell"):
			macAddr = line[4]
			#Performs calculations and saves the outcome.
			i, strength = findStrength(i, text)
			
			#Now, we have to save if this MAC address has already been
			#recorded or not yet.
			
			if macAddr in macAddresses:
				macAddresses[macAddr] += strength
			else:
				macAddresses[macAddr] = strength


def findStrength(lineNo, text):
	#Looks for the line which contains the sinal strength.
	while (text[lineNo].lstrip().split(" ")[0][:7] != "Quality"):
		lineNo += 1
		
	#This string will have the following format:
	#	level=n
	#where n is the signal strength.
	signalLevel = text[lineNo].lstrip().split(" ")[3]
		
	#Returns the line where we stopped, as well as the strength.
	return lineNo, int(signalLevel[6:])

if __name__ == "__main__":
	main()
