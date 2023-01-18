# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    invalid_asm_tests.py                               :+:      :+:    :+:    #
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

# If file is failed, it is saved to this object
class failedFile():
    def __init__(self, file, output, exitCode, refOutput):
        self.file = file
        self.output = output
        self.exitCode = exitCode
        self.refOutput = refOutput
SEGFAULT = "segmentation fault"
SEG = -11

invalidFiles_path = 'eval_tests/champs/error_files/'

# Leave empty if in root of repo
path_asm = ''
path_asm_ref = 'eval_tests/asm_ref'
# Paths to your invalid files and valid files

def main():
	#Paths
	workDir = get_path()
	path_errors = workDir + invalidFiles_path 
	asm = f"{workDir}{path_asm}asm"
	asm_ref = f'{workDir}{path_asm_ref}'

	invalidFiles = get_files(path_errors)

	failedFiles = runFiles(asm, invalidFiles, asm_ref)

	print_failed_files(failedFiles)

	save_to_file(failedFiles, "invalid_file_fails.txt")

def get_path():
	current_dir = os.path.abspath(os.getcwd())
	current_dir += '/'
	return current_dir

def get_files(path):
	files = []
	temp = ""
	i = 0
	files = os.listdir(path)
	for file in files:
		temp = path + file
		files[i] = temp
		i += 1
	return files

def print_array(array):
	i = 0
	for obj in array:
		print(f"{bcolors.OKCYAN}[{i}]{bcolors.ENDC}")
		print(f"{bcolors.YELLOW}FILE:{bcolors.ENDC} {obj.file}")
		print(f"{bcolors.YELLOW}EXIT CODE:{bcolors.ENDC} {obj.exitCode}")
		print(f"{bcolors.YELLOW}OUTPUT:{bcolors.ENDC} {obj.output}")
		print(f"{bcolors.YELLOW}REF OUTPUT:{bcolors.ENDC} {obj.refOutput}")
		print("")
		i += 1

def runFiles(program: str, files: list, ref_program: str):
	failed_files = []
	output = ""
	for file in files:
		fileName = os.path.basename(file).strip()
		print(f"{bcolors.HEADER}TEST FILE:{bcolors.ENDC} [{fileName}] ", end='')
		output = subprocess.run([program, file], capture_output=True)
		ref_output = subprocess.run([ref_program, file], capture_output=True)
		# print(output)
		if not output.stdout.decode('utf-8') and not output.stderr.decode('utf-8'):
			failed_files.append(failedFile(
				file,
				output.stdout.decode('utf-8'),
				output.returncode,
				ref_output.stdout.decode('utf-8')))
		# 	print(f"{bcolors.FAIL}SEGFAULT{bcolors.ENDC}")
		# elif output.returncode != 0:
		else:
			print(f"{bcolors.OKGREEN}OK{bcolors.ENDC}")
		# else:
		# 	print(f"{bcolors.FAIL}FAIL - file compiled{bcolors.ENDC}")
				
		print(f"{bcolors.HEADER}OUTPUT:{bcolors.ENDC}{output.stdout.decode('utf-8')}")
		output = subprocess.run([ref_program, file], capture_output=True)
		print(f"{bcolors.HEADER}REF OUTPUT:{bcolors.ENDC}{output.stdout.decode('utf-8')}")
		print('----------------------------')
		
	return failed_files

def print_failed_files(failedFiles: list):
	failedFilesCount = len(failedFiles)
	if failedFilesCount == 0:
		print(f"{bcolors.OKGREEN}~~~~~~~~~~~ ALL INVALID FILES PASSED ~~~~~~~~~~~{bcolors.ENDC}")
	else:
		print(f'{bcolors.HEADER}FAILED FILE COUNT:{bcolors.ENDC}')
		print(failedFilesCount)
		print_array(failedFiles)
		print(f"{bcolors.YELLOW}FAILED FILES SAVED TO:{bcolors.ENDC}\ninvalid_file_fails.txt")

def save_to_file(failedFiles: list, filename: str):
	i = 0
	original_stdout = sys.stdout
	with open(filename, 'w') as f:
		sys.stdout = f
		for obj in failedFiles:
			print(f"[{i}]")
			print(f"File:{os.path.basename(obj.file)}")
			print(f"Output:{obj.output}")
			print("----------")
			i += 1
		sys.stdout = original_stdout # Reset the standard
	

if __name__ == "__main__":
	main()
