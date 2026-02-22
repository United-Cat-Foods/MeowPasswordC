import re
import subprocess

from behave import when, then


@when("I run meowpass without arguments")
def step_run_meowpass_no_args(context):
    result = subprocess.run(
        [context.binary],
        capture_output=True,
        text=True,
        timeout=30,
    )
    context.result = result


@when('I run meowpass with "{args}"')
def step_run_meowpass_with_args(context, args):
    cmd = [context.binary] + args.split()
    result = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        timeout=30,
    )
    context.result = result


@then("the exit code should be {code:d}")
def step_check_exit_code(context, code):
    assert context.result.returncode == code, (
        f"Expected exit code {code}, got {context.result.returncode}\n"
        f"stdout: {context.result.stdout}\n"
        f"stderr: {context.result.stderr}"
    )


@then('the output should contain "{text}"')
def step_output_contains(context, text):
    output = context.result.stdout + context.result.stderr
    assert text in output, (
        f'Expected output to contain "{text}"\nActual output:\n{output}'
    )


@then('the output should not contain "{text}"')
def step_output_not_contains(context, text):
    output = context.result.stdout + context.result.stderr
    assert text not in output, (
        f'Expected output NOT to contain "{text}"\nActual output:\n{output}'
    )


@then("the output should show {count:d} candidates")
def step_check_candidate_count(context, count):
    output = context.result.stdout
    matches = re.findall(r"Candidate \d+:", output)
    assert len(matches) == count, (
        f"Expected {count} candidates, found {len(matches)}\n"
        f"Output:\n{output}"
    )


@then("each candidate password should contain letters")
def step_candidates_have_letters(context):
    output = context.result.stdout
    passwords = re.findall(r"Candidate \d+: (.+)", output)
    for i, pw in enumerate(passwords, 1):
        assert re.search(r"[a-zA-Z]", pw), (
            f"Candidate {i} password '{pw}' contains no letters"
        )


@then("each candidate password should contain digits")
def step_candidates_have_digits(context):
    output = context.result.stdout
    passwords = re.findall(r"Candidate \d+: (.+)", output)
    for i, pw in enumerate(passwords, 1):
        assert re.search(r"\d", pw), (
            f"Candidate {i} password '{pw}' contains no digits"
        )


@then("each candidate password should contain symbols")
def step_candidates_have_symbols(context):
    output = context.result.stdout
    passwords = re.findall(r"Candidate \d+: (.+)", output)
    for i, pw in enumerate(passwords, 1):
        assert re.search(r"[^a-zA-Z0-9]", pw), (
            f"Candidate {i} password '{pw}' contains no symbols"
        )


@then("the selected password should be at most {length:d} characters long")
def step_check_password_max_length(context, length):
    output = context.result.stdout
    match = re.search(r"^Password: (.+)$", output, re.MULTILINE)
    assert match, f"Could not find selected password in output:\n{output}"
    password = match.group(1).strip()
    assert len(password) <= length, (
        f"Password '{password}' is {len(password)} chars, "
        f"expected at most {length}"
    )


@then('each candidate should have a "{label}" line')
def step_each_candidate_has_label(context, label):
    output = context.result.stdout
    candidates = re.findall(r"Candidate \d+:", output)
    label_lines = re.findall(re.escape(label), output)
    assert len(label_lines) >= len(candidates), (
        f"Expected at least {len(candidates)} '{label}' lines, "
        f"found {len(label_lines)}\nOutput:\n{output}"
    )
