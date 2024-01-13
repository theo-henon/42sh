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

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo.sh"))
def test_echo(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_toto.sh"))
def test_echo_toto(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_true.sh"))
def test_echo_true(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_false.sh"))
def test_echo_false(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_multiple_args.sh"))
def test_echo_multiple_args(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_n_option.sh"))
def test_echo_n_option(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_e_option.sh"))
def test_echo_e_option(filename, input_type):
    assert_cmd(filename, input_type)

@pytest.mark.parametrize("filename,input_type", get_test_parameters("echo_E_option.sh"))
def test_echo_E_option(filename, input_type):
    assert_cmd(filename, input_type)