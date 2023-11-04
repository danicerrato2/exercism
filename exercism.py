import argparse
import os
import subprocess
import sys

TRACKS = ['c', 'csharp', 'javascript']

def execute_command(command : str) -> (str, str):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    error = result.stderr.decode('utf-8')
    
    return (output, error)

def download_exercise(args : argparse.Namespace):
    command = f"exercism.exe download --track={args.track[0]} --exercise={args.exercise[0]}"
    if args.force:
        command += " --force"
    
    _, error = execute_command(command)
    
    print(error[:-1] if error.startswith("Error") else "Exercise downloaded successfully")
        
def test_c(exercise : str = None):    
    if exercise != None:        
        output, error = execute_command(f"cd c/{exercise}; make | grep \"FAIL\"")

        if output.find("FAIL") != -1:
            print("\n" + output)
        elif error != '':
            print("\n" + error)
        else:
            print(f"Exercise '{exercise}' passed")
    
    else:
        exercises = [f.path for f in os.scandir('c/') if f.is_dir()]
        for exercise_name in exercises:
            test_c(exercise_name.replace('c/', ''))

def test_csharp(exercise : str = None):
    if exercise != None:
        output, error = execute_command(
            f"cd csharp/{exercise}; dotnet test -v q | grep \"FAIL\|warning\|error\"")

        if error != '':
            print("\n" + error)
        elif output.find("error") != -1 or output.find("warning") != -1:
            print("\n" + output)
        else:
            print(f"Exercise '{exercise}' passed")
    
    else:
        exercises = [f.path for f in os.scandir('csharp/') if f.is_dir()]
        for exercise_name in exercises:
            test_csharp(exercise_name.replace('csharp/', ''))

def test_javascript(exercise : str = None):
    if exercise != None:
        _, error = execute_command(f"cd javascript/{exercise}; npm test")

        if error.find("Error:") != -1:
            print(f"Exercise '{exercise}' failed:")
            errors = [line for line in error.splitlines() if line.find("Error:") != -1]
            for line in errors:
                print(line)
        elif error.find("●") != -1:
            print(f"Exercise '{exercise}' failed:")
            fails = [line for line in error.splitlines() if line.find("●") != -1]
            for line in fails:
                print(line)
        else:
            print(f"Exercise '{exercise}' passed")
    
    else:
        exercises = [f.path for f in os.scandir('javascript/') if f.is_dir()]
        for exercise_name in exercises:
            test_javascript(exercise_name.replace('javascript/', ''))
        
def test(args : argparse.Namespace):
    if args.track is None:
        for track in TRACKS:
            print(f"- Track '{track}':")
            test_track = getattr(sys.modules[__name__], f"test_{track}")
            test_track()
            print()
    elif args.track[0] in TRACKS:
        print(f"- Track '{args.track[0]}':")
        test_track = getattr(sys.modules[__name__], f"test_{args.track[0]}")
        test_track(args.exercise[0] if args.exercise != None else None)
        print()
    else:
        print(f"Error: Track '{args.track[0]}' not started yet or not existing\n" + 
              f"These are the active tracks: {TRACKS}\n")
        
def add_exercism_arguments(parser : argparse.ArgumentParser):
    is_download = parser.description == "Download"
    
    parser.add_argument("-t", "--track",
                       required=is_download,
                       nargs=1,
                       type=str,
                       help="Include the name of the track")
    parser.add_argument("-e", "--exercise",
                        required=is_download,
                        nargs=1,
                        type=str,
                        help="Include the name of the exercise")
    if is_download:
        parser.add_argument("-f", "--force",
                        required=False,
                        action='store_true',
                        help="Include it if you want to force the download")

def init_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()
    
    download = subparsers.add_parser("download", description="Download")
    add_exercism_arguments(download)
    download.set_defaults(func=download_exercise)
    
    tests = subparsers.add_parser("tests", description="Tests")
    add_exercism_arguments(tests)
    tests.set_defaults(func=test)
    
    return parser

if __name__ == '__main__':
    parser = init_parser()
    args = parser.parse_args()
    args.func(args)