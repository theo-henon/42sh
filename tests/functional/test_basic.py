import pytest

from shell_script import ShellScript

def get_test_parameters(filename):
    return [
            (filename, "string"),
            (filename, "file"),
            (filename, "stdin")
    ]

def assert_cmd(filename, input_type):
    script = ShellScript(filename)
    if input_type == "string":
        script.exec_from_string()
    elif input_type == "file":
        script.exec_from_file()
    elif input_type == "stdin":
        script.exec_from_stdin()


@pytest.mark.parametrize("filename,input_type", get_test_parameters("empty.sh"))
def test_empty(filename, input_type):
    assert_cmd(filename, input_type)

