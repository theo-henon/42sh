from os import getenv

EXE = getenv("EXE")
REFSH_STRINPUT = ["bash", "--posix", "-c"]
REFSH_FILEINPUT = ["bash", "--posix"]
SH_STRINPUT = [EXE,  "-c"]
SH_FILEINPUT = [EXE]
