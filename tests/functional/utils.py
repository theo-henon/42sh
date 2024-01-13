def assert_cmd(cmd, input_type):
    if input_type == "string":
        cmd.exec_from_string()
    elif input_type == "file":
        cmd.exec_from_file()
    elif input_type == "stdin":
        cmd.exec_from_stdin()