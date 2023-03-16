import os

# function to generate the Makefile
def generate_makefile(folder):
    # get a list of all the .c files in the folder
    c_files = [f for f in os.listdir(folder) if f.endswith('.c')]

    # open the Makefile for writing
    with open('Makefile', 'w') as f:
        # write the default target
        f.write('all: ' + ' '.join([os.path.splitext(f)[0] for f in c_files]) + '\n\n')

        # write a target for each .c file
        for c_file in c_files:
            target = os.path.splitext(c_file)[0]
            f.write(target + ': ' + c_file + '\n')
            f.write('\tgcc -Wall -o ' + target + ' ' + c_file + '\n\n')

        # write the clean target
        f.write('clean:\n\trm -f ' + ' '.join([os.path.splitext(f)[0] for f in c_files]) + '\n')

    print('Makefile generated successfully!')

    # compile and run the Makefile
    os.system('make')
    os.system('./' + os.path.splitext(c_files[0])[0])

# ask the user for the folder name
folder = "D:\\odevler\\bruh"

# generate the Makefile and compile/run it
generate_makefile(folder)

