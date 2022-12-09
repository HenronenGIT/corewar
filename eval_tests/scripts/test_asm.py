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

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKCYAN = '\033[96m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

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

def print_failed_files(failed_error_files, failed_valid_files):
	print(bcolors.WARNING + "FAILED ERROR_FILES:" + bcolors.ENDC)
	for obj in failed_error_files:
		# print("FAILED FILE:" + obj.file,"OUTPUT:" + obj.output, sep='\n')
		print(f"{bcolors.FAIL}FAILED FILE:{bcolors.ENDC} {obj.file}")
		print(f"{bcolors.FAIL}OUTPUT:{bcolors.ENDC} {obj.output}")
		print(f"{bcolors.FAIL}EXIT CODE:{bcolors.ENDC} {obj.exitCode}")
		print("")

	print(bcolors.WARNING + "FAILED VALID_FILES:" + bcolors.ENDC)
	for obj in failed_valid_files:
		print(f"{bcolors.FAIL}FAILED FILE:{bcolors.ENDC} {obj.file}")
		print(f"{bcolors.FAIL}OUTPUT:{bcolors.ENDC} {obj.output}")
		print(f"{bcolors.FAIL}EXIT CODE:{bcolors.ENDC} {obj.exitCode}")


def run_error_files(program, file_array):
	failed_files = []
	output = ""
	for file in file_array:
		output = subprocess.run([program, file], capture_output=True)
		if output.returncode == 0:
			failed_files.append(failedFile(file, output.stdout.decode('utf-8'), output.returncode))
	return failed_files

def run_valid_files(program, file_array):
	failed_files = []
	for file in file_array:
		output = subprocess.run([program, file], capture_output=True)
		if output.returncode != 0:
			failed_files.append(failedFile(file, output.stdout.decode('utf-8'), output.returncode))
	return failed_files


def main():
	#Paths
	workDir = get_path()
	asm = workDir + "asm/asm" #<------ EDIT THIS
	path_errors = workDir + "eval_tests/tests/error_files/" #<---- Path to error files
	path_valid = workDir + "eval_tests/tests/valid_files/" #<---- Path to valid files

	error_files_arr = get_files(path_errors)
	valid_files_arr = get_files(path_valid)

	failed_invalid_files = run_error_files(asm, error_files_arr)
	failed_valid_files = run_valid_files(asm, valid_files_arr)

	print_failed_files(failed_invalid_files, failed_valid_files)

if __name__ == "__main__":
	main()
