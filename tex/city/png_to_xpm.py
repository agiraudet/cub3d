import os
import subprocess
import sys

for file in sys.argv:
    if file == sys.argv[0]:
        continue
    subprocess.run(["convert", file, file[:-4] + '.xpm'])
