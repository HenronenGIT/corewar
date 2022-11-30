import subprocess
import os

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


def main():
	# Path to asm executable
	asm = "/Users/hmaronen/workspace/github/corewar/asm/asm"
	# Path to Corewar folder
	corewar_folder = "/Users/hmaronen/workspace/github/corewar/"
	# Path to test folder
	error_files = corewar_folder + "eval_tests/tests/error_files/"

	file_list = os.listdir(error_files)
	failed_files = []

	for file in file_list:
		exit_status = os.system(asm + " " + error_files + file)
		if exit_status == 0:
			failed_files.append(file)

	print(bcolors.WARNING + "FAILED FILES:" + bcolors.ENDC)
	for file in failed_files:
		print(file)

if __name__ == "__main__":
	main()