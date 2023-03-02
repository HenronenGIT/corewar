# corewar, the final project
![image](https://user-images.githubusercontent.com/58331418/222431336-818401a1-05c1-4db1-9832-82bfa9376a24.png)


This is the README to the final project of Hive Helsinki algorithm branch. Our corewar team consisted of 4 people:

[Henri Maronen](https://github.com/HenronenGIT)

[Otto Koponen](https://github.com/ottkopo)

[William Donnelly](https://github.com/wsdonnelly)

[Anton Kilk](https://github.com/AntonKilk)


## corewar

Corewar is a multiplayer game, where champions fight for memory in a virtual arena. The winner of the game is the last champion to have played the live statement. For this project 2 parts needed to be created. First the assembler that would take a file of instructions and convert that file into bytecode that is readable by the virtual machine. The second part was the virtual machine which would take the champions and create the arena where the champions will fight to the death. After that the VM is able to execute instructions from all the champions according to the game rules.

## Assembler

The assmebler was worked on by Otto and Henri. The purpose of the Assembler was to take a champion file and convert it to bytecode. It was basically a simplified compiler. We had divided the work into 2 parts, where Henri would work on parsing and analyzing the original input file and converting the values in that file into a structure that was then taken by Otto. Otto would convert the values from that structure into that final bytecode and print that information into a file.


## Virtual Machine 
Coming soon...


## How to try it out?

1. Clone the repository

2. In the root of the repository do ``make`` or ``make asm`` and ``make vm``

3. First you need to run the assembler to create some files for the VM. Files can be found in eval_tests/champs/valid_files

4. Create 4 different champions by running this command 4 times: ``./asm eval_tests/champs/valid_files/*any file you want*``
  - this should create 4 different .cor files in the eval_tests/champs/valid_files folder
  - NOTE: you can also move 4 files from eval_tests/champs/valid_files/ to the root of the repository and just run those 4 files from there with ``./asm file_name.s``. Might be a bit faster.
  
5. run the 4 .cor files with the vm using ``./vm eval_tests/champs/valid_files/*file1.cor* eval_tests/champs/valid_files/*file2.cor* eval_tests/champs/valid_files/*file3.cor* eval_tests/champs/valid_files/*file4.cor*``


## Test out some of our scripts:

``make valid``: Uses a reference asm provided to us by Hive to create .cor files and after that creates a .cor file with our assembler from the same source and diffs the 2 .cor files that were produced.

``make invalid``: Runs our assembler with all files from eval_tests/champs/error_files and checks that none seg fault and that they produce an error message.

More coming soon...
