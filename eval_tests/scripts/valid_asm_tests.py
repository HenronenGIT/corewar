# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valid_asm_tests.py                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmaronen <hmaronen@student.hive.fi>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 10:10:20 by hmaronen          #+#    #+#              #
#    Updated: 2022/12/09 10:10:21 by hmaronen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import subprocess
import sys
import logging

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKCYAN = '\033[96m'
	OKGREEN = '\033[92m'
	YELLOW = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'
	GREY = '\x1b[38;20m'

# 1. Leave empty if in root of repo
path_asm = ''
# 2. Path to Reference program
path_asm_ref = 'eval_tests/asm_ref'
# 3. Path to test files
path = 'eval_tests/tests/valid_files/'

def main():
	if not os.path.exists('eval_tests/failed_our/'):
		os.mkdir('eval_tests/failed_our/')
	if not os.path.exists('eval_tests/failed_ref/'):
		os.mkdir('eval_tests/failed_ref/')
	#Paths
	workDir = get_path()
	asm = f"{workDir}{path_asm}asm"
	asm_ref = f'{workDir}{path_asm_ref}'
	pathFiles = f"{workDir}{path}"

	# Fetch all the files from test folder
	filesArr = get_files(pathFiles)

	# Test every single file one by one
	for file in filesArr:
		testFile(file, asm, asm_ref)


def get_path():
	current_dir = os.path.abspath(os.getcwd())
	current_dir += '/'
	return current_dir

def get_files(path):
	list = []
	temp = ""
	list = os.listdir(path)
	for i, file in enumerate(list):
		temp = f"{path}{file}"
		list[i] = temp
	return list

def testFile(testFile, asm, asm_ref):
	print(f"{bcolors.HEADER}TESTING WITH:{bcolors.ENDC} {os.path.basename(testFile)} ", end='')
	runFile(asm_ref, testFile, True)
	runFile(asm, testFile, False)

	testFile = os.path.basename(testFile)
	failedFile = testFile.replace('.s', '.txt')

	output = subprocess.run(['diff', 'ref.txt', 'our.txt'], capture_output=True)
	if len(output.stdout) != 0:
		print(f"{bcolors.YELLOW}DIFF{bcolors.ENDC}")
		status = subprocess.call(f'cp our.txt eval_tests/failed_our/our_{failedFile}', shell=True) 
		status = subprocess.call(f'cp ref.txt eval_tests/failed_ref/ref_{failedFile}', shell=True) 
	else:
		print(f"{bcolors.OKGREEN}OK{bcolors.ENDC}")

def change_extension(file):
	changed_str = file.replace('.s', '.cor')
	return changed_str

def runFile(program, testFile, is_refProgram):
	outputFile = 'ref.txt' if is_refProgram else 'our.txt'
	corExtension = change_extension(testFile)
	corFile = os.path.basename(corExtension)

	output = subprocess.run([program, testFile], capture_output=True)
	if is_refProgram == False:
		if output.returncode != 0:
			print(f"{bcolors.FAIL}FAIL - File did not compile{bcolors.ENDC}")
	output = subprocess.run(['xxd', corExtension], capture_output=True)

	with open(outputFile, 'w') as file:
		file.write(output.stdout.decode('utf-8'))
	output = subprocess.run(['rm', corExtension], capture_output=True)

if __name__ == "__main__":
	main()
