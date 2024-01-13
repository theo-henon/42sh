from os import getenv

REFSH_STRINPUT = ["bash", "--posix", "-c"]
REFSH_FILEINPUT = ["bash", "--posix"]
SH_STRINPUT = [getenv("EXE"), "-c"]
SH_FILEINPUT = [getenv("EXE")]
