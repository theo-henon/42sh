import os
import subprocess
import sys

import config

class ShellScript():
    def __init__(self, filename):
        self.filename = os.path.join(config.SCRIPTS_DIR, filename)
        self.content = self.__read_script()

    def __read_script(self):
        file = open(self.filename)
        content = file.read()
        return content

    def exec_from_string(self):
        ref_args = config.REFSH_STRINPUT.copy()
        ref_args.append(self.content)
        ref_out = subprocess.run(ref_args, subprocess.PIPE)

        args = config.SH_STRINPUT.copy()
        args.append(self.content)
        out = subprocess.run(args, subprocess.PIPE)

        assert ref_out.stdout == out.stdout
        assert ref_out.returncode == out.returncode

    def exec_from_file(self):
        ref_args = config.REFSH_FILEINPUT.copy()
        ref_args.append(self.filename)
        ref_out = subprocess.run(ref_args, subprocess.PIPE)

        args = config.SH_FILEINPUT.copy()
        args.append(self.filename)
        out = subprocess.run(args, subprocess.PIPE)

        assert ref_out.stdout == out.stdout 
        assert ref_out.returncode == out.returncode


    def exec_from_stdin(self):
        encoded_content = self.content.encode()
        ref_p = subprocess.Popen(config.REFSH_FILEINPUT, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        ref_stdout = ref_p.communicate(input=encoded_content)[0]
        
        p = subprocess.Popen(config.SH_FILEINPUT, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout = p.communicate(input=encoded_content)[0]

        assert ref_stdout == stdout 
        assert ref_p.returncode == p.returncode