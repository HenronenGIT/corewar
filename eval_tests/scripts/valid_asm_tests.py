# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_asm.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+         #
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


def main():
	#Paths
	workDir = get_path()
	asm = f"{workDir}{path_asm}asm"
	pathFiles = f"{workDir}{path}"

	filesArr = get_files(pathFiles)
	for file in filesArr:
		testFile(file, asm, asm_ref)

def get_files(path):
	list = []
	temp = ""
	list = os.listdir(path)
	for i, file in enumerate(list):
		temp = f"{path}{file}"
		list[i] = temp
	return list

def testFile(testFile, asm, asm_ref):
	print(f"{bcolors.OKCYAN}TESTING WITH:{bcolors.ENDC} {os.path.basename(testFile)}")
	runFile(asm_ref, testFile, 'ref')
	runFile(asm, testFile, 'org')

	# print(f"{bcolors.GREY}Diffing the files{bcolors.ENDC}")
	output = subprocess.run(['diff', 'ref.txt', 'our.txt'], capture_output=True)
	if len(output.stdout) != 0:
		print(f"{bcolors.FAIL}FAIL{bcolors.ENDC}")
	else:
		print(f"{bcolors.OKGREEN}OK{bcolors.ENDC}")

def change_extension(file):
	changed_str = file.replace('.s', '.cor')
	return changed_str

# Leave empty if in root of repo
path_asm = ''
asm_ref = '/Users/hmaronen/workspace/github/corewar/eval_tests/asm'
# Paths to your invalid files and valid files
# invalidFiles_path = 'eval_tests/tests/error_files/'
path = 'eval_tests/tests/valid_files/'

def runFile(program, testFile, type):
	if type == 'ref':
		outputFile = 'ref.txt'
	else:
		outputFile = 'our.txt'
	corExtension = change_extension(testFile)
	corFile = os.path.basename(corExtension)

	output = subprocess.run([asm_ref, testFile], capture_output=True)
	subprocess.run(['mv', corExtension, './'])
	output = subprocess.run(['xxd', corFile], capture_output=True)

	with open(outputFile, 'w') as file:
		file.write(output.stdout.decode('utf-8'))
	output = subprocess.run(['rm', corFile], capture_output=True)

def get_path():
	current_dir = os.path.abspath(os.getcwd())
	current_dir += '/'
	return current_dir


if __name__ == "__main__":
	main()
