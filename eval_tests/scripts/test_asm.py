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

# Leave empty if in root of repo
path_asm = ''
# Paths to your invalid files and valid files
invalidFiles_path = 'eval_tests/tests/error_files/'
validFiles_path = 'eval_tests/tests/valid_files/'

def main():
	#Paths
	workDir = get_path()
	path_errors = workDir + invalidFiles_path 
	asm = workDir + path_asm + 'asm'
	path_valid = workDir + validFiles_path

	invalid_files_arr = get_files(path_errors)
	valid_files_arr = get_files(path_valid)

	failed_invalid_files = run_error_files(asm, invalid_files_arr)
	failed_valid_files = run_valid_files(asm, valid_files_arr)

	print_failed_files(failed_invalid_files, failed_valid_files)

	save_to_file(failed_invalid_files, "invalid_file_fails.txt")
	save_to_file(failed_valid_files, "valid_file_fails.txt")
	print()
	print(f"{bcolors.OKBLUE}Failed files saved to:{bcolors.ENDC}\ninvalid_file_fails.txt\nvalid_file_fails.txt")

# If file is failed, it is saved to this ibject
class failedFile():
    def __init__(self, file, output, exitCode):
        self.file = file
        self.output = output
        self.exitCode = exitCode

def get_path():
	current_dir = os.path.abspath(os.getcwd())
	current_dir += '/'
	return current_dir

def get_files(path):
	list = []
	temp = ""
	i = 0
	list = os.listdir(path)
	for file in list:
		temp = path + file
		list[i] = temp
		i += 1
	return list

def print_array(array):
	i = 0
	for obj in array:
		print(f"{bcolors.OKCYAN}[{i}]{bcolors.ENDC}")
		print(f"{bcolors.FAIL}FILE:{bcolors.ENDC} {obj.file}")
		print(f"{bcolors.FAIL}OUTPUT:{bcolors.ENDC} {obj.output}")
		print(f"{bcolors.FAIL}EXIT CODE:{bcolors.ENDC} {obj.exitCode}")
		print("")
		i += 1

def run_error_files(program, file_array):
	
	failed_files = []
	output = ""
	print(f"{bcolors.OKBLUE}----INVALID FILES----{bcolors.ENDC}")
	for file in file_array:
		print(f"Testing with: {os.path.basename(file)}")
		output = subprocess.run([program, file], capture_output=True)
		if output.returncode == 0:
			failed_files.append(failedFile(file, output.stdout.decode('utf-8'), output.returncode))
			print(f"{bcolors.FAIL}FAIL{bcolors.ENDC}")
		else:
			print(f"{bcolors.OKGREEN}OK{bcolors.ENDC}")
	return failed_files

def run_valid_files(program, file_array):
	failed_files = []
	print(f"{bcolors.OKBLUE}----VALID FILES----{bcolors.ENDC}")
	for file in file_array:
		print(f"Testing with: {os.path.basename(file)}")
		output = subprocess.run([program, file], capture_output=True)
		if output.returncode != 0:
			failed_files.append(failedFile(file, output.stdout.decode('utf-8'), output.returncode))
			print(f"{bcolors.FAIL}FAIL{bcolors.ENDC}")
		else:
			print(f"{bcolors.OKGREEN}OK{bcolors.ENDC}")
	return failed_files

def print_failed_files(failed_error_files, failed_valid_files):
	print(f"{bcolors.YELLOW}FAILED {bcolors.UNDERLINE}INVALID{bcolors.ENDC} {bcolors.YELLOW}FILES:{bcolors.ENDC}")
	if len(failed_error_files) == 0:
		print(f"{bcolors.OKGREEN}ALL INVALID FILES PASSED {bcolors.ENDC}")
	else:
		print_array(failed_error_files)

	print(f"{bcolors.YELLOW}FAILED {bcolors.UNDERLINE}VALID{bcolors.ENDC} {bcolors.YELLOW}FILES:{bcolors.ENDC}")
	if len(failed_valid_files) == 0:
		print(f"{bcolors.OKGREEN}ALL VALID FILES PASSED {bcolors.ENDC}")
	else:
		print_array(failed_valid_files)

def save_to_file(array, filename):
	i = 0
	original_stdout = sys.stdout
	with open(filename, 'w') as f:
		sys.stdout = f
		for obj in array:
			print(f"[{i}]")
			print(f"File:{os.path.basename(obj.file)}")
			print(f"Output:{obj.output}")
			print("----------")
			i += 1
		sys.stdout = original_stdout # Reset the standard

if __name__ == "__main__":
	main()
