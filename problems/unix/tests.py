import subprocess

def run_exe(exe_path : str, input : str):
    process = subprocess.Popen(
        exe_path, stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    ) 
    return process.communicate(input=input) # (out, err)

def test(exe_path : str, input : str, target : str, indent : str):
    out, err = run_exe(exe_path, input)
    if out[-1] == "\n" or out[-1] == "\r":
        out = out[:-1]
    print(indent + "input: " + input)
    print(indent + "target output:" + target)
    if err:
        print(indent + "(X)Error: " + err)
        return False
    if out == target:
        print(indent + "(V)Passed: " + out)
        return True
    else:
        print(indent + "(X)Failed: " + out)
        return False

print("Test 1:")
test("unix.exe", "/home////////////////////Downloads/////", "/home/Downloads", " " * 4)
