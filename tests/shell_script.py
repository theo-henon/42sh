import subprocess

import config

class ShellScript():
    def __init__(self, script_path):
        self.script_path = script_path
        self.content = self.__read_script()

    def __read_script(self):
        file = open(self.script_path)
        content = file.read()
        return content

    def __outdiff(self, ref_out, out):
        return f"Expected stdout content : {str(ref_out)}, but got: {str(out)}"
    
    def __codediff(self, refcode, code):
        return f"Expected exit code: {refcode}, but got exit code: {code}"

    def exec_from_string(self):
        ref_args = config.REFSH_STRINPUT.copy()
        ref_args.append(self.content)
        ref_out = subprocess.run(ref_args, stdout=subprocess.PIPE)

        args = config.SH_STRINPUT.copy()
        args.append(self.content)
        out = subprocess.run(args, stdout=subprocess.PIPE)

        if ref_out.stdout != out.stdout:
            raise AssertionError(self.__outdiff(ref_out.stdout, out.stdout))
        if ref_out.returncode != out.returncode:
            raise AssertionError(self.__codediff(ref_out.returncode, out.returncode))


    def exec_from_file(self):
        ref_args = config.REFSH_FILEINPUT.copy()
        ref_args.append(self.script_path)
        ref_out = subprocess.run(ref_args, stdout=subprocess.PIPE)

        args = config.SH_FILEINPUT.copy()
        args.append(self.script_path)
        out = subprocess.run(args, stdout=subprocess.PIPE)

        if ref_out.stdout != out.stdout:
            raise AssertionError(self.__outdiff(ref_out.stdout, out.stdout))
        if ref_out.returncode != out.returncode:
            raise AssertionError(self.__codediff(ref_out.returncode, out.returncode))


    def exec_from_stdin(self):
        encoded_content = self.content.encode()
        ref_p = subprocess.Popen(config.REFSH_FILEINPUT, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        ref_stdout = ref_p.communicate(input=encoded_content)[0]

        p = subprocess.Popen(config.SH_FILEINPUT, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout = p.communicate(input=encoded_content)[0]

        if ref_stdout != stdout:
            raise AssertionError(self.__outdiff(ref_stdout, stdout))
        if ref_p.returncode != p.returncode:
            raise AssertionError(self.__codediff(ref_p.returncode, p.returncode))
