#!/usr/bin/python
import subprocess
import os

if __name__ == '__main__':
	try:
		i = 0
		j = 16
		while (j <= 65536):
			print("aaaa")
			string = "./servidor " + str((4100 + i)) + " " + str(j) + " & sleep 1s && ./cliente 127.0.0.1 " + str((4100 + i)) + " 3MB.txt " + str(j)
			print("aaaa")
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		while (j <= 65536):
			string = "./servidor " + str((4100 + i)) + " " + str(j) + " & sleep 1s && ./cliente 127.0.0.1 " + str((4100 + i)) + " 9MB.txt " + str(j)
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		while (j <= 65536):
			string = "./servidor " + str((4100 + i)) + " " + str(j) + " & sleep 1s && ./cliente 127.0.0.1 " + str((4100 + i)) + " 18MB.txt " + str(j)
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		while (j <= 65536):
			string = "./servidor " + str((4100 + i)) + " " + str(j) + " & sleep 1s && ./cliente 127.0.0.1 " + str((4100 + i)) + " 36MB.txt " + str(j)
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
	except:
		print ("Erro")

