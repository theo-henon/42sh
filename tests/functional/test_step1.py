import os
import pytest

from shell_script import ShellScript
from utils import assert_cmd

scripts_dir = './tests/functional/inputs/step1'
scripts = [f for f in os.listdir(scripts_dir) if os.path.isfile(os.path.join(scripts_dir, f))]

@pytest.mark.parametrize('script', scripts)
def test_script(script):
    cmd = ShellScript(os.path.join(scripts_dir, script))
    errors = []

    for input_type in ("string", "file", "stdin"):
        try:
            assert_cmd(cmd, input_type)
        except AssertionError as e:
            errors.append(f"Failed for {input_type} input: {str(e)}")

    if errors:
        raise AssertionError("\n" + "\n".join(errors))