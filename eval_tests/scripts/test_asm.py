import os
import pathlib

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


def get_path():
	current_dir = os.path.abspath(os.getcwd())
	current_dir += '/'
	return current_dir

def main():
	work_dir = get_path()

	# Path to asm executable
	asm = work_dir + "asm/asm"

	# Path to test folder
	error_files = work_dir + "eval_tests/tests/error_files/"
	valid_files = work_dir + "eval_tests/tests/valid_files/"

	file_list_1 = os.listdir(error_files)
	file_list_2 = os.listdir(valid_files)
	failed_files_1 = []
	failed_files_2 = []

	# Test error_files and if return value is wrong, save that file.
	for file in file_list_1:
		exit_status = os.system(asm + " " + error_files + file)
		if exit_status == 0:
			failed_files_1.append(file)

	# Test valid_files and if return value is wrong, save that file.
	for file in file_list_2:
		exit_status = os.system(asm + " " + valid_files + file)
		# print(f"FILE: {file}")
		# print(f"EXII STATUS: {exit_status}")
		if exit_status != 0:
			failed_files_2.append(file)

	print(bcolors.WARNING + "FAILED ERROR_FILES:" + bcolors.ENDC)
	for file in failed_files_1:
		print(file)
	print(bcolors.WARNING + "FAILED VALID_FILES:" + bcolors.ENDC)
	for file in failed_files_2:
		print(file)


if __name__ == "__main__":
	main()