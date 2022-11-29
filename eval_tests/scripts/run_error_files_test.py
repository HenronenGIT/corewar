import subprocess
import os

# FNULL = open(os.devnull, 'w')    #use this if you want to suppress output to stdout from the subprocess
executable = "/Users/hmaronen/workspace/github/corewar/asm/asm"
filename = "/Users/hmaronen/workspace/github/corewar/test.s"
exit_status = 0

exit_status = os.system(executable + " " + filename)

#if exit status == 0, everything went well.
