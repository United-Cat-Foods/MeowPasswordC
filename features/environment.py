import os
import subprocess

PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MEOWPASS_BINARY = os.path.join(PROJECT_DIR, "meowpass")


def before_all(context):
    """Build the meowpass binary before running tests."""
    result = subprocess.run(
        ["make", "-C", PROJECT_DIR],
        capture_output=True,
        text=True,
    )
    assert result.returncode == 0, f"Build failed:\n{result.stderr}"
    context.binary = MEOWPASS_BINARY
