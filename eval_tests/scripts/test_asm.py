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


def get_files(path):
    list = []
    list = os.listdir(path)
    return list


def print_failed_files(failed_error_files, failed_valid_files):
    print(bcolors.WARNING + "FAILED ERROR_FILES:" + bcolors.ENDC)
    for file in failed_error_files:
        print(file)
    print(bcolors.WARNING + "FAILED VALID_FILES:" + bcolors.ENDC)
    for file in failed_valid_files:
        print(file)


def run_error_files(program, path_to_files, file_array):
    failed_files = []
    for file in file_array:
        exit_status = os.system(program + " " + path_to_files + file)
        if exit_status == 0:
            failed_files.append(file)
    return failed_files

def run_valid_files(program, path_to_files, file_array):
    failed_files = []
    for file in file_array:
        exit_status = os.system(program + " " + path_to_files + file)
        if exit_status != 0:
            failed_files.append(file)
    return failed_files


def main():
    work_dir = get_path()

    # Path to asm executable
    asm = work_dir + "asm/asm"

    # Path to test files
    path_error_files = work_dir + "eval_tests/tests/error_files/"
    path_valid_files = work_dir + "eval_tests/tests/valid_files/"

    error_files_arr = get_files(path_error_files)
    valid_files_arr = get_files(path_valid_files)

    error_files_arr = []
    valid_files_arr = []
    failed_error_files = []
    failed_valid_files = []

    error_files_arr = get_files(path_error_files)
    valid_files_arr = get_files(path_valid_files)

    failed_error_files = run_error_files(asm, path_error_files, error_files_arr)
    failed_valid_files = run_valid_files(asm, path_valid_files, valid_files_arr)

    print_failed_files(failed_error_files, failed_valid_files)

if __name__ == "__main__":
    main()
