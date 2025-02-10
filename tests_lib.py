import subprocess

class ConsoleColors:
    RED = '\033[31m'
    GREEN = '\033[32m'
    RESET = '\033[0m'

def run_exe(exe_path : str, input : str):
    process = subprocess.Popen(
        exe_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    return process.communicate(input) # (out, err)

def test(exe_path : str, input : str, target : str, indent : str):
    out, err = run_exe(exe_path, input)
    print(indent + "input: " + input)
    print(indent + "target output:" + target)
    if err:
        print(indent + f"({ConsoleColors.RED}X{ConsoleColors.RESET})Error: " + err)
        return False
    if out[-1] == "\n" or out[-1] == "\r":
        out = out[:-1]
    if out == target:
        print(indent + f"({ConsoleColors.GREEN}V{ConsoleColors.RESET})Passed: " + out)
        return True
    else:
        print(indent + f"({ConsoleColors.RED}X{ConsoleColors.RESET})Failed: " + out)
        return False
    
def apply_tests_range(exe_path : str, tests_count : int, tests_gen):
    passed_count = 0
    for i in range(1, tests_count + 1):
        print(f"Test {i}:")
        input, target = tests_gen()
        passed_count += test(exe_path, input, target, " " * 4)
    print(f"Passed: {passed_count}")
    print(f"Failed: {tests_count - passed_count}")
