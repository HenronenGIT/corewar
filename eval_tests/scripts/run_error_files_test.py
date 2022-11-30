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


# FNULL = open(os.devnull, 'w')    #use this if you want to suppress output to stdout from the subprocess
executable = "/Users/hmaronen/workspace/github/corewar/asm/asm"
filename = "/Users/hmaronen/workspace/github/corewar/test.s"
exit_status = 0

# Path to Corewar folder
corewar_path = "/Users/hmaronen/workspace/github/corewar/"
# Path to test folder
error_files = corewar_path + "eval_tests/tests/error_files/"



file_list = os.listdir(error_files)
# print(dir_list)
# print(dir_list[0])

failed_files = []
for file in file_list:
	exit_status = os.system(executable + " " + error_files + file)
	if exit_status == 0:
		failed_files.append(file)
		print(file)

print(bcolors.WARNING + "FAILED FILES:" + bcolors.ENDC)
for file in failed_files:
	print(file)

# exit_status = os.system(executable + " " + filename)

#if exit status == 0, everything went well.
