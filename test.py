#!/usr/bin/python
import subprocess
import os

if __name__ == '__main__':
	try:
		arquivo = "dados.txt"
		i = 0
		j = 16
		subprocess.call('echo "3mb FILE --------------------------------------------------------------------------" >> ' + arquivo, shell = True)
		print ("Analisando arquivo de 3 mb ...")
		while (j <= 65536):
			string = "./servidor " + str((4100 + i)) + " " + str(j) + " > /dev/null & sleep 1s && ./cliente 127.0.0.1 " + str((4100 + i)) + " 3MB.txt " + str(j) + " | grep kbps >> " + arquivo
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		subprocess.call('echo "9mb FILE --------------------------------------------------------------------------" >> ' + arquivo, shell = True)
		print ("Analisando arquivo de 9 mb ...")
		while (j <= 65536):
			string = "./servidor " + str((4200 + i)) + " " + str(j) + " > /dev/null & sleep 1s && ./cliente 127.0.0.1 " + str((4200 + i)) + " 9MB.txt " + str(j) + " | grep kbps >> " + arquivo
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		subprocess.call('echo "18mb FILE --------------------------------------------------------------------------" >> ' + arquivo, shell = True)
		print ("Analisando arquivo de 18 mb ...")
		while (j <= 65536):
			string = "./servidor " + str((4300 + i)) + " " + str(j) + " > /dev/null & sleep 1s && ./cliente 127.0.0.1 " + str((4300 + i)) + " 18MB.txt " + str(j) + " | grep kbps >> " + arquivo
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		i = 0
		j = 16
		subprocess.call('echo "36mb FILE --------------------------------------------------------------------------" >> ' + arquivo, shell = True)
		print ("Analisando arquivo de 36 mb ...")
		while (j <= 65536):
			string = "./servidor " + str((4400 + i)) + " " + str(j) + " > /dev/null & sleep 1s && ./cliente 127.0.0.1 " + str((4400 + i)) + " 36MB.txt " + str(j) + " | grep kbps >> " + arquivo
			subprocess.call(string, shell = True)
			i = i +1
			j = j*2
		subprocess.call('echo "END FILE --------------------------------------------------------------------------" >> ' + arquivo, shell = True)
	except:
		print ("Erro")

